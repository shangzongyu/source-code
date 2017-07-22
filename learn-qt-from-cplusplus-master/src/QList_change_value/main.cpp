#include <QList>
#include <iostream>
int main()
{
	QList<int> list;
	list << 1 << 3 << 5;

	QList<int>::iterator  it;
	for (it=list.begin(); it!=list.end(); ++it) {
		*it = *it * 2;
		std::cout << *it << " ";
	}
	
	QMutableListIterator<int> javaIt(list);
	while ( javaIt.hasNext() ) {
		int value = javaIt.next() * 2;
		javaIt.setValue(value);
		std::cout << value << " ";
	}
}