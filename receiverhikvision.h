﻿#ifndef HIKVISIONRECEIVER_H
#define HIKVISIONRECEIVER_H
#include <Windows.h>
#include "HCNetSDK.h"
#include <QDebug>
#include <QException>
#include <QLabel>
#include <QRgb>
#include <QPixmap>
#include <QImage>
#include "plaympeg4.h"
#include "frontendinfo.h"
#include "renderwindow.h"
#include "opencv.hpp"


class hikvisionReceiver:public QObject
{
    Q_OBJECT
public:
    hikvisionReceiver();
    long play(HWND hWnd, NET_DVR_PREVIEWINFO struPlayInfo, QLabel * displayLabel);
    virtual ~hikvisionReceiver();
    long userID;
    static void CALLBACK fRealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser);
    static void CALLBACK DecCBFun(long nPort, char * pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2);
    static QColor getColor(const cv::Mat &pos);
    static QLabel * displayLabel;
    static QImage img;
    static int count;

};

#endif // HIKVISIONRECEIVER_H
