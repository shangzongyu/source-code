#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QBitmap>
#include <QPicture>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QImage image;
    // 加载一张图片
    image.load("../mydrawing3/image.png");
    // 输出图片的一些信息
    qDebug() << image.size() << image.format() << image.depth();
    // 在界面上绘制图片
    painter.drawImage(QPoint(10, 10), image);
    // 获取镜像图片
    QImage mirror = image.mirrored();
    // 将图片进行扭曲
    QTransform transform;
    transform.shear(0.2, 0);
    QImage image2 = mirror.transformed(transform);
    painter.drawImage(QPoint(10, 160), image2);
    // 将镜像图片保存到文件
    image2.save("../mydrawing3/mirror.png");
}
