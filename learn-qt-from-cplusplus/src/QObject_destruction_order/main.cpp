#include <QtGui>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	QDialog dialog;
	QPushButton button("OK", &dialog);

	// QPushButton button("OK");
	// QDialog dialog;
	// button.setParent(&dialog);
	

	dialog.show();
	return a.exec();
}
