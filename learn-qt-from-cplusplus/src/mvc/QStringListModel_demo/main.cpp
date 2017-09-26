#include <QApplication>
#include <QtGui/QListView>
#include <QStringList>
#include <QStringListModel>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QStringList list;
	list << "One" << "Two" << "Three" << "Four" << "Five";
	QStringListModel listModel(list);
	QListView listView;
	listView.setModel( &listModel );
	listView.show();
    
	return app.exec();
 }
