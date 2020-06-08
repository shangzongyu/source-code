#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void showTextFrame();            // 遍历文档框架
    void showTextBlock();            // 遍历所有文本块
    void setTextFont(bool checked);  // 设置字体格式

    void insertTable();              // 插入表格
    void insertList();               // 插入列表
    void insertImage();              // 插入图片

};

#endif // MAINWINDOW_H
