#include <QCoreApplication>
#include <QList>
#include <QListIterator>
#include <QMutableListIterator>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<QString> list;
    list << "A" << "B" << "C" << "D";
    QListIterator<QString> i(list); // 创建列表的只读迭代器，将list作为参数
    qDebug() << "the forward is :";
    while (i.hasNext())             // 正向遍历列表，结果为A，B，C，D
        qDebug() << i.next();
    qDebug() << "the backward is :";
    while (i.hasPrevious())         // 反向遍历列表，结果为D，C，B，A
        qDebug() << i.previous();

    QMutableListIterator<QString> j(list);
    j.toBack();                                // 返回列表尾部
    while (j.hasPrevious()) {
        QString str = j.previous();
        if(str == "B") j.remove();             // 删除项目“B”
    }
    j.insert("Q");                             // 在列表最前面添加项目“Q”
    j.toBack();
    if(j.hasPrevious()) j.previous() = "N";    // 直接赋值
    j.previous();
    j.setValue("M");                           // 使用setValue()进行赋值
    j.toFront();
    qDebug()<< "the forward is :";
    while (j.hasNext())                        // 正向遍历列表，结果为Q，A，M，N
        qDebug() << j.next();

    return a.exec();
}

