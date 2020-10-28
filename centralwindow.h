#ifndef CENTRALWINDOW_H
#define CENTRALWINDOW_H

#include <QWidget>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QTimer>
#include <QGLWidget>
#include <QMouseEvent>

#define M_PI 3.1415

class centralwindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit centralwindow(QWidget *parent = nullptr);
    static QVector<QVector3D> vertices_positions;
    static QVector<QVector3D> vertices_colors;
    static QVector<uint8_t> vertices_reflectivity;
    static QVector<QVector3D> vertices_buffer;
    static QVector<uint8_t> reflectivity_buffer;


    float TempscaleFactor;
    QPoint StartPoint;     //记录鼠标按下的点
    QPoint EndPoint;       //鼠标移动过程中的点
    /*gluLookAt函数中第一组坐标跟第三组坐标*/
    GLdouble eyex;
    GLdouble eyey;
    GLdouble eyez;

    GLdouble upx;
    GLdouble upy;
    GLdouble upz;


    float CurrentAngleZ;     //当前与Z轴的夹角
    float CurrentAngleY;     //当前与Y轴的夹角

    float LastAngleZ;        //上一次与Z轴的夹角
    float LastAngleY;        //上一次与Y轴的夹角
    void scaleVariable(float delta);
    void RotateViewPoint();
    void drawCoordinate();
    void drawShape();


protected:
    // initializeGL(),设置opengl渲染环境，定义显示列表等。该函数只在第一次调用resizeGL()或paintGL()前被自动调用一次
    // resizeGL():设置opengl的viewport视口、投影等。每次部件改变大小都会调用该函数
    // paintGL()：渲染opengl场景，每当部件更新时都会调用该函数。
public:
    void initializeGL() ;
    void resizeGL(int w,int h) ;
    void paintGL() ;
    void mouseMoveEvent(QMouseEvent *event);
//    void mouseClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


signals:

public slots:
    void updateWindowSLOT();


private:
    QOpenGLShaderProgram * program;
    QOpenGLBuffer vbo;

 //   void onMouseClick(int button, int state, int x, int y);
//    void onKeyboardClick

};

#endif // CENTRALWINDOW_H
