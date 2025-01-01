#include "../header/add_window.h"
#include "../header/generate_action.h"
#include "../header/generate_button.h"
#include "../header/load_routine.h"
#include <gtk/gtk.h>


// Fonction qui génère une nouvelle fenêtre liée à chaque bouton
void open_new_window(GtkButton *button, gpointer user_data, GtkFlowBox *flow_box) {
    // ID de la fenêtre
    int window_id = GPOINTER_TO_INT(user_data);

    // Crée une nouvelle fenêtre
    GtkWidget *new_window = gtk_window_new();
    char window_title[50];
    snprintf(window_title, sizeof(window_title), "Routine %d", window_id);
    gtk_window_set_title(GTK_WINDOW(new_window), window_title);
    gtk_window_set_default_size(GTK_WINDOW(new_window), 700, 700);

    //Crée une page en fixed
    GtkWidget *fixed_routine_page = gtk_fixed_new();

    char label_text[50];
    snprintf(label_text, sizeof(label_text), "C'est la routine %d", window_id);
    GtkWidget *label = gtk_label_new(label_text);

    GtkWidget *button_add = gtk_button_new_with_label("Ajouter une action");

    gtk_fixed_put(GTK_FIXED(fixed_routine_page), button_add, 650, 0);
    
    GtkWidget *routine_flow_box = gtk_flow_box_new();
    gtk_widget_set_size_request(routine_flow_box, 200, 450);
    
    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(routine_flow_box), 2);

    // Configure une scroll window
    GtkWidget *scrolled_window_with_box = gtk_scrolled_window_new();
    gtk_widget_set_size_request(scrolled_window_with_box, 200, 600);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window_with_box), routine_flow_box);
    
    gtk_fixed_put(GTK_FIXED(fixed_routine_page), scrolled_window_with_box, 300, 50);

    load_actions_for_routine(GTK_FLOW_BOX(routine_flow_box), "routine.json", window_id);


    g_signal_connect(button_add, "clicked", G_CALLBACK(on_action_button_clicked), routine_flow_box);
   

    gtk_window_set_child(GTK_WINDOW(new_window), fixed_routine_page);
    gtk_window_present(GTK_WINDOW(new_window));
}