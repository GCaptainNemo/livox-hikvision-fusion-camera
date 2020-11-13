#include "receiverlivox.h"


typedef enum {
  kDeviceStateDisconnect = 0,
  kDeviceStateConnect = 1,
  kDeviceStateSampling = 2,
} DeviceState;

typedef struct {
  uint8_t handle;
  DeviceState device_state;
  DeviceInfo info;
} DeviceItem;

int livoxreceiver::lidar_count = 1;
uint32_t livoxreceiver::data_receive_count = 0;
int livoxreceiver::bufferVertexCount = 0;
extern QImage _img_;
extern cv::Mat _img_mat_;
extern std::vector<std::vector<GLfloat>> color_vector;


char livoxreceiver::broadcast_code_list[kMaxLidarCount][kBroadcastCodeSize] = {
    "1HDDH1200105361"
};

livoxreceiver * livoxreceiver::replaceThisLivoxReceiver;

DeviceItem devices[kMaxLidarCount] = {};


livoxreceiver::livoxreceiver()
{
    livoxreceiver::replaceThisLivoxReceiver = this;
}
void livoxreceiver::OnDeviceBroadcast(const BroadcastDeviceInfo *info)
{
    if (!info || info->dev_type == kDeviceTypeHub) {
        // 如果连接的设备是livox集线器（Hub）则直接返回
      return;
    }

    printf("Receive Broadcast Code %s\n", info->broadcast_code);


    //将设备的广播码与待连接的广播码broadcast_code_list[i]做比较
    if (lidar_count > 0) {
        bool found = false;
        int i = 0;
        for (i = 0; i < lidar_count; ++i) {

            //将设备的广播码与待连接的广播码broadcast_code_list[i]做比较
          if (strncmp(info->broadcast_code, broadcast_code_list[i], kBroadcastCodeSize) == 0) {
            found = true;
            break;
          }
    }
    if (!found) {
      return;
    }
    }

    bool result = false;
    uint8_t handle = 0;
    // addlidartoConnect 返回livox_statu
    result = AddLidarToConnect(info->broadcast_code, &handle);
    if (result == kStatusSuccess) {
        /** Set the point cloud data for a specific Livox LiDAR. */
        SetDataCallback(handle, GetLidarData, NULL);
        // setDataCallback, handle是设备的门把，GetLidarData是一个函数指针代表返回的操作，client_data表示用户关于命令的信息。
        devices[handle].handle = handle;
        devices[handle].device_state = kDeviceStateDisconnect;
    }
};

void livoxreceiver::OnDeviceInfoChange(const DeviceInfo *info, DeviceEvent type)
{
    if (info == NULL) {
        return;
    }

    uint8_t handle = info->handle;
    if (handle >= kMaxLidarCount)
    {
        return;
    }
    if (type == kEventConnect) {
        LidarConnect(info);
        qDebug() << "[WARNING] Lidar sn: [%s] Connect!!!\n" <<  info->broadcast_code;
    }
    else if (type == kEventDisconnect) {
        LidarDisConnect(info);
        printf("[WARNING] Lidar sn: [%s] Disconnect!!!\n", info->broadcast_code);
    }
    else if (type == kEventStateChange) {
        LidarStateChange(info);
        printf("[WARNING] Lidar sn: [%s] StateChange!!!\n", info->broadcast_code);
    }

    if (devices[handle].device_state == kDeviceStateConnect) {
        printf("Device Working State %d\n", devices[handle].info.state);
    if (devices[handle].info.state == kLidarStateInit) {
        printf("Device State Change Progress %u\n", devices[handle].info.status.progress);
    }
    else {
      printf("Device State Error Code 0X%08x\n", devices[handle].info.status.status_code.error_code);
    }
    printf("Device feature %d\n", devices[handle].info.feature);
    SetErrorMessageCallback(handle, livoxreceiver::OnLidarErrorStatusCallback);
    if (devices[handle].info.state == kLidarStateNormal) {
        LidarStartSampling(handle, livoxreceiver::OnSampleCallback, NULL); // 点云开始采样
        devices[handle].device_state = kDeviceStateSampling;
    }
    }
}


