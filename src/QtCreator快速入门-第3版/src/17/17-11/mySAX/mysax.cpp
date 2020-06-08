#include "mysax.h"
#include <QtXml>
#include <QListWidget>

MySAX::MySAX()
{
    list = new QListWidget;
    list->show();
}

MySAX::~MySAX()
{
    delete list;
}

bool MySAX::readFile(const QString &fileName)
{
    QFile file(fileName);

    // 读取文件内容
    QXmlInputSource inputSource(&file);

    // 建立QXmlSimpleReader对象
    QXmlSimpleReader reader;

    // 设置内容处理器
    reader.setContentHandler(this);

    // 设置错误处理器
    reader.setErrorHandler(this);

    // 解析文件
    return reader.parse(inputSource);
}

// 已经解析完一个元素的起始标签
bool MySAX::startElement(const QString &namespaceURI, const QString &localName,
                         const QString &qName, const QXmlAttributes &atts)
{
    if (qName == "library")
        list->addItem(qName);
    else if (qName == "book")
        list->addItem("    " + qName + atts.value("id"));
    return true;
}

// 已经解析完一块字符数据
bool MySAX::characters(const QString &ch)
{
    currentText = ch;
    return true;
}

// 已经解析完一个元素的结束标签
bool MySAX::endElement(const QString &namespaceURI, const QString &localName,
                       const QString &qName)
{
    if (qName == "title" || qName == "author")
        list->addItem("        " + qName + " : " + currentText);
    return true;
}

// 错误处理
bool MySAX::fatalError(const QXmlParseException &exception)
{
    qDebug() << exception.message();
    return false;
}

