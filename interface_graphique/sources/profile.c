#include "profile.h"
#include <gtk/gtk.h>

void open_user_profile(GtkButton *button, gpointer user_data) {
    // Implémentation de la fonction
    GtkWidget *new_window = gtk_window_new();
    char window_title[50];
    snprintf(window_title, sizeof(window_title), "Profile");
    gtk_window_set_title(GTK_WINDOW(new_window), window_title);
    gtk_window_set_default_size(GTK_WINDOW(new_window), 700, 700);
    GtkWidget *user_profile = gtk_fixed_new();
    gtk_window_set_child(GTK_WINDOW(new_window), user_profile);
    gtk_window_present(GTK_WINDOW(new_window));
    // ... Ajoutez les autres éléments de la fenêtre ici ...
}
