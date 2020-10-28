#include "centralwindow.h"
#define GLUT_DISABLE_ATEXIT_HACK


#include <gl/GLU.h>
#include <GL/glut.h>

QVector<QVector3D> centralwindow::vertices_positions = {};
QVector<uint8_t> centralwindow::vertices_reflectivity = {};
QVector<QVector3D> centralwindow::vertices_buffer = {};
QVector<uint8_t> centralwindow::reflectivity_buffer = {};

//QVector<QVector3D> centralwindow::vertices_colors = {{1, 1, 1} * 1000}
centralwindow::centralwindow(QWidget *parent) : QOpenGLWidget(parent)
{

    this->eyex = 0.1;
    this->eyey = 0.1;
    this->eyez = 0.1;

    this->upx = 0;
    this->upy = 0.1;
    this->upz = 0;

    this->CurrentAngleZ = 0;
    this->CurrentAngleY = 0;
    LastAngleZ = M_PI / 4;
    LastAngleY = M_PI / 4;

    this->TempscaleFactor = 1;

}

void centralwindow::updateWindowSLOT()
{
    this->update();
}




void centralwindow::initializeGL()
{
    // 为当前环境初始化OpenGL函数,此时QOpenglFunctions对象只可以使用这个上下文。
    initializeOpenGLFunctions();
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

void centralwindow::resizeGL(int w,int h)
{

};


void centralwindow::paintGL()
{
    // qDebug() << "REPAINT AGAIN!!!!!";

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // gluLookAt creates a viewing matrix derived from an eye point,
    // a reference point indicating the center of the scene, and an UP vector.
    gluLookAt(eyex * 0.1, eyey * 0.1,eyez * 0.1, 0, 0, 0, upx * 0.1, upy * 0.1, upz * 0.1);
//    glPointSize(3);
    glScalef(TempscaleFactor, TempscaleFactor, TempscaleFactor);
    drawCoordinate();
    drawShape();




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


void centralwindow::drawShape()
{
    qDebug() << "length = " << centralwindow::vertices_buffer.length();
    glPointSize(3);
    for(int i=0; i<centralwindow::vertices_buffer.length(); i++)
    {
        glBegin(GL_QUADS);
        glColor4f(centralwindow::reflectivity_buffer[i], 0, 0, 0);
            glVertex3f(centralwindow::vertices_buffer[i].x() / 1000 + 0.5f,
                    centralwindow::vertices_buffer[i].y() / 1000 + 0.5f,
                    centralwindow::vertices_buffer[i].z() / 1000);
            glVertex3f(centralwindow::vertices_buffer[i].x() / 1000 - 0.5f,
                    centralwindow::vertices_buffer[i].y() / 1000+ 0.5f,
                    centralwindow::vertices_buffer[i].z() / 1000);
            glVertex3f(centralwindow::vertices_buffer[i].x() / 1000 + 0.5f,
                    centralwindow::vertices_buffer[i].y() / 1000- 0.5f,
                    centralwindow::vertices_buffer[i].z() / 1000);
            glVertex3f(centralwindow::vertices_buffer[i].x()/ 1000 - 0.5f,
                    centralwindow::vertices_buffer[i].y()/ 1000 - 0.5f,
                    centralwindow::vertices_buffer[i].z()/ 1000);
        glEnd();
    }
    centralwindow::vertices_buffer.clear();
    centralwindow::reflectivity_buffer.clear();
}


void centralwindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint ed(event->pos());
    EndPoint = ed;
    RotateViewPoint();
    this->repaint();
}
//    void mouseClickEvent(QMouseEvent *event);

void centralwindow::RotateViewPoint()
{
    float avAnale = M_PI / 180 * 0.6; //把每次移动的角度单位化

    /*把每次移动点跟开始按下鼠标记录的点作差，然后乘以avAngle,最后把上一次释放鼠标后时记录的
      角度相加起来*/
    CurrentAngleZ = (EndPoint.x() - StartPoint.x()) * avAnale;
    CurrentAngleZ += LastAngleZ;
    CurrentAngleY = (EndPoint.y()-StartPoint.y()) * avAnale;
    CurrentAngleY += LastAngleY;

    QVector3D vector1(sin(CurrentAngleY) * sin(CurrentAngleZ), cos(CurrentAngleY), sin(CurrentAngleY) * cos(CurrentAngleZ));
    vector1 = vector1.normalized();  //将坐标单位化
    eyex = vector1.x();
    eyey = vector1.y();
    eyez = vector1.z();

    /*主要计算第三组坐标*/
    QVector3D vectorA(0, sin(CurrentAngleY), 0);
    QVector3D vectorB = QVector3D(0, 0, 0)-QVector3D(sin(CurrentAngleY) * sin(CurrentAngleZ),
                                                     0, sin(CurrentAngleY) * cos(CurrentAngleZ));
    QVector3D vectorAB = QVector3D::crossProduct(vectorA,vectorB);


    QVector3D vectorC = QVector3D(0, 0, 0) - vector1;
    QVector3D vector2 = QVector3D::crossProduct(vectorC, vectorAB);
    vector2=vector2.normalized();
    upx = vector2.x();
    upy = vector2.y();
    upz = vector2.z();
}

void centralwindow::drawCoordinate()
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


void centralwindow::mousePressEvent(QMouseEvent *event)
{
    QPoint st(event->pos());
    StartPoint = st;
}

void centralwindow::mouseReleaseEvent(QMouseEvent *event)
{
    /*记录上一次的角度*/
    LastAngleZ = CurrentAngleZ;
    LastAngleY = CurrentAngleY;

}





void centralwindow::wheelEvent(QWheelEvent *event)
{

    qDebug() << "event->delta() = " << event->delta();
    if (event->delta() >= 0){
        this->scaleVariable(0.1);
    }
    else{
        this->scaleVariable(- 0.1);
    }
}

void centralwindow::scaleVariable(float delta)
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



