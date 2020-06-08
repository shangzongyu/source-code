#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLabel *label = new QLabel(this);
    label->setText(tr("hello Qt!"));
    label->move(100,50);

    QLabel *label2 = new QLabel(this);
    label2->setText(tr("password", "mainwindow"));
    label2->move(100,80);

    QLabel *label3 = new QLabel(this);
    int id = 123;
    QString name = "yafei";
    label3->setText(tr("ID is %1,Name is %2").arg(id).arg(name));
    label3->resize(150, 12);
    label3->move(100, 120);
}

MainWindow::~MainWindow()
{
    delete ui;
}
