#include "ListView.moc"

ListView::ListView(QWidget *parent, const char *name) : QMainWindow(parent, name)
{
  listview = new QListView(this, "listview1");

  listview->addColumn("Artist");
  listview->addColumn("Title");
  listview->addColumn("Catalogue");

  listview->setRootIsDecorated(TRUE);

  QListViewItem *toplevel = new QListViewItem(listview, "Avril Lavigne", 
                                              "Let Go", "AVCD01");

  new QListViewItem(toplevel, "Complicated");
  new QListViewItem(toplevel, "Sk8er Boi");
                                                                                                                                    
  setCentralWidget(listview);
}

int main(int argc, char **argv)
{
  QApplication app(argc,argv);
  ListView *window = new ListView();

  app.setMainWidget(window);
  window->show();

  return app.exec();
}
