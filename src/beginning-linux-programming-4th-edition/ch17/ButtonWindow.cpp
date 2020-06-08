
#include "ButtonWindow.moc"
#include <qpushbutton.h>
#include <qapplication.h>
#include <iostream>

ButtonWindow::ButtonWindow(QWidget *parent, const char *name) 
             : QMainWindow(parent, name)
{
  this->setCaption("This is the window Title");
  QPushButton *button = new QPushButton("Click Me!", this, "Button1");
  button->setGeometry(50,30,70,20);
  connect (button, SIGNAL(clicked()), this, SLOT(Clicked()));
}

ButtonWindow::~ButtonWindow()
{
}

void ButtonWindow::Clicked(void)
{
  std::cout << "clicked!\n";
}

int main(int argc, char **argv)
{
  QApplication app(argc,argv);
  ButtonWindow *window = new ButtonWindow();

  app.setMainWidget(window);
  window->show();

  return app.exec();
}

