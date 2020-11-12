#include "frontendinfo.h"

// 用float避免精度溢出
float EXPAR[3][4] = {
{1.5993911940460570e-02, -7.1372456774609350e-03, 9.9984661548908593e-01, 6.7234933376312256e-02},
{-9.9985608975934914e-01, 5.5427869106450256e-03, 1.6033629795127791e-02, -4.6745467931032181e-02},
{-5.6563726879350074e-03, -9.9995916778506633e-01, -7.0475677089644195e-03, 7.4506714940071106e-02}
};

float DIST[5] =
{
    4.9811000000000001e-02, -2.7529999999999998e-03,
    -2.2499999999999998e-03, 3.9249999999999997e-03,
    0.
};

float INPAR[3][3] = {
    {1.6634617699999999e+03, 0., 9.7235897999999997e+02},
    {0., 1.6652231500000000e+03, 5.1716867000000002e+02},
    {0., 0., 1.}
};


cv::Mat frontEndInfo::rotateVector(3, 3, CV_32FC1);
cv::Mat frontEndInfo::translatevector(3, 1, CV_32FC1);

cv::Mat frontEndInfo::extrinsticMat(3, 4, CV_32FC1, EXPAR);

cv::Mat frontEndInfo::intrinsticMat(3, 3, CV_32FC1, INPAR);
cv::Mat frontEndInfo::distVector(5, 1, CV_32FC1, DIST);
cv::Mat frontEndInfo::transfromMat(
        frontEndInfo::intrinsticMat * frontEndInfo::extrinsticMat);



frontEndInfo::frontEndInfo()
{
//    float a[4] = {1, 0, 0, 1};
//    cv::Mat mat(4, 1, CV_32FC1, a);
//    cv::Mat newPos = frontEndInfo::transfromPar * mat;

//    qDebug() << "newPos width = " << newPos.size().width;
//    qDebug() << "newPos = " << newPos.at<float>(1);

}

void frontEndInfo::setExtrinsticPar(float expr[12]){
    frontEndInfo::extrinsticMat = cv::Mat(3, 4, CV_32FC1, expr);
};

void frontEndInfo::setIntrinsticPar(float inpr[9]){
    frontEndInfo::intrinsticMat = cv::Mat(3, 3, CV_32FC1, inpr);
};

void frontEndInfo::calculateTransfromPar()
{
    frontEndInfo::transfromMat = frontEndInfo::intrinsticMat * frontEndInfo::extrinsticMat;
}

void frontEndInfo::calculateRotateTranslateVector()
{
    cv::Mat rotateMatrix = frontEndInfo::extrinsticMat(cv::Rect(0, 0, 3, 3));
    cv::Rodrigues(rotateMatrix, frontEndInfo::rotateVector);
    // Rect
    frontEndInfo::translatevector = frontEndInfo::extrinsticMat(cv::Rect(3, 0, 1, 3));
    qDebug() << "has been calculated";
}

