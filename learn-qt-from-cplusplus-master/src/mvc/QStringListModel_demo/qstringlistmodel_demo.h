#ifndef QSTRINGLISTMODEL_DEMO_H
#define QSTRINGLISTMODEL_DEMO_H

#include <QtGui/QMainWindow>
#include "ui_qstringlistmodel_demo.h"

class QStringListModel_demo : public QMainWindow
{
	Q_OBJECT

public:
	QStringListModel_demo(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QStringListModel_demo();

private:
	Ui::QStringListModel_demoClass ui;
};

#endif // QSTRINGLISTMODEL_DEMO_H
