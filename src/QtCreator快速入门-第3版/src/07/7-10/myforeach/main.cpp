#include <QCoreApplication>
#include <QList>
#include <QMap>
#include <QMultiMap>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<QString> list;
    list.insert(0, "A");
    list.insert(1, "B");
    list.insert(2, "C");
    qDebug() <<"the list is :";
    foreach (QString str, list) {   // 从list中获取每一项
        qDebug() << str;            // 结果为A，B，C
    }

    QMap<QString,int> map;
    map.insert("first", 1);
    map.insert("second", 2);
    map.insert("third", 3);
    qDebug() << endl << "the map is :";
    foreach (QString str, map.keys())   // 从map中获取每一个键
        // 输出键和对应的值，结果为(first,1),(second,2),(third,3)
        qDebug() << str << " : " << map.value(str);

    QMultiMap<QString,int> map2;
    map2.insert("first", 1);
    map2.insert("first", 2);
    map2.insert("first", 3);
    map2.insert("second", 2);
    qDebug() << endl << "the map2 is :";
    QList<QString> keys = map2.uniqueKeys(); // 返回所有键的列表
    foreach (QString str, keys) {            // 遍历所有的键
        foreach (int i, map2.values(str))    // 遍历键中所有的值
            qDebug() << str << " : " << i;
    }// 结果为(first,3),(first,2),(first,1),(second,2)
    return a.exec();
}
