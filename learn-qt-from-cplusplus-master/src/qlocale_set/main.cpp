#include <QLocale>
#include <QTextStream>
#include <QIODevice>

QTextStream out( stdout, QIODevice::WriteOnly);
int main( ) 
{
	double x = 123.456;
	out.setLocale( QLocale(QLocale::German) );
	out << fixed << x << endl;
}
