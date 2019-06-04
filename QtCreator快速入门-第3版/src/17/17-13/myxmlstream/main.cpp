#include <QCoreApplication>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("../myxmlstream/my2.xml");
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Error: cannot open file";
        return 1;
    }

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("bookmark");
    stream.writeAttribute("href", "http://www.qt.io/");
    stream.writeTextElement("title", "Qt Home");
    stream.writeEndElement();
    stream.writeEndDocument();

    file.close();

    qDebug() << "write finished!";

    return a.exec();
}

