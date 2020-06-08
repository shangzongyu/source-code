#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextFrame>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTextDocument *document = ui->textEdit->document();   // 获取文档对象
    QTextFrame *rootFrame = document->rootFrame();        // 获取根框架
    QTextFrameFormat format;                              // 创建框架格式
    format.setBorderBrush(Qt::red);                       // 边界颜色
    format.setBorder(3);                                  // 边界宽度
    rootFrame->setFrameFormat(format);                    // 框架使用格式

    QTextFrameFormat frameFormat;
    frameFormat.setBackground(Qt::lightGray);                  // 设置背景颜色
    frameFormat.setMargin(10);                                 // 设置边距
    frameFormat.setPadding(5);                                 // 设置填衬
    frameFormat.setBorder(2);
    frameFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Dotted); // 设置边框样式
    QTextCursor cursor = ui->textEdit->textCursor();                  // 获取光标
    cursor.insertFrame(frameFormat);                                  // 在光标处插入框架

    QAction *action_textFrame = new QAction(tr("框架"), this);
    connect(action_textFrame, &QAction::triggered, this, &MainWindow::showTextFrame);
    ui->mainToolBar->addAction(action_textFrame);      // 在工具栏添加动作

    QAction *action_textBlock = new QAction(tr("文本块"), this);
    connect(action_textBlock, &QAction::triggered, this, &MainWindow::showTextBlock);
//    ui->mainToolBar->addAction(action_textBlock);

    QAction *action_font = new QAction(tr("字体"), this);
    action_font->setCheckable(true);                   // 设置动作可以被选中
    connect(action_font, &QAction::toggled, this, &MainWindow::setTextFont);
//    ui->mainToolBar->addAction(action_font);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTextFrame()                    // 遍历框架
{
    QTextDocument *document = ui->textEdit->document();
    QTextFrame *frame = document->rootFrame();
    QTextFrame::iterator it;                          // 建立QTextFrame类的迭代器
    for (it = frame->begin(); !(it.atEnd()); ++it) {
        QTextFrame *childFrame = it.currentFrame();  // 获取当前框架的指针
        QTextBlock childBlock = it.currentBlock();   // 获取当前文本块
        if (childFrame)
            qDebug() << "frame";
        else if (childBlock.isValid())
            qDebug() << "block:" << childBlock.text();
    }
}

void MainWindow::showTextBlock()          // 遍历文本块
{
    QTextDocument *document = ui->textEdit->document();
    QTextBlock block = document->firstBlock();         // 获取文档的第一个文本块
    for (int i = 0; i < document->blockCount(); i++) {
        qDebug() << tr("文本块%1，文本块首行行号为:%2，长度为:%3,内容为：")
                    .arg(i).arg(block.firstLineNumber()).arg(block.length())
                 << block.text();
        block = block.next();                         // 获取下一个文本块
    }
}

void MainWindow::setTextFont(bool checked)         // 设置字体格式
{
    if(checked){                                   // 如果处于选中状态
        QTextCursor cursor = ui->textEdit->textCursor();
        QTextBlockFormat blockFormat;              // 文本块格式
        blockFormat.setAlignment(Qt::AlignCenter); // 水平居中
        cursor.insertBlock(blockFormat);           // 使用文本块格式
        QTextCharFormat charFormat;                // 字符格式
        charFormat.setBackground(Qt::lightGray);   // 背景色
        charFormat.setForeground(Qt::blue);        // 字体颜色
        // 使用宋体，12号，加粗，倾斜
        charFormat.setFont(QFont(tr("宋体"), 12, QFont::Bold, true));
        charFormat.setFontUnderline(true);         // 使用下划线
        cursor.setCharFormat(charFormat);          // 使用字符格式
        cursor.insertText(tr("测试字体"));         // 插入文本
    }
    else{/*恢复默认的字体格式*/}        // 如果处于非选中状态，可以进行其他操作
}


















