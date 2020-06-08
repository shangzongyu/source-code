#include <QList>
#include <QPair>
#include <string>
#include <iostream>
using namespace std;

int main()
{
	typedef QPair<string,double> pair_type;
	QList< pair_type > list;

	list << pair_type("pi",3.14) << pair_type("e", 2.718);
	foreach( pair_type element, list)
		cout << element.first  << " " << element.second << endl;
}