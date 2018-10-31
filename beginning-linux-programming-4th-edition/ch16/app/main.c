/* CD Application graphical user interface using Gnome/Gtk+ */
#include <stdio.h>
#include <stdlib.h>

#include "app_gnome.h"

/* Need to reference username and password entry boxes from
   interface.c */
extern GtkWidget *username_entry;
extern GtkWidget *password_entry;

gint main(gint argc, gchar *argv[])
{
  GtkWidget *login_dialog; 
  const char *user_const;
  const char *pass_const;
  gchar username[100];
  gchar password[100]; 
  gint result;
  
  
  gnome_program_init ("CdDatabase", "0.1", LIBGNOMEUI_MODULE,
                      argc, argv,
                      GNOME_PARAM_APP_DATADIR, "",
                      NULL);
  GtkWidget *main_window = create_main_window();
  gtk_widget_show_all(main_window);

  /* Must login to database before we start, so create dialog to
     input username and password */
  login_dialog = create_login_dialog();
 
  while (1)
  {   
    result = gtk_dialog_run (GTK_DIALOG (login_dialog));
    /* If we click cancel, then confirm exit */
    if (result != GTK_RESPONSE_ACCEPT)
    {
      if (confirm_exit())
        return 0;
      else
        continue;
    }
    /* Retrieve username and password */
    user_const = gtk_entry_get_text(GTK_ENTRY (username_entry));
    pass_const = gtk_entry_get_text(GTK_ENTRY (password_entry));
    strcpy(username, user_const);
    strcpy(password, pass_const);
    
    if (database_start(username, password) == TRUE)
      break;

    /* If we couldn't logon, then display error message and try again */
    GtkWidget * error_dialog = gtk_message_dialog_new (GTK_WINDOW(main_window),
                              GTK_DIALOG_DESTROY_WITH_PARENT,
                              GTK_MESSAGE_ERROR,
                              GTK_BUTTONS_CLOSE,
                              "Could not log on! - Check Username and Password");
    gtk_dialog_run (GTK_DIALOG (error_dialog));
    gtk_widget_destroy (error_dialog);
  }
  
  gtk_widget_destroy (login_dialog);
  gtk_main();
 
  return 0;
}
