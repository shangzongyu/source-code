#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDomDocument doc;

    // 添加处理指令即XML说明
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml",
                                                  "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    // 添加根元素
    QDomElement root = doc.createElement("书库");
    doc.appendChild(root);

    // 添加第一个图书元素及其子元素
    QDomElement book = doc.createElement("图书");
    QDomAttr id = doc.createAttribute("编号");
    QDomElement title = doc.createElement("书名");
    QDomElement author = doc.createElement("作者");
    QDomText text;
    id.setValue(QString("1"));
    book.setAttributeNode(id);
    text = doc.createTextNode("Qt");
    title.appendChild(text);
    text = doc.createTextNode("shiming");
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);

    // 添加第二个图书元素及其子元素
    book = doc.createElement("图书");
    id = doc.createAttribute("编号");
    title = doc.createElement("书名");
    author = doc.createElement("作者");
    id.setValue(QString("2"));
    book.setAttributeNode(id);
    text = doc.createTextNode("Linux");
    title.appendChild(text);
    text = doc.createTextNode("yafei");
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);

    QFile file("my.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return ;
    QTextStream out(&file);

    // 将文档保存到文件，4为子元素缩进字符数
    doc.save(out, 4);
    file.close();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doXml(const QString operate)
{
    ui->listWidget->clear();
    ui->listWidget->addItem(tr("没有找到相关内容！"));
    QFile file("my.xml");
    if (!file.open(QIODevice::ReadOnly)) return ;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return ;
    }
    file.close();

    // 以标签名进行查找
    QDomNodeList list = doc.elementsByTagName("图书");
    for(int i=0; i<list.count(); i++)
    {
        QDomElement e = list.at(i).toElement();
        if(e.attribute("编号") == ui->lineEdit->text())
        {   // 如果元素的“编号”属性值与我们所查的相同
            if (operate == "delete") {
                // 如果是删除操作
                QDomElement root = doc.documentElement();

                // 从根节点上删除该节点
                root.removeChild(list.at(i));
                QFile file("my.xml");
                if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                    return ;
                QTextStream out(&file);
                doc.save(out,4);
                file.close();
                ui->listWidget->clear();
                ui->listWidget->addItem(tr("删除成功！"));
            } else if (operate == "update") {
                // 如果是更新操作
                QDomNodeList child = list.at(i).childNodes();

                // 将它子节点的首个子节点（就是文本节点）的内容更新
                child.at(0).toElement().firstChild()
                        .setNodeValue(ui->lineEdit_2->text());
                child.at(1).toElement().firstChild()
                        .setNodeValue(ui->lineEdit_3->text());
                QFile file("my.xml");
                if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
                    return ;
                QTextStream out(&file);
                doc.save(out,4);
                file.close();
                ui->listWidget->clear();
                ui->listWidget->addItem(tr("更新成功！"));
            } else if (operate == "find") {
                // 如果是查找操作
                ui->listWidget->clear();
                ui->listWidget->addItem(e.tagName()
                                        + e.attribute("编号"));
                QDomNodeList list = e.childNodes();
                for(int i=0; i<list.count(); i++)
                {
                    QDomNode node = list.at(i);
                    if(node.isElement())
                        ui->listWidget->addItem("   "
                                                + node.toElement().tagName() + " : "
                                                + node.toElement().text());
                }
            }
        }
    }

}

// 显示全部按钮
void MainWindow::on_pushButton_5_clicked()
{
    // 先清空显示
    ui->listWidget->clear();
    QFile file("my.xml");
    if (!file.open(QIODevice::ReadOnly)) return ;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return ;
    }
    file.close();
    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        if (n.isElement())
        {
            QDomElement e = n.toElement();
            ui->listWidget->addItem(e.tagName() + e.attribute("编号"));
            QDomNodeList list = e.childNodes();
            for (int i=0; i<list.count(); i++)
            {
                QDomNode node = list.at(i);
                if(node.isElement())
                    ui->listWidget->addItem("   " + node.toElement().tagName()
                                            + " : " + node.toElement().text());
            }
        }
        n = n.nextSibling();
    }
}

// 添加按钮
void MainWindow::on_pushButton_4_clicked()
{
    // 先清空显示，然后显示“无法添加！”，这样如果添加失败则会显示“无法添加！”
    ui->listWidget->clear();
    ui->listWidget->addItem(tr("无法添加！"));
    QFile file("my.xml");
    if (!file.open(QIODevice::ReadOnly)) return;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();
    QDomElement root = doc.documentElement();
    QDomElement book = doc.createElement("图书");
    QDomAttr id = doc.createAttribute("编号");
    QDomElement title = doc.createElement("书名");
    QDomElement author = doc.createElement("作者");
    QDomText text;

    // 我们获得了最后一个孩子结点的编号，然后加1，便是新的编号
    QString num = root.lastChild().toElement().attribute("编号");
    int count = num.toInt() +1;
    id.setValue(QString::number(count));
    book.setAttributeNode(id);
    text = doc.createTextNode(ui->lineEdit_2->text());
    title.appendChild(text);
    text = doc.createTextNode(ui->lineEdit_3->text());
    author.appendChild(text);
    book.appendChild(title);
    book.appendChild(author);
    root.appendChild(book);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return ;
    QTextStream out(&file);
    doc.save(out, 4);
    file.close();

    // 最后更改显示为“添加成功！”
    ui->listWidget->clear();
    ui->listWidget->addItem(tr("添加成功！"));
}

// 查找按钮
void MainWindow::on_pushButton_clicked()
{
    doXml("find");
}

// 删除按钮
void MainWindow::on_pushButton_2_clicked()
{
    doXml("delete");
}

// 更新按钮
void MainWindow::on_pushButton_3_clicked()
{
    doXml("update");
}
