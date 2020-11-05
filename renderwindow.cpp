#include "renderwindow.h"

#include "gl/GLU.h"
//#include <GL/glut.h>
#include <QThread>


//int maxNumVertex = 1500;


GLfloat renderWindow::vertexPositions[1500][3];
GLfloat renderWindow::vertexReflectivity[1500][3];


renderWindow::renderWindow(QWidget *parent) : QOpenGLWidget(parent)
{
    QMatrix4x4 lastmatrix;
//    QMatrix4x4 matrix;
    glm::vec3 r_axis_world;
    compareToOrijinScaleFactor = 1;
    compareToLastScaleFactor = 1;
    rotateAngle = 0;
    sceneManager = new RoamingScenceManager();

}

renderWindow::~renderWindow()
{
    delete sceneManager;
}

void renderWindow::updateWindowSLOT()
{
//    this->update();
}




void renderWindow::initializeGL()
{

    // 为当前context初始化OpenGL函数
    // 此时QOpenglFunctions对象只可以使用这个上下文。
//    initializeOpenGLFunctions();
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);

//    // 创建顶点着色器
//    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
//    const char *vertexshader =
//             "#version 460 core                         \n"
//             "in vec4 vPosition;                        \n"
//             "in vec3 vColor;                           \n"
//             "out vec4 color;                           \n"
//             "uniform mat4 matrix;                      \n"
//             "void main() { "
//             "                                          \n"
//             "   color = vec4(vColor, 1.0);             \n"
//             "   gl_Position = matrix * vPosition;      \n"
//             "}                                         \n";
//     vshader->compileSourceCode(vertexshader);
//     // 创建片段着色器
//     QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
//     const char *fragmentShader =
//             "#version 460                           \n"
//             "in vec4 color;                             \n"
//             "out vec4 fColor;                           \n"
//             "void main() {                              \n"
//             "   fColor = color;                         \n"
//             "}                                          \n";
//     fshader->compileSourceCode(fragmentShader);

////     // 创建着色器程序
//     program = new QOpenGLShaderProgram;
//     program->addShader(vshader);
//     program->addShader(fshader);

//     program->bind();
//     program->link();

    sceneManager->init();
    glGenBuffers(1, &VBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glewInit();

    glGenVertexArrays(1, &VAOID);



};


glm::vec2 renderWindow::scaleMouse(glm::vec2 coords, glm::vec2 viewport)
{
//    conver x and y to [-1, 1]
    float newx = static_cast<float>(coords.x * 2.f) / static_cast<float>(viewport.x) - 1.f;
    float newy = 1.0f - static_cast<float>(coords.y) * 2.f / static_cast<float>(viewport.y);
    return glm::vec2(glm::vec2(newx, newy));
};

glm::vec3 renderWindow::projectToSphere(glm::vec2 xy)
{
    float d = glm::length(xy);

    glm::vec3 result;
    float r = 2;
    if(d < r / sqrtf(2.f))
    {
        result.z = sqrtf(r * r - d * d);
    }
    else
    {
        result.z = r * r / 2 / d;
    }
    result.x = xy.x;
    result.y = xy.y;
    return glm::normalize(result);

}
void renderWindow::resizeGL(int w,int h)
{

};


void renderWindow::paintGL()
{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    qDebug() << "isCreate = " << vbo.create();

//    vbo.bind();
//    vbo.allocate(
//                &renderWindow::vertexPositions, 1500 * 6 * sizeof(GLfloat));
//    qDebug() << "allocate finish";

//    GLuint vPosition = program->attributeLocation("vPosition");
//    program->setAttributeBuffer(vPosition, GL_FLOAT, 0, 3, 0);
//    glEnableVertexAttribArray(vPosition);


//    vbo.write(1500 * 3 * sizeof(float),
//              &renderWindow::vertexReflectivity, 1500 * 3 * sizeof(GLfloat));
//    GLuint vColor = program->attributeLocation("vColor");
//    program->setAttributeBuffer(vColor, GL_FLOAT, 1500 * 3 * sizeof(GLfloat), 3, 0);

////    matrix = lastmatrix;
////    matrix.scale(compareToLastScaleFactor, compareToLastScaleFactor, compareToLastScaleFactor);
////    matrix.rotate(rotateAngle, QVector3D(r_axis_world.x, r_axis_world.y, r_axis_world.z));
//    QMatrix4x4 matrix;

//    matrix.translate(*sceneManager->TempTranslateVec);
//    matrix.scale(sceneManager->TempscaleFactor, sceneManager->TempscaleFactor, sceneManager->TempscaleFactor);
//    matrix.lookAt(*sceneManager->NewEye, *sceneManager->NewView, *sceneManager->NewUp);
//    //    glLoadIdentity();
////    glTranslatef(TempTranslateVec->X(),TempTranslateVec->Y(),TempTranslateVec->Z());
////    glScalef(TempscaleFactor,TempscaleFactor,TempscaleFactor);
////    gluLookAt(NewEye->X(),NewEye->Y(),NewEye->Z(),
////              NewView->X(),NewView->Y(),NewView->Z(),
////              NewUp->X(),NewUp->Y(),NewUp->Z());

//    drawCoordinate();

//    program->setUniformValue("matrix", matrix);
//    glDrawArrays(GL_POINTS, 0, 1500);

    sceneManager->render();
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(renderWindow::vertexPositions),
                 renderWindow::vertexPositions,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

}


