#include "renderwindow.h"
#define GLUT_DISABLE_ATEXIT_HACK


#include <gl/GLU.h>
#include <GL/glut.h>
QMutex renderWindow::qmutex;
//QVector<QVector3D> renderWindow::vertices_positions = {};
GLfloat renderWindow::vertexPositions[1500][3];
GLfloat renderWindow::vertexReflectivity[1500][3];


//QVector<QVector3D> centralwindow::vertices_colors = {{1, 1, 1} * 1000}
renderWindow::renderWindow(QWidget *parent) : QOpenGLWidget(parent)
{
    eyex = 0;
    eyey = 0;
    eyez = 1;

    upx = 0;
    upy = 1;
    upz = 0;
    CurrentAngleZ=0;
    CurrentAngleY=0;
    LastAngleZ=M_PI/4;
    LastAngleY=M_PI/4;
//    this->CurrentAngleX = 0;
//    this->CurrentAngleY = 0;
//    this->LastAngleX = M_PI / 2;
//    this->LastAngleY = M_PI / 2;
//    this->LastAngleZ = 0.95532;   // 与z轴正向的夹角
//    this->LastAngleY = 0.95532;



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
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);


     // 创建顶点着色器
     QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
     const char *vertexshader =
             "#version 450                           \n"
             "in vec4 vPosition;                        \n"
             "in vec4 vColor;                           \n"
             "out vec4 color;                           \n"
             "uniform mat4 matrix;                      \n"
             "void main() {                             \n"
             "   color = vColor;                        \n"
             "   gl_Position = matrix * vPosition;      \n"
             "}                                         \n";
     vshader->compileSourceCode(vertexshader);
     // 创建片段着色器
     QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
     const char *fragmentShader =
             "#version 450                           \n"
             "in vec4 color;                             \n"
             "out vec4 fColor;                           \n"
             "void main() {                              \n"
             "   fColor = color;                         \n"
             "}                                          \n";
     fshader->compileSourceCode(fragmentShader);

     // 创建着色器程序
     program = new QOpenGLShaderProgram;
     program->addShader(vshader);
     program->addShader(fshader);

     program->bind();
     program->link();

};

void renderWindow::resizeGL(int w,int h)
{

};


void renderWindow::paintGL()
{
    // 获得当下的上下文
//    QOpenGLExtraFunctions  * f = QOpenGLContext::currentContext()->extraFunctions();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // gluLookAt creates a viewing matrix derived from an eye point,
    // a reference point indicating the center of the scene, and an UP vector.
    // eye:相机光心所在的位置  center: 相机朝向的位置， up：相机的顶部在的位置（可以歪着头看）


    vbo.create();
    vbo.bind();

    this->vbo.allocate(
                &renderWindow::vertexPositions, 1500 * 6 * sizeof(float));
    GLuint vPosition = program->attributeLocation("vPosition");
    program->setAttributeBuffer(vPosition, GL_FLOAT, 0, 3, 0);
    glEnableVertexAttribArray(vPosition);


    vbo.write(1500 * 3 * sizeof(float),
              &renderWindow::vertexReflectivity, 1500 * 3 * sizeof(float));
    GLuint vColor = program->attributeLocation("vColor");
    program->setAttributeBuffer(vColor, GL_FLOAT, 1500 * 3 * sizeof(float), 3, 0);

    QMatrix4x4 matrix;
    matrix.scale(TempscaleFactor, TempscaleFactor, TempscaleFactor);
    matrix.lookAt(QVector3D(eyex * 0.1, eyey * 0.1, eyez * 0.1),
                  QVector3D(0, 0, 0),
                  QVector3D(upx * 0.1, upy * 0.1, upz * 0.1));
    drawCoordinate();

    program->setUniformValue("matrix", matrix);
    glDrawArrays(GL_POINTS, 0, 1500);

//    batchManager->renderAll();
//    drawShape();
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
//    float avAnale = 0.6; //把每次移动的角度单位化
//    this->yDeltaRotateAngle  = (EndPoint.x() - StartPoint.x()) * avAnale ;
//    this->xDeltaRotateAngle  = -(EndPoint.x() - StartPoint.x()) * avAnale ;
    float avAnale = M_PI / 180 * 0.6; //把每次移动的角度单位化

        /*把每次移动点跟开始按下鼠标记录的点作差，然后乘以avAngle,最后把上一次释放鼠标后时记录的
          角度相加起来*/
    CurrentAngleZ = (EndPoint.x() - StartPoint.x()) * avAnale;
    CurrentAngleZ += LastAngleZ;
    CurrentAngleY = (EndPoint.y() - StartPoint.y()) * avAnale;
    CurrentAngleY += LastAngleY;


//    QVector3D vector1(sin(CurrentAngleY) * sin(CurrentAngleZ), cos(CurrentAngleY),
//                      sin(CurrentAngleY) * cos(CurrentAngleZ));
    QVector3D vector1(sin(CurrentAngleY) * sin(CurrentAngleZ), cos(CurrentAngleY),
                      sin(CurrentAngleY) * cos(CurrentAngleZ));
    vector1 = vector1.normalized();  //将坐标单位化
    eyex = vector1.x();
    eyey = vector1.y();
    eyez = vector1.z();

    /*主要计算第三组坐标*/
    QVector3D vectorA(0, sin(CurrentAngleY), 0);
    QVector3D vectorB = - QVector3D(sin(CurrentAngleY) * sin(CurrentAngleZ),
                                    0, sin(CurrentAngleY) * cos(CurrentAngleZ));
    QVector3D vectorAB = QVector3D::crossProduct(vectorA, vectorB);


    QVector3D vectorC = QVector3D(0, 0, 0)-vector1;
    QVector3D vector2 = QVector3D::crossProduct(vectorC, vectorAB);
    vector2 = vector2.normalized();
    upx = vector2.x();
    upy = vector2.y();
    upz = vector2.z();
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


    LastAngleZ=CurrentAngleZ;
    LastAngleY=CurrentAngleY;

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



