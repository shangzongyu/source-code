#include <QApplication>
#include "myopenglwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    MyOpenGLWidget w;
    w.resize(400, 300);
    w.show();
    return app.exec();
}
