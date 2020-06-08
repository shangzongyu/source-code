#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stringdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    StringDialog *dlg = new StringDialog(this);

    connect(dlg, &StringDialog::stringChanged, [=](QString str) {
        if (str == "qt")
            ui->stringLabel->setText("hello qt!");
        else ui->stringLabel->setText("error!");
        });

    dlg->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showString(QVariant str)
{
    ui->stringLabel->setText(str.toString());
}
