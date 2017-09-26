#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

private slots: 
	void updateSelection(const QItemSelection &selected,
						 const QItemSelection &deselected);
private:
	QStandardItemModel  * model;
	QTableView * tableView;
};

#endif
