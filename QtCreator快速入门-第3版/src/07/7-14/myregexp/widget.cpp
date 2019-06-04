#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QRegExp rx("^\\d\\d?$");           // 两个字符都必须为数字，第二个字符可以没有
    qDebug() << rx.indexIn("a1");            // 结果为-1，不是数字开头
    qDebug() << rx.indexIn("5");             // 结果为0
    qDebug() << rx.indexIn("5b");            // 结果为-1，第二个字符不是数字
    qDebug() << rx.indexIn("12");            // 结果为0
    qDebug() << rx.indexIn("123");           // 结果为-1，超过了两个字符
    qDebug() << "*******************";       // 输出分割符，为了显示清晰
    rx.setPattern("\\b(mail|letter)\\b");    // 匹配mail或者letter单词
    qDebug() << rx.indexIn("emailletter");   // 结果为-1，mail不是一个单词
    qDebug() << rx.indexIn("my mail");       // 返回3
    qDebug() << rx.indexIn("my email letter"); // 返回9
    qDebug() << "*******************";
    rx.setPattern("M(?!ail)");               // 匹配字符M，其后面不能跟有ail字符
    QString str1 = "this is M";
    str1.replace(rx, "Mail");                // 使用"Mail"替换匹配到的字符
    qDebug() << "str1: " << str1;            // 结果为this is Mail
    QString str2 = "my M,your Ms,his Mail";
    str2.replace(rx,"Mail");
    qDebug() << "str2: " << str2;            // 结果为my Mail,your Mails,his Mail
    qDebug() << "*******************";
    QString str3 = "One Eric another Eirik, and an Ericsson. "
                   "How many Eiriks, Eric?"; // 一个字符串如果一行写不完，换行后两行都需要加双引号
    QRegExp rx2("\\bEi?ri[ck]\\b");         // 匹配Eric或者Eirik
    int pos = 0;
    int count = 0;
    while (pos >= 0) {
        pos = rx2.indexIn(str3, pos);
        if (pos >= 0) {
            ++pos;                         // 从匹配的字符的下一个字符开始匹配
            ++count;                       // 匹配到的数目加1
        }
    }
    qDebug() << "count: " << count;        // 结果为3

    QRegExp rx3("*.txt");
    rx3.setPatternSyntax(QRegExp::Wildcard);
    qDebug() << rx3.exactMatch("README.txt");        // 结果为true
    qDebug() << rx3.exactMatch("welcome.txt.bak");   // 结果为false

    QRegExp rx4("(\\d+)");
    QString str4 = "Offsets: 12 14 99 231 7";
    QStringList list;
    int pos2 = 0;
    while ((pos2 = rx4.indexIn(str4, pos2)) != -1) {
        list << rx4.cap(1);                      // 第一个捕获到的文本
        pos2 += rx4.matchedLength();             // 上一个匹配的字符串的长度
    }
    qDebug() << list;                            // 结果12,14,99,231,7

    QRegExp rxlen("(\\d+)(?:\\s*)(cm|inch)");
    int pos3 = rxlen.indexIn("Length: 189cm");
    if (pos3 > -1) {
        QString value = rxlen.cap(1);            // 结果为189
        QString unit = rxlen.cap(2);             // 结果为cm
        QString string = rxlen.cap(0);           // 结果为189cm
        qDebug() << value << unit << string;
    }

    QRegExp rx5("\\b(\\w+)\\W+\\1\\b");
    rx5.setCaseSensitivity(Qt::CaseInsensitive); // 设置不区分大小写
    qDebug() << rx5.indexIn("Hello--hello");     // 结果为0
    qDebug() << rx5.cap(1);                      // 结果为Hello

    QRegExp rx6("\\b你好\\b");                  // 匹配中文
    qDebug() << rx6.indexIn("你好");            // 结果为0
    qDebug() << rx6.cap(0); // 整个字符串完全匹配，使用cap(0)捕获，结果为“你好”

}

Widget::~Widget()
{
    delete ui;
}
