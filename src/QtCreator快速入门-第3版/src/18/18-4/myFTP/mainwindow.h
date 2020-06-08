#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QFtp;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFtp *ftp;

private slots:
    void ftpCommandStarted(int);
    void ftpCommandFinished(int, bool);

};

#endif // MAINWINDOW_H
