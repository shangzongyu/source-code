#include "mydesignerplugin.h"
#include <QPushButton>
#include <QHBoxLayout>

MyDesignerPlugin::MyDesignerPlugin(QWidget *parent) :
    QWidget(parent)
{
    QPushButton *button1 = new QPushButton(this);
    QPushButton *button2 = new QPushButton(this);
    button1->setText("hello");
    button2->setText("Qt!");
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(button1);
    layout->addWidget(button2);
    setLayout(layout);

}
