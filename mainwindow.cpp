#include "mainwindow.h"
//#include "frontendinfo.h"
#include <QString>
#include <QDebug>



int MainWindow::lidar_count = 1;
uint32_t MainWindow::data_receive_count = 0;
int MainWindow::bufferVertexCount = 0;

MainWindow* MainWindow::replaceThisPointer = nullptr;
QMutex MainWindow::vector_qmutex;

char MainWindow::broadcast_code_list[kMaxLidarCount][kBroadcastCodeSize] = {
    "1HDDH1200105361"
};


DeviceItem devices[kMaxLidarCount] = {};


void setLidarThreadObject::setLidarSLOT()
{
    qDebug() << "Current Thread ID2: " << QThread::currentThreadId();

    if (!Init()) {
        return;
    }
    qDebug() << "Livox SDK has been initialized.\n";
    // 设置广播码到达的行为和设备状态转变的行为
    LivoxSdkVersion _sdkversion;
    GetLivoxSdkVersion(&_sdkversion);
    qDebug() << "Livox SDK version " << _sdkversion.major << _sdkversion.minor<< _sdkversion.patch;


    // /////////////////////////////////////////////////////////////////////////////////////////////////
    // 朝command handler发送设置命令，broadcastCallback & devicestateUpdateCallback
    // ///////////////////////////////////////////////////////////////////////////////////////////////////

    SetBroadcastCallback(MainWindow::OnDeviceBroadcast);
    SetDeviceStateUpdateCallback(MainWindow::OnDeviceInfoChange);
    if (!Start()) {
        Uninit();  // uninitialize the SDK.
    }
    qDebug() << "Start discovering device.\n";

    #ifdef WIN32
      Sleep(30000);
    #else
      Sleep(30);
    #endif

    /* Uninitialize Livox-SDK. */
    Uninit();

}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    this->setAttribute(Qt::WA_DeleteOnClose);

    MainWindow::replaceThisPointer = this;
    centralWidget = new QWidget(this);
    centralHLayout = new QHBoxLayout();

    label = new QLabel(centralWidget);
    hsplitter = new QSplitter(Qt::Horizontal, this);

    renderRgbPCWidget = new renderWindow(centralWidget);
    hsplitter->addWidget(this->renderRgbPCWidget);
    hsplitter->addWidget(this->label);
    centralHLayout->addWidget(hsplitter);

//    centralHLayout->addWidget(this->renderRgbPCWidget);
//    centralHLayout->addWidget(this->label);
    centralWidget->setLayout(centralHLayout);
    this->setCentralWidget(centralWidget);

    hikvisionReceive = new hikvisionReceiver();


//    HWND hwnd = (HWND)this->label->winId();
    NET_DVR_PREVIEWINFO struPlayInfo;
//    long previewID = hikvisionReceive->play(hwnd,struPlayInfo);
    long previewID = hikvisionReceive->play(NULL, struPlayInfo, label);


    qDebug() << "Current Thread ID: " << QThread::currentThreadId();
    setLidarThreadObject * setLidarThreadObj = new setLidarThreadObject();
    QThread * thread = new QThread();
    setLidarThreadObj->moveToThread(thread);
    connect(this, SIGNAL(setLidarSIGNAL()), setLidarThreadObj, SLOT(setLidarSLOT()));
    connect(thread, SIGNAL(finished()), setLidarThreadObj, SLOT(deleteLater()) );
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()) );

    thread->start();
    emit setLidarSIGNAL();
}



/* Callback function when broadcast message received.
 * You need to add listening device broadcast code and set the point cloud data callback in this function.
 * 一般computer会接受局域网下所有lidar的广播，为了只收到其中某个的信息，可以1. 添加监听设备的广播码，
 * 2. 在这个函数中设置点云数据回调
 * BroadcastDeviceInfo是一个结构体，存储着广播设备的信息。
 */
void MainWindow::OnDeviceBroadcast(const BroadcastDeviceInfo *info)
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

void MainWindow::OnDeviceInfoChange(const DeviceInfo *info, DeviceEvent type)
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
    SetErrorMessageCallback(handle, MainWindow::OnLidarErrorStatusCallback);
    if (devices[handle].info.state == kLidarStateNormal) {
        LidarStartSampling(handle, MainWindow::OnSampleCallback, NULL); // 点云开始采样
        devices[handle].device_state = kDeviceStateSampling;
    }
    }
}


void MainWindow::GetLidarData(uint8_t handle, LivoxEthPacket *data, uint32_t data_num, void *client_data) {
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
            if (MainWindow::bufferVertexCount < 10000)
            {

            MainWindow::bufferVertexCount += 1;
            LivoxExtendRawPoint *p_point_data = (LivoxExtendRawPoint *)data->data;


//            MainWindow::vector_qmutex.lock();
            renderWindow::vertices_positions << QVector3D(p_point_data->x , p_point_data->y, p_point_data->z);
//            MainWindow::vector_qmutex.unlock();

            renderWindow::vertices_reflectivity << p_point_data->reflectivity;
            }
            else
            {
//                MainWindow::vector_qmutex.lock();

                renderWindow::vertices_buffer.swap(renderWindow::vertices_positions);
                renderWindow::reflectivity_buffer.swap(renderWindow::vertices_reflectivity);

                replaceThisPointer->renderRgbPCWidget->update();

//                MainWindow::vector_qmutex.lock();
                qDebug() << "vertices_positions's length = " << renderWindow::vertices_positions.length();
//                MainWindow::vector_qmutex.unlock();
                MainWindow::bufferVertexCount = 0;
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



// 静态函数，Lidar有错误状态时的动作函数
void MainWindow::OnLidarErrorStatusCallback(livox_status status, uint8_t handle, ErrorMessage *message)
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




void MainWindow::OnSampleCallback(livox_status status, uint8_t handle, uint8_t response, void *data)
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
void MainWindow::OnStopSampleCallback(livox_status status, uint8_t handle, uint8_t response, void *data)
{

}


/* Query the firmware version of Livox LiDAR. 获得激光雷达的固件版本*/
void MainWindow::OnDeviceInformation(livox_status status, uint8_t handle, DeviceInformationResponse *ack, void *data) {
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

void MainWindow::LidarConnect(const DeviceInfo *info)
{
    uint8_t handle = info->handle;
    QueryDeviceInformation(handle, MainWindow::OnDeviceInformation, NULL);
    if (devices[handle].device_state == kDeviceStateDisconnect) {
      devices[handle].device_state = kDeviceStateConnect;
      devices[handle].info = *info;
    }
}

void MainWindow::LidarDisConnect(const DeviceInfo *info) {
  uint8_t handle = info->handle;
  devices[handle].device_state = kDeviceStateDisconnect;
}

void MainWindow::LidarStateChange(const DeviceInfo *info) {
  uint8_t handle = info->handle;
  devices[handle].info = *info;
}




MainWindow::~MainWindow()
{

}

