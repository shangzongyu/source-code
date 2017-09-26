#ifndef QTREEWIDGET_DEMO_H
#define QTREEWIDGET_DEMO_H

#include <QtGui/QMainWindow>
#include "ui_qtreewidget_demo.h"

class QTreeWidget_demo : public QMainWindow
{
	Q_OBJECT

public:
	QTreeWidget_demo(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QTreeWidget_demo();

private:
	Ui::QTreeWidget_demoClass ui;
};

#endif // QTREEWIDGET_DEMO_H
