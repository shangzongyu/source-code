#include <gtk/gtk.h>
#include <stdio.h>

static int count = 0;

void button_clicked ( GtkWidget *button, gpointer data)
{
  printf("%s pressed %d time(s) \n", (char *) data, ++count);
}

int main (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *button;

  gtk_init(&argc, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  button = gtk_button_new_with_label("Hello World!");
  gtk_container_add(GTK_CONTAINER(window), button);

 
  g_signal_connect(GTK_OBJECT (button), "clicked", 
                   GTK_SIGNAL_FUNC (button_clicked), 
                   "Button 1");
  gtk_widget_show(button);
  gtk_widget_show(window);
  
  gtk_main ();

  return 0;
} 
