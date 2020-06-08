#include <QCoreApplication>
#include <QtXml>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 新建QDomDocument类对象，它代表一个XML文档
    QDomDocument doc;
    QFile file("../myDOM1/my.xml");
    if (!file.open(QIODevice::ReadOnly)) return 0;

    // 将文件内容读到doc中
    if (!doc.setContent(&file)) {
        file.close();
        return 0;
    }

    // 关闭文件
    file.close();

    // 获得doc的第一个结点，即XML说明
    QDomNode firstNode = doc.firstChild();

    // 输出XML说明,nodeName()为“xml”,nodeValue()为版本和编码信息
    qDebug() << qPrintable(firstNode.nodeName())
             << qPrintable(firstNode.nodeValue());

    // 返回根元素
    QDomElement docElem = doc.documentElement();

    // 返回根节点的第一个子结点
    QDomNode n = docElem.firstChild();

    // 如果结点不为空，则转到下一个节点
    while(!n.isNull())
    {
        // 如果结点是元素
        if (n.isElement())
        {
            // 将其转换为元素
            QDomElement e = n.toElement();

            // 返回元素标记和id属性的值
            qDebug() << qPrintable(e.tagName())
                     << qPrintable(e.attribute("id"));

            // 获得元素e的所有子结点的列表
            QDomNodeList list = e.childNodes();

            // 遍历该列表
            for(int i=0; i<list.count(); i++)
            {
                QDomNode node = list.at(i);
                if(node.isElement())
                    qDebug() << "   "<< qPrintable(node.toElement().tagName())
                             <<qPrintable(node.toElement().text());
            }
        }

        // 转到下一个兄弟结点
        n = n.nextSibling();
    }

    return a.exec();
}

