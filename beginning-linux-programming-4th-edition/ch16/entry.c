#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

const char * password = "secret";

void closeApp ( GtkWidget *window, gpointer data)
{
  gtk_main_quit();
}

void button_clicked (GtkWidget *button, gpointer data)
{
  const char *password_text = gtk_entry_get_text(GTK_ENTRY((GtkWidget *) data));

  if (strcmp(password_text, password) == 0)
    printf("Access granted!\n");
  else
    printf("Access denied!\n");
}


int main (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *username_label, *password_label;
  GtkWidget *username_entry, *password_entry;
  GtkWidget *ok_button;
  GtkWidget *hbox1, *hbox2;
  GtkWidget *vbox;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "GtkEntryBox");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  g_signal_connect ( GTK_OBJECT (window), "destroy", 
                       GTK_SIGNAL_FUNC ( closeApp), NULL);

  username_label = gtk_label_new("Login:");
  password_label = gtk_label_new("Password:");

  username_entry = gtk_entry_new();
  password_entry = gtk_entry_new();
  gtk_entry_set_visibility(GTK_ENTRY (password_entry), FALSE);	

  ok_button = gtk_button_new_with_label("Ok");

  g_signal_connect (GTK_OBJECT (ok_button), "clicked", 
                      GTK_SIGNAL_FUNC(button_clicked), password_entry);

  hbox1 = gtk_hbox_new ( TRUE, 5 );
  hbox2 = gtk_hbox_new ( TRUE, 5 );

  vbox = gtk_vbox_new ( FALSE, 10);

  gtk_box_pack_start(GTK_BOX(hbox1), username_label, TRUE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(hbox1), username_entry, TRUE, FALSE, 5);

  gtk_box_pack_start(GTK_BOX(hbox2), password_label, TRUE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(hbox2), password_entry, TRUE, FALSE, 5);

  gtk_box_pack_start(GTK_BOX(vbox), hbox1, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), hbox2, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), ok_button, FALSE, FALSE, 5);

  gtk_container_add(GTK_CONTAINER(window), vbox);

  gtk_widget_show_all(window);
  gtk_main ();

  return 0;
}  
