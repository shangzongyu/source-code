#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>

class MyClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ getUserName WRITE setUserName
               NOTIFY userNameChanged) // 注册属性userName
public:
    explicit MyClass(QObject *parent = 0);
    QString getUserName() const         // 实现READ读函数
    {return m_userName;}
    void setUserName(QString userName)  // 实现WRITE写函数
    {
        m_userName = userName;
        emit userNameChanged(userName); // 当属性值改变时发射该信号
    }
signals:
    void userNameChanged(QString);      // 声明NOTIFY通知消息
private:
    QString m_userName;                 // 私有变量，存放userName属性的值
};

#endif // MYCLASS_H
