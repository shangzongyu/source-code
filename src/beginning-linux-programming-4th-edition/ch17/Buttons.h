#include <qmainwindow.h>
#include <qcheckbox.h>
#include <qbutton.h>
#include <qradiobutton.h>

class Buttons : public QMainWindow
{
  Q_OBJECT

  public:
    Buttons(QWidget *parent = 0, const char *name = 0);
  private:
    void PrintActive(QButton *button);
    QCheckBox *checkbox;
    QRadioButton *radiobutton1, *radiobutton2;

  private slots:
    void Clicked();

};

