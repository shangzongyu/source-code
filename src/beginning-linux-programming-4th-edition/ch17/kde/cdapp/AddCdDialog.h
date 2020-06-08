#include <kde/kdialogbase.h>
#include <qlineedit.h>

class AddCdDialog : public KDialogBase
{
  Q_OBJECT

  public:
    AddCdDialog ( QWidget *parent );

  private:
    QLineEdit *artist_entry, *title_entry, *catalogue_entry;
    
  public slots:
    void okClicked();
};

