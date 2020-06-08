#include "myaction.h"
#include <QLineEdit>
#include <QSplitter>
#include <QLabel>


MyAction::MyAction(QObject *parent) :
    QWidgetAction(parent)
{
    // 创建行编辑器
    lineEdit = new QLineEdit;

    // 将行编辑器的按下回车键信号与我们的发送文本槽关联
    connect(lineEdit, &QLineEdit::returnPressed, this, &MyAction::sendText);
}

QWidget * MyAction::createWidget(QWidget *parent) //创建部件
{
    // 这里使用inherits()函数判断父部件是否是菜单或者工具栏
    // 如果是，则创建该父部件的子部件，并且返回子部件
    // 如果不是，则直接返回0
    if(parent->inherits("QMenu") || parent->inherits("QToolBar")){
        QSplitter *splitter = new QSplitter(parent);
        QLabel *label = new QLabel;
        label->setText(tr("插入文本："));
        splitter->addWidget(label);
        splitter->addWidget(lineEdit);
        return splitter;
    }
    return 0;
}

void MyAction::sendText()
{
    emit getText(lineEdit->text());   // 发射信号，将行编辑器中的内容发射出去
    lineEdit->clear();                // 清空行编辑器中的内容
}
