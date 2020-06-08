#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

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
    // 填充界面背景为白色
    painter.fillRect(rect(), Qt::white);
    painter.setPen(QPen(Qt::red, 11));
    // 绘制一条线段
    painter.drawLine(QPoint(5, 6), QPoint(100, 99));
    // 将坐标系统进行平移，使(200, 150)点作为原点
    painter.translate(200, 150);
    // 开启抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    // 重新绘制相同的线段
    painter.drawLine(QPoint(5, 6), QPoint(100, 99));

    // 保存painter的状态
    painter.save();
    // 将坐标系统旋转90度
    painter.rotate(90);
    painter.setPen(Qt::cyan);
    // 重新绘制相同的线段
    painter.drawLine(QPoint(5, 6), QPoint(100, 99));
    // 恢复painter的状态
    painter.restore();

    painter.setBrush(Qt::darkGreen);
    // 绘制一个矩形
    painter.drawRect(-50, -50, 100, 50);
    painter.save();
    // 将坐标系统进行缩放
    painter.scale(0.5, 0.4);
    painter.setBrush(Qt::yellow);
    // 重新绘制相同的矩形
    painter.drawRect(-50, -50, 100, 50);
    painter.restore();

    painter.setPen(Qt::blue);
    painter.setBrush(Qt::darkYellow);
    // 绘制一个椭圆
    painter.drawEllipse(QRect(60, -100, 50, 50));
    // 将坐标系统进行扭曲
    painter.shear(1.5, -0.7);
    painter.setBrush(Qt::darkGray);
    // 重新绘制相同的椭圆
    painter.drawEllipse(QRect(60, -100, 50, 50));

}
