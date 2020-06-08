#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection()
{
    // 创建一个数据库连接，使用“connection1”为连接名
    QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE", "connection1");
    db1.setDatabaseName("my1.db");
    if (!db1.open()) {
        QMessageBox::critical(0, "Cannot open database1",
                              "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }

    // 这里要指定连接
    QSqlQuery query1(db1);
    query1.exec("create table student (id int primary key, "
                "name varchar(20))");
    query1.exec("insert into student values(0, 'LiMing')");
    query1.exec("insert into student values(1, 'LiuTao')");
    query1.exec("insert into student values(2, 'WangHong')");

    // 创建另一个数据库连接，要使用不同的连接名，这里是“connection2”
    QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE", "connection2");
    db2.setDatabaseName("my2.db");
    if (!db2.open()) {
        QMessageBox::critical(0, "Cannot open database1",
                              "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }

    // 这里要指定连接
    QSqlQuery query2(db2);
    query2.exec("create table student (id int primary key, "
                "name varchar(20))");
    query2.exec("insert into student values(10, 'LiQiang')");
    query2.exec("insert into student values(11, 'MaLiang')");
    query2.exec("insert into student values(12, 'ZhangBin')");
    return true;
}

#endif // CONNECTION_H

