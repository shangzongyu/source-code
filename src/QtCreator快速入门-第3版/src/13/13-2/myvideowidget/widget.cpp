#include "widget.h"
#include "ui_widget.h"
#include <QMediaPlayer>
#include <QVideoWidget>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    videoWidget->resize(600, 300);
    player->setVideoOutput(videoWidget);
    player->setMedia(QUrl::fromLocalFile("../myvideowidget/video.wmv"));
    player->play();

    // 亮度
    ui->brightnessSlider->setValue(videoWidget->brightness());
    connect(ui->brightnessSlider, &QSlider::sliderMoved,
            videoWidget, &QVideoWidget::setBrightness);
    connect(videoWidget, &QVideoWidget::brightnessChanged,
            ui->brightnessSlider, &QSlider::setValue);
    // 对比度
    ui->contrastSlider->setValue(videoWidget->contrast());
    connect(ui->contrastSlider, &QSlider::sliderMoved,
            videoWidget, &QVideoWidget::setContrast);
    connect(videoWidget, &QVideoWidget::contrastChanged,
            ui->contrastSlider, &QSlider::setValue);
    // 色相
    ui->hueSlider->setValue(videoWidget->hue());
    connect(ui->hueSlider, &QSlider::sliderMoved,
            videoWidget, &QVideoWidget::setHue);
    connect(videoWidget, &QVideoWidget::hueChanged,
            ui->hueSlider, &QSlider::setValue);
    // 饱和度
    ui->saturationSlider->setValue(videoWidget->saturation());
    connect(ui->saturationSlider, &QSlider::sliderMoved,
            videoWidget, &QVideoWidget::setSaturation);
    connect(videoWidget, &QVideoWidget::saturationChanged,
            ui->saturationSlider, &QSlider::setValue);
}

Widget::~Widget()
{
    delete ui;
}
