#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QBitmap>
#include <QPicture>
#include <QDebug>
#include <QDesktopWidget>
#include <QLabel>
#include <QWindow>
#include <QScreen>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QWindow window;
    QPixmap grab =  window.screen()->grabWindow(QApplication::desktop()->winId());
    grab.save("../mydrawing3/screen.png");
    QLabel *label = new QLabel(this);
    label->resize(400, 200);
    QPixmap pix = grab.scaled(label->size(), Qt::KeepAspectRatio,
                                Qt::SmoothTransformation);
    label->setPixmap(pix);
    label->move(0, 100);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load("../mydrawing3/yafeilinux.png");
    painter.drawPixmap(0, 0, pix.width(), pix.height(), pix);
    painter.setBrush(QColor(255, 255, 255, 100));
    painter.drawRect(0, 0, pix.width(), pix.height());
    painter.drawPixmap(100, 0, pix.width(), pix.height(), pix);
    painter.setBrush(QColor(0, 0, 255, 100));
    painter.drawRect(100, 0, pix.width(), pix.height());

}