void renderWindow::drawCoordinate()
{
//    /*红色轴是X轴，绿色是Y轴，蓝色是Z轴*/
//    glBegin(GL_LINES);
//    glColor3f(1.0f, 0.0, 0.0);
//    glVertex3f(0.0,0.0,0.0);
//    glVertex3f(0.5,0.0,0.0);
//    glEnd();
//    glPushMatrix();
//    glTranslatef(0.5, 0.0f, 0.0f);
//    glRotatef(90.0f,0.0f,1.0f,0.0f);

////    glutWireCone(0.027,0.09,10,10);
//    glPopMatrix();


//    glBegin(GL_LINES);
//    glColor3f(0.0,1.0f,0.0);
//    glVertex3f(0.0,0.0,0.0);
//    glVertex3f(0.0,0.5,0.0);
//    glEnd();
//    glPushMatrix();
//    glTranslatef(0.0, 0.5f, 0.0f);
//    glRotatef(-90.0f,1.0f,0.0f,0.0f);
////    glutWireCone(0.027,0.09,10,10);
//    glPopMatrix();


//    glBegin(GL_LINES);
//    glColor3f(0.0,0.0,1.0f);
//    glVertex3f(0.0,0.0,0.0);
//    glVertex3f(0.0,0.0,0.5);
//    glEnd();
//    glPushMatrix();
//    glTranslatef(0.0, 0.0f, 0.5f);
////    glutWireCone(0.027, 0.09, 10, 10);
//    glPopMatrix();

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


}


void renderWindow::mousePressEvent(QMouseEvent *event)
{

//    qDebug() << "x = " << event->pos().x() << "y = " << event->pos().y();
//    QPoint st(event->pos());
//    StartPoint = st;
    sceneManager->getInitPos(event->x(),event->y());

}


void renderWindow::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug() << "mouse move to " << event->pos().x();
//    compareToLastScaleFactor = 1;
//    QPoint ed(event->pos());

//    GLint viewport[4];
//    glGetIntegerv(GL_VIEWPORT, viewport);
//    glm::vec2 newMouse = scaleMouse(glm::vec2(ed.x(), ed.y()),
//                                    glm::vec2(viewport[2], viewport[3]));
//    glm::vec2 oldMouse = scaleMouse(glm::vec2(StartPoint.x(), StartPoint.y()),
//                                    glm::vec2(viewport[2], viewport[3]));
//    setRotateParameter(newMouse, oldMouse);

//    StartPoint = ed;
////    EndPoint = ed;

//    this->update();
//    lastmatrix = matrix;
    if(event->buttons()&Qt::LeftButton)
    {
        if(event->modifiers()==Qt::CTRL)
        {
            sceneManager->executeTranslateOperation(event->x(),event->y());
        }
        else
        {
            sceneManager->executeRotateOperation(event->x(),event->y());
        }
    }
    update();

}
//    void mouseClickEvent(QMouseEvent *event);

void renderWindow::setRotateParameter(glm::vec2 newMouse, glm::vec2 oldMouse)
{

//    if(newMouse == oldMouse){
//        return;
//    }
    glm::vec3 p1 = projectToSphere(oldMouse);
    glm::vec3 p2 = projectToSphere(newMouse);
    r_axis_world = glm::cross(p1, p2);
    glm::vec3 d = p1 - p2;
    rotateAngle = 180 * glm::length(d) ;

};


void renderWindow::mouseReleaseEvent(QMouseEvent *event)
{


    lastmatrix = matrix;

}





void renderWindow::wheelEvent(QWheelEvent *event)
{
//    rotateAngle = 0;

//    if (event->delta() >= 0)
//    {
//        this->scaleVariable(0.1);
//    }
//    else
//    {
//        this->scaleVariable(- 0.1);
//    }
    if(event->delta()>=0)
    {
        sceneManager->executeScaleOperation(-0.1);
    }else
    {
        sceneManager->executeScaleOperation(0.1);
    }
    update();
}

void renderWindow::scaleVariable(float delta)
{
    if(compareToOrijinScaleFactor >= 0.1)
    {

        compareToLastScaleFactor = (compareToOrijinScaleFactor + delta) / compareToOrijinScaleFactor;
        compareToOrijinScaleFactor += delta;

    }
    else if(delta > 0)
    {

        compareToLastScaleFactor = (compareToOrijinScaleFactor + delta) / compareToOrijinScaleFactor;
        compareToOrijinScaleFactor += delta;

    }
//    else{
//        TempscaleFactor = 0;
//    }

    this->update();
    lastmatrix = matrix;


};



