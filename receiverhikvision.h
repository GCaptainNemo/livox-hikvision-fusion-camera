#ifndef HIKVISIONRECEIVER_H
#define HIKVISIONRECEIVER_H
#include <Windows.h>
#include <HCNetSDK.h>
#include <QDebug>
// #include "opencv.hpp"


class hikvisionReceiver:public QObject
{
    Q_OBJECT
public:
    hikvisionReceiver();
    long play(HWND hWnd, NET_DVR_PREVIEWINFO struPlayInfo);
    virtual ~hikvisionReceiver();
    long userID;
    void CALLBACK fRealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser);

};

#endif // HIKVISIONRECEIVER_H
