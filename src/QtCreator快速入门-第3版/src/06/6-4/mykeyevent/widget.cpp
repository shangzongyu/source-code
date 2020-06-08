#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>

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

void Widget::keyPressEvent(QKeyEvent *event)       // 键盘按下事件
{
    if(event->modifiers() == Qt::ControlModifier){ // 是否按下Ctrl键
        if(event->key() == Qt::Key_M)              // 是否按下M键
            setWindowState(Qt::WindowMaximized);   // 窗口最大化
    }
    else QWidget::keyPressEvent(event);
}

void Widget::keyReleaseEvent(QKeyEvent *event)     // 按键释放事件
{
    // 其他操作
}
