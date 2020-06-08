#include "KDEMenu.h"

#include <kde/kapp.h>
#include <kde/kaction.h>
#include <kde/kstdaccel.h>
#include <kde/kmenubar.h>
#include <kde/kaboutdialog.h>

KDEMenu::KDEMenu( const char * name ) : KMainWindow ( 0L, name )
{

  KAction *act = new KAction("&New",
                             "filenew",
                             KStdAccel::shortcut(KStdAccel::New),
                             this,
                             SLOT(newFile()),
                             this);

  KAction *act2 = KStdAction::quit(KApplication::kApplication(), 
      SLOT(quit()), actionCollection());

  KAction *help_action = KStdAction::aboutApp(this, 
      SLOT(aboutApp()), actionCollection());                           
  QPopupMenu *file_menu = new QPopupMenu;
  QPopupMenu *help_menu = new QPopupMenu;
  
  menuBar()->insertItem("&File", file_menu);
  menuBar()->insertItem("&Help", help_menu);
  
  act->plug(file_menu);
  file_menu->insertSeparator();
  act2->plug(file_menu);

  help_action->plug(help_menu);
  
  act->plug(toolBar());
  act2->plug(toolBar());
}

void KDEMenu::newFile()
{

}

void KDEMenu::aboutApp()
{
   KAboutDialog *about = new KAboutDialog(this, "dialog");
   about->setAuthor(QString("A. N. Author"), QString("an@email.net"),
                    QString("http://url.com"), QString("work"));
   about->setVersion("1.0");

   about->show();
   
}

int main(int argc, char **argv)
{
  KApplication app( argc, argv, "cdapp" );
  KDEMenu *window = new KDEMenu("bob");

  app.setMainWidget(window);
  window->show();

  return app.exec();
}
  
