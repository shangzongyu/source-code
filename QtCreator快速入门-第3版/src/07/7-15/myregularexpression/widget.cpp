#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    QRegularExpression re("^(\\d\\d)/(\\d\\d)/(\\d\\d\\d\\d)$");
    QRegularExpressionMatch match = re.match("08/12/1985");
    if (match.hasMatch()) {
        QString matched = match.captured(0);
        QString day = match.captured(1);
        QString month = match.captured(2);
        QString year = match.captured(3);
        qDebug() << "matched: " << matched << endl
                 << "day: " << day << endl
                 << "month: " << month << endl
                 << "year: " << year;
    }

    QString pattern("^(Jan|Feb|Mar|Apr|May) \\d\\d?, \\d\\d\\d\\d$");
    QRegularExpression re1(pattern);

    QString input("Jan 21,");
    QRegularExpressionMatch match1 = re1.match(input, 0,
                                               QRegularExpression::PartialPreferCompleteMatch);
    bool hasMatch = match1.hasMatch();
    bool hasPartialMatch = match1.hasPartialMatch();

    qDebug() << "hasMatch: " << hasMatch << "hasParticalMatch: " << hasPartialMatch;
}

Widget::~Widget()
{
    delete ui;
}