void livoxreceiver::GetLidarData(uint8_t handle, LivoxEthPacket *data, uint32_t data_num, void *client_data) {
    if (data) {
//    data_receive_count++ ;
//    if (data_receive_count % 100 == 0) {
//      /* Parsing the timestamp and the point cloud data. */
//        // 解析时间戳和点云数据，通过C/C++强制转换（type）a进行
//        // 类型转换函数写法 operator type() {// Todo; return Data;};

        uint64_t cur_timestamp = *((uint64_t *)(data->timestamp));
        // LivoxRawData都是结构体，存储一个点的坐标和反射率信息。
        if(data ->data_type == kCartesian)
        {
            LivoxRawPoint *p_point_data = (LivoxRawPoint *)data->data;
            qDebug() << "data = [%d, %d, %d]" << p_point_data->x << p_point_data->y<< p_point_data->z;
        }
        else if ( data ->data_type == kSpherical)
        {
            LivoxSpherPoint *p_point_data = (LivoxSpherPoint *)data->data;
        }
        else if ( data ->data_type == kExtendCartesian)
        {
            if (livoxreceiver::bufferVertexCount < 1500)
            {

                LivoxExtendRawPoint *p_point_data = (LivoxExtendRawPoint *)data->data;
                renderWindow::vertexPositions[livoxreceiver::bufferVertexCount][0] = GLfloat(p_point_data->x) / 1000;
                renderWindow::vertexPositions[livoxreceiver::bufferVertexCount][1] = GLfloat(p_point_data->y )/ 1000;
                renderWindow::vertexPositions[livoxreceiver::bufferVertexCount][2] = GLfloat(p_point_data->z )/ 1000;
                // reflectivity and color two mode
                if(renderWindow::isColor)
                {
                    float rgb[3] = {0.0, 0.0, 0.0};
                    livoxreceiver::getColor(frontEndInfo::intrinsticMat, frontEndInfo::extrinsticMat,
                                            p_point_data->x, p_point_data->y, p_point_data->z, _img_mat_.rows, _img_mat_.cols,
                                            rgb);
                    if (rgb[0] < 0.003922 && rgb[1] < 0.003922 && rgb[2] < 0.003922) {
                        livoxreceiver::bufferVertexCount -= 1;
                    }
                    else{
                        renderWindow::vertexColor[livoxreceiver::bufferVertexCount][0] = rgb[0];
                        renderWindow::vertexColor[livoxreceiver::bufferVertexCount][1] = rgb[1];
                        renderWindow::vertexColor[livoxreceiver::bufferVertexCount][2] = rgb[2];
                    }
                }
                else{
//                    renderWindow::vertexReflectivity[livoxreicever::bufferVertexCount][0] =
//                            GLfloat(p_point_data->reflectivity) / 255;
//                    renderWindow::vertexReflectivity[livoxreceiver::bufferVertexCount][1] =
//                            GLfloat(p_point_data->reflectivity) / 255;
//                    renderWindow::vertexReflectivity[livoxreceiver::bufferVertexCount][2] =
//                            GLfloat(p_point_data->reflectivity) / 255;
                    // pseudo color.
                    renderWindow::vertexReflectivity[livoxreceiver::bufferVertexCount][0] =
                        abs(255 - GLfloat(p_point_data->reflectivity)) / 255;
                    renderWindow::vertexReflectivity[livoxreceiver::bufferVertexCount][1] =
                        abs(127 - GLfloat(p_point_data->reflectivity)) / 255;
                    renderWindow::vertexReflectivity[livoxreceiver::bufferVertexCount][2] =
                        GLfloat(p_point_data->reflectivity) / 255;

                }
                livoxreceiver::bufferVertexCount += 1;

            }
            else
            {
                qDebug() << "Current Thread ID in getLidarcallback:" << QThread::currentThreadId();
//                MainWindow::replaceThisPointer->renderRgbPCWidget->update();
                livoxreceiver::bufferVertexCount = 0;
                emit livoxreceiver::replaceThisLivoxReceiver->updateRenderWindowSIGNAL(); //
                qDebug() << "buffer clean ";
            }

        }
        else if ( data ->data_type == kExtendSpherical)
        {
            LivoxExtendSpherPoint *p_point_data = (LivoxExtendSpherPoint *)data->data;
        }
        else if ( data ->data_type == kDualExtendCartesian)
        {
            LivoxDualExtendRawPoint *p_point_data = (LivoxDualExtendRawPoint *)data->data;
        }
        else if ( data ->data_type == kDualExtendSpherical)
        {
            LivoxDualExtendSpherPoint *p_point_data = (LivoxDualExtendSpherPoint *)data->data;   // 点云数据强制转换
        }
        else if ( data ->data_type == kImu)
        {
            LivoxImuPoint *p_point_data = (LivoxImuPoint *)data->data;
        }
}
}

// use extrinsic and intrinsic to get the corresponding U and V
void livoxreceiver::getUV(const cv::Mat &matrix_in, const cv::Mat &matrix_out,
                          const float &x, const float &y, const float &z,
                          float* UV)
{
    double pos[4][1] = {x, y, z, 1};
    cv::Mat coordinate(4, 1, CV_64F, pos);

    // calculate the result of u and v
//    cv::Mat result = matrix_in * matrix_out * coordinate;
    cv::Mat result = frontEndInfo::transfromMat * coordinate;


    float u = result.at<double>(0, 0);
    float v = result.at<double>(1, 0);
    float depth = result.at<double>(2, 0);
    UV[0] = u / depth;
    UV[1] = v / depth;

}

