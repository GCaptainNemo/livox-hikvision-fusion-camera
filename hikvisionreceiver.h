#ifndef HIKVISIONRECEIVER_H
#define HIKVISIONRECEIVER_H
#include <Windows.h>
#include <HCNetSDK.h>
#include <QDebug>

class hikvisionReceiver:public QObject
{
    Q_OBJECT
public:
    hikvisionReceiver();
    long play(long userID, HWND hWnd, NET_DVR_PREVIEWINFO struPlayInfo);
    virtual ~hikvisionReceiver();




};

#endif // HIKVISIONRECEIVER_H
