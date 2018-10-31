#include "ComboBox.moc"

#include <qlayout.h>
#include <iostream>

ComboBox::ComboBox(QWidget *parent, const char *name) : QMainWindow(parent, name)
{
  QWidget *widget = new QWidget(this);
  setCentralWidget(widget);

  QVBoxLayout *vbox = new QVBoxLayout(widget, 5, 10,"vbox");

  QComboBox *editablecombo = new QComboBox(TRUE, widget, "editable");
  vbox->addWidget(editablecombo);
  QComboBox *readonlycombo = new QComboBox(FALSE, widget, "readonly");
  vbox->addWidget(readonlycombo);

  static const char* items[] = { "Macbeth", "Twelfth Night", "Othello", 0 };
  editablecombo->insertStrList (items);
  readonlycombo->insertStrList (items);

  connect (editablecombo, SIGNAL(textChanged(const QString&)),
           this, SLOT(Changed(const QString&))); 
  resize( 350, 200 );
  
}
void ComboBox::Changed(const QString& s)
{
  std::cout << s << "\n";
}


int main(int argc, char **argv)
{
  QApplication app(argc,argv);
  ComboBox *window = new ComboBox();

  app.setMainWidget(window);
  window->show();

  return app.exec();
}

