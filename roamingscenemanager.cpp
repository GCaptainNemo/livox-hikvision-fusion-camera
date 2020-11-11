#include "roamingscenemanager.h"

#include "gl/glew.h"
#include "GL/glut.h"

RoamingScenceManager::RoamingScenceManager()
{
    OldMouse = new QVector3D();
    Mouse = new QVector3D();

    NewEye = new QVector3D(100, 0, 0);
    NewUp = new QVector3D(0, 0, 1);
    NewView = new QVector3D(0, 0, 0);

    AuxY = new QVector3D(0, 1, 0);
    AuxZ = new QVector3D(100, 0, 0);
//    *AuxZ=*NewEye - *NewView;
    AuxX = new QVector3D();
    *AuxX = QVector3D::crossProduct(*AuxY,*AuxZ);
    AuxX->normalize();

    TempTranslateVec = new QVector3D(0, 0, 0);
    TempscaleFactor = 1;
}

RoamingScenceManager::~RoamingScenceManager()
{
    delete OldMouse;
    delete Mouse;
    delete NewEye;
    delete NewUp;
    delete NewView;
    delete AuxX;
    delete AuxY;
    delete AuxZ;
    delete TempTranslateVec;
}

void RoamingScenceManager::init()
{
    init_CoordinaryDisplayList();
    glShadeModel(GL_SMOOTH);
//    glClearColor(0.156, 0.156, 0.168, 0.0);
    glClearColor(0, 0, 0, 0.0);

    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-1000/2,1000/2,-1000/2,1000/2,-1000/2,1000/2);
}

void RoamingScenceManager::calculateMatrix(QMatrix4x4 &matrix)
{
    *NewView = *NewEye  * -1;
    matrix.translate(TempTranslateVec->x() / 5, TempTranslateVec->y() / 5, TempTranslateVec->z() / 5);
    matrix.scale(TempscaleFactor, TempscaleFactor, TempscaleFactor);
    matrix.lookAt(*NewEye, *NewView, *NewUp);


}


//void RoamingScenceManager::render()
//{
//    glClearColor(0.156   ,   0.156  ,    0.168 ,     0.0);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glTranslatef(TempTranslateVec->x(), TempTranslateVec->y(), TempTranslateVec->z());
//    glScalef(TempscaleFactor, TempscaleFactor, TempscaleFactor);
//    gluLookAt(NewEye->x(), NewEye->y(), NewEye->z(),
//              NewView->x(), NewView->y(), NewView->z(),
//              NewUp->x(), NewUp->y(), NewUp->z());
//    glColor3f(1,0,0);
////    glutWireCube(250);

//    glCallList(ID_COORDINATY);

//}

void RoamingScenceManager::executeRotateOperation(int x, int y)
{
    Mouse->setX(x);
    Mouse->setY(y);

    QVector3D MouseTrace = *AuxY * (OldMouse->y()-Mouse->y()) + *AuxX * (Mouse->x()-OldMouse->x());
    QVector3D RotateAsix = QVector3D::crossProduct(MouseTrace, *AuxZ);
    RotateAsix.normalize();

    float angle=MouseTrace.length();
    QMatrix4x4 rotatMatrix;
    rotatMatrix.rotate(angle,RotateAsix);

    *NewEye = rotatMatrix*(*NewEye);
    *NewUp = rotatMatrix*(*NewUp);

    NewUp->normalize();
    *AuxY = *NewUp;
    *AuxZ = *NewEye - *NewView;
    *AuxX = QVector3D::crossProduct(*AuxY, *AuxZ);
    AuxX->normalize();
    //更新鼠标
    *OldMouse = *Mouse;
}

void RoamingScenceManager::executeScaleOperation(float factor)
{
      if(TempscaleFactor <= 0)
      {
          TempscaleFactor = 0.1;
      }else
      {
          TempscaleFactor += factor;
      }
}

void RoamingScenceManager::executeTranslateOperation(int x, int y)
{
    Mouse->setX(x);
    Mouse->setY(y);
    QVector3D vec( -OldMouse->x() + Mouse->x(),- Mouse->y() + OldMouse->y(),0);
    *TempTranslateVec = *TempTranslateVec+vec;
    *OldMouse = *Mouse;
}

void RoamingScenceManager::getInitPos(int x, int y)
{
    Mouse->setX(x);
    Mouse->setY(y);
    *OldMouse = *Mouse;
}

void RoamingScenceManager::init_CoordinaryDisplayList()
{
    ID_COORDINATY=glGenLists(1);
    glNewList(ID_COORDINATY,GL_COMPILE);
    /*红色轴是X轴，绿色是Y轴，蓝色是Z轴*/
    int length=50;
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(length,0.0,0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,length,0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,length);
    glEnd();

    glLineWidth(1);
    glEnd();
    glEndList();
}
