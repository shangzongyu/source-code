#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QtGui/QMainWindow>
#include "ui_calendarwidget.h"

class calendarwidget : public QMainWindow
{
	Q_OBJECT

public:
	calendarwidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	~calendarwidget();

private:
	Ui::calendarwidgetClass ui;
};

#endif // CALENDARWIDGET_H
