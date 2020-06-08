#include "mylineedit.h"
#include <QKeyEvent>
#include <QDebug>

MyLineEdit::MyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{

}

void MyLineEdit::keyPressEvent(QKeyEvent *event) // 键盘按下事件
{
    qDebug() << tr("MyLineEdit键盘按下事件");
    QLineEdit::keyPressEvent(event);          // 执行QLineEdit类的默认事件处理
    event->ignore();                          // 忽略该事件
}


bool MyLineEdit::event(QEvent *event)  // 事件
{
    if(event->type() == QEvent::KeyPress)
        qDebug() << tr("MyLineEdit的event()函数");
    return QLineEdit::event(event);   // 执行QLineEdit类event()函数的默认操作
}
