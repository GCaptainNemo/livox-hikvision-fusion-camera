#ifndef LIVOXRECEIVER_H
#define LIVOXRECEIVER_H

#include "livox_sdk.h"
#include <apr_general.h>
#include <apr_getopt.h>
#include <QDebug>
#include <QThread>
#include <QColor>
#include "renderwindow.h"
#include "receiverhikvision.h"
#include "opencv.hpp"

// prepare to fengzhuang livox receive
class livoxreceiver:public QObject
{
    Q_OBJECT
public:
    livoxreceiver();
    ~livoxreceiver();

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

signals:
    void updateRenderWindowSIGNAL();


    //
public:
    static int lidar_count;
    static uint32_t data_receive_count; //  uint32_t goes from 0 to 2^32 - 1.
    static char broadcast_code_list[kMaxLidarCount][kBroadcastCodeSize];  //  32 × 16
    static int bufferVertexCount;
    static livoxreceiver * replaceThisLivoxReceiver;
    static void getColor(const cv::Mat &pos, QColor& color);


};

#endif // LIVOXRECEIVER_H
