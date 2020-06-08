#include "myopenglwidget.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{

}


void MyOpenGLWidget::initializeGL()
{
    for (int i = 0; i < 2; ++i)
        textures[i] = new QOpenGLTexture(QImage(QString("../myopengl/side%1.png")
                                                .arg(i + 1)).mirrored());
    // 为当前环境初始化OpenGL函数
    initializeOpenGLFunctions();

    // 创建顶点着色器
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
            "in vec4 vPosition;                        \n"
            "in vec4 vTexCoord;                        \n"
            "out vec4 texCoord;                        \n"
            "uniform mat4 matrix;                      \n"
            "void main() {                             \n"
            "   texCoord = vTexCoord;                  \n"
            "   gl_Position = matrix * vPosition;      \n"
            "}                                         \n";
    vshader->compileSourceCode(vsrc);
    // 创建片段着色器
    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
            "uniform sampler2D tex;                     \n"
            "in vec4 texCoord;                          \n"
            "out vec4 fColor;                           \n"
            "void main() {                              \n"
            "   fColor = texture(tex, texCoord);        \n"
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
    GLfloat vertices[2][4][3] = {
        { {-0.8f, 0.8f, 0.8f}, {-0.8f, -0.8f, 0.8f}, {0.8f, -0.8f, 0.8f}, {0.8f, 0.8f, 0.8f} },
        { {0.8f, 0.8f, 0.8f}, {0.8f, -0.8f, 0.8f}, {0.8f, -0.8f, -0.8f}, {0.8f, 0.8f, -0.8f} }
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, 40*sizeof(GLfloat));

    GLuint vPosition = program->attributeLocation("vPosition");
    program->setAttributeBuffer(vPosition, GL_FLOAT, 0, 3, 0);
    glEnableVertexAttribArray(vPosition);


    // 纹理坐标
    GLfloat coords[2][4][2] = {
        { {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f} },
        { {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f} }
    };
    vbo.write(24*sizeof(GLfloat), coords, 16*sizeof(GLfloat));
    GLuint vTexCoord = program->attributeLocation("vTexCoord");
    program->setAttributeBuffer(vTexCoord, GL_FLOAT, 24*sizeof(GLfloat), 2, 0);
    glEnableVertexAttribArray(vTexCoord);
    program->setUniformValue("tex", 0);

    QMatrix4x4 matrix;
    matrix.perspective(45.0f, (GLfloat)w/(GLfloat)h, 0.1f, 100.0f);
    matrix.translate(0, 0, -3);
    matrix.rotate(-60, 0, 1, 0);  //绕Y轴逆时针旋转
    program->setUniformValue("matrix", matrix);


    // 绘制
    for(int i=0; i<2; i++) {
        textures[i]->bind();
        glDrawArrays(GL_TRIANGLE_FAN, i*4, 4);
    }
}



