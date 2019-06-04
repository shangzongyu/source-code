#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWhatsThis>
#include "assistant.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAction *action = QWhatsThis::createAction(this);
    ui->mainToolBar->addAction(action);

    QAction *help = new QAction("help",this);
    ui->mainToolBar->addAction(help);
    connect(help, &QAction::triggered, this, &MainWindow::startAssistant);

    // 创建Assistant对象
    assistant = new Assistant;

}

MainWindow::~MainWindow()
{
    delete ui;
    // 销毁assistant
    delete assistant;
}

void MainWindow::startAssistant()
{
    // 按下“help”按钮，运行Qt Assistant，显示index.html页面
    assistant->showDocumentation("index.html");
}

