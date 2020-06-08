#ifndef QPOINTER_DEMO_H
#define QPOINTER_DEMO_H

#include <QtGui/QMainWindow>
#include "ui_qpointer_demo.h"

class qpointer_demo : public QMainWindow
{
	Q_OBJECT

public:
	qpointer_demo(QWidget *parent = 0, Qt::WFlags flags = 0);
	~qpointer_demo();

private:
	Ui::qpointer_demoClass ui;
};

#endif // QPOINTER_DEMO_H
