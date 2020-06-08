#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlaylist>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
//    player->setMedia(QUrl::fromLocalFile("E:/src/13/13-5/myplayer/music.mp3"));
    connect(player, &QMediaPlayer::positionChanged,
            this, &MainWindow::updatePosition);

    connect(player, &QMediaPlayer::stateChanged, this, &MainWindow::stateChanged);
    connect(player, &QMediaPlayer::mediaStatusChanged,
            this, &MainWindow::mediaStatusChanged);
    connect(player, static_cast<void(QMediaPlayer::*)(QMediaPlayer::Error)>
            (&QMediaPlayer::error), this, &MainWindow::showError);

    connect(player, &QMediaPlayer::metaDataAvailableChanged,
            this, &MainWindow::metaDataAvailableChanged);


    playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl::fromLocalFile("E:/src/13/13-5/myplayer/music.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("E:/src/13/13-5/myplayer/music2.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("E:/src/13/13-5/myplayer/music3.mp3"));
    playlist->setCurrentIndex(0);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{ // 播放
    player->play();
}

void MainWindow::on_pushButton_2_clicked()
{ // 暂停
    player->pause();
}

void MainWindow::on_pushButton_3_clicked()
{ // 停止
    player->stop();
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{ // 设置播放进度
    player->setPosition(position * 1000);
}

void MainWindow::updatePosition(qint64 position)
{ // 更新滑块显示
    ui->horizontalSlider->setMaximum(player->duration() / 1000);
    ui->horizontalSlider->setValue(position / 1000);
}

void MainWindow::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    switch (status) {
    case QMediaPlayer::UnknownMediaStatus:
        ui->label->setText(tr("媒体未知状况！"));
        break;
    case QMediaPlayer::NoMedia:
        ui->label->setText(tr("没有媒体文件！"));
        break;
    case QMediaPlayer::BufferingMedia:
        ui->label->setText(tr("正在缓冲媒体文件！"));
        break;
    case QMediaPlayer::BufferedMedia:
        ui->label->setText(tr("媒体文件缓冲完成！"));
        break;
    case QMediaPlayer::LoadingMedia:
        ui->label->setText(tr("正在加载媒体！"));
        break;
    case QMediaPlayer::StalledMedia:
        ui->label->setText(tr("播放停滞！"));
        break;
    case QMediaPlayer::EndOfMedia:
        ui->label->setText(tr("播放结束！"));
        break;
    case QMediaPlayer::LoadedMedia:
        ui->label->setText(tr("媒体加载完成！"));
        break;
    case QMediaPlayer::InvalidMedia:
        ui->label->setText(tr("不可用的媒体文件！"));
        break;
    default: break;
    }
}

void MainWindow::stateChanged(QMediaPlayer::State state)
{
    switch (state) {
    case QMediaPlayer::StoppedState:
        ui->label_2->setText(tr("停止状态！"));
        break;
    case QMediaPlayer::PlayingState:
        ui->label_2->setText(tr("播放状态！"));
        break;
    case QMediaPlayer::PausedState:
        ui->label_2->setText(tr("暂停状态！"));
        break;
    default: break;
    }
}

void MainWindow::showError(QMediaPlayer::Error error)
{
    switch (error) {
    case QMediaPlayer::NoError:
        ui->label_3->setText(tr("没有错误！"));
        break;
    case QMediaPlayer::ResourceError:
        ui->label_3->setText(tr("媒体资源无法被解析！"));
        break;
    case QMediaPlayer::FormatError:
        ui->label_3->setText(tr("不支持该媒体格式！"));
        break;
    case QMediaPlayer::NetworkError:
        ui->label_3->setText(tr("发生了一个网络错误！"));
        break;
    case QMediaPlayer::AccessDeniedError:
        ui->label_3->setText(tr("没有播放权限！"));
        break;
    case QMediaPlayer::ServiceMissingError:
        ui->label_3->setText(tr("没有发现有效的播放服务！"));
        break;
    default: break;
    }
}

// 获取元数据
void MainWindow::metaDataAvailableChanged(bool available)
{
    if(available) {
        QString title = player->metaData("Title").toString();
        QString author = player->metaData("Author").toString();
        setWindowTitle(title + "-" + author);
    }
}


