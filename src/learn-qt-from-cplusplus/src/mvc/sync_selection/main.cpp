#include <QApplication>
#include <QtGui/QListView>
#include <QtGui/QSplitter>
#include <QStringList>
#include <QStringListModel>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QSplitter splitter;	

	QStringList numbers;
	numbers << "One" << "Two" << "Three" << "Four" << "Five";
	QStringListModel model(numbers);

	QListView v1,v2;
	v1.setModel( &model );
	v2.setModel( &model );
	v1.setSelectionModel( v2.selectionModel() );
	
	splitter.addWidget( &v1 );
	splitter.addWidget( &v2 );
	splitter.show();
	return app.exec();
 }
