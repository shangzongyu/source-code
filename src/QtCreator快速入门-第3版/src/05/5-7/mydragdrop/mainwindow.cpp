#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDragEnterEvent>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) // 拖动进入事件
{
    if(event->mimeData()->hasUrls())                    // 数据中是否包含URL
        event->acceptProposedAction();                  // 如果是则接收动作
    else event->ignore();                               // 否则忽略该事件
}
void MainWindow::dropEvent(QDropEvent *event)           // 放下事件
{
    const QMimeData *mimeData = event->mimeData();      // 获取MIME数据
    if(mimeData->hasUrls()){                            // 如果数据中包含URL
        QList<QUrl> urlList = mimeData->urls();         // 获取URL列表
        // 将其中第一个URL表示为本地文件路径
        QString fileName = urlList.at(0).toLocalFile();
        if(!fileName.isEmpty()){                        // 如果文件路径不为空
            QFile file(fileName);     // 建立QFile对象并且以只读方式打开该文件
            if(!file.open(QIODevice::ReadOnly)) return;
            QTextStream in(&file);                      // 建立文本流对象
            ui->textEdit->setText(in.readAll());  // 将文件中所有内容读入编辑器
        }
    }
}
