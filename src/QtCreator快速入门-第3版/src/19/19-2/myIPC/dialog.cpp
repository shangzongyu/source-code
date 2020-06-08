#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QBuffer>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    sharedMemory.setKey("QSharedMemoryExample");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::loadFromFile()
{
    if (sharedMemory.isAttached())
        detach();
    ui->label->setText(tr("选择一个图片文件！"));
    QString fileName = QFileDialog::getOpenFileName(0, QString(), QString(),
                                                    tr("Images (*.png *.jpg)"));
    QImage image;
    if (!image.load(fileName)) {
        ui->label->setText(tr("选择的文件不是图片，请选择图片文件！"));
        return;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));

    // 将图片加载到共享内存
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << image;
    int size = buffer.size();
    if (!sharedMemory.create(size)) {
        ui->label->setText(tr("无法创建共享内存段！"));
        return;
    }
    sharedMemory.lock();
    char *to = (char*)sharedMemory.data();
    const char *from = buffer.data().data();
    memcpy(to, from, qMin(sharedMemory.size(), size));
    sharedMemory.unlock();
}

void Dialog::loadFromMemory()
{
    if (!sharedMemory.attach()) {
        ui->label->setText(tr("无法连接到共享内存段，\n"
                              "请先加载一张图片！"));
        return;
    }
    QBuffer buffer;
    QDataStream in(&buffer);
    QImage image;

    sharedMemory.lock();
    buffer.setData((char*)sharedMemory.constData(), sharedMemory.size());
    buffer.open(QBuffer::ReadOnly);
    in >> image;
    sharedMemory.unlock();

    sharedMemory.detach();
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void Dialog::detach()
{
    if (!sharedMemory.detach())
        ui->label->setText(tr("无法从共享内存中分离！"));
}


void Dialog::on_loadFromFileButton_clicked()
{
    loadFromFile();
}

void Dialog::on_loadFromSharedMemoryButton_clicked()
{
    loadFromMemory();
}
