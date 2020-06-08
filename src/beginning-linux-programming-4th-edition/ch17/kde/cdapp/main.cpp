#include "MainWindow.h"
#include "app_mysql.h"
#include "LogonDialog.h"

#include <kapp.h>
#include <qmessagebox.h>


int main( int argc, char **argv )
{
  char username[100];
  char password[100];

  KApplication a( argc, argv, "cdapp" );

  LogonDialog *dialog = new LogonDialog();

  while (1)
  {
    if (dialog->exec() == QDialog::Accepted)
    {
      strcpy(username, dialog->getUsername());
      strcpy(password, dialog->getPassword());
        
      if (database_start(username, password))
        break;
      QMessageBox::information(0, "Title", "Could not Logon: Check username and/or password",
                            QMessageBox::Ok);
        continue;
    }
    else
    {
      if (QMessageBox::information(0, "Title", "Are you sure you want to quit?",
                               QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
      {
        return 0;
      }
    }
  }
  delete dialog;
            
  MainWindow *window = new MainWindow( "Cd App" );
  window->resize( 600, 400 );

  a.setMainWidget( window );
  window->show();

  return a.exec();
}
