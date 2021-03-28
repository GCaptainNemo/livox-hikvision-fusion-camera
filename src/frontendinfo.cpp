#include "frontendinfo.h"

// 用float避免精度溢出
//double EXPAR[3][4] = {
//{1.5993911940460570e-02, -7.1372456774609350e-03, 9.9984661548908593e-01, 6.7234933376312256e-02},
//{-9.9985608975934914e-01, 5.5427869106450256e-03, 1.6033629795127791e-02, -4.6745467931032181e-02},
//{-5.6563726879350074e-03, -9.9995916778506633e-01, -7.0475677089644195e-03, 7.4506714940071106e-02}
//};
cv::Mat frontEndInfo::rotateVector(3, 3, CV_64F);

cv::Mat frontEndInfo::translatevector(3, 1, CV_64F);
cv::Mat frontEndInfo::extrinsticMat(3, 4, CV_64F);

cv::Mat frontEndInfo::intrinsticMat(3, 3, CV_64F);
cv::Mat frontEndInfo::distortionMatrix(5, 1, CV_64F);
cv::Mat frontEndInfo::transfromMat(3, 4, CV_64F);

void set_calib(){
double rotate[3][3] = {
    {1.5993911940460570e-02, -7.1372456774609350e-03, 9.9984661548908593e-01},
    {-9.9985608975934914e-01, 5.5427869106450256e-03, 1.6033629795127791e-02},
    {-5.6563726879350074e-03, -9.9995916778506633e-01, -7.0475677089644195e-03}
};
double translate[3] = {6.7234933376312256e-02, -4.6745467931032181e-02, 7.4506714940071106e-02};
double DIST[5] =
{
    4.9811000000000001e-02, -2.7529999999999998e-03,
    -2.2499999999999998e-03, 3.9249999999999997e-03,
    0.
};

double INPAR[3][3] = {
    {1.6634617699999999e+03, 0., 9.7235897999999997e+02},
    {0., 1.6652231500000000e+03, 5.1716867000000002e+02},
    {0., 0., 1.}
};


cv::Mat rotate_(3, 3, CV_64F, rotate);
frontEndInfo::rotateVector = rotate_.t();
cv::Mat translate_(3, 1, CV_64F, translate);

frontEndInfo::translatevector = -translate_;
cv::hconcat(frontEndInfo::rotateVector,
            frontEndInfo::rotateVector * frontEndInfo::translatevector,
            frontEndInfo::transfromMat);

cv::Mat intrinstic_(3, 3, CV_64F, INPAR);
frontEndInfo::intrinsticMat = intrinstic_.clone();

cv::Mat distortion_(5, 1, CV_64F, DIST);
frontEndInfo::distortionMatrix = distortion_.clone();
}
//        frontEndInfo::intrinsticMat * frontEndInfo::extrinsticMat);



frontEndInfo::frontEndInfo()
{
    
}

void frontEndInfo::setExtrinsticPar(double * expr){
    frontEndInfo::extrinsticMat = cv::Mat(3, 4, CV_64F, expr);
};

void frontEndInfo::setIntrinsticPar(double * inpr){
    frontEndInfo::intrinsticMat = cv::Mat(3, 3, CV_64F, inpr);
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

