#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QFile *qssFile;
};

#endif // MAINWINDOW_H
