#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>
#include <QLineEdit>

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include <QListWidget>
#include <QWebEngineHistory>

#include "webview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    view = new WebView(this);
    view->load(QUrl("http://www.qter.org/"));
    setCentralWidget(view);
    resize(1024, 680);

    progress = 0;

    // 关联信号和槽
    connect(view, &QWebEngineView::loadProgress, this, &MainWindow::setProgress);
    connect(view, &QWebEngineView::titleChanged, this, &MainWindow::adjustTitle);
    connect(view, &QWebEngineView::loadFinished, this, &MainWindow::finishLoading);

    locationEdit = new QLineEdit(this);
    locationEdit->setText("http://www.qter.org/");
    connect(locationEdit, &QLineEdit::returnPressed, this, &MainWindow::changeLocation);

    // 向工具栏添加动作和部件
    ui->mainToolBar->addAction(view->pageAction(QWebEnginePage::Back));
    ui->mainToolBar->addAction(view->pageAction(QWebEnginePage::Forward));
    ui->mainToolBar->addAction(view->pageAction(QWebEnginePage::Reload));
    ui->mainToolBar->addAction(view->pageAction(QWebEnginePage::Stop));
    ui->mainToolBar->addWidget(locationEdit);

    connect(view, &QWebEngineView::iconUrlChanged,
            this, &MainWindow::handleIconUrlChanged);
    manager = new QNetworkAccessManager(this);

    QMenu *viewMenu = new QMenu(tr("查看"));
    QAction *zoomIn = viewMenu->addAction(tr("放大"));
    zoomIn->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Plus));
    connect(zoomIn, &QAction::triggered, [this]() {
        view->setZoomFactor(view->zoomFactor() + 0.1);
        ui->statusBar->showMessage(tr("缩放%1%").arg(view->zoomFactor()*100));
    });
    QAction *zoomOut = viewMenu->addAction(tr("缩小"));
    zoomOut->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Minus));
    connect(zoomOut, &QAction::triggered, [this]() {
        view->setZoomFactor(view->zoomFactor() - 0.1);
        ui->statusBar->showMessage(tr("缩放%1%").arg(view->zoomFactor()*100));
    });
    QAction *resetZoom = viewMenu->addAction(tr("重置"));
    resetZoom->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_0));
    connect(resetZoom, &QAction::triggered, [this]() {
        view->setZoomFactor(1.0);
        ui->statusBar->showMessage(tr("缩放%1%").arg(view->zoomFactor()*100));
    });
    menuBar()->addMenu(viewMenu);

    ui->mainToolBar->addAction(tr("历史"), this, SLOT(showHistory()));
    historyList = new QListWidget;
    historyList->setWindowTitle(tr("历史记录"));
    historyList->setMinimumWidth(300);
    connect(historyList, &QListWidget::clicked, this, &MainWindow::gotoHistory);

    findEdit = new QLineEdit(this);
    findEdit->setMaximumWidth(150);
    ui->mainToolBar->addWidget(findEdit);
    ui->mainToolBar->addAction(tr("查找"), [this]() {
        view->findText(findEdit->text());
    });
}



MainWindow::~MainWindow()
{
    delete ui;
}


// 地址栏按下回车处理槽
void MainWindow::changeLocation()
{
    QUrl url = QUrl(locationEdit->text());
    view->load(url);
    view->setFocus();
}

void MainWindow::setProgress(int p)
{
    progress = p;
    adjustTitle();
}

// 调整标题槽
void MainWindow::adjustTitle()
{
    if ( progress <= 0 || progress >= 100) {
        setWindowTitle(view->title());
    } else {
        setWindowTitle(QString("%1 (%2%)").arg(view->title()).arg(progress));
    }
}

// 加载完成处理槽
void MainWindow::finishLoading(bool finished)
{
    if (finished) {
        progress = 100;
        setWindowTitle(view->title());
    } else {
        setWindowTitle("web page loading error!");
    }
}

// 获取图标文件
void MainWindow::handleIconUrlChanged(const QUrl &url)
{
    QNetworkRequest iconRequest(url);
    QNetworkReply *iconReply = manager->get(iconRequest);
    iconReply->setParent(this);
    connect(iconReply, &QNetworkReply::finished, this, &MainWindow::handleIconLoaded);
}
// 对获取的图标文件进行处理
void MainWindow::handleIconLoaded()
{
    QIcon icon;
    QNetworkReply *iconReply = qobject_cast<QNetworkReply*>(sender());
    if (iconReply && iconReply->error() == QNetworkReply::NoError) {
        QByteArray data = iconReply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(data);
        icon.addPixmap(pixmap);
        iconReply->deleteLater();
    } else {
        icon = QIcon(QStringLiteral("../mywebengine/defaulticon.png"));
    }
    setWindowIcon(icon);
}

// 显示历史记录窗口
void MainWindow::showHistory()
{
    historyList->clear();
    foreach (QWebEngineHistoryItem item, view->history()->items()) {
        QListWidgetItem *history = new QListWidgetItem(item.title());
        historyList->addItem(history);
    }
    historyList->show();
}

// 跳转到记录
void MainWindow::gotoHistory(const QModelIndex &index)
{
    QWebEngineHistoryItem item = view->history()->itemAt(index.row());
    view->history()->goToItem(item);
}

WebView *MainWindow::createView()
{
    return view;
}
