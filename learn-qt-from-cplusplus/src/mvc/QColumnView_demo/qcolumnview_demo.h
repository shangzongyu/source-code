#ifndef QCOLUMNVIEW_DEMO_H
#define QCOLUMNVIEW_DEMO_H

#include <QtGui/QMainWindow>
#include "ui_qcolumnview_demo.h"

class QColumnView_demo : public QMainWindow
{
	Q_OBJECT

public:
	QColumnView_demo(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QColumnView_demo();

private:
	Ui::QColumnView_demoClass ui;
};

#endif // QCOLUMNVIEW_DEMO_H
