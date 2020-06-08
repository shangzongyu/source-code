#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QAbstractSocket>
class QTcpSocket;

namespace Ui {
class Client;
}

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

private:
    Ui::Client *ui;
    QTcpSocket *tcpSocket;
    QString message;
    // 用来存放数据的大小信息
    quint16 blockSize;

private slots:
    void newConnect();
    void readMessage();
    void displayError(QAbstractSocket::SocketError);


    void on_connectButton_clicked();
};

#endif // CLIENT_H
