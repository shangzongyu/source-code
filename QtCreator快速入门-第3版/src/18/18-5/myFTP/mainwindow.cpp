#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qftp.h"
#include <QTextCodec>
#include <QFile>
#include <QTreeWidgetItem>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setValue(0);
    connect(ui->fileList, &QTreeWidget::itemActivated,
            this, &MainWindow::processItem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ftpCommandStarted(int)
{
    int id = ftp->currentCommand();
    switch (id)
    {
    case QFtp::ConnectToHost :
        ui->label->setText(tr("正在连接到服务器…"));
        break;
    case QFtp::Login :
        ui->label->setText(tr("正在登录…"));
        break;
    case QFtp::Get :
        ui->label->setText(tr("正在下载…"));
        break;
    case QFtp::Close :
        ui->label->setText(tr("正在关闭连接…"));
    }
}

void MainWindow::ftpCommandFinished(int, bool error)
{
    if(ftp->currentCommand() == QFtp::ConnectToHost) {
        if (error)
            ui->label->setText(tr("连接服务器出现错误：%1").arg(ftp->errorString()));
        else ui->label->setText(tr("连接到服务器成功"));
    } else if (ftp->currentCommand() == QFtp::Login) {
        if (error)
            ui->label->setText(tr("登录出现错误：%1").arg(ftp->errorString()));
        else {
            ui->label->setText(tr("登录成功"));
            ftp->list();
        }
    } else if (ftp->currentCommand() == QFtp::Get) {
        if(error)
            ui->label->setText(tr("下载出现错误：%1").arg(ftp->errorString()));
        else {
            ui->label->setText(tr("已经完成下载"));
            file->close();
        }
        ui->downloadButton->setEnabled(true);
    } else if (ftp->currentCommand() == QFtp::List) {
        if (isDirectory.isEmpty())
        {
            ui->fileList->addTopLevelItem(
                        new QTreeWidgetItem(QStringList()<< tr("<empty>")));
            ui->fileList->setEnabled(false);
            ui->label->setText(tr("该目录为空"));
        }
    } else if (ftp->currentCommand() == QFtp::Close) {
        ui->label->setText(tr("已经关闭连接"));
    }
}

// 连接按钮
void MainWindow::on_connectButton_clicked()
{
    ui->fileList->clear();
    currentPath.clear();
    isDirectory.clear();
    ui->progressBar->setValue(0);
    ftp = new QFtp(this);
    connect(ftp, &QFtp::commandStarted, this,
            &MainWindow::ftpCommandStarted);
    connect(ftp, &QFtp::commandFinished,
            this, &MainWindow::ftpCommandFinished);
    connect(ftp, &QFtp::listInfo, this, &MainWindow::addToList);
    connect(ftp, &QFtp::dataTransferProgress,
            this, &MainWindow::updateDataTransferProgress);
    QString ftpServer = ui->ftpServerLineEdit->text();
    QString userName = ui->userNameLineEdit->text();
    QString passWord = ui->passWordLineEdit->text();
    ftp->connectToHost(ftpServer, 21);
    ftp->login(userName, passWord);
}

void MainWindow::addToList(const QUrlInfo &urlInfo)
{
    // 注意：因为服务器上文件使用UTF-8编码，所以要进行编码转换，这样显示中文才不会乱码
    QString name = QString::fromUtf8(urlInfo.name().toLatin1());
    QString owner = QString::fromUtf8(urlInfo.owner().toLatin1());
    QString group = QString::fromUtf8(urlInfo.group().toLatin1());
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, name);
    item->setText(1, QString::number(urlInfo.size()));
    item->setText(2, owner);
    item->setText(3, group);
    item->setText(4, urlInfo.lastModified().toString("yyyy-MM-dd"));
    QPixmap pixmap(urlInfo.isDir() ? "../myFTP/dir.png" : "../myFTP/file.png");
    item->setIcon(0, pixmap);
    isDirectory[name] = urlInfo.isDir();
    ui->fileList->addTopLevelItem(item);
    if (!ui->fileList->currentItem()) {
        ui->fileList->setCurrentItem(ui->fileList->topLevelItem(0));
        ui->fileList->setEnabled(true);
    }
}

void MainWindow::processItem(QTreeWidgetItem *item, int)
{
    // 如果这个文件是个目录，则打开
    if (isDirectory.value(item->text(0))) {
        // 注意：因为目录名称可能是中文，在使用ftp命令cd()前需要先进行编码转换
        QString name = QLatin1String(item->text(0).toUtf8());
        ui->fileList->clear();
        isDirectory.clear();
        currentPath += "/";
        currentPath += name;
        ftp->cd(name);
        ftp->list();
        ui->cdToParentButton->setEnabled(true);
    }
}

// 返回上级目录按钮
void MainWindow::on_cdToParentButton_clicked()
{
    ui->fileList->clear();
    isDirectory.clear();
    currentPath = currentPath.left(currentPath.lastIndexOf('/'));
    if (currentPath.isEmpty()) {
        ui->cdToParentButton->setEnabled(false);
        ftp->cd("/");
    } else {
        ftp->cd(currentPath);
    }
    ftp->list();
}

// 下载按钮
void MainWindow::on_downloadButton_clicked()
{
    // 注意：因为文件名称可能是中文，所以在使用get()函数前需要进行编码转换
    QString fileName = ui->fileList->currentItem()->text(0);
    QString name = QLatin1String(fileName.toUtf8());
    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly)) {
        delete file;
        return;
    }
    ui->downloadButton->setEnabled(false);
    ftp->get(name, file);
}

void MainWindow::updateDataTransferProgress(qint64 readBytes,qint64 totalBytes)
{
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(readBytes);
}
