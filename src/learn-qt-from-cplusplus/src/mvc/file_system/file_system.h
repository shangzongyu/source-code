#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <QtGui/QMainWindow>
#include "ui_file_system.h"

class file_system : public QMainWindow
{
	Q_OBJECT

public:
	file_system(QWidget *parent = 0, Qt::WFlags flags = 0);
	~file_system();

private:
	Ui::file_systemClass ui;
};

#endif // FILE_SYSTEM_H
