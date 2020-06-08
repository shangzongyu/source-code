#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //    // 设置pushButton的背景为黄色
    //    ui->pushButton->setStyleSheet("background:yellow");
    //    // 设置horizontalSlider的背景为蓝色
    //    ui->horizontalSlider->setStyleSheet("background:blue");

    //    setStyleSheet("QPushButton{background:yellow}QSlider{background:blue}");

    qssFile = new QFile(":/qss/my.qss", this);
    // 只读方式打开该文件
    qssFile->open(QFile::ReadOnly);
    // 读取文件全部内容，使用tr()函数将其转换为QString类型
    QString styleSheet = tr(qssFile->readAll());
    // 为QApplication设置样式表
    qApp->setStyleSheet(styleSheet);
    qssFile->close();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(qssFile->fileName() == ":/qss/my.qss")
        qssFile->setFileName(":/qss/my1.qss");
    else qssFile->setFileName(":/qss/my.qss");
    qssFile->open(QFile::ReadOnly);
    QString styleSheet = tr(qssFile->readAll());
    qApp->setStyleSheet(styleSheet);
    qssFile->close();
}
