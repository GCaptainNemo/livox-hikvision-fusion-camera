#include "renderwindow.h"

#include "gl/GLU.h"
//#include <GL/glut.h>
#include <QThread>


GLfloat renderWindow::vertexPositions[1500][3];
GLfloat renderWindow::vertexReflectivity[1500][3];
GLfloat renderWindow::vertexColor[1500][3];
bool renderWindow::isColor = true;



renderWindow::renderWindow(QWidget *parent) : QOpenGLWidget(parent)
{
    sceneManager = new RoamingScenceManager();

}

renderWindow::~renderWindow()
{
    delete sceneManager;
}

void renderWindow::updateWindowSLOT()
{
    this->update();
}




void renderWindow::initializeGL()
{

    // 为当前context初始化OpenGL函数
    // 此时QOpenglFunctions对象只可以使用这个上下文。
    this->initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
//    glClearColor(0.156, 0.156, 0.168, 0.0);
    glClearColor(0, 0, 0, 0.0);


    // ////////////////////////////////////////////////////////////////////////////
    // vertex render initialize
    // ////////////////////////////////////////////////////////////////////////////


    // 创建顶点着色器
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vertexshader =
             "#version 330 core                         \n"
             "in vec4 vPosition;   \n"
             "in vec4 vColor;      \n"
             "out vec4 color;                           \n"
             "uniform mat4 matrix;                      \n"
             "void main() {                             \n"
             "   color = vColor;                        \n"
             "   gl_Position = matrix * vPosition;      \n"
             "}                                         \n";


     vshader->compileSourceCode(vertexshader);
    //     // 创建片段着色器
     QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
     const char *fragmentShader =
             "#version 330 core                          \n"
             "in vec4 color;                             \n"
             "out vec4 FragColor;                        \n"
             "void main() {                              \n"
             "   FragColor = color;                      \n"
             "}                                          \n";
     fshader->compileSourceCode(fragmentShader);

    ////     // 创建着色器程序
    vertexShaderProgram = new QOpenGLShaderProgram;
    vertexShaderProgram->addShader(vshader);
    vertexShaderProgram->addShader(fshader);
    vertexShaderProgram->bind();
    vertexShaderProgram->link();

    vboVertex.create();
    vboVertex.bind();
    vboVertex.allocate(
                &renderWindow::vertexPositions, 1500 * 6 * sizeof(GLfloat));

    vaoVertex.create();
    vaoVertex.bind();


    GLuint vPosition = vertexShaderProgram->attributeLocation("vPosition");
    vertexShaderProgram->setAttributeBuffer(vPosition, GL_FLOAT, 0, 3, 0);
    vertexShaderProgram->enableAttributeArray(vPosition);

    GLuint vColor = vertexShaderProgram->attributeLocation("vColor");
    vertexShaderProgram->setAttributeBuffer(vColor, GL_FLOAT, 1500 * 3 * sizeof(GLfloat), 3, 0);
    vertexShaderProgram->enableAttributeArray(vColor);

    vaoVertex.release();
    vboVertex.release();
    vertexShaderProgram->release();
//    \

    // ////////////////////////////////////////////////////////////////////////////
    // coordinate render initialize
    // ////////////////////////////////////////////////////////////////////////////

    coordinateShaderProgram = new QOpenGLShaderProgram;
    coordinateShaderProgram->addShader(vshader);
    coordinateShaderProgram->addShader(fshader);
    coordinateShaderProgram->bind();
    coordinateShaderProgram->link();

    vboCoordinate.create();
    vboCoordinate.bind();
    GLfloat coordinatePosColor[12][3] =
    {
        {0, 0, 0}, {5, 0, 0},
        {0, 0, 0}, {0, 5, 0},
        {0, 0, 0}, {0, 0, 5},
        {1.0, 0, 0}, {1.0, 0, 0},
        {0, 1.0, 0}, {0, 1.0, 0},
        {0, 0, 1.0}, {0, 0, 1.0}
    };
    vboCoordinate.allocate(coordinatePosColor,
                           12 * 3 * sizeof (GLfloat));

    vaoCoordinate.create();
    vaoCoordinate.bind();

    GLuint coorPosition = coordinateShaderProgram->attributeLocation("vPosition");
    coordinateShaderProgram->setAttributeBuffer(coorPosition, GL_FLOAT, 0, 3, 0);
    coordinateShaderProgram->enableAttributeArray(coorPosition);

    GLuint coorColor = coordinateShaderProgram->attributeLocation("vColor");
    coordinateShaderProgram->setAttributeBuffer(coorColor, GL_FLOAT, 6 * 3 * sizeof(GLfloat), 3, 0);
    coordinateShaderProgram->enableAttributeArray(coorColor);

    qDebug() << "vcolor, vPostion, coorColor, coorPosition = "
              << coorColor << coorPosition;

    vaoCoordinate.release();
    vboCoordinate.release();
    coordinateShaderProgram->release();



//    sceneManager->init();
//    glGenVertexArrays(1, &VAOID);
//    glBindVertexArray(VAOID);

//    glGenBuffers(1, &VBOID);
//    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
//    glBufferData(GL_ARRAY_BUFFER, 1500 * 6 * sizeof(GLfloat),
//                 renderWindow::vertexPositions, GL_STREAM_DRAW);

//    const char * vertexShaderSource =
//       " #version 330 core                                   \n "
//       " layout (location = 0) in vec3 aPos;                 \n "
//       "                                                     \n "
//       " void main()                                         \n "
//       " {                                                   \n "
//       "     gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n "
//       " }                                                   \n ";
//    const char * fragmentShaderSource =
//           " #version 330 core                             \n "
//           " out vec4 FragColor;                           \n "
//           "                                               \n "
//           " void main()                                   \n "
//           " {                                             \n "
//           "     FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n "
//           " }                                             \n ";

//    unsigned int vertexShader;
//    vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);

//    unsigned int fragmentShader;
//    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);

//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);

//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), (void *)0);
//    glEnableVertexAttribArray(0);

};

