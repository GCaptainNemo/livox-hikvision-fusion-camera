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
    static cv::Mat distortionMatrix;
    void setExtrinsticPar(double * expr);
    void setIntrinsticPar(double * inpr);
    void calculateTransfromPar();
    static void calculateRotateTranslateVector();

};

#endif // FRONTENDINFO_H
