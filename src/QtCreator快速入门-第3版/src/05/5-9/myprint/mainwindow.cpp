#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAction *action_print = new QAction(tr("打印"),this);
    QAction *action_printPreview = new QAction(tr("打印预览"),this);
    QAction *action_pdf = new QAction(tr("生成pdf"),this);
    connect(action_print,SIGNAL(triggered()),this,SLOT(doPrint()));
    connect(action_printPreview,SIGNAL(triggered()),this,SLOT(doPrintPreview()));
    connect(action_pdf,SIGNAL(triggered()),this,SLOT(createPdf()));
    ui->mainToolBar->addAction(action_print);
    ui->mainToolBar->addAction(action_printPreview);
    ui->mainToolBar->addAction(action_pdf);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doPrint()                    // 打印
{
    QPrinter printer;                         // 创建打印机对象
    QPrintDialog dlg(&printer, this);         // 创建打印对话框
    // 如果编辑器中有选中区域，则打印选中区域
    if (ui->textEdit->textCursor().hasSelection())
        dlg.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if (dlg.exec() == QDialog::Accepted) {    // 如果在对话框中按下了打印按钮
        ui->textEdit->print(&printer);        // 则执行打印操作
    }
}

void MainWindow::doPrintPreview()                    // 打印预览
{
    QPrinter printer;
    QPrintPreviewDialog preview(&printer, this);     // 创建打印预览对话框
    // 当要生成预览页面时，发射paintRequested()信号
    connect(&preview, &QPrintPreviewDialog::paintRequested,
            this, &MainWindow::printPreview);
    preview.exec();
}

void MainWindow::printPreview(QPrinter *printer)
{
    ui->textEdit->print(printer);
}

void MainWindow::createPdf()                // 生成PDF文件
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("导出PDF文件"),
                                                    QString(), "*.pdf");
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");        // 如果文件后缀为空，则默认使用.pdf
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);    // 指定输出格式为pdf
        printer.setOutputFileName(fileName);
        ui->textEdit->print(&printer);
    }
}

