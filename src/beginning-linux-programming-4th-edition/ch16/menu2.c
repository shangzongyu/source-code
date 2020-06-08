#include <gnome.h>

void closeApp ( GtkWidget *window, gpointer data)
{
  gtk_main_quit();
}

void item_clicked(GtkWidget *widget, gpointer user_data)
{
  printf("Item Clicked!\n");
}

static GnomeUIInfo filemenu[] = {
  GNOMEUIINFO_MENU_NEW_ITEM ("New", "Menu Hint", NULL, NULL ),
  GNOMEUIINFO_MENU_OPEN_ITEM (NULL, NULL),
  GNOMEUIINFO_MENU_SAVE_AS_ITEM (NULL, NULL),
  GNOMEUIINFO_SEPARATOR,
  GNOMEUIINFO_MENU_EXIT_ITEM (NULL, NULL),
  GNOMEUIINFO_END
};

static GnomeUIInfo editmenu[] = {
  GNOMEUIINFO_MENU_FIND_ITEM (NULL, NULL),
  GNOMEUIINFO_END
};

static GnomeUIInfo menubar[] = {
  GNOMEUIINFO_MENU_FILE_TREE (filemenu),
  GNOMEUIINFO_MENU_EDIT_TREE (editmenu),
  GNOMEUIINFO_END
};

int main (int argc, char *argv[])
{
  GtkWidget *app;

  gnome_program_init ("gnome1", "0.1", LIBGNOMEUI_MODULE,
                      argc, argv,
                      GNOME_PARAM_NONE);
  app = gnome_app_new("gnome1", "Menus, menus, menus");

  gtk_window_set_default_size ( GTK_WINDOW(app), 300, 200);
  g_signal_connect ( GTK_OBJECT (app), "destroy",
                       GTK_SIGNAL_FUNC ( closeApp), NULL);

  gnome_app_create_menus ( GNOME_APP(app), menubar);

  gtk_widget_show(app);

  gtk_main();
  return 0;

}

