#ifndef FRONTENDINFO_H
#define FRONTENDINFO_H

#include <QString>
#include "livox_sdk.h"

class frontEndInfo
{
public:
    frontEndInfo();

//    static QString frontEndIpPort;
//    static QString broadcastCode;
//    typedef enum {
//      kDeviceStateDisconnect = 0,
//      kDeviceStateConnect = 1,
//      kDeviceStateSampling = 2,
//    } DeviceState;

//    typedef struct {
//      uint8_t handle;
//      DeviceState device_state;
//      DeviceInfo info;
//    } DeviceItem;



//    DeviceItem devices[kMaxLidarCount];  // 结构体数组
//    uint32_t data_recveive_count[kMaxLidarCount]; //  goes from 0 to 2^32 - 1.
//    #define BROADCAST_CODE_LIST_SIZE  3
//    int lidar_count = BROADCAST_CODE_LIST_SIZE;
//    char broadcast_code_list[kMaxLidarCount][kBroadcastCodeSize] = {
//      "000000000000002",
//      "000000000000003",
//      "000000000000004"
//    };



};

#endif // FRONTENDINFO_H
