#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QActionGroup;
QT_END_NAMESPACE

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
    void on_actionQuit_triggered();

    void changeBrush();

private:
    void loadPlugins();

private:
    Ui::MainWindow *ui;

    QActionGroup *brushActionGroup;
};

#endif // MAINWINDOW_H
