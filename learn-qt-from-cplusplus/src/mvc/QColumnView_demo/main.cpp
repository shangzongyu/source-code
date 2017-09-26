#include <QtGui>

int  main(int argc, char **argv)
{
    QApplication app(argc, argv);

   	QFileSystemModel model;
	model.setRootPath("C:/");
	QColumnView *cview = new QColumnView;
    cview->setModel(&model);

	cview->show();
    return app.exec();
}
