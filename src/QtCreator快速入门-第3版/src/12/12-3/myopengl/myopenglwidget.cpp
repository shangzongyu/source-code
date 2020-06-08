#include "myopenglwidget.h"
#include <QOpenGLShaderProgram>

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

void MyOpenGLWidget::initializeGL()
{
    // 为当前环境初始化OpenGL函数
    initializeOpenGLFunctions();

    // 创建顶点着色器
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
            "in vec4 vPosition;                        \n"
            "void main() {                             \n"
            "   gl_Position = vPosition;               \n"
            "}                                         \n";
    vshader->compileSourceCode(vsrc);
    // 创建片段着色器
    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
            "void main() {                              \n"
            "   gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
            "}                                          \n";
    fshader->compileSourceCode(fsrc);

    // 创建着色器程序
    program = new QOpenGLShaderProgram;
    program->addShader(vshader);
    program->addShader(fshader);

    program->link();
    program->bind();
}

void MyOpenGLWidget::resizeGL(int , int )
{  
}

void MyOpenGLWidget::paintGL()
{
    int w = width();
    int h = height();
    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 顶点位置
    GLfloat vertices[] = {
        -0.8f, 0.8f,
        -0.8f, -0.8f,
        0.8f, -0.8f,
        0.8f, 0.8f
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, 8*sizeof(GLfloat));

    GLuint vPosition = program->attributeLocation("vPosition");
    program->setAttributeBuffer(vPosition, GL_FLOAT, 0, 2, 0);
    glEnableVertexAttribArray(vPosition);

    // 绘制
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}



