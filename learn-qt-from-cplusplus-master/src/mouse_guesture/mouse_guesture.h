#ifndef MOUSE_GUESTURE_H
#define MOUSE_GUESTURE_H

#include <QtGui/QMainWindow>
#include "ui_mouse_guesture.h"

class mouse_guesture : public QMainWindow
{
	Q_OBJECT

public:
	mouse_guesture(QWidget *parent = 0, Qt::WFlags flags = 0);
	~mouse_guesture();

private:
	Ui::mouse_guestureClass ui;
};

#endif // MOUSE_GUESTURE_H
