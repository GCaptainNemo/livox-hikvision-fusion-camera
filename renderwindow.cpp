#include "renderwindow.h"
#define GLUT_DISABLE_ATEXIT_HACK


#include <gl/GLU.h>
#include <GL/glut.h>
QMutex renderWindow::qmutex;
QVector<QVector3D> renderWindow::vertices_positions = {};
QVector<uint8_t> renderWindow::vertices_reflectivity = {};
QVector<QVector3D> renderWindow::vertices_buffer = {};
QVector<uint8_t> renderWindow::reflectivity_buffer = {};

//QVector<QVector3D> centralwindow::vertices_colors = {{1, 1, 1} * 1000}
renderWindow::renderWindow(QWidget *parent) : QOpenGLWidget(parent)
{
    this->eyex = 0;
    this->eyey = 0;
    this->eyez = 1;

    this->upx = 0;
    this->upy = 1;
    this->upz = 0;

//    this->CurrentAngleX = 0;
//    this->CurrentAngleY = 0;
//    this->LastAngleX = M_PI / 2;
//    this->LastAngleY = M_PI / 2;
//    this->LastAngleZ = 0.95532;   // 与z轴正向的夹角
//    this->LastAngleY = 0.95532;

    this->xRotateAngle = 0;
    this->yRotateAngle = 0;

    this->TempscaleFactor = 1;

}

void renderWindow::updateWindowSLOT()
{
    this->update();
}




void renderWindow::initializeGL()
{
    // 为当前context初始化OpenGL函数
    // 此时QOpenglFunctions对象只可以使用这个上下文。
    initializeOpenGLFunctions();
    extrafunctions =
            new QOpenGLExtraFunctions(QOpenGLContext::currentContext());
    batchManager = new BatchManager(15, 4500, extrafunctions);


//    glutInit(0, nullptr);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);





     // 创建顶点着色器
//     QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
//     const char *vsrc =
//             "#version 450                           \n"
//             "in vec4 vPosition;                        \n"
//             "in vec4 vColor;                           \n"
//             "out vec4 color1;                           \n"
//             "uniform mat4 matrix;                      \n"
//             "void main() {                             \n"
//             "   color1 = vColor;                        \n"
//             "   gl_Position = matrix * vPosition;      \n"
//             "}                                         \n";
//     vshader->compileSourceCode(vsrc);
//     // 创建片段着色器
//     QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
//     const char *fsrc =
//             "#version 450                           \n"
//             "in vec4 color1;                             \n"
//             "out vec4 fColor;                           \n"
//             "void main() {                              \n"
//             "   fColor = color1;                         \n"
//             "}                                          \n";
//     fshader->compileSourceCode(fsrc);

//     // 创建着色器程序
//     program = new QOpenGLShaderProgram;
//     program->addShader(vshader);
//     program->addShader(fshader);

//     program->bind();
//     program->link();

};

void renderWindow::resizeGL(int w,int h)
{

};


void renderWindow::paintGL()
{
    // qDebug() << "REPAINT AGAIN!!!!!";
    // 获得当下的上下文
    QOpenGLExtraFunctions  * f = QOpenGLContext::currentContext()->extraFunctions();

//    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // gluLookAt creates a viewing matrix derived from an eye point,
    // a reference point indicating the center of the scene, and an UP vector.
    // eye:相机光心所在的位置  center: 相机朝向的位置， up：相机的顶部在的位置（可以歪着头看）
    gluLookAt(eyex * 0.1, eyey * 0.1, eyez * 0.1, 0, 0, 0, upx * 0.1, upy * 0.1, upz * 0.1);
//    glPointSize(3);
    glScalef(TempscaleFactor, TempscaleFactor, TempscaleFactor);
    glRotatef(yDeltaRotateAngle, 0, 1, 0);
    glRotatef(xDeltaRotateAngle, 1, 0, 0);

    drawCoordinate();
//    batchManager->renderAll();
//    drawShape();




//     // 顶点位置
////    GLfloat vertices[2][4][3] = {
////        { {-0.8f, 0.8f, 0.8f}, {-0.8f, -0.8f, 0.8f}, {0.8f, -0.8f, 0.8f}, {0.8f, 0.8f, 0.8f} },
////        { {0.8f, 0.8f, 0.8f}, {0.8f, -0.8f, 0.8f}, {0.8f, -0.8f, -0.8f}, {0.8f, 0.8f, -0.8f} }
////    };
////    centralwindow::vertices << QVector3D(1, 0, -2) << QVector3D(0, 1, -2) << QVector3D(-1, 0, -2);
//    vbo.create();  // 创造一个buffer对象在Opengl服务器（GPU），如果生成成功返回true
//    vbo.bind();  // bind it to the context
//    vbo.allocate(&centralwindow::vertices_positions, sizeof(vertices_positions));
//    //  Allocates count bytes of space to the buffer. Any previous contents will be removed.

//    GLuint vPosition = program->attributeLocation("vPosition");
//    program->setAttributeBuffer(vPosition, GL_FLOAT, 0, 3, 0);
//    glEnableVertexAttribArray(vPosition);


//    // 顶点颜色
//    GLfloat colors[2][4][3] = {
//        { {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f} },
//        { {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f} }
//    };


//    vbo.write(24*sizeof(GLfloat), colors, 24*sizeof(GLfloat));
//    GLuint vColor = program->attributeLocation("vColor");
//    program->setAttributeBuffer(vColor, GL_FLOAT, 24*sizeof(GLfloat), 3, 0);
//    glEnableVertexAttribArray(vColor);

//    QMatrix4x4 matrix;
//    matrix.perspective(45.0f, (GLfloat)w/(GLfloat)h, 0.1f, 100.0f);
//    matrix.translate(0, 0, -3);
//    matrix.rotate(-60, 0, 1, 0);  //绕Y轴逆时针旋转
//    program->setUniformValue("matrix", matrix);


//    // render
//    glDrawArrays(GL_POINTS, 0, 1000);   //对点进行渲染，GLDrawArrayas(primitives类型， 数组起点开始处，顶点数组的数量)
}


