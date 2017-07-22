#include <QPair>
#include <QString>
#include <QMap>
#include <QFile>
#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[])
{
	qint32 i=0x12345678;
	typedef QPair<float, float>      pair_type;
	typedef QMap<QString, pair_type> map_type;
	map_type  map;
	map.insert("United States", pair_type(14.6,  2.7) );
	map.insert("PRC China",		pair_type( 6.1, 13.0) );
	map.insert("Japan",			pair_type( 5.4,  1.3) );
	map.insert("Germany",		pair_type( 3.3,  0.8) );
	map.insert("United Kingdom",pair_type( 2.3,  0.6) );

	QFile file("facts.dat");
	if (!file.open(QIODevice::WriteOnly)) {
		cerr << "Cannot open file for writing: "
			<< qPrintable(file.errorString()) << endl;
		return -1;
	}
	QDataStream out(&file);
	out << i << map;
	file.close();

	map.clear();
	if (!file.open(QIODevice::ReadOnly)) {
		cerr << "Cannot open file for reading: "
			<< qPrintable(file.errorString()) << endl;
		return -1;
	}
	QDataStream in(&file);
	in >> i >> map;
	map_type::iterator  it;
	for (it=map.begin();  it!=map.end(); it++)
		cout << setw(15) << qPrintable( it.key() ) 
		     << setw(5)  << it.value().first  
			 << setw(5)  << it.value().second << endl;
	
	return 0;
}


