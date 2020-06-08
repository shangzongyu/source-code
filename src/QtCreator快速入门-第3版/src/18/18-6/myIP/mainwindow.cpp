#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
    qDebug() << "localHostName: " << localHostName << endl
             << "IP Address: " << info.addresses();

    foreach (QHostAddress address, info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            qDebug() << address.toString();
    }

    QHostInfo::lookupHost("www.baidu.com", this, SLOT(lookedUp(QHostInfo)));

    // 获取所有网络接口的列表
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();

    // 遍历每一个网络接口
    foreach (QNetworkInterface interface, list)
    {
        // 接口名称
        qDebug() << "Name: " << interface.name();

        // 硬件地址
        qDebug() << "HardwareAddress: " << interface.hardwareAddress();

        // 获取IP地址条目列表，每个条目包含一个IP地址，一个子网掩码和一个广播地址
        QList<QNetworkAddressEntry> entryList = interface.addressEntries();

        // 遍历每一个IP地址条目
        foreach (QNetworkAddressEntry entry, entryList)
        {
            // IP地址
            qDebug() << "IP Address: " << entry.ip().toString();

            // 子网掩码
            qDebug() << "Netmask: " << entry.netmask().toString();

            // 广播地址
            qDebug() << "Broadcast: " << entry.broadcast().toString();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::lookedUp(const QHostInfo &host)
{
    if (host.error() != QHostInfo::NoError) {
        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }
    foreach (const QHostAddress &address, host.addresses())
        qDebug() << "Found address:" << address.toString();
}

