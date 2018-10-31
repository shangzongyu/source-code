
#include <gnome.h>
#include "app_mysql.h"

enum {
  COLUMN_TITLE,
  COLUMN_ARTIST,
  COLUMN_CATALOGUE,
  N_COLUMNS
};

GtkWidget *create_main_window();

GtkWidget *create_addcd_dialog();

GtkWidget *create_login_dialog();

void add_widget_with_label ( GtkContainer *box, gchar *caption, GtkWidget *widget);

void quit_app( GtkWidget * window, gpointer data);

gint confirm_exit();

gboolean delete_event_handler ( GtkWidget *window, GdkEvent *event, gpointer data);

void addcd_dialog_button_clicked (GtkDialog * dialog, gint response, gpointer userdata);

void on_addcd_activate (GtkMenuItem * menuitem, gpointer user_data);

void on_quit_activate (GtkMenuItem  * menuitem, gpointer user_data);

void on_about_activate (GtkMenuItem  * menuitem, gpointer user_data);

void on_search_button_clicked  (GtkButton *button, gpointer userdata);
