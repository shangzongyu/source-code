#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class Assistant;

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
    Assistant *assistant;

private slots:
    void startAssistant();

};

#endif // MAINWINDOW_H
