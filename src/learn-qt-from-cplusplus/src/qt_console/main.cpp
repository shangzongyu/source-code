#include <QDebug>
#include <QRect>
#include <QTextStream>

QTextStream cin(stdin, QIODevice::ReadOnly);
QTextStream cout(stdout, QIODevice::WriteOnly);

int main(int argc, char *argv[])
{
	QString str;
	cin >> str;
	cout << "the string is "<< str << endl;
	qDebug() << "Qt types " << QRect(0,0,10,10) << endl;
}

