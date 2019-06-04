#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

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

    void showResult();
    void showState(QProcess::ProcessState);
    void showError();
    void showFinished(int, QProcess::ExitStatus);


private:
    Ui::MainWindow *ui;
    QProcess myProcess;
};

#endif // MAINWINDOW_H
