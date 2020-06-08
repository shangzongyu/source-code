#include <QTextStream>
#include <QIODevice>
#include <QVariant>
#include <QDate>
#include <QFile>

QTextStream  cout(stdout, QIODevice::WriteOnly);
void display(QVariant & v )
{
	cout << v.typeName() << " : " << v.toString() << endl;
}

int main()
{
	QVariant v1(123); 
	display(v1);

	QVariant v2( QDate(2011,10,8) );
	display(v2);	

	QFile f("objects.dat");
	if ( !f.open(QIODevice::WriteOnly) )  return -1;
	QDataStream out( &f );
	out << v1 ;
	f.close();

	if (!f.open(QIODevice::ReadOnly) ) return -1;
	QDataStream in( &f);
	QVariant v3;
	in >> v3;
	f.close();
	
	display(v3);
}
