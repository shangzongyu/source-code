/* Functions to create the user interface for the
   Gnome/gtk+ CD application */

#include "app_gnome.h"

GtkWidget *treeview;
GtkWidget *appbar;
GtkWidget *artist_entry;
GtkWidget *title_entry;
GtkWidget *catalogue_entry;
GtkWidget *username_entry;
GtkWidget *password_entry;

static GtkWidget *app;

static GnomeUIInfo filemenu[] =
{
  GNOMEUIINFO_MENU_NEW_ITEM ("_New CD", NULL, on_addcd_activate, NULL),
  GNOMEUIINFO_SEPARATOR,
  GNOMEUIINFO_MENU_EXIT_ITEM (on_quit_activate, NULL),
  GNOMEUIINFO_END
};

static GnomeUIInfo helpmenu[] =
{
  GNOMEUIINFO_MENU_ABOUT_ITEM (on_about_activate, NULL),
  GNOMEUIINFO_END
};

static GnomeUIInfo menubar[] =
{
  GNOMEUIINFO_MENU_FILE_TREE (filemenu),
  GNOMEUIINFO_MENU_HELP_TREE (helpmenu),
  GNOMEUIINFO_END
};


GtkWidget *create_main_window()
{
  GtkWidget *toolbar;
  GtkWidget *vbox;
  GtkWidget *hbox;
  GtkWidget *label;
  GtkWidget *entry;
  GtkWidget *search_button;
  GtkWidget *scrolledwindow;
  GtkCellRenderer *renderer;

  app = gnome_app_new ("GnomeCD", "CD Database");

  gtk_window_set_position ( GTK_WINDOW( app), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size ( GTK_WINDOW( app ), 540, 480);

  gnome_app_create_menus (GNOME_APP (app), menubar);

  toolbar = gtk_toolbar_new ();
  gnome_app_add_toolbar (GNOME_APP (app), GTK_TOOLBAR (toolbar), "toolbar",
                                BONOBO_DOCK_ITEM_BEH_EXCLUSIVE,
                                BONOBO_DOCK_TOP, 1, 0, 0);

  gtk_container_set_border_width (GTK_CONTAINER (toolbar), 1);

  gtk_toolbar_insert_stock (GTK_TOOLBAR (toolbar),
                            "gtk-add",
                            "Add new CD",
                            NULL, GTK_SIGNAL_FUNC (on_addcd_activate), NULL, -1);

  gtk_toolbar_insert_space (GTK_TOOLBAR (toolbar), 1);

  gtk_toolbar_insert_stock (GTK_TOOLBAR (toolbar),
                            "gtk-quit",
                            "Quit the Application",
                            NULL, GTK_SIGNAL_FUNC (on_quit_activate), NULL, -1);

  label = gtk_label_new("Search String:");
  entry = gtk_entry_new ();
  search_button = gtk_button_new_with_label("Search");

  scrolledwindow = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow),
                                  GTK_POLICY_AUTOMATIC,
                                  GTK_POLICY_AUTOMATIC);
  
  vbox = gtk_vbox_new (FALSE, 0);
  hbox = gtk_hbox_new (FALSE, 0);
  
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 5);  
  gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 5); 
  gtk_box_pack_start (GTK_BOX (hbox), entry, TRUE, TRUE, 6);  
  gtk_box_pack_start (GTK_BOX (hbox), search_button, FALSE, FALSE, 5); 
  gtk_box_pack_start (GTK_BOX (vbox), scrolledwindow, TRUE, TRUE, 0);
  
  treeview = gtk_tree_view_new();
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW(treeview),
                                               COLUMN_TITLE,
                                               "Title", renderer,
                                               "text", COLUMN_TITLE,
                                               NULL);
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW(treeview),
                                               COLUMN_ARTIST,
                                               "Artist", renderer,
                                               "text", COLUMN_ARTIST,
                                               NULL);
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW(treeview),
                                               COLUMN_CATALOGUE,
                                               "Catalogue", renderer,
                                               "text", COLUMN_CATALOGUE,
                                               NULL);

  gtk_tree_view_set_search_column (GTK_TREE_VIEW (treeview),
                                             COLUMN_TITLE);

  gtk_container_add (GTK_CONTAINER (scrolledwindow), treeview);

  gnome_app_set_contents (GNOME_APP (app), vbox);
  
  appbar = gnome_appbar_new (FALSE, TRUE, GNOME_PREFERENCES_NEVER);
  gnome_app_set_statusbar (GNOME_APP (app), appbar);

  gnome_app_install_menu_hints (GNOME_APP (app), menubar);

  gtk_signal_connect (GTK_OBJECT (search_button), "clicked",
                      GTK_SIGNAL_FUNC (on_search_button_clicked),
                      entry);

  gtk_signal_connect (GTK_OBJECT(app), "delete_event",
                      GTK_SIGNAL_FUNC ( delete_event_handler ),
                      NULL);

  gtk_signal_connect (GTK_OBJECT(app), "destroy",
                      GTK_SIGNAL_FUNC ( quit_app ), NULL);

  return app;
}

GtkWidget *create_addcd_dialog()
{
  artist_entry = gtk_entry_new();
  title_entry = gtk_entry_new();
  catalogue_entry = gtk_entry_new();

  GtkWidget *dialog =  gtk_dialog_new_with_buttons ("Add CD",
                                              NULL,
                                              GTK_DIALOG_DESTROY_WITH_PARENT,
                                              GTK_STOCK_OK,
                                              GTK_RESPONSE_ACCEPT,
                                              GTK_STOCK_CANCEL,
                                              GTK_RESPONSE_REJECT,
                                              NULL);

  add_widget_with_label ( GTK_CONTAINER (GTK_DIALOG (dialog)->vbox),
                          "Artist", artist_entry);
  add_widget_with_label ( GTK_CONTAINER (GTK_DIALOG (dialog)->vbox),
                          "Title", title_entry);
  add_widget_with_label ( GTK_CONTAINER (GTK_DIALOG (dialog)->vbox),
                          "Catalogue", catalogue_entry);

  gtk_signal_connect ( GTK_OBJECT (dialog), "response",
                       GTK_SIGNAL_FUNC (addcd_dialog_button_clicked), NULL);

 return dialog;
}

GtkWidget *create_login_dialog()
{
  GtkWidget *dialog = gtk_dialog_new_with_buttons("Database Login",
                                          NULL,
                                          GTK_DIALOG_MODAL,
                                          GTK_STOCK_OK,
                                          GTK_RESPONSE_ACCEPT,
                                          GTK_STOCK_CANCEL,
                                          GTK_RESPONSE_REJECT,
                                          NULL);

  username_entry = gtk_entry_new();
  password_entry = gtk_entry_new();

  gtk_entry_set_visibility(GTK_ENTRY (password_entry), FALSE);

  add_widget_with_label ( GTK_CONTAINER (GTK_DIALOG (dialog)->vbox) , "Username", username_entry);
  add_widget_with_label ( GTK_CONTAINER (GTK_DIALOG (dialog)->vbox) , "Password", password_entry);

  gtk_widget_show_all(GTK_WIDGET (GTK_DIALOG (dialog)->vbox));

  return dialog;
}

/* Helper function to add a widget with given label to a container */
void add_widget_with_label ( GtkContainer *box, gchar *caption, GtkWidget *widget)
{
  GtkWidget *label = gtk_label_new (caption);
  GtkWidget *hbox = gtk_hbox_new (TRUE, 4);

  gtk_container_add(GTK_CONTAINER (hbox), label);
  gtk_container_add(GTK_CONTAINER (hbox), widget);

  gtk_container_add(box, hbox);
}
