#include <QApplication>
#include <QWidget>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget widget;
    widget.resize(400, 300);       // 设置窗口大小
    widget.move(200, 100);         // 设置窗口位置
    widget.show();
    int x = widget.x();
    qDebug("x: %d", x);            // 输出x的值
    int y = widget.y();
    qDebug("y: %d", y);
    QRect geometry = widget.geometry();
    QRect frame = widget.frameGeometry();
    qDebug() << "geometry: " << geometry << "frame: " << frame;

    return a.exec();
}
