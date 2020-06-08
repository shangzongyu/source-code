#include <QFile>
#include <qDebug>
int main(int argc, char *argv[])
{
	QFile  f("data/test.txt");
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
         return -1;

	QByteArray data=f.readAll();
	qDebug() << data;
}

