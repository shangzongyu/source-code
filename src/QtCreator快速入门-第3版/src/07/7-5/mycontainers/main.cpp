#include <QCoreApplication>
#include <QList>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<QString> list;
    list << "aa" << "bb" << "cc"; // 插入项目
    if(list[1] == "bb") list[1] = "ab";
    list.replace(2, "bc");        // 将“cc”换为“bc”
    qDebug() << "the list is: ";  // 输出整个列表
    for(int i=0; i<list.size(); ++i){
        qDebug() << list.at(i);   // 现在列表为aa ab bc
    }
    list.append("dd");            // 在列表尾部添加
    list.prepend("mm");           // 在列表头部添加
    QString str = list.takeAt(2); // 从列表中删除第3个项目，并获取它
    qDebug() << "at(2) item is: " << str;
    qDebug() << "the list is: ";
    for(int i=0; i<list.size(); ++i)
    {
        qDebug() << list.at(i);   // 现在列表为mm aa bc dd
    }
    list.insert(2, "mm");         // 在位置2插入项目
    list.swap(1,3);               // 交换项目1和项目3
    qDebug() << "the list is: ";
    for(int i=0; i<list.size(); ++i)
    {
        qDebug() << list.at(i);   // 现在列表为mm bc mm aa dd
    }
    qDebug() << "contains 'mm' ?" << list.contains("mm"); // 列表中是否包含“mm”
    qDebug() << "the 'mm' count: " << list.count("mm"); // 包含“mm”的个数
    // 第一个“mm”的位置，默认从位置0开始往前查找，返回第一个匹配的项目的位置
    qDebug() << "the first 'mm' index: " << list.indexOf("mm");
    // 第二个“mm”的位置，我们指定从位置1开始往前查找
    qDebug() << "the second 'mm' index: " << list.indexOf("mm", 1);
    return a.exec();
}
