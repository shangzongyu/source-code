#ifndef INTROSPECT_QOBJECT_H
#define INTROSPECT_QOBJECT_H

#include <QtGui/QMainWindow>
#include "ui_introspect_qobject.h"

class introspect_qobject : public QMainWindow
{
	Q_OBJECT

public:
	introspect_qobject(QWidget *parent = 0, Qt::WFlags flags = 0);
	~introspect_qobject();

private:
	Ui::introspect_qobjectClass ui;
};

#endif // INTROSPECT_QOBJECT_H
