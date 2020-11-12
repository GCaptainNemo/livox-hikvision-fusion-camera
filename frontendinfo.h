#ifndef FRONTENDINFO_H
#define FRONTENDINFO_H

#include <QString>
#include "livox_sdk.h"
#include <opencv.hpp>
#include <QDebug>
// to save camera intrinstic / extrinstic matrix parameter
class frontEndInfo
{
public:
    //
    frontEndInfo();
    static cv::Mat extrinsticMat;
    static cv::Mat intrinsticMat;
    static cv::Mat transfromMat;
    static cv::Mat rotateVector;
    static cv::Mat translatevector;
    static cv::Mat distVector;
    void setExtrinsticPar(float expr[12]);
    void setIntrinsticPar(float inpr[9]);
    void calculateTransfromPar();
    static void calculateRotateTranslateVector();

};

#endif // FRONTENDINFO_H
