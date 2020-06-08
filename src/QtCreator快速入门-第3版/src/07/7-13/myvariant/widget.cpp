#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QVariant v1(15);
    qDebug() << v1.toInt();                     // 结果为15
    QVariant v2(12.3);
    qDebug() << v2.toFloat();                   // 结果为12.3
    QVariant v3("nihao");
    qDebug() << v3.toString();                  // 结果为"nihao"
    QColor color = QColor(Qt::red);
    QVariant v4 = color;
    qDebug() << v4.type();                      // 结果为QVariant::QColor
    qDebug() << v4.value<QColor>();             // 结果为QColor(ARGB 1,1,0,0)
    QString str = "hello";
    QVariant v5 = str;
    qDebug() << v5.canConvert(QVariant::Int);   // 结果为true
    qDebug() << v5.toString();                  // 结果为"hello"
    qDebug() << v5.convert(QVariant::Int);      // 结果为false
    qDebug() << v5.toString();                  // 转换失败，v5被清空，结果为"0"

}

Widget::~Widget()
{
    delete ui;
}
