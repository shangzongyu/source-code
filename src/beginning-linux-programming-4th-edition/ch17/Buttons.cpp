#include "Buttons.moc"
#include <qbuttongroup.h>

#include <qpushbutton.h>

#include <qapplication.h>
#include <qlabel.h>
#include <qlayout.h>

#include <iostream>

Buttons::Buttons(QWidget *parent, const char *name) : QMainWindow(parent, name)
{
  QWidget *widget = new QWidget(this);
  setCentralWidget(widget);

  QVBoxLayout *vbox = new QVBoxLayout(widget,5, 10,"vbox");

  checkbox = new QCheckBox("CheckButton", widget, "check");
  vbox->addWidget(checkbox);
  QButtonGroup *buttongroup = new QButtonGroup(0);

  radiobutton1 = new QRadioButton("RadioButton1", widget, "radio1");
  buttongroup->insert(radiobutton1);
  vbox->addWidget(radiobutton1);

  radiobutton2 = new QRadioButton("RadioButton2", widget, "radio2");
  buttongroup->insert(radiobutton2);
  vbox->addWidget(radiobutton2);

  QPushButton *button = new QPushButton ("Ok", widget, "button");
  vbox->addWidget(button);

  resize( 350, 200 );

  connect (button, SIGNAL(clicked()), this, SLOT(Clicked()));
}

void Buttons::PrintActive(QButton *button)
{
  if (button->isOn())
    std::cout << button->name() << " is checked\n";
  else
    std::cout << button->name() << " is not checked\n";
}

void Buttons::Clicked(void)
{
   PrintActive(checkbox);
   PrintActive(radiobutton1);
   PrintActive(radiobutton2);
   std::cout << "\n";
}

int main(int argc, char **argv)
{
  QApplication app(argc,argv);
  Buttons *window = new Buttons();

  app.setMainWidget(window);
  window->show();

  return app.exec();
}


