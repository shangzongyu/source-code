#include <QCoreApplication>
#include <QList>
#include <QDebug>
#include <QMap>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<QString> list;
    list << "A" << "B" << "C" << "D";
    QList<QString>::iterator i;      // 使用读写迭代器
    qDebug() << "the forward is :";
    for (i = list.begin(); i != list.end(); ++i) {
        *i = (*i).toLower();         // 使用QString的toLower()函数转换为小写
        qDebug() << *i;              // 结果为a，b，c，d
    }
    qDebug() << "the backward is :";
    while (i != list.begin()) {
        --i;
        qDebug() << *i;               // 结果为d，c，b，a
    }
    QList<QString>::const_iterator j; // 使用只读迭代器
    qDebug() << "the forward is :";
    for (j = list.constBegin(); j != list.constEnd(); ++j)
        qDebug() << *j;               // 结果为a，b，c，d

    QMap<QString, int> map;
    map.insert("one",1);
    map.insert("two",2);
    map.insert("three",3);
    QMap<QString, int>::const_iterator p;
    qDebug() << "the forward is :";
    for (p = map.constBegin(); p != map.constEnd(); ++p)
        qDebug() << p.key() << ":" << p.value();// 结果为(one,1),(three,3),(two,2)

    return a.exec();
}
