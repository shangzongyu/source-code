#include "introspect_qobject.h"

introspect_qobject::introspect_qobject(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

introspect_qobject::~introspect_qobject()
{

}
