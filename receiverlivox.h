#ifndef LIVOXRECEIVER_H
#define LIVOXRECEIVER_H

#include "livox_sdk.h"
#include <apr_general.h>
#include <apr_getopt.h>



// prepare to fengzhuang livox receive
class livoxreceiver
{
public:
    livoxreceiver();
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

};

#endif // LIVOXRECEIVER_H
