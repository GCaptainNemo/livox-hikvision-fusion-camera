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
    hikvisionReceiver * hikvisionReceiveOBJ;
    livoxreceiver * livoxReceiveOBJ;

public:

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
