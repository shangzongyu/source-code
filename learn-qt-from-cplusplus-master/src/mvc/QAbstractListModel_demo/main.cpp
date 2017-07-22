#include "ListModel.h"
#include <QApplication>
#include <QListView>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ListModel list(0);
	QListView listView;
	listView.setModel( & list );
	listView.show();
	return a.exec();
}
