#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QLabel *label = new QLabel(&w);
    label->setText("Hello World! 你好Qt！");
    label->resize(200, 20);
    label->move(120, 120);
    w.show();

    return a.exec();
}
