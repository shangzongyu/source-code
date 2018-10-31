#include "AddCdDialog.h"
#include "app_mysql.h"

#include <qlayout.h>
#include <qlabel.h>

AddCdDialog::AddCdDialog( QWidget *parent)
   : KDialogBase( parent, "AddCD", false, "Add CD ",
     KDialogBase::Ok|KDialogBase::Cancel, KDialogBase::Ok, true )
{

  QWidget *widget = new QWidget(this);
  setMainWidget(widget);

  QGridLayout *grid = new QGridLayout(widget,3,2,10, 5,"grid");

  grid->addWidget(new QLabel("Artist", widget, "artistlabel"), 0, 0, 0);
  grid->addWidget(new QLabel("Title", widget, "titlelabel"), 1, 0, 0);
  grid->addWidget(new QLabel("Catalogue", widget, "cataloguelabel"), 2, 0, 0);

  artist_entry = new QLineEdit( widget, "artist_entry");
  title_entry = new QLineEdit( widget, "title_entry");
  catalogue_entry = new QLineEdit( widget, "catalogue_entry");

  grid->addWidget(artist_entry, 0,1, 0);
  grid->addWidget(title_entry, 1,1, 0);
  grid->addWidget(catalogue_entry, 2,1, 0);

  connect (this, SIGNAL(okClicked()), this, SLOT(okClicked()));

 }

void AddCdDialog::okClicked()
{
  char artist[200];
  char title[200];
  char catalogue[200];
  int cd_id = 0;

  strcpy(artist, artist_entry->text());
  strcpy(title, title_entry->text());
  strcpy(catalogue, catalogue_entry->text());

  add_cd(artist, title, catalogue, &cd_id);
  
}

 