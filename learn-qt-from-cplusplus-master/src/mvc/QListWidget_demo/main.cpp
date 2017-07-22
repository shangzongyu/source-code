#include <QtGui/QApplication>
#include <QtGui/QListWidget>
#include <QtGui/QSplitter>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QSplitter splitter;

	QListWidget * left = new QListWidget();
	QStringList list;
	list << "98" << "99" << "100" << "101" << "102";
	left->addItems( list );
	left->sortItems();

	QListWidget * right = new QListWidget();
	for ( int i=98; i<103; i++) {
		QListWidgetItem * item = new QListWidgetItem;
		item->setData(Qt::DisplayRole, i);
		right->addItem(item);
	}
	right->sortItems();

	splitter.addWidget(left);
	splitter.addWidget(right);
	splitter.show();

	return app.exec();
}
