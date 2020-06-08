#include "widget.h"
#include "ui_widget.h"
#include <QAudioRecorder>
#include <QDebug>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    audioRecorder = new QAudioRecorder;

    QStringList inputs = audioRecorder->audioInputs();
    ui->comboBox->addItems(inputs);

    connect(audioRecorder, &QAudioRecorder::durationChanged, this,
            &Widget::updateProgress);

    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/pcm");
    audioSettings.setQuality(QMultimedia::HighQuality);
    audioRecorder->setAudioSettings(audioSettings);
}

Widget::~Widget()
{
    delete ui;
}

// 选择按钮
void Widget::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName();
    ui->lineEdit->setText(fileName);
}

// 开始按钮
void Widget::on_pushButton_2_clicked()
{
    audioRecorder->setAudioInput(ui->comboBox->currentText());
    audioRecorder->setOutputLocation(QUrl::fromLocalFile(ui->lineEdit->text()));
    audioRecorder->record();
}

// 停止按钮
void Widget::on_pushButton_4_clicked()
{
    audioRecorder->stop();
}

void Widget::updateProgress(qint64 duration)
{
    if (audioRecorder->error() != QMediaRecorder::NoError || duration < 1000)
        return;

    setWindowTitle(tr("Recorded %1 sec").arg(duration / 1000));
}
