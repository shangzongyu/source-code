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
    QRectF rect(10.0, 10.0, 380.0, 280.0);
    painter.setPen(Qt::red);
    painter.drawRect(rect);
    painter.setPen(Qt::blue);
    painter.drawText(rect, Qt::AlignHCenter, tr("AlignHCenter"));
    painter.drawText(rect, Qt::AlignLeft, tr("AlignLeft"));
    painter.drawText(rect, Qt::AlignRight, tr("AlignRight"));
    painter.drawText(rect, Qt::AlignVCenter, tr("AlignVCenter"));
    painter.drawText(rect, Qt::AlignBottom, tr("AlignBottom"));
    painter.drawText(rect, Qt::AlignCenter, tr("AlignCenter"));
    painter.drawText(rect, Qt::AlignBottom | Qt::AlignRight,
                     tr("AlignBottom\nAlignRight"));

    QFont font("宋体", 15, QFont::Bold, true);
    //设置下划线
    font.setUnderline(true);
    //设置上划线
    font.setOverline(true);
    //设置字母大小写
    font.setCapitalization(QFont::SmallCaps);
    //设置字符间的间距
    font.setLetterSpacing(QFont::AbsoluteSpacing, 10);
    //使用字体
    painter.setFont(font);
    painter.setPen(Qt::green);
    painter.drawText(120, 80, tr("yafeilinux"));

    painter.translate(100, 100);
    painter.rotate(90);
    painter.drawText(0, 0, tr("helloqt"));

}
