#include <gtk/gtk.h>

void closeApp ( GtkWidget *window, gpointer data)
{
  gtk_main_quit();
}

int main (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *spinbutton;
  GtkObject *adjustment;

  gtk_init (&argc, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size ( GTK_WINDOW(window), 300, 200);
  g_signal_connect ( GTK_OBJECT (window), "destroy",
                       GTK_SIGNAL_FUNC ( closeApp), NULL);
                       
  adjustment = gtk_adjustment_new(100.0, 50.0, 150.0, 0.5, 0.05, 0.05); 
  spinbutton = gtk_spin_button_new(GTK_ADJUSTMENT(adjustment), 0.01, 2);

  gtk_container_add(GTK_CONTAINER(window), spinbutton);
  gtk_widget_show_all(window);
  gtk_main ();

  return 0;
}
