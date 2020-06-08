#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database1",
                              "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;

    // 创建student表
    query.exec("create table student (id int primary key, "
                       "name varchar, course int)");
    query.exec("insert into student values(1, '李强', 11)");
    query.exec("insert into student values(2, '马亮', 11)");
    query.exec("insert into student values(3, '孙红', 12)");

    // 创建course表
    query.exec("create table course (id int primary key, "
                       "name varchar, teacher varchar)");
    query.exec("insert into course values(10, '数学', '王老师')");
    query.exec("insert into course values(11, '英语', '张老师')");
    query.exec("insert into course values(12, '计算机', '白老师')");

    return true;
}

#endif // CONNECTION_H
