#include "add_window.h"
#include "generate_action.h"
#include "generate_button.h"
#include <gtk/gtk.h>


void open_new_window(GtkButton *button, gpointer user_data, GtkFlowBox *flow_box) {
    // Claiming window ID
    int window_id = GPOINTER_TO_INT(user_data);

    // Create new window
    GtkWidget *new_window = gtk_window_new();
    char window_title[50];
    snprintf(window_title, sizeof(window_title), "Routine %d", window_id);
    gtk_window_set_title(GTK_WINDOW(new_window), window_title);
    gtk_window_set_default_size(GTK_WINDOW(new_window), 700, 700);

    GtkWidget *fixed_routine_page = gtk_fixed_new();

    char label_text[50];
    snprintf(label_text, sizeof(label_text), "C'est la routine %d", window_id);
    GtkWidget *label = gtk_label_new(label_text);

    //GtkWidget *button_delete = gtk_button_new_with_label("Supprimer la routine");
    GtkWidget *button_add = gtk_button_new_with_label("Ajouter une action");

    gtk_fixed_put(GTK_FIXED(fixed_routine_page), button_add, 650, 0);

    // Attach data for the delete button
    //g_object_set_data(G_OBJECT(button_delete), "flow_box", flow_box);
    //g_object_set_data(G_OBJECT(button_delete), "window_id", GINT_TO_POINTER(window_id));

    
    GtkWidget *routine_flow_box = gtk_flow_box_new();
    gtk_widget_set_size_request(routine_flow_box, 200, 450);  // Size of the box
    
    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(routine_flow_box), 2);

    // Setting box as scrolled_window child and setting size
    GtkWidget *scrolled_window_with_box = gtk_scrolled_window_new();
    gtk_widget_set_size_request(scrolled_window_with_box, 200, 600);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window_with_box), routine_flow_box);
    
    gtk_fixed_put(GTK_FIXED(fixed_routine_page), scrolled_window_with_box, 300, 50);  // Position at (300, 50)

    g_signal_connect(button_add, "clicked", G_CALLBACK(on_action_button_clicked), routine_flow_box);
    // Add functionality for the add button (if needed)
    // g_signal_connect(button_add, "clicked", G_CALLBACK(on_generate_add_action), GINT_TO_POINTER(window_id));

    gtk_window_set_child(GTK_WINDOW(new_window), fixed_routine_page);
    gtk_window_present(GTK_WINDOW(new_window));
}
