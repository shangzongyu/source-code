#include "qpointer_demo.h"
#include <QtGui>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qpointer_demo w;
	w.show();

	QPointer<QLabel> p1 = new QLabel();
	QPointer<QLabel> p2 = p1;

	delete p1;
	if ( p1==NULL && p2==NULL) 
		QMessageBox::information(0,"", "p1 and p2 are NULL");

	return a.exec();
}

