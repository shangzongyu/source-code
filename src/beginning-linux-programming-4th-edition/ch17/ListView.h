#include <qmainwindow.h>
#include <qlistview.h>


class ListView : public QMainWindow
{
  Q_OBJECT

  public:
    ListView(QWidget *parent = 0, const char *name = 0);

  private:
    QListView *listview;

  private slots:

};