void renderWindow::drawShape()
{

//    renderWindow::qmutex.lock();
//    qDebug() << "length = " << renderWindow::vertices_buffer.length();
//    glPointSize(3);
//    for(int i=0; i < renderWindow::vertices_buffer.length(); i++)
//    {

//        glBegin(GL_QUADS);
//        glColor4f(renderWindow::reflectivity_buffer[i], 0, 0, 0);
//            glVertex3f(renderWindow::vertices_buffer[i].x() / 1000 + 0.5f,
//                    renderWindow::vertices_buffer[i].y() / 1000 + 0.5f,
//                    renderWindow::vertices_buffer[i].z() / 1000);
//            glVertex3f(renderWindow::vertices_buffer[i].x() / 1000 - 0.5f,
//                    renderWindow::vertices_buffer[i].y() / 1000+ 0.5f,
//                    renderWindow::vertices_buffer[i].z() / 1000);
//            glVertex3f(renderWindow::vertices_buffer[i].x() / 1000 + 0.5f,
//                    renderWindow::vertices_buffer[i].y() / 1000- 0.5f,
//                    renderWindow::vertices_buffer[i].z() / 1000);
//            glVertex3f(renderWindow::vertices_buffer[i].x()/ 1000 - 0.5f,
//                    renderWindow::vertices_buffer[i].y()/ 1000 - 0.5f,
//                    renderWindow::vertices_buffer[i].z()/ 1000);
//        glEnd();
//    }

//    renderWindow::vertices_buffer.clear();
//    renderWindow::reflectivity_buffer.clear();
//    renderWindow::qmutex.unlock();
}


void renderWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint ed(event->pos());
    EndPoint = ed;
    RotateViewPoint();
    this->repaint();
}
//    void mouseClickEvent(QMouseEvent *event);

void renderWindow::RotateViewPoint()
{
//    float avAnale = M_PI / 180 * 0.6; //把每次移动的角度单位化
    float avAnale = 0.6; //把每次移动的角度单位化
    this->yDeltaRotateAngle  = (EndPoint.x() - StartPoint.x()) * avAnale ;
    this->xDeltaRotateAngle  = -(EndPoint.x() - StartPoint.x()) * avAnale ;

}

void renderWindow::drawCoordinate()
{
    /*红色轴是X轴，绿色是Y轴，蓝色是Z轴*/
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.5,0.0,0.0);
    glEnd();
    glPushMatrix();
    glTranslatef(0.5, 0.0f, 0.0f);
    glRotatef(90.0f,0.0f,1.0f,0.0f);

//    glutWireCone(0.027,0.09,10,10);
    glPopMatrix();


    glBegin(GL_LINES);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.5,0.0);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0, 0.5f, 0.0f);
    glRotatef(-90.0f,1.0f,0.0f,0.0f);
//    glutWireCone(0.027,0.09,10,10);
    glPopMatrix();


    glBegin(GL_LINES);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,0.5);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0, 0.0f, 0.5f);
//    glutWireCone(0.027, 0.09, 10, 10);
    glPopMatrix();

}


void renderWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint st(event->pos());
    StartPoint = st;
}

void renderWindow::mouseReleaseEvent(QMouseEvent *event)
{
    /*记录上一次的角度*/
//    LastAngleX = CurrentAngleX;
//    LastAngleY = CurrentAngleY;

    this->xRotateAngle -= this->xDeltaRotateAngle;
    this->yRotateAngle += this->yDeltaRotateAngle;

}





void renderWindow::wheelEvent(QWheelEvent *event)
{


    if (event->delta() >= 0){
        this->scaleVariable(0.1);
    }
    else{
        this->scaleVariable(- 0.1);
    }
}

void renderWindow::scaleVariable(float delta)
{
    if(TempscaleFactor >= 0.1)
    {

        TempscaleFactor += delta;
    }
    else if(delta > 0)
    {
        TempscaleFactor += delta;
    }
//    else{
//        TempscaleFactor = 0;
//    }
    this->repaint();
};



