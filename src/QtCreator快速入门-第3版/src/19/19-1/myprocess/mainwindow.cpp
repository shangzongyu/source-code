#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&myProcess, &QProcess::readyRead, this, &MainWindow::showResult);
    connect(&myProcess, &QProcess::stateChanged,
            this, &MainWindow::showState);
    connect(&myProcess, &QProcess::errorOccurred,
            this, &MainWindow::showError);
    connect(&myProcess, SIGNAL(finished(int,QProcess::ExitStatus)),
            this, SLOT(showFinished(int, QProcess::ExitStatus)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString program = "cmd.exe";
    QStringList arguments;
    arguments << "/c dir&pause";
    myProcess.start(program, arguments);
}

void MainWindow::showResult()
{
    QTextCodec *codec = QTextCodec::codecForLocale();
    qDebug() << "showResult: " << endl << codec->toUnicode(myProcess.readAll());
}

void MainWindow::showState(QProcess::ProcessState state)
{
    qDebug() << "showState: ";
    if (state == QProcess::NotRunning) {
        qDebug() << "Not Running";
    } else if (state == QProcess::Starting) {
        qDebug() << "Starting";
    }  else {
        qDebug() << "Running";
    }
}

void MainWindow::showError()
{
    qDebug() << "showError: " << endl << myProcess.errorString();
}

void MainWindow::showFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "showFinished: " << endl << exitCode << exitStatus;
}


