#include <QString>
#include <QStringList>
#include <QMetaProperty>
#include <QtGui>

QString objToString(const QObject* obj)
{
	QString result;
	const QMetaObject *meta = obj->metaObject();
	for (int i=0; i < meta->propertyCount(); ++i) {
		const QMetaProperty mp = meta->property(i);
		result += QString(" %1 %2 = %3;\n")
			.arg(mp.typeName())
			.arg(mp.name())
			.arg(obj->property(mp.name()).toString());
	}
	return result;
}
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QFileDialog * p = new QFileDialog();
	QString str = objToString(p);
	QMessageBox::information(0,"",str);
}
