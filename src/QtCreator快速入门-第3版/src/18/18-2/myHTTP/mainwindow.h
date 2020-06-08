#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QNetworkReply;
class QNetworkAccessManager;
#include <QUrl>
class QFile;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startRequest(QUrl url);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QUrl url;
    QFile *file;

private slots:
    void httpFinished();
    void httpReadyRead();
    void updateDataReadProgress(qint64, qint64);

    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
