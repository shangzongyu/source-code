#include "MainWindow.h"
#include "AddCdDialog.h"
#include "app_mysql.h"

#include <qvbox.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlistview.h>
#include <kde/kapp.h>
#include <kde/kmenubar.h>
#include <kde/klocale.h>
#include <kde/kpopupmenu.h>
#include <kde/kstatusbar.h>
#include <kde/kaction.h>
#include <kde/kstdaccel.h>

#include <string.h>


MainWindow::MainWindow ( const char * name ) : KMainWindow ( 0L, name )
{
  setCaption("CD Database");

  KAction *addcd_action = new KAction("&Add CD", "filenew",
                          KStdAccel::shortcut(KStdAccel::New),
                          this,
                          SLOT(AddCd()),
                          this);

  KAction *quit_action = KStdAction::quit(KApplication::kApplication(),
                         SLOT(quit()), actionCollection());                        
    
  QPopupMenu * filemenu = new QPopupMenu;
  QString about = ("CD App\n\n"
                 "(C) 2007 Wrox Press\n"
                 "email@email.com\n");

  QPopupMenu *helpmenu = helpMenu(about);
  menuBar()->insertItem( "&File", filemenu);
  menuBar()->insertItem(i18n("&Help"), helpmenu);

  addcd_action->plug(filemenu);
  filemenu->insertSeparator();
  quit_action->plug(filemenu);

  addcd_action->plug(toolBar());
  quit_action->plug(toolBar());
             
  QVBox *vbox = new QVBox (this);
  QHBox *hbox = new QHBox (vbox);
    
  QLabel *label = new QLabel(hbox);
  label->setText( "Search Text:" );

  search_entry = new QLineEdit ( hbox );

  QPushButton *button = new QPushButton( "Search", hbox);

  list = new QListView( vbox, "name", 0L);
  list->setRootIsDecorated(TRUE);
  list->addColumn("Title");
  list->addColumn("Artist");
  list->addColumn("Catalogue");
    
  connect ( button, SIGNAL (clicked() ), this, SLOT (doSearch() ));
  connect( search_entry , SIGNAL( returnPressed() ),
                this, SLOT( doSearch() ) );

  statusBar()->message("");
    
  setCentralWidget( vbox );
  resize (300,400);
}

void MainWindow::doSearch()
{
  cd_search_st *cd_res = new cd_search_st;
  current_cd_st *cd = new current_cd_st;
  struct current_tracks_st ct;
  int res1, i, j, res2, res3;
  char track_title[110];
  char search_text[100];
  char statusBar_text[200];
  QListViewItem *cd_item;
    
  strcpy(search_text, search_entry->text());
  
  res1 = find_cds(search_text, cd_res);
    /* Update the status bar to display the search results */
  sprintf(statusBar_text, " Displaying %d result(s) for search string ' %s '",
          res1 <= MAX_CD_RESULT ? res1 : MAX_CD_RESULT, search_text);
  statusBar()->message(statusBar_text);

  i = 0;
  list->clear();
    
  while (i < res1 && i < MAX_CD_RESULT) {

    res2 = get_cd(cd_res->cd_id[i], cd);

    cd_item = new QListViewItem(list, cd->title, cd->artist_name, cd->catalogue);

    res3 = get_cd_tracks(cd_res->cd_id[i++], &ct);
    j = 0;
     /* Populate the tree with the current cd's tracks */
    while (j < res3) {

      sprintf(track_title, " Track %d. ", j+1);
      strcat(track_title, ct.track[j++]);

      new QListViewItem(cd_item, track_title);
     }    
  }
}

void MainWindow::AddCd()
{
  AddCdDialog *dialog = new AddCdDialog(this);
  dialog->show();  
}

