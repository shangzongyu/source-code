#include <QCoreApplication>
#include <QVector>
#include <QStringList>
#include <QDebug>
#include <algorithm>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList list;
    list << "one" << "two" << "three";

    qDebug() << QObject::tr("std::copy算法：");
    QVector<QString> vect(3);
    // 将list中所有项目复制到vect中
    std::copy(list.begin(), list.end(), vect.begin());
    qDebug() << vect; //结果为one,two,three

    qDebug() << endl << QObject::tr("std::equal算法：");
    // 从list的开始到结束的所有项目与vect的开始及其后面的等数量的项目进行比较，
    // 全部相同则返回true
    bool ret1 = std::equal(list.begin(), list.end(), vect.begin());
    qDebug() << "euqal: " << ret1; //结果为true

    qDebug() << endl << QObject::tr("std::find算法：");
    // 从list中查找"two",返回第一个对应的值的迭代器，如果没有找到则返回end()
    QList<QString>::iterator i = std::find(list.begin(), list.end(), "two");
    qDebug() << *i;     // 结果为"two"

    qDebug() << endl << QObject::tr("std::fill算法：");
    // 将list中的所有项目填充为"eleven"
    std::fill(list.begin(), list.end(), "eleven");
    qDebug() << list;  // 结果eleven,eleven,eleven

    QList<int> list1;
    list1 << 3 << 3 << 6 << 6 << 6 << 8;

    qDebug() << endl << QObject::tr("std::count算法：");
    int countOf6 = std::count(list1.begin(), list1.end(), 6); // 查找6的个数
    qDebug() << "countOf6: " << countOf6; // 结果为3

    qDebug() << endl << QObject::tr("std::lower_bound算法：");
    // 返回第一个出现5的位置，如果没有5，则返回5应该在的位置，
    // list1被查找的范围中的项目必须是升序
    QList<int>::iterator j = std::lower_bound(list1.begin(), list1.end(), 5);
    list1.insert(j, 5);
    qDebug() << list1; // 结果3,3,5,6,6,6,8

    QList<int> list2;
    list2 << 33 << 12 << 68 << 6 << 12;

    qDebug() << endl << QObject::tr("std::sort算法：");
    // 使用快速排序算法对list2进行升序排序，排序后两个12的位置不确定
    std::sort(list2.begin(), list2.end());
    qDebug() << list2; // 结果6,12,12,33,68

    qDebug() << endl << QObject::tr("std::stable_sort算法：");
    // 使用一种稳定排序算法对list2进行升序排序，
    // 排序前在前面的12,排序后依然在前面
    std::stable_sort(list2.begin(), list2.end());
    qDebug() << list2; // 结果6,12,12,33,68

    qDebug() << endl << QObject::tr("std::greater算法：");
    // 可以在qSort()算法中使其反向排序
    qSort(list2.begin(), list2.end(), std::greater<int>());
    qDebug() << list2; // 结果68,33,12,12,6

    qDebug() << endl << QObject::tr("std::swap算法：");
    double pi = 3.14;
    double e = 2.71;
    std::swap(pi, e);                         // 交换pi和e的值
    qDebug() << "pi:" << pi << "e:" << e; // 结果pi=2.71,e=3.14

    return a.exec();
}

