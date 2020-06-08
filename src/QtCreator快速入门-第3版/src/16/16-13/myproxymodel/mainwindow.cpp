#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
#include <QSortFilterProxyModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList list;
    list << "yafei" << "yafeilinux" << "Qt" << "Qt Creator";
    QStringListModel *listModel = new QStringListModel(list, this);
    filterModel = new QSortFilterProxyModel(this);

    // 为代理模型添加源模型
    filterModel->setSourceModel(listModel);

    // 在视图中使用代理模型
    ui->listView->setModel(filterModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QRegExp rx(ui->lineEdit->text());
    filterModel->setFilterRegExp(rx);
}
