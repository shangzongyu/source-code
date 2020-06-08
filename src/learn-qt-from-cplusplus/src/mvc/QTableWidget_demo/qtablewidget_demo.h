#ifndef QTABLEWIDGET_DEMO_H
#define QTABLEWIDGET_DEMO_H

#include <QtGui/QMainWindow>
#include "ui_qtablewidget_demo.h"

class QTableWidget_demo : public QMainWindow
{
	Q_OBJECT

public:
	QTableWidget_demo(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QTableWidget_demo();

private:
	Ui::QTableWidget_demoClass ui;
};

#endif // QTABLEWIDGET_DEMO_H
