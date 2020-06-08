#include <QTextStream>
#include <QTextCodec>
#include <QFile>
QTextStream cout(stdout, QIODevice::WriteOnly);

int main(int argc, char *argv[])
{
	QFile src_f("data/latin1.txt");
	if ( !src_f.open(QIODevice::ReadOnly)) return -1;
	QByteArray src_data = src_f.readAll();

	QTextCodec *codec = QTextCodec::codecForName("latin1");
	QString dest_data = codec->toUnicode(src_data);

	QFile dest_f("data/unicode.txt");
	if (!dest_f.open(QIODevice::WriteOnly )) return -1;
	dest_f.write((char*)dest_data.data(), dest_data.length()*sizeof(QChar));
	cout<< "data converted" << endl;
}

