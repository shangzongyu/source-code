#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QAbstractSocket>
#include <QTcpServer>
class QTcpSocket;
class QFile;

namespace Ui {
class Server;
}

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private:
    Ui::Server *ui;

    QTcpServer tcpServer;
    QTcpSocket *tcpServerConnection;
    qint64 totalBytes;     // 存放总大小信息
    qint64 bytesReceived;  // 已收到数据的大小
    qint64 fileNameSize;   // 文件名的大小信息
    QString fileName;      // 存放文件名
    QFile *localFile;      // 本地文件
    QByteArray inBlock;    // 数据缓冲区

private slots:
    void start();
    void acceptConnection();
    void updateServerProgress();
    void displayError(QAbstractSocket::SocketError socketError);


    void on_startButton_clicked();
};

#endif // SERVER_H
