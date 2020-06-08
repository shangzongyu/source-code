#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    QPushButton *button = new QPushButton(this); // 创建按钮
    button->setObjectName("myButton");           // 指定按钮的对象名
    ui->setupUi(this);                      // 要在定义了部件以后再调用这个函数
}


Widget::~Widget()
{
    delete ui;
}

void Widget::on_myButton_clicked()          // 使用自动关联
{
    close();
}

