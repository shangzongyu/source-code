#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyleFactory>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setStyle(QStyleFactory::create("windows"));

    // 获取pushButton的调色板
    QPalette palette1 = ui->pushButton->palette();
    // 设置按钮文本颜色为红色
    palette1.setColor(QPalette::ButtonText, Qt::red);
    // 设置按钮背景色为绿色
    palette1.setColor(QPalette::Button, Qt::green);
    // pushButton使用修改后的调色板
    ui->pushButton->setPalette(palette1);
    // 设置spinBox不可用
    ui->spinBox->setDisabled(true);
    QPalette palette2 = ui->spinBox->palette();
    // 设置spinBox不可用时的背景颜色为蓝色
    palette2.setColor(QPalette::Disabled,QPalette::Base,Qt::blue);
    ui->spinBox->setPalette(palette2);

}

MainWindow::~MainWindow()
{
    delete ui;
}
