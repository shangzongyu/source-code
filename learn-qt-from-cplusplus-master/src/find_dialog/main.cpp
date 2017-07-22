#include "find_dialog.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FindDialog w;
	w.show();
	return a.exec();
}