// get RGB value of the lidar point
void livoxreceiver::getColor(const cv::Mat &matrix_in, const cv::Mat &matrix_out,
                             const float &x, const float &y, const float &z,
                             int row, int col,
                             float* RGB) {
    float UV[2] = {0, 0};
    livoxreceiver::getUV(matrix_in, matrix_out, x, y, z, UV);  // get U and V from the x,y,z

    int u = int(UV[0]);
    int v = int(UV[1]);

    int32_t index = v*col + u;
    if (index < row*col && index >= 0) {
        RGB[0] = color_vector[index][0];
        RGB[1] = color_vector[index][1];
        RGB[2] = color_vector[index][2];
    }
}




void livoxreceiver::getColor(const cv::Mat &pos, QColor& color)
{
//    qDebug() << "in getColr";

    std::vector<cv::Point2f> projectedPoints;

    cv::projectPoints(pos,
                      frontEndInfo::rotateVector,
                      frontEndInfo::translatevector,
                      frontEndInfo::intrinsticMat,
                      frontEndInfo::distortionMatrix, projectedPoints);

    int x = (int) projectedPoints[0].x;
    int y = (int) projectedPoints[0].y;
//    int x = 0;
//    int y = 0;

//    QColor a;
//    color =  QColor(0.0, 0.0, 0.0);
//    return;

    if (!_img_.isNull() && 0<=x && x < 1920 && 0<= y && y< 1080 )
    {
//        hikvisionReceiver::lock.lockForRead();
        color = _img_.pixelColor(x, y);

//        hikvisionReceiver::lock.unlock();
//        qDebug() << "r = " << a.red();
//        return a;
    }
    else{
        color =  QColor(0.0, 0.0, 0.0);
    }
}


// 静态函数，Lidar有错误状态时的动作函数
void livoxreceiver::OnLidarErrorStatusCallback(livox_status status, uint8_t handle, ErrorMessage *message)
{
    static uint32_t error_message_count = 0;
    if (message != NULL) {
      ++error_message_count;
      if (0 == (error_message_count % 100)) {
        printf("handle: %u\n", handle);
        printf("temp_status : %u\n", message->lidar_error_code.temp_status);
        printf("volt_status : %u\n", message->lidar_error_code.volt_status);
        printf("motor_status : %u\n", message->lidar_error_code.motor_status);
        printf("dirty_warn : %u\n", message->lidar_error_code.dirty_warn);
        printf("firmware_err : %u\n", message->lidar_error_code.firmware_err);
        printf("pps_status : %u\n", message->lidar_error_code.device_status);
        printf("fan_status : %u\n", message->lidar_error_code.fan_status);
        printf("self_heating : %u\n", message->lidar_error_code.self_heating);
        printf("ptp_status : %u\n", message->lidar_error_code.ptp_status);
        printf("time_sync_status : %u\n", message->lidar_error_code.time_sync_status);
        printf("system_status : %u\n", message->lidar_error_code.system_status);
      }
    }
  }

/* Callback function of starting sampling. 开始采样的callback函数*/




void livoxreceiver::OnSampleCallback(livox_status status, uint8_t handle, uint8_t response, void *data)
{
  printf("OnSampleCallback statue %d handle %d response %d \n", status, handle, response);
  if (status == kStatusSuccess) {
    if (response != 0)
    {
      devices[handle].device_state = kDeviceStateConnect;
    }
  }
  else if (status == kStatusTimeout)
  {
    devices[handle].device_state = kDeviceStateConnect;
  }
}

/* Callback function of stopping sampling. 停止采样的callback函数*/
void livoxreceiver::OnStopSampleCallback(livox_status status, uint8_t handle, uint8_t response, void *data)
{

}


/* Query the firmware version of Livox LiDAR. 获得激光雷达的固件版本*/
void livoxreceiver::OnDeviceInformation(livox_status status, uint8_t handle, DeviceInformationResponse *ack, void *data) {
  if (status != kStatusSuccess) {
    qDebug() << "Device Query Informations Failed %d\n" << status;
  }
  if (ack) {
    printf("firm ver: %d.%d.%d.%d\n",
           ack->firmware_version[0],
           ack->firmware_version[1],
           ack->firmware_version[2],
           ack->firmware_version[3]);
  }
}

void livoxreceiver::LidarConnect(const DeviceInfo *info)
{
    uint8_t handle = info->handle;
    QueryDeviceInformation(handle, livoxreceiver::OnDeviceInformation, NULL);
    if (devices[handle].device_state == kDeviceStateDisconnect) {
      devices[handle].device_state = kDeviceStateConnect;
      devices[handle].info = *info;
    }
}

void livoxreceiver::LidarDisConnect(const DeviceInfo *info) {
  uint8_t handle = info->handle;
  devices[handle].device_state = kDeviceStateDisconnect;
}

void livoxreceiver::LidarStateChange(const DeviceInfo *info) {
  uint8_t handle = info->handle;
  devices[handle].info = *info;
}


livoxreceiver::~livoxreceiver()
{

}
