#include "receiverhikvision.h"

long nPort;
QLabel * hikvisionReceiver::displayLabel = nullptr;
QReadWriteLock hikvisionReceiver::lock;
QImage _img_;
cv::Mat _img_mat_;
std::vector<std::vector<float>> color_vector;
int hikvisionReceiver::count = 0;

hikvisionReceiver::hikvisionReceiver()
{
    // hikvision camera sdk initialize
    bool isok = NET_DVR_Init();
    if(isok == false)
    {
        qDebug() << "NET_DVR_Init error;error number is " <<NET_DVR_GetLastError();
        return;
    }
    //设置连接时间与重连时间
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);

    NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;


    char ip_address[] = "192.168.1.64";
    char user[] = "admin";
    char password[] = "a12345678";

    userID = NET_DVR_Login_V30(ip_address, 8000, user, password, &DeviceInfoTmp);
    if(userID < 0)
    {
        qDebug() << "NET_DVR_Login_V30 error;" << "error number is " << NET_DVR_GetLastError();
        NET_DVR_Cleanup();
        return;
    }
    qDebug() << userID;
}


void hikvisionReceiver::correctDistortion()
{
    // 注意这里并没有用cv::projectPoints直接在图像上投影得到U,V因为，调用这个API本身也要先矫正图像,这样更快。
        // use intrinsic matrix and distortion matrix to correct the photo first
    cv::Mat view, rview, map1, map2;
    cv::Size imageSize = _img_mat_.size();
    cv::initUndistortRectifyMap(frontEndInfo::intrinsticMat, frontEndInfo::distortionMatrix, cv::Mat(),
        cv::getOptimalNewCameraMatrix(frontEndInfo::intrinsticMat, frontEndInfo::distortionMatrix, imageSize, 1, imageSize, 0),
        imageSize, CV_16SC2, map1, map2);
    cv::remap(_img_mat_, _img_mat_, map1, map2, cv::INTER_LINEAR);  // correct the distortion
    int row = _img_mat_.rows;
    int col = _img_mat_.cols;

    color_vector.resize(row * col);
    for (unsigned int i = 0; i < color_vector.size(); ++i) {
        color_vector[i].resize(3);
    }
    for (int v = 0; v < row; ++v) {
        int a = v*col;
        for (int u = 0; u < col; ++u) {
            // for .bmp photo, the 3 channels are BGR
            color_vector[a + u][0] = float(_img_mat_.at<cv::Vec3b>(v, u)[0]) / 255;
            color_vector[a + u][1] = float(_img_mat_.at<cv::Vec3b>(v, u)[1]) / 255;
            color_vector[a + u][2] = float(_img_mat_.at<cv::Vec3b>(v, u)[2]) / 255;
        }
    }
}

long hikvisionReceiver::play(HWND hWnd, NET_DVR_PREVIEWINFO struPlayInfo, QLabel * label)
{
    hikvisionReceiver::displayLabel = label;
    struPlayInfo = {0};
    struPlayInfo.hPlayWnd = hWnd;   //需要 SDK 解码时句柄设为有效值，仅取流不解码时可设为空
    struPlayInfo.lChannel = 1;      //预览通道号
    struPlayInfo.dwStreamType = 0;  //码流类型：0-主码流，1-子码流，2-三码流，3-虚拟码流，以此类推
    struPlayInfo.dwLinkMode = 0;    //0- TCP 方式，1- UDP 方式，2- 多播方式，3- RTP 方式，4-RTP/RTSP，5-RSTP/HTTP
    struPlayInfo.bBlocked = 1;      //0- 非阻塞取流，1- 阻塞取流

    long IRealPlayHandle = NET_DVR_RealPlay_V40(userID, &struPlayInfo, hikvisionReceiver::fRealDataCallBack, NULL);

    if(IRealPlayHandle < 0)
    {
        // NET_DVR_DVROPRATEFAILED 29 设备操作失败
        qDebug() << "NET_DVR_RealPlay_V40 error;error number " <<NET_DVR_GetLastError();
        NET_DVR_Logout(userID);
        return 0;
    }
    else
        return IRealPlayHandle;

}


