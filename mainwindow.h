#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "livox_sdk.h"
#include <apr_general.h>
#include <apr_getopt.h>
#include <QThread>
#include <QMutex>
#include "centralwindow.h"
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QSplitter>

#include "receiverhikvision.h"


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



class setLidarThreadObject: public QObject
{
    Q_OBJECT
public slots:
    void setLidarSLOT();

};




class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    // /////////////////////////////////////////////////////////////////////////////////////
    // 用静态函数避免实例化调用 livox receiver
    // /////////////////////////////////////////////////////////////////////////////////////

    static void GetLidarData(uint8_t handle, LivoxEthPacket *data, uint32_t data_num, void *client_data);
    static void OnDeviceBroadcast(const BroadcastDeviceInfo *info);

    /* Callback function of changing of device state. */

    static void OnDeviceInfoChange(const DeviceInfo *info, DeviceEvent type);
    static void OnLidarErrorStatusCallback(livox_status status, uint8_t handle, ErrorMessage *message);
    static void OnSampleCallback(livox_status status, uint8_t handle, uint8_t response, void *data);
    static void OnStopSampleCallback(livox_status status, uint8_t handle, uint8_t response, void *data);
    static void OnDeviceInformation(livox_status status, uint8_t handle, DeviceInformationResponse *ack, void *data);
    static void LidarConnect(const DeviceInfo *info);

    static void LidarDisConnect(const DeviceInfo *info);
    static void LidarStateChange(const DeviceInfo *info);
    renderWindow * renderRgbPCWidget;
public:

    static int lidar_count;
    static uint32_t data_receive_count; //  uint32_t goes from 0 to 2^32 - 1.
    static char broadcast_code_list[kMaxLidarCount][kBroadcastCodeSize];  //  32 × 16
    setLidarThreadObject * setlidar_thread;
    static MainWindow * replaceThisPointer;
    static int bufferVertexCount;
//    static renderWindow * pointerToRenderWindow;

signals:
    void setLidarSIGNAL();


protected:
    QWidget * centralWidget;
    QHBoxLayout * centralHLayout;
    QLabel * label;
    QSplitter * hsplitter;


    hikvisionReceiver * hikvisionReceive;
};



#endif // MAINWINDOW_H
