#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSoundEffect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    effect = new QSoundEffect(this);
    effect->setSource(QUrl::fromLocalFile("../mysoundeffect/sound.wav"));
    effect->setVolume(0.25f);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 播放按钮
void MainWindow::on_pushButton_clicked()
{
    effect->play();
}
// 停止按钮
void MainWindow::on_pushButton_2_clicked()
{
    effect->stop();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    effect->setLoopCount(arg1);
}
