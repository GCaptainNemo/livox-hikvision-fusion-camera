#ifndef CENTRALWINDOW_H
#define CENTRALWINDOW_H
#define GLEW_STATIC
#include "GL/glew.h"
//#pragma comment(lib, "glew32.lib")

#include <glm/glm.hpp>
#include <QWidget>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QTimer>


#include <QMouseEvent>
#include <QLabel>
#include <QOpenGLExtraFunctions>
#include <QMutex>
#include <QOpenGLContext>
#include <vector>
//#include "batchmanager.h"
#include "roamingscenemanager.h"

#define M_PI 3.1415



class renderWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    static GLfloat vertexPositions[1500][3];
    static GLfloat vertexReflectivity[1500][3];

    float compareToOrijinScaleFactor;
    float compareToLastScaleFactor;

    QPoint StartPoint;     //记录鼠标按下的点
    QPoint EndPoint;       //鼠标移动过程中的点
    /*gluLookAt函数中第一组坐标跟第三组坐标*/

    QMatrix4x4 matrix ;
    QMatrix4x4 lastmatrix ;

    GLfloat rotateAngle;
    glm::vec3 r_axis_world;
    QOpenGLBuffer vbo;
    QOpenGLShaderProgram * program;
    unsigned int VBOID;
    unsigned int VAOID;

private:
    RoamingScenceManager * sceneManager;
    //^^^^------ variables above ------|------ functions below ------vvvv

public:
    void scaleVariable(float delta);
    void drawCoordinate();
    void renderPoint();
    QOpenGLExtraFunctions * extrafunctions;
    glm::vec2 scaleMouse(glm::vec2 coords, glm::vec2 viewport);
    glm::vec3 projectToSphere(glm::vec2 xy);
    void setRotateParameter(glm::vec2 newMouse, glm::vec2 oldMouse);

protected:
public:
    explicit renderWindow(QWidget *parent = nullptr);
    ~renderWindow();
    void initializeGL() ;
    void resizeGL(int w,int h) ;
    void paintGL() ;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);





signals:

public slots:
    void updateWindowSLOT();


private:

 //   void onMouseClick(int button, int state, int x, int y);
//    void onKeyboardClick

};

#endif // CENTRALWINDOW_H
