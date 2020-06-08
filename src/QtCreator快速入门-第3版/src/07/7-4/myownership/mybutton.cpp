#include "mybutton.h"
#include <QDebug>
MyButton::MyButton(QWidget *parent) :
    QPushButton(parent)
{
}

MyButton::~MyButton()
{
    qDebug() << "delete button";
}
