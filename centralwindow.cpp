#include "centralwindow.h"

QVector<QVector3D> centralwindow::vertices_positions = {};
QVector<uint8_t> centralwindow::vertices_reflectivity = {};
QVector<QVector3D> centralwindow::vertices_buffer = {};
QVector<uint8_t> centralwindow::reflectivity_buffer = {};

//QVector<QVector3D> centralwindow::vertices_colors = {{1, 1, 1} * 1000}
centralwindow::centralwindow(QWidget *parent) : QOpenGLWidget(parent)
{

//    QTimer * timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(updateWindowSLOT()));
//    timer->start(30);
//    glutMousFunc();




}

void centralwindow::updateWindowSLOT()
{
    this->update();
}

void centralwindow::mouseMoveEvent(QMouseEvent *event)
{

}

void centralwindow::mouseClickEvent(QMouseEvent *event){}

void centralwindow::mousePressEvent(QMouseEvent *event, const QPoint &mousePos)
{

}
void centralwindow::mouseReleaseEvent(QMouseEvent *event){}


void centralwindow::initializeGL()
{
    // 为当前环境初始化OpenGL函数,此时QOpenglFunctions对象只可以使用这个上下文。
    initializeOpenGLFunctions();
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

void centralwindow::resizeGL(int w,int h) {

};


void centralwindow::paintGL()
{
    // qDebug() << "REPAINT AGAIN!!!!!";
    int w = width();
    int h = height();
    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    qDebug() << "length = " << centralwindow::vertices_buffer.length();

    glPointSize(3);

    for(int i=0; i<centralwindow::vertices_buffer.length(); i++)
    {
//        qDebug() << "render_point = " << i << centralwindow::vertices_buffer[i].x() ;
        glBegin(GL_POINTS);
        glColor4f(centralwindow::reflectivity_buffer[i], 0, 0, 0);
//        glBegin(GL_TRIANGLES);

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

