#include "client.h"
#include "ui_client.h"
#include <QtNetwork>

Client::Client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Client::readMessage);
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

}

Client::~Client()
{
    delete ui;
}

void Client::newConnect()
{
    // 初始化数据大小信息为0
    blockSize = 0;

    // 取消已有的连接
    tcpSocket->abort();
    tcpSocket->connectToHost(ui->hostLineEdit->text(),
                             ui->portLineEdit->text().toInt());
}

void Client::readMessage()
{
    QDataStream in(tcpSocket);
    // 设置数据流版本，这里要和服务器端相同
    in.setVersion(QDataStream::Qt_5_6);

    // 如果是刚开始接收数据
    if (blockSize == 0) {
        //判断接收的数据是否大于两字节，也就是文件的大小信息所占的空间
        //如果是则保存到blockSize变量中，否则直接返回，继续接收数据
        if(tcpSocket->bytesAvailable() < (int)sizeof(quint16)) return;
        in >> blockSize;
    }
    // 如果没有得到全部的数据，则返回，继续接收数据
    if(tcpSocket->bytesAvailable() < blockSize) return;
    // 将接收到的数据存放到变量中
    in >> message;
    // 显示接收到的数据
    ui->messageLabel->setText(message);
}

void Client::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpSocket->errorString();
}

void Client::on_connectButton_clicked()
{
    newConnect();
}
