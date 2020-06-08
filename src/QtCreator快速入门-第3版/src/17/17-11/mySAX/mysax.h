#ifndef MYSAX_H
#define MYSAX_H

#include <QXmlDefaultHandler>
class QListWidget;

class MySAX : public QXmlDefaultHandler
{
public:
    MySAX();
    ~MySAX();
    bool readFile(const QString &fileName);
protected:
    bool startElement(const QString &namespaceURI, const QString &localName,
                      const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName,
                    const QString &qName);
    bool characters(const QString &ch);
    bool fatalError(const QXmlParseException &exception);
private:
    QListWidget *list;
    QString currentText;
};


#endif // MYSAX_H
