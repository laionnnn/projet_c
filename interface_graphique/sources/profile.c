#include "profile.h"
#include <gtk/gtk.h>

void open_user_profile(GtkButton *button, gpointer user_data) {
    // Implémentation de la fonction
    GtkWidget *new_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(new_window), "Profile");
    gtk_window_set_default_size(GTK_WINDOW(new_window), 700, 700);
    GtkWidget *user_profile = gtk_fixed_new();

    GtkWidget *last_name = gtk_label_new ("Nom : ");
    GtkWidget *age = gtk_label_new ("Age : ");
    GtkWidget *sexe = gtk_label_new ("Sexe : ");
    GtkWidget *first_name = gtk_label_new ("Prénom : ");
    GtkWidget *status = gtk_label_new ("Status social : ");

    GtkWidget *last_name_entry = gtk_entry_new();
    GtkWidget *age_entry = gtk_entry_new();
    GtkWidget *sexe_entry = gtk_entry_new();
    GtkWidget *first_name_entry = gtk_entry_new();
    GtkWidget *status_entry = gtk_entry_new();

    gtk_fixed_put(GTK_FIXED(user_profile), last_name, 50, 50);  // Position at (0, 0)
    gtk_fixed_put(GTK_FIXED(user_profile), age, 50, 100);  // Position at (0, 0)
    gtk_fixed_put(GTK_FIXED(user_profile), sexe, 50, 150);  // Position at (0, 0)
    gtk_fixed_put(GTK_FIXED(user_profile), first_name, 50, 200);  // Position at (0, 0)
    gtk_fixed_put(GTK_FIXED(user_profile), status, 50, 250);  // Position at (0, 0)

    gtk_fixed_put(GTK_FIXED(user_profile), last_name_entry, 100, 50);
    gtk_fixed_put(GTK_FIXED(user_profile), age_entry, 100, 100);
    gtk_fixed_put(GTK_FIXED(user_profile), sexe_entry, 100, 150);
    gtk_fixed_put(GTK_FIXED(user_profile), first_name_entry, 100, 200);
    gtk_fixed_put(GTK_FIXED(user_profile), status_entry, 100, 250);

    gtk_window_set_child(GTK_WINDOW(new_window), user_profile);
    gtk_window_present(GTK_WINDOW(new_window));
}
