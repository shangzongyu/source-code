#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class WebView;
class QLineEdit;

class QNetworkAccessManager;

#include <QModelIndex>
class QListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    WebView *createView();

private:
    Ui::MainWindow *ui;
    WebView *view;

    QLineEdit *locationEdit;
    int progress;

    QNetworkAccessManager *manager;

    QListWidget *historyList;

    QLineEdit *findEdit;


protected slots:
    void changeLocation(); // 改变路径
    void setProgress(int); // 更新进度
    void adjustTitle();    // 更新标题显示
    void finishLoading(bool); // 加载完成后进行处理

    void handleIconUrlChanged(const QUrl &url);
    void handleIconLoaded();

    void showHistory(); // 显示历史记录
    void gotoHistory(const QModelIndex &index); // 转到历史记录

};

#endif // MAINWINDOW_H
