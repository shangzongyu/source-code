#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include "connection.h"
#include <QVariant>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建数据库连接
    if (!createConnection()) return 1;

    // 使用QSqlQuery查询整张表
    QSqlQuery query;
    query.exec("select * from student");
    while(query.next())
    {
        qDebug() << query.value(0).toInt() << query.value(1).toString();
    }
    return a.exec();
}
