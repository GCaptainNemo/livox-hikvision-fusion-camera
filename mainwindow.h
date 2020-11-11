#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <apr_general.h>
#include <apr_getopt.h>
#include <QThread>
#include <QMutex>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QSplitter>
#include <vector>
#include <QString>
#include <QDebug>

#include "renderwindow.h"
#include "livox_sdk.h"
#include "receiverhikvision.h"
#include "receiverlivox.h"

//typedef enum {
//  kDeviceStateDisconnect = 0,
//  kDeviceStateConnect = 1,
//  kDeviceStateSampling = 2,
//} DeviceState;

//typedef struct {
//  uint8_t handle;
//  DeviceState device_state;
//  DeviceInfo info;
//} DeviceItem;



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

    renderWindow * renderRgbPCWidget;
    hikvisionReceiver * hikvisionReceive;
    livoxreceiver * livoxReceive;

public:

    static uint32_t data_receive_count; //  uint32_t goes from 0 to 2^32 - 1.
    static char broadcast_code_list[kMaxLidarCount][kBroadcastCodeSize];  //  32 × 16
    setLidarThreadObject * setlidar_thread;

signals:
    void setLidarSIGNAL();


protected:
    QWidget * centralWidget;
    QHBoxLayout * centralHLayout;
    QLabel * label;
    QSplitter * hsplitter;



};



#endif // MAINWINDOW_H
