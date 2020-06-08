#include <qdialog.h>
#include <qlineedit.h>

class LogonDialog : public QDialog
{
  Q_OBJECT

  public:
    LogonDialog (QWidget *parent = 0, const char *name = 0);
    QString getUsername();
    QString getPassword();
    
  private:
    QLineEdit *username_entry, *password_entry;

};