void renderWindow::resizeGL(int w,int h)
{

};


void renderWindow::paintGL()
{
    qDebug() << "in paintGL";
//    glClearColor(0.156   ,   0.156  ,    0.168 ,     0.0);
    int w = width();
    int h = height();
    int side = qMin(w, h);
    glViewport((w-side) / 2, (h-side) / 2, side, side);
    glClearColor(0, 0, 0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ////////////////////////////////////////////////////////////////////////
    // calculate modelview matrix
    // ////////////////////////////////////////////////////////////////////////

    QMatrix4x4 matrix;
    matrix.ortho(-50, 50, -50, 50, -5000, 5000);
    sceneManager->calculateMatrix(matrix);

    // ////////////////////////////////////////////////////////////////////////
    // positions & color buffer allocate
    // ////////////////////////////////////////////////////////////////////////
    vertexShaderProgram->bind();
    vaoVertex.bind();
    vboVertex.bind();

    vboVertex.write(0,
    &renderWindow::vertexPositions, 1500 * 3 * sizeof(GLfloat));

    if(!renderWindow::isColor)
    {
        vboVertex.write(1500 * 3 * sizeof(float),
              &renderWindow::vertexReflectivity, 1500 * 3 * sizeof(GLfloat));
    }
    else{
        vboVertex.write(1500 * 3 * sizeof(float),
              &renderWindow::vertexReflectivity, 1500 * 3 * sizeof(GLfloat));

    }
    vertexShaderProgram->bind();
    vertexShaderProgram->setUniformValue("matrix", matrix);
    vaoVertex.bind();
    glDrawArrays(GL_POINTS, 0, 1500);
    vaoVertex.release();
    vertexShaderProgram->release();
    vboVertex.release();


    // ////////////////////////////////////////////////////////////////////////
    // draw coordinate
    // ////////////////////////////////////////////////////////////////////////

    coordinateShaderProgram->bind();
    coordinateShaderProgram->setUniformValue("matrix", matrix);
    vaoCoordinate.bind();
    glDrawArrays(GL_LINES, 0, 6);
    vaoCoordinate.release();
    coordinateShaderProgram->release();


    // ////////////////////////////////////////////////////////////

//    glBindVertexArray(0);
//    sceneManager->render();
//    glBindVertexArray(VAOID);
//    glUseProgram(shaderProgram);
//    glDrawArrays(GL_POINTS, 0, 1500);
//    //    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
////    glBufferData(GL_ARRAY_BUFFER,
////                 sizeof(renderWindow::vertexPositions),
////                 renderWindow::vertexPositions,
////                 GL_STATIC_DRAW);
////    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
////    glEnableVertexAttribArray(0);

}


void renderWindow::drawCoordinate()
{
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
    if(event->delta() >= 0)
    {
        sceneManager->executeScaleOperation(0.1);
    }else
    {
        sceneManager->executeScaleOperation(-0.1);
    }
    this->update();
}
