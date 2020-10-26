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


protected:
    // initializeGL(),设置opengl渲染环境，定义显示列表等。该函数只在第一次调用resizeGL()或paintGL()前被自动调用一次
    // resizeGL():设置opengl的viewport视口、投影等。每次部件改变大小都会调用该函数
    // paintGL()：渲染opengl场景，每当部件更新时都会调用该函数。
public:
    void initializeGL() ;
    void resizeGL(int w,int h) ;
    void paintGL() ;
    void mouseMoveEvent(QMouseEvent *event);
    void mouseClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

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
