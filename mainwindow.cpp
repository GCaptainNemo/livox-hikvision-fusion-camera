#include "mainwindow.h"
//#include "frontendinfo.h"




char MainWindow::broadcast_code_list[kMaxLidarCount][kBroadcastCodeSize] = {
    "1HDDH1200105361"
};




void setLidarThreadObject::setLidarSLOT()
{
    qDebug() << "Current Thread ID2 in setlidarSLOT: " << QThread::currentThreadId();

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

    SetBroadcastCallback(livoxreceiver::OnDeviceBroadcast);
    SetDeviceStateUpdateCallback(livoxreceiver::OnDeviceInfoChange);
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

    // test
    frontEndInfo a;


    this->setAttribute(Qt::WA_DeleteOnClose);
    centralWidget = new QWidget(this);
    centralHLayout = new QHBoxLayout();
    label = new QLabel(centralWidget);
    hsplitter = new QSplitter(Qt::Horizontal, this);
    renderRgbPCWidget = new renderWindow(centralWidget);
    hsplitter->addWidget(this->renderRgbPCWidget);
    hsplitter->addWidget(this->label);
    centralHLayout->addWidget(hsplitter);
    centralWidget->setLayout(centralHLayout);
    this->setCentralWidget(centralWidget);

    // ////////////////////////////////////////////////////////////////////////////
    // set layout /////////////////////////////////////////////////////////////////
    // ////////////////////////////////////////////////////////////////////////////


    hikvisionReceive = new hikvisionReceiver();


    NET_DVR_PREVIEWINFO struPlayInfo;
//    HWND hwnd = (HWND)this->label->winId();
//    long previewID = hikvisionReceive->play(hwnd,struPlayInfo);
    long previewID = hikvisionReceive->play(NULL, struPlayInfo, label);

    // ///////////////////////////////////////////////////////////////
    // livox point cloud receive
    // ///////////////////////////////////////////////////////////////

    livoxReceive = new livoxreceiver();
    connect(livoxReceive, SIGNAL(updateRenderWindowSIGNAL()), renderRgbPCWidget, SLOT(update()));
    qDebug() << "main Current Thread ID: " << QThread::currentThreadId();
    setLidarThreadObject * setLidarThreadObj = new setLidarThreadObject();
    QThread * thread = new QThread();
    setLidarThreadObj->moveToThread(thread);
    connect(this, SIGNAL(setLidarSIGNAL()), setLidarThreadObj, SLOT(setLidarSLOT()));
    connect(thread, SIGNAL(finished()), setLidarThreadObj, SLOT(deleteLater()) );
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()) );

    thread->start();
    emit setLidarSIGNAL();
}



MainWindow::~MainWindow()
{

}

