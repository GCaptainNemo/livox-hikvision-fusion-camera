#include "hikvisionreceiver.h"

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


    // c语言中  能隐式类型转换的 在c++中可以用 const_cast<>()进行类型转换
    char * ip_address = const_cast<char * > ("192.168.1.64");
    char * user = const_cast<char * > ("admin");
    char * password = const_cast<char * > ("a12345678");

    long userID = NET_DVR_Login_V30(ip_address, 8000, user, password, &DeviceInfoTmp);
    if(userID < 0)
    {
        qDebug() << "NET_DVR_Login_V30 error;" << "error number is " << NET_DVR_GetLastError();
        return;
    }
    qDebug() << userID;



}


long hikvisionReceiver::play(long userID, HWND hWnd, NET_DVR_PREVIEWINFO struPlayInfo)
{
    struPlayInfo={0};
    struPlayInfo.hPlayWnd = hWnd;   //需要 SDK 解码时句柄设为有效值，仅取流不解码时可设为空
    struPlayInfo.lChannel = 1;      //预览通道号
    struPlayInfo.dwStreamType = 0;  //码流类型：0-主码流，1-子码流，2-三码流，3-虚拟码流，以此类推
    struPlayInfo.dwLinkMode = 1;    //0- TCP 方式，1- UDP 方式，2- 多播方式，3- RTP 方式，4-RTP/RTSP，5-RSTP/HTTP
    struPlayInfo.bBlocked = 1;      //0- 非阻塞取流，1- 阻塞取流

    long IRealPlayHandle = NET_DVR_RealPlay_V40(userID,&struPlayInfo,NULL,NULL);

    if(IRealPlayHandle <0)
    {
        qDebug() << "NET_DVR_RealPlay_V40 error;error number " <<NET_DVR_GetLastError();
        NET_DVR_Logout(userID);
        return 0;
    }
    else
        return IRealPlayHandle;
}


hikvisionReceiver::~hikvisionReceiver(){

}
