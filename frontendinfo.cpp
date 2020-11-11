#include "frontendinfo.h"

// 用float避免精度溢出
float EXPAR[3][4] = {
{1.5993911940460570e-02, -7.1372456774609350e-03, 9.9984661548908593e-01, 6.7234933376312256e-02},
{-9.9985608975934914e-01, 5.5427869106450256e-03, 1.6033629795127791e-02, -4.6745467931032181e-02},
{-5.6563726879350074e-03, -9.9995916778506633e-01, -7.0475677089644195e-03, 7.4506714940071106e-02}
};



float INPAR[3][3] = {
    {1.6634617699999999e+03, 0., 9.7235897999999997e+02},
    {0., 1.6652231500000000e+03, 5.1716867000000002e+02},
    {0., 0., 1.}
};

cv::Mat frontEndInfo::rotateVector(3, 3, CV_32FC1);
cv::Mat frontEndInfo::translatevector(3, 3, CV_32FC1);

cv::Mat frontEndInfo::livoxExtrinsticPar(3, 4, CV_32FC1, EXPAR);


cv::Mat frontEndInfo::hikvisionIntrinsticPar(3, 3, CV_32FC1, INPAR);
cv::Mat frontEndInfo::transfromPar(
        frontEndInfo::hikvisionIntrinsticPar * frontEndInfo::livoxExtrinsticPar);



frontEndInfo::frontEndInfo()
{
//    float a[4] = {1, 0, 0, 1};
//    cv::Mat mat(4, 1, CV_32FC1, a);
//    cv::Mat newPos = frontEndInfo::transfromPar * mat;

//    qDebug() << "newPos width = " << newPos.size().width;
//    qDebug() << "newPos = " << newPos.at<float>(1);


}

void frontEndInfo::setExtrinsticPar(float expr[12]){
    frontEndInfo::livoxExtrinsticPar = cv::Mat(3, 4, CV_32FC1, expr);
};

void frontEndInfo::setIntrinsticPar(float inpr[9]){
    frontEndInfo::hikvisionIntrinsticPar = cv::Mat(3, 3, CV_32FC1, inpr);
};

void frontEndInfo::calculateTransfromPar()
{
    frontEndInfo::transfromPar = frontEndInfo::hikvisionIntrinsticPar * frontEndInfo::livoxExtrinsticPar;
}

void frontEndInfo::calculateRotateTranslateVector()
{
    cv::Mat rotateMatrix = frontEndInfo::livoxExtrinsticPar(cv::Rect(0, 0, 3, 3));
//    cv::Mat rotateVector(3, 1, CV_32FC1);
    cv::Rodrigues(rotateMatrix, frontEndInfo::rotateVector);
//    return rotateVector;
    frontEndInfo::translatevector = frontEndInfo::livoxExtrinsticPar(cv::Rect(0, 2, 1, 3));
}