// 解码回调，视频为YUV数据（YV12），音频为PCM数据
void hikvisionReceiver::DecCBFun(long nPort, char * pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2)
{

    long lFrameType = pFrameInfo->nType;

    if (lFrameType == T_YV12)
    {
        // width =  1920 Height =  1080
        cv::Mat destImg(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC3);

        cv::Mat YUVimage(pFrameInfo->nHeight + pFrameInfo->nHeight / 2,
                    pFrameInfo->nWidth, CV_8UC1, pBuf);

        cv::cvtColor(YUVimage, destImg, cv::COLOR_YUV420p2RGB);
//        hikvisionReceiver::img = QImage((const uchar * )(destImg.data), destImg.cols, destImg.rows, destImg.cols * destImg.channels(), QImage::Format_RGB888);

        QImage img = QImage((const uchar * )(destImg.data), destImg.cols, destImg.rows, destImg.cols * destImg.channels(),
                            QImage::Format_RGB888);
//        if (hikvisionReceiver::count == 0)
        if (_img_.isNull())
        {
            qDebug() << "is Null";

            _img_= img.copy();
            // 此时已是RGB格式
//            _img_mat_ = cv::Mat(_img_.height(), _img_.width(), CV_8UC3,
//                                (void*)_img_.constBits(), _img_.bytesPerLine()).clone();
            _img_mat_ = destImg.clone();
            hikvisionReceiver::correctDistortion();


        }
        hikvisionReceiver::displayLabel->setPixmap(QPixmap::fromImage(img));
        hikvisionReceiver::displayLabel->setMaximumWidth(700);
    }
}


void hikvisionReceiver::fRealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser)
{
//    LONG nPort = -1;
    switch (dwDataType)
    {
    // 第一次先进入系统头
    case NET_DVR_SYSHEAD: //系统头
        qDebug() << "in the xitongtou!";

        if (!PlayM4_GetPort(&nPort))  //获取播放库未使用的通道号，nPort应该是不同路摄像头的标识。
        {
            break;
        }
        qDebug() << "nPort = " << nPort;

        //m_iPort = lPort; //第一次回调的是系统头，将获取的播放库port号赋值给全局port，下次回调数据时即使用此port号播放
        if (dwBufSize > 0)
        {
            qDebug() << "dwBufSize > 0";

            if (!PlayM4_SetStreamOpenMode(nPort, STREAME_REALTIME))  //设置实时流播放模式
            {
                break;
            }
            qDebug() << "dwBufSize > 1";

            if (!PlayM4_OpenStream(nPort, pBuffer, dwBufSize, 10 * 1024 * 1024)) //打开流接口
            {
                break;
            }
            qDebug() << "dwBufSize > 2";

            if (!PlayM4_Play(nPort, NULL)) //播放开始
            {
                break;
            }
            qDebug() << "dwBufSize > 3";

            // 设置解码回调函数

            if (!PlayM4_SetDecCallBack(nPort, hikvisionReceiver::DecCBFun))
            {
                qDebug() << "dwBufSize > 4";
                break;
            }
        }
        break;
    case NET_DVR_STREAMDATA:   //码流数据
        // 第二次进入
        if (dwBufSize > 0 && nPort != -1)
        {
            if (!PlayM4_InputData(nPort, pBuffer, dwBufSize))
            {
                qDebug() << "error" << PlayM4_GetLastError(nPort) << endl;
                break;
            }
        }
        break;
    default: //其他数据
        qDebug() << "in other";
        if (dwBufSize > 0 && nPort != -1)
        {
            if (!PlayM4_InputData(nPort, pBuffer, dwBufSize))
            {
                break;
            }
        }
        break;
    }
}


hikvisionReceiver::~hikvisionReceiver()
{

}
