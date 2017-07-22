#include <QApplication>
#include <QtGui/QTreeView>
#include <QtGui/QSplitter>
#include <QStringList>
#include <QStringListModel>
#include <QFileSystemModel>
#include "RevertProxyModel.h"
#include "TreeModel.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QSplitter splitter;	

	QTreeView v1,v2;
	TreeModel treeModel;
	v1.setModel( & treeModel );

	RevertProxyModel proxyModel(0);
	proxyModel.setSourceModel( & treeModel );
	v2.setModel( &proxyModel );
		
	splitter.addWidget( &v1 );
	splitter.addWidget( &v2 );
	splitter.show();
	return app.exec();
 }
