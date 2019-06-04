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
    QPainterPath path;
    // 移动当前点到点(50, 250)
    path.moveTo(50, 250);
    // 从当前点即(50, 250)绘制一条直线到点(50, 230)，完成后当前点更改为(50, 230)
    path.lineTo(50, 230);
    // 从当前点和点(120, 60)之间绘制一条三次贝塞尔曲线
    path.cubicTo(QPointF(105, 40), QPointF(115, 80), QPointF(120, 60));
    path.lineTo(130, 130);
    // 向路径中添加一个椭圆
    path.addEllipse(QPoint(130, 130), 30, 30);

    painter.setPen(Qt::darkYellow);
    // 绘制路径
    painter.drawPath(path);

    // 平移坐标系统后重新绘制路径
    path.translate(200,0);
    painter.setPen(Qt::darkBlue);
    painter.drawPath(path);
}
