#include <QtGui>

 int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QSplitter splitter;

	QStandardItemModel listModel;
	QStandardItem *rootItem = listModel.invisibleRootItem();
	for (int row = 0; row < 4; ++row) {
		QStandardItem *item = new QStandardItem(
			QString("%0").arg(row) );
		rootItem->appendRow( item );
	}	
	QListView listView;
	listView.setModel ( & listModel );
	splitter.addWidget( & listView );

	QStandardItemModel tableModel(4, 4);
	for (int row = 0; row < 4; ++row) {
		 for (int column = 0; column < 4; ++column) {
			 QStandardItem *item = new QStandardItem(
				 QString("%0,%1").arg(row).arg(column));
			 tableModel.setItem(row, column, item);
		 }
	}	
	QTableView tableView;
	tableView.setModel( & tableModel );
	splitter.addWidget( & tableView );

	QStandardItemModel treeModel;
	QStandardItem *parentItem = treeModel.invisibleRootItem();
	for (int i = 0; i < 4; ++i) {
	 QStandardItem *item = new QStandardItem(QString("%0").arg(i));
	 parentItem->appendRow(item);
	 parentItem = item;
	}
	QTreeView treeView;
	treeView.setModel( & treeModel );
	splitter.addWidget(& treeView );
	
	splitter.show(); 
	return a.exec();
}
