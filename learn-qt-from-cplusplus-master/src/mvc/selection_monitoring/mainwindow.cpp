#include "mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	model     = new QStandardItemModel(8, 4, this);
	tableView = new QTableView(this);
	tableView->setModel(model);

	QItemSelectionModel * selectionModel = tableView->selectionModel();
	connect(selectionModel, SIGNAL( selectionChanged(QItemSelection, QItemSelection) ),
			this,			SLOT  ( updateSelection (QItemSelection, QItemSelection) ) ); 
	resize(600,400);
	setCentralWidget(tableView);
}
MainWindow::~MainWindow()
{
}
void MainWindow::updateSelection(const QItemSelection &selected,
		const QItemSelection &deselected)
{
     QModelIndexList items = selected.indexes();
     QModelIndex index;
     foreach (index, items) {
         QString text = QString("(%1,%2)")
			 .arg( index.row() + 1 ).arg( index.column() + 1 );
         model->setData(index, text);
     }
	 items = deselected.indexes();
     foreach (index, items)
         model->setData(index, "");
	
	 QItemSelectionModel * selectionModel = tableView->selectionModel();
	 QModelIndexList whole_list = selectionModel->selectedIndexes();
	 setWindowTitle( QString("%1 item selected")
			.arg( whole_list.size() ) );
}
