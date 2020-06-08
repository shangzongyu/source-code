#include <kde/kmainwindow.h>
#include <qlistview.h>
#include <qlineedit.h>

class MainWindow : public KMainWindow
{
  Q_OBJECT

  public:
    MainWindow ( const char * name );

  public slots:
     void doSearch();
     void AddCd();
     
  private:
     QListView *list;
     QLineEdit *search_entry;
     
};

