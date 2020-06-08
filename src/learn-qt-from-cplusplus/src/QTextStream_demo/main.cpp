#include <QTextStream>
#include <QTextCodec>
#include <QFile>

int main(int argc, char *argv[])
{
	QFile src_f("data/latin1.txt");
	if ( !src_f.open(QIODevice::ReadOnly)) return -1;
	QTextStream in( & src_f );
	in.setCodec("latin1");
	QString data = in.readAll();

	QFile dest_f("data/unicode.txt");
	if (!dest_f.open(QIODevice::WriteOnly )) return -1;
	QTextStream out( & dest_f );
	out.setCodec("UTF-16");  
	out << data;
}

