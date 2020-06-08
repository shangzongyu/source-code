#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QBitmap>
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //    QPixmap pixmap(":/image/yafeilinux.png");
    //    ui->label->setPixmap(pixmap);
    //    ui->label->setMask(pixmap.mask());


    QPixmap pix;
    // 加载图片
    pix.load(":/image/yafeilinux.png");
    // 设置窗口大小为图片大小
    resize(pix.size());
    // 为窗口设置遮罩
    setMask(pix.mask());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // 从窗口左上角开始绘制图片
    painter.drawPixmap(0, 0, QPixmap(":/image/yafeilinux.png"));
}

void Widget::mousePressEvent(QMouseEvent *)
{   // 关闭窗口
    close();
}

