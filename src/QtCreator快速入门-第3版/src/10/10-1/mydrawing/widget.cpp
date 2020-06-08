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
    painter.drawLine(QPoint(0, 0), QPoint(100, 100));

    //创建画笔
    QPen pen(Qt::green, 5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
    //使用画笔
    painter.setPen(pen);
    QRectF rectangle(70.0, 40.0, 80.0, 60.0);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;
    //绘制圆弧
    painter.drawArc(rectangle, startAngle, spanAngle);

    //重新设置画笔
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    //绘制一个矩形
    painter.drawRect(160, 20, 50, 40);
    // 创建画刷
    QBrush brush(QColor(0, 0, 255), Qt::Dense4Pattern);
    // 使用画刷
    painter.setBrush(brush);
    // 绘制椭圆
    painter.drawEllipse(220, 20, 50, 50);
    // 设置纹理
    brush.setTexture(QPixmap("../mydrawing/yafeilinux.png"));
    // 重新使用画刷
    painter.setBrush(brush);
    // 定义四个点
    static const QPointF points[4] = {
        QPointF(270.0, 80.0),
        QPointF(290.0, 10.0),
        QPointF(350.0, 30.0),
        QPointF(390.0, 70.0)
    };
    // 使用四个点绘制多边形
    painter.drawPolygon(points, 4);

    // 使用画刷填充一个矩形区域
    painter.fillRect(QRect(10, 100, 150, 20), QBrush(Qt::darkYellow));
    // 擦除一个矩形区域的内容
    painter.eraseRect(QRect(50, 0, 50, 120));


    // 线性渐变
    QLinearGradient linearGradient(QPointF(40, 190), QPointF(70, 190));
    // 插入颜色
    linearGradient.setColorAt(0, Qt::yellow);
    linearGradient.setColorAt(0.5, Qt::red);
    linearGradient.setColorAt(1, Qt::green);
    // 指定渐变区域以外的区域的扩散方式
    linearGradient.setSpread(QGradient::RepeatSpread);
    // 使用渐变作为画刷
    painter.setBrush(linearGradient);
    painter.drawRect(10, 170, 90, 40);

    // 辐射渐变
    QRadialGradient radialGradient(QPointF(200, 190), 50, QPointF(275, 200));
    radialGradient.setColorAt(0, QColor(255, 255, 100, 150));
    radialGradient.setColorAt(1, QColor(0, 0, 0, 50));
    painter.setBrush(radialGradient);
    painter.drawEllipse(QPointF(200, 190), 50, 50);

    // 锥形渐变
    QConicalGradient conicalGradient(QPointF(350, 190), 60);
    conicalGradient.setColorAt(0.2, Qt::cyan);
    conicalGradient.setColorAt(0.9, Qt::black);
    painter.setBrush(conicalGradient);
    painter.drawEllipse(QPointF(350, 190), 50, 50);

    // 画笔使用线性渐变来绘制直线和文字
    painter.setPen(QPen(linearGradient,2));
    painter.drawLine(0, 280, 100, 280);
    painter.drawText(150, 280, tr("helloQt!"));

}
