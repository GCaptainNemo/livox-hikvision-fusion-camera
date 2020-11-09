#ifndef ROAMINGSCENCEMANAGER_H
#define ROAMINGSCENCEMANAGER_H

#include <QVector3D>
#include <QMatrix4x4>
//class Vector3D;
//class Position3D;
class RoamingScenceManager
{
public:
    RoamingScenceManager();
    ~RoamingScenceManager();

    void init();
    void render();
    void calculateMatrix(QMatrix4x4 &matrix);

    void executeRotateOperation(int x, int y);
    void executeScaleOperation(float factor);
    void executeTranslateOperation(int x,int y);
    void getInitPos(int x, int y);

    //辅助坐标系三根轴
    QVector3D * AuxX;
    QVector3D * AuxY;
    QVector3D * AuxZ;

    //旋转后观察点方向与视线向上方向
    QVector3D * NewEye;
    QVector3D * NewUp;
    QVector3D * NewView;


    QVector3D * OldMouse;
    QVector3D * Mouse;

    QVector3D * TempTranslateVec;
    unsigned int VBO;
    unsigned int VAO;

    float TempscaleFactor;

    int ID_COORDINATY;
    void init_CoordinaryDisplayList();
};

#endif // ROAMINGSCENCEMANAGER_H
