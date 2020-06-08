#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
class QTcpServer;

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
    QTcpServer *tcpServer;

private slots:
    void sendMessage();

};

#endif // SERVER_H
