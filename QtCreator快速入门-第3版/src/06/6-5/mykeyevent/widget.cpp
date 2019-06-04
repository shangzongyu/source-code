#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setFocus();                                          // 使主界面获得焦点

    keyUp = false;        // 初始化变量
    keyLeft = false;
    move = false;

}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)       // 键盘按下事件
{
    //    if(event->key() == Qt::Key_Up){                  // 如果是向上方向键
    //        qDebug() << "press:"<<event->isAutoRepeat(); // 是否自动重复
    //    }

    if (event->key() == Qt::Key_Up) {
        if(event->isAutoRepeat()) return;    // 按键重复时不做处理
        keyUp = true;                        // 标记向上方向键已经按下
    }
    else if (event->key() == Qt::Key_Left) {
        if (event->isAutoRepeat()) return;
        keyLeft = true;
    }

}

void Widget::keyReleaseEvent(QKeyEvent *event)     // 按键释放事件
{
    //    if(event->key() == Qt::Key_Up){
    //        qDebug() << "release:"<< event->isAutoRepeat();
    //        qDebug() << "up";
    //    }

    if (event->key() == Qt::Key_Up) {
        if (event->isAutoRepeat()) return;
        keyUp = false;                      // 释放按键后将标志设置为false
        if (move) {                         // 如果已经完成了移动
            move = false;                   // 设置标志为false
            return;                         // 直接返回
        }
        if (keyLeft) {                       // 如果向左方向键已经按下且没有释放
            ui->pushButton->move(30, 80);    // 斜移
            move = true;                    // 标记已经移动
        } else {                            // 否则直接上移
            ui->pushButton->move(120, 80);
        }
    }
    else if (event->key() == Qt::Key_Left) {
        if (event->isAutoRepeat()) return;
        keyLeft = false;
        if (move) {
            move = false;
            return;
        }
        if (keyUp) {
            ui->pushButton->move(30, 80);
            move = true;
        } else {
            ui->pushButton->move(30, 120);
        }
    }
    else if (event->key() == Qt::Key_Down) {
        ui->pushButton->move(120, 120);  // 使用向下方向键来还原按钮的位置
    }

}
