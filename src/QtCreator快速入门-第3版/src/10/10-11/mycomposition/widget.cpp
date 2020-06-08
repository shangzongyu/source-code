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
    QPainter painter;
    QImage image(400, 300, QImage::Format_ARGB32_Premultiplied);
    painter.begin(&image);
    painter.setBrush(Qt::green);
    painter.drawRect(100, 50, 200, 200);
    painter.setBrush(QColor(0, 0, 255, 150));
    painter.drawRect(50, 0, 100, 100);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawRect(250, 0, 100, 100);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.drawRect(50, 200, 100, 100);
    painter.setCompositionMode(QPainter::CompositionMode_Xor);
    painter.drawRect(250, 200, 100, 100);
    painter.end();
    painter.begin(this);
    painter.drawImage(0, 0, image);
}
