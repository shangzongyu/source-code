#include <qmainwindow.h>


class ButtonWindow : public QMainWindow
{
  Q_OBJECT
  
  public:
    ButtonWindow(QWidget *parent = 0, const char *name = 0);
    virtual ~ButtonWindow();

  private slots:
    void Clicked();

};


