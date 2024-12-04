#include "add_window.h"
#include <gtk/gtk.h>

void open_new_window(GtkButton *button, gpointer user_data) {
    // Claiming window ID
    int window_id = GPOINTER_TO_INT(user_data);
    
    // Create new window
    GtkWidget *new_window = gtk_window_new();
    char window_title[50];
    snprintf(window_title, sizeof(window_title), "Routine %d", window_id);
    gtk_window_set_title(GTK_WINDOW(new_window), window_title);
    gtk_window_set_default_size(GTK_WINDOW(new_window), 500, 500);
    
    
    char label_text[50];
    snprintf(label_text, sizeof(label_text), "C'est la routine %d", window_id);
    GtkWidget *label = gtk_label_new(label_text);
    gtk_window_set_child(GTK_WINDOW(new_window), label);

    gtk_window_present(GTK_WINDOW(new_window));
}