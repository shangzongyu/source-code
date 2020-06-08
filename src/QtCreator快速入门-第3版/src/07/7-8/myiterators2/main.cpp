#include <QCoreApplication>
#include <QMapIterator>
#include <QMutableMapIterator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QMap<QString, QString> map;
    map.insert("Paris", "France");
    map.insert("Guatemala City", "Guatemala");
    map.insert("Mexico City", "Mexico");
    map.insert("Moscow", "Russia");
    QMapIterator<QString,QString> i(map);
    while(i.hasNext()) {
        i.next();
        qDebug() << i.key() << " : " << i.value();
    }
    if(i.findPrevious("Mexico")) qDebug() << "find 'Mexico'";  // 向前查找键的值
    QMutableMapIterator<QString, QString> j(map);
    while (j.hasNext()) {
        if (j.next().key().endsWith("City")) // endsWith()是QString类的函数
            j.remove();                      // 删除含有“City”结尾的键的项目
    }
    while(j.hasPrevious()) {
        j.previous();          // 现在的键值对为(paris,France),(Moscow,Russia)
        qDebug() << j.key() << " : " << j.value();
    }
    return a.exec();
}
