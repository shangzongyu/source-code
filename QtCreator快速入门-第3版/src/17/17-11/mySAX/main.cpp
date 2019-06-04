#include "mysax.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MySAX sax;
    sax.readFile("../mySAX/my.xml");
    return app.exec();
}
