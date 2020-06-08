#include "widget.h"
#include "ui_widget.h"
#include <QMouseEvent>
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    pix = QPixmap(400, 300);
    pix.fill(Qt::white);
    tempPix = pix;
    isDrawing = false;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        // 当鼠标左键按下时获取当前位置作为矩形的开始点
        startPoint = event->pos();
        // 标记正在绘图
        isDrawing = true;
    }
}
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton) {
        // 当按着鼠标左键进行移动时，获取当前位置作为结束点，绘制矩形
        endPoint = event->pos();
        // 将缓冲区的内容复制到临时缓冲区，这样进行动态绘制时，
        // 每次都是在缓冲区图像的基上进行绘制，就不会产生拖影现象了
        tempPix = pix;
        // 更新显示
        update();
    }
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        // 当鼠标左键松开时，获取当前位置为结束点，完成矩形绘制
        endPoint = event->pos();
        // 标记已经结束绘图
        isDrawing = false;
        update();
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    int x = startPoint.x();
    int y = startPoint.y();
    int width = endPoint.x() - x;
    int height = endPoint.y() - y;
    QPainter painter;
    painter.begin(&tempPix);
    painter.drawRect(x, y, width, height);
    painter.end();
    painter.begin(this);
    painter.drawPixmap(0, 0, tempPix);
    // 如果已经完成了绘制，那么更新缓冲区
    if(!isDrawing)
        pix = tempPix;
}

