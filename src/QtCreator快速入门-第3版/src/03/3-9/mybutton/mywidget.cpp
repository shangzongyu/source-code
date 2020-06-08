#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>
#include <QMenu>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    ui->pushBtn1->setText(tr("&nihao"));   // 这样便指定了Alt+N为加速键
    ui->pushBtn2->setText(tr("帮助(&H)"));
    ui->pushBtn2->setIcon(QIcon("../mybutton/images/help.png"));
    ui->pushBtn3->setText(tr("z&oom"));
    QMenu *menu = new QMenu(this);
    menu->addAction(QIcon("../mybutton/images/zoom-in.png"), tr("放大"));
    ui->pushBtn3->setMenu(menu);

}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushBtn1_toggled(bool checked)
{
    qDebug() << tr("按钮是否按下：") << checked;
}
