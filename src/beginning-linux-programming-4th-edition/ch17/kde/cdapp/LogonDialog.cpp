#include "LogonDialog.h"
#include "app_mysql.h"

#include <qpushbutton.h>
#include <qlayout.h>
#include <qlabel.h>

LogonDialog::LogonDialog( QWidget *parent, const char *name): QDialog(parent, name)
{
  QGridLayout *grid = new QGridLayout(this, 3, 2, 10, 5,"grid");

  grid->addWidget(new QLabel("Username", this, "usernamelabel"), 0, 0, 0);
  grid->addWidget(new QLabel("Password", this, "passwordlabel"), 1, 0, 0);

  username_entry = new QLineEdit( this, "username_entry");
  password_entry = new QLineEdit( this, "password_entry");
  password_entry->setEchoMode(QLineEdit::Password);
  
  grid->addWidget(username_entry, 0, 1, 0);
  grid->addWidget(password_entry, 1, 1, 0);

  QPushButton *button = new QPushButton ("Ok", this, "button");
  grid->addWidget(button, 2, 1,Qt::AlignRight);

  connect (button, SIGNAL(clicked()), this, SLOT(accept()));

}

QString LogonDialog::getUsername()
{
  if (username_entry == NULL)
    return NULL;
    
  return username_entry->text();
}

QString LogonDialog::getPassword()
{
  if (password_entry == NULL)
    return NULL;

  return password_entry->text();
}


 