#include <QtGui>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	 
	QObject * pObject = new QFileDialog();
	const QMetaObject * p = pObject->metaObject();
		
	QString str;
	QTextStream textStream( &str );
	textStream << p->className() << " inherits "
	   << p->superClass()->className() << endl;

	textStream << " === methods === " << endl;
	for(int i = p->methodOffset(); i < p->methodCount(); ++i)
	    textStream << p->method(i).signature() << endl;

	textStream << " === enumerators === " << endl;
	for(int i = p->enumeratorOffset(); i < p->enumeratorCount(); ++i)
	   textStream << p->enumerator(i).name() << endl;

	QMessageBox::information(0,"",str);

	if ( qobject_cast<QDialog *> (pObject) ) 
		QMessageBox::information(0,"","The object has the type of QDialog");
	if ( pObject->inherits("QWidget") )
		QMessageBox::information(0,"","The object has the type of QWidget");
	return 0;
}
