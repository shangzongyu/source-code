#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextFrame>
#include <QDebug>
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

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
    ui->mainToolBar->addAction(action_textBlock);

    QAction *action_font = new QAction(tr("字体"), this);
    action_font->setCheckable(true);                   // 设置动作可以被选中
    connect(action_font, &QAction::toggled, this, &MainWindow::setTextFont);
    ui->mainToolBar->addAction(action_font);

    QAction *action_textTable = new QAction(tr("表格"),this);
    QAction *action_textList = new QAction(tr("列表"),this);
    QAction *action_textImage = new QAction(tr("图片"),this);
    connect(action_textTable, &QAction::triggered, this, &MainWindow::insertTable);
    connect(action_textList, &QAction::triggered, this, &MainWindow::insertList);
    connect(action_textImage, &QAction::triggered, this, &MainWindow::insertImage);
    ui->mainToolBar->addAction(action_textTable);
    ui->mainToolBar->addAction(action_textList);
    ui->mainToolBar->addAction(action_textImage);

    QAction *action_textFind = new QAction(tr("查找"), this);
    connect(action_textFind, &QAction::triggered, this, &MainWindow::textFind);
    ui->mainToolBar->addAction(action_textFind);

    findDialog = new QDialog(this);         // 创建对话框
    lineEdit = new QLineEdit(findDialog);            // 创建行编辑器
    QPushButton *btn = new QPushButton(findDialog);  // 创建按钮
    btn->setText(tr("查找下一个"));
    connect(btn, &QPushButton::clicked, this, &MainWindow::findNext); // 关联信号和槽
    QVBoxLayout *layout = new QVBoxLayout;    // 创建垂直布局管理器
    layout->addWidget(lineEdit);              // 添加部件
    layout->addWidget(btn);
    findDialog->setLayout(layout);                   // 在对话框中使用布局管理器
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

void MainWindow::insertTable()        // 插入表格
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTableFormat format;          // 表格格式
    format.setCellSpacing(2);         // 表格外边白
    format.setCellPadding(10);        // 表格内边白
    cursor.insertTable(2, 2, format); // 插入2行2列表格
}
void MainWindow::insertList()         // 插入列表
{
    QTextListFormat format;           // 列表格式
    format.setStyle(QTextListFormat::ListDecimal);   // 数字编号
    ui->textEdit->textCursor().insertList(format);
}
void MainWindow::insertImage()        // 插入图片
{
    QTextImageFormat format;          // 图片格式
    format.setName("../myrichtext/logo.png");       // 图片路径
    ui->textEdit->textCursor().insertImage(format);
}

void MainWindow::textFind()                   // 查找文本
{
    findDialog->show();
}
void MainWindow::findNext()     // 查找下一个
{
    QString string = lineEdit->text();
    // 使用查找函数查找指定字符串，查找方式为向后查找
    bool isfind = ui->textEdit->find(string, QTextDocument::FindBackward);
    if(isfind){                // 如果查找成功，输出字符串所在行和列的编号
        qDebug() << tr("行号:%1 列号:%2")
                    .arg(ui->textEdit->textCursor().blockNumber())
                    .arg(ui->textEdit->textCursor().columnNumber());
    }
}


















