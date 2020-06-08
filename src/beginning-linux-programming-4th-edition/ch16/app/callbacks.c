/* This file contains callback functions and some helper functions
   for the Gnome/Gtk+ CD application */
#include "app_gnome.h"

extern GtkWidget *treeview;
extern GtkWidget *app;
extern GtkWidget *appbar;
extern GtkWidget *artist_entry;
extern GtkWidget *title_entry;
extern GtkWidget *catalogue_entry;

GtkWidget *addcd_dialog;

void quit_app( GtkWidget * window, gpointer data)
{
  database_end();
  gtk_main_quit();
}

gint confirm_exit()
{
  gint result;
  GtkWidget * dialog = gtk_message_dialog_new (NULL,
                                  GTK_DIALOG_MODAL,
                                  GTK_MESSAGE_QUESTION,
                                  GTK_BUTTONS_YES_NO,
                                  "Are you sure you want to quit?");

  result = gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);

  return (result == GTK_RESPONSE_YES);
}

gboolean delete_event_handler ( GtkWidget *window, GdkEvent *event, gpointer data)
{
  return !confirm_exit();
}

void addcd_dialog_button_clicked (GtkDialog * dialog, gint response, 
    gpointer userdata)
{
  const gchar *artist_const;
  const gchar *title_const;
  const gchar *catalogue_const;
  gchar artist[200];
  gchar title[200];
  gchar catalogue[200];
  gint *cd_id;

  if (response == GTK_RESPONSE_ACCEPT)
  {
    artist_const = gtk_entry_get_text(GTK_ENTRY (artist_entry));
    title_const =  gtk_entry_get_text(GTK_ENTRY (title_entry));
    catalogue_const = gtk_entry_get_text(GTK_ENTRY (catalogue_entry));

    strcpy(artist, artist_const);
    strcpy(title, title_const);
    strcpy(catalogue, catalogue_const);
    
    add_cd(artist, title, catalogue, cd_id);
  }

  addcd_dialog = NULL;
  gtk_widget_destroy(GTK_WIDGET(dialog));
}

/* This is the heart of the application - When we click on search, we
   fetch matching cds and their tracks, and display using the GtkTreeView */
void on_search_button_clicked  (GtkButton *button, gpointer userdata)
{
  struct cd_search_st cd_res;
  struct current_cd_st cd;
  struct current_tracks_st ct;
  gint res1, res2, res3;
  gchar track_title[110];
  const gchar *search_string_const;
  gchar search_string[200];
  gchar search_text[200];
  gint i = 0, j = 0;

  GtkTreeStore *tree_store;
  GtkTreeIter parent_iter, child_iter;

  memset(&track_title, 0, sizeof(track_title));

  /* Get the search string, and copy into a non-const pointer */
  search_string_const = gtk_entry_get_text(GTK_ENTRY (userdata));
  strcpy (search_string, search_string_const);

  /* Fetch matching cds */
  res1 = find_cds(search_string, &cd_res);

  /* Update the appbar to display the search results */
  sprintf(search_text, 
        " Displaying %d result(s) for search string ' %s '",
        MIN(res1, MAX_CD_RESULT), search_string);
  gnome_appbar_push (GNOME_APPBAR( appbar), search_text);

  tree_store = gtk_tree_store_new (N_COLUMNS,
                                   G_TYPE_STRING,
                                   G_TYPE_STRING,
                                   G_TYPE_STRING);
                                   
  /* Fetch the cd detail for each matching cd and get the tracks */                                  
  while (i < res1 && i < MAX_CD_RESULT)
  {
     res2 = get_cd(cd_res.cd_id[i], &cd);

      /* Add a new row to the model */
      gtk_tree_store_append (tree_store, &parent_iter, NULL);
      gtk_tree_store_set (tree_store, &parent_iter,
                          COLUMN_TITLE, cd.title,
                          COLUMN_ARTIST, cd.artist_name,
                          COLUMN_CATALOGUE, cd.catalogue, -1
                          );

     res3 = get_cd_tracks(cd_res.cd_id[i++], &ct);
     j = 0;
     /* Populate the tree with the current cd's tracks */
     while (j < res3)
     {

       sprintf(track_title, " Track %d. ", j+1);
       strcat(track_title, ct.track[j++]);

       gtk_tree_store_append (tree_store, &child_iter, &parent_iter);
       gtk_tree_store_set (tree_store, &child_iter,
                          COLUMN_TITLE, track_title, -1);
     }
   }

  gtk_tree_view_set_model (GTK_TREE_VIEW (treeview), 
    GTK_TREE_MODEL(tree_store));

}


void on_addcd_activate (GtkMenuItem * menuitem, gpointer user_data)
{
  /* Check to see if we have already created dialog */
  if (addcd_dialog != NULL)
      return;

  addcd_dialog = create_addcd_dialog();
  gtk_widget_show_all (addcd_dialog);

}


gboolean close_app ( GtkWidget * window, gpointer data)
{
  gboolean exit;

  if ((exit = confirm_exit()))
  {
    quit_app(NULL, NULL);
  }
  return exit;
}

void on_quit_activate (GtkMenuItem  * menuitem, gpointer user_data)
{
  close_app(NULL, NULL);
}

void on_about_activate (GtkMenuItem  * menuitem, gpointer user_data)
{
  const char * authors[] = {"Wrox Press", NULL};
  GtkWidget *about = gnome_about_new ("CD Database", "1.0",
                              "(c) Wrox Press",
                              "Beginning Linux Programming",
                              (const char ** ) authors, NULL,
                              "Translators", NULL);
  gtk_widget_show(about);
}

