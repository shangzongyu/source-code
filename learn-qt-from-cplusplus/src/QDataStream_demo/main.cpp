#include <QFile>
#include <QDataStream>
#include <QColor>
#include <QString>
#include <QDebug>

struct ColorText{
	QString text;
	QColor  color;
};

QDataStream& operator << (QDataStream & stream, const ColorText & data)
{ 
	stream << data.text << data.color;
	return stream;
}
QDataStream& operator >> (QDataStream & stream, ColorText & data)
{
	stream >> data.text >> data.color;
	return stream;
}
int main()
{
	ColorText data;
	data.text  = "Red";  data.color = Qt::red;

	QFile file( "test.dat" );
	if( !file.open( QIODevice::ReadWrite) )  return -1;
	QDataStream stream( &file );
	stream << data;

	file.seek(0);	stream >> data;
	file.close();
	qDebug() << data.text << " " << data.color;
}
