#include "widget.h"
#include "ui_widget.h"
#include "mylineedit.h"
#include <QKeyEvent>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    lineEdit = new MyLineEdit(this);
    lineEdit->move(100, 100);

    lineEdit->installEventFilter(this);   // 在Widget上为lineEdit安装事件过滤器
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    qDebug() << tr("Widget键盘按下事件");
}

bool Widget::eventFilter(QObject *obj, QEvent *event) // 事件过滤器
{
    if(obj == lineEdit){              // 如果是lineEdit部件上的事件
        if(event->type() == QEvent::KeyPress)
            qDebug() << tr("Widget的事件过滤器");
    }
    return QWidget::eventFilter(obj, event);
}

