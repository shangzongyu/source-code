#include <QMultiHash>
#include <QTextStream>

QTextStream cout(stdout, QIODevice::WriteOnly);

int main( )
{
	QMultiHash<QString, double>  hash;
	hash.insert("food", 85);
	hash.insert("book", 150);
	hash.insert("food", 50);
	hash.insert("food", 60);
	hash.insert("transport", 20);

	QMultiHash<QString, double>::iterator it = hash.find("food");
	while (  it != hash.end() && it.key() == "food" ) {
		cout << it.value() << " ";
		++it;
	}

	return 0;
}
