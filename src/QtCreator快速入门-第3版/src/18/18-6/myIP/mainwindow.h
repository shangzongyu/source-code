#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QHostInfo;


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


private slots:
    void lookedUp(const QHostInfo &host);

};

#endif // MAINWINDOW_H
