#include <QApplication>
#include <QFileSystemModel>
#include <QtGui/QTreeView>

int main(int argc, char *argv[])
{
	 QApplication app(argc, argv);
     QFileSystemModel model;
	 model.setRootPath("C:/Documents and Settings");
	 QTreeView treeView;
     treeView.setModel(&model);
     treeView.show();
	 return app.exec();
 }

