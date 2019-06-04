#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMovie>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置标签的对齐方式为居中对齐、自动填充背景为暗色
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setBackgroundRole(QPalette::Dark);
    ui->label->setAutoFillBackground(true);
    movie = new QMovie(this);
    movie->setFileName("../mymovie/movie.gif");
    // 设置缓存模式
    movie->setCacheMode(QMovie::CacheAll);
    // 设置动画大小为标签的大小
    QSize size = ui->label->size();
    movie->setScaledSize(size);
    ui->label->setMovie(movie);
    // 设置水平滑块的最大最小值，当动画播放时自动更改滑块的值
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(movie->frameCount());
    connect(movie, &QMovie::frameChanged,
            ui->horizontalSlider, &QSlider::setValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{// 播放进度
    movie->jumpToFrame(value);
}

void MainWindow::on_pushButton_clicked()
{// 开始按钮
    movie->start();
}

void MainWindow::on_pushButton_2_toggled(bool checked)
{// 暂停按钮
    movie->setPaused(checked);
}

void MainWindow::on_pushButton_3_clicked()
{// 停止按钮
    movie->stop();
}

void MainWindow::on_pushButton_4_clicked()
{// 截屏按钮
    int id = movie->currentFrameNumber();
    QPixmap pix = movie->currentPixmap();
    pix.save(QString("../mymovie/%1.png").arg(id));
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{// 播放速度
    movie->setSpeed(arg1);
}
