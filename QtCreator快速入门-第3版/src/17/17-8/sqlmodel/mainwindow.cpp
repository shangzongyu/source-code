#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRelationalDelegate>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this);
    model->setTable("student");
    model->setRelation(2, QSqlRelation("course", "id", "name"));
    model->select();

    QTableView *view = new QTableView(this);
    view->setModel(model);
    setCentralWidget(view);

    view->setItemDelegate(new QSqlRelationalDelegate(view));
}

MainWindow::~MainWindow()
{
    delete ui;
}
