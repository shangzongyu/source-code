#include <QCoreApplication>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QFile file("../myxmlstream/my.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"Error: cannot open file";
        return 1;
    }

    QXmlStreamReader reader;

    // 设置文件，这时会将流设置为初始状态
    reader.setDevice(&file);

    // 如果没有读到文档结尾，而且没有出现错误
    while (!reader.atEnd()) {
        // 读取下一个记号，它返回记号的类型
        QXmlStreamReader::TokenType type = reader.readNext();

        // 下面便根据记号的类型来进行不同的输出
        if (type == QXmlStreamReader::StartDocument)
            qDebug() << reader.documentEncoding() << reader.documentVersion();
        if (type == QXmlStreamReader::StartElement) {
            qDebug() << "<" << reader.name() << ">";
            if (reader.attributes().hasAttribute("id"))
                qDebug() << reader.attributes().value("id");
        }
        if (type == QXmlStreamReader::EndElement)
            qDebug() << "</" << reader.name() << ">";
        if (type == QXmlStreamReader::Characters && !reader.isWhitespace())
            qDebug() << reader.text();
    }

    // 如果读取过程中出现错误，那么输出错误信息
    if (reader.hasError()) {
        qDebug() << "error: " << reader.errorString();
    }

    file.close();

    return a.exec();
}

