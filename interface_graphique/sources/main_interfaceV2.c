#include <gtk/gtk.h>
#include <json-c/json.h>
#include "../header/generate_button.h"
#include "../header/profile.h"
#include "../header/load_routine.h"
#include "../header/delete.h"
#include "../header/rename.h"
#include "../header/interface_stat.h"
#include "../header/add_routine_json.h"

static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    
    // Créer les boutons pour la page principale
    GtkWidget *button_add = gtk_button_new_with_label("Ajouter une action");
    GtkWidget *button_stats = gtk_button_new_with_label("Statistique");
    GtkWidget *button_user_profile = gtk_button_new_with_label("Profile");
    GtkWidget *iterations_spin = gtk_spin_button_new_with_range(0, 1000, 1);
    GtkWidget *button_back = gtk_button_new_with_label("Retour à la page principale");
    GtkWidget *delete_entry = gtk_entry_new();
    GtkWidget *iteration_title = gtk_label_new("Nombre d'itération :");
    GtkWidget *old_name = gtk_entry_new();
    GtkWidget *new_name = gtk_entry_new();
    GtkWidget *delete = gtk_button_new_with_label("Supprimer");
    GtkWidget *reload = gtk_button_new_with_label("Actualiser");
    GtkWidget *rename_button = gtk_button_new_with_label("Renommer");


    // Ajoute le texte pour delete_entry
    gtk_entry_set_placeholder_text(GTK_ENTRY(delete_entry), "Supprimer une action");
    gtk_entry_set_placeholder_text(GTK_ENTRY(old_name), "Renommer : ancien nom");
    gtk_entry_set_placeholder_text(GTK_ENTRY(new_name), "Renommer : nouveau nom");

    // Créer un conteneur GtkFixed
    GtkWidget *fixed_main = gtk_fixed_new();

    // Positionner les boutons à des endroits spécifiques
    gtk_fixed_put(GTK_FIXED(fixed_main), button_add, 650, 0);  
    gtk_fixed_put(GTK_FIXED(fixed_main), reload, 650, 100);  
    gtk_fixed_put(GTK_FIXED(fixed_main), button_stats, 0, 0);
    gtk_fixed_put(GTK_FIXED(fixed_main), rename_button, 0, 100);  
    gtk_fixed_put(GTK_FIXED(fixed_main), button_user_profile, 0, 50);
    gtk_fixed_put(GTK_FIXED(fixed_main), iterations_spin, 350, 0);
    gtk_fixed_put(GTK_FIXED(fixed_main), iteration_title, 200, 0);
    gtk_fixed_put(GTK_FIXED(fixed_main), delete_entry, 200, 50);
    gtk_fixed_put(GTK_FIXED(fixed_main), delete, 650, 50);
    gtk_fixed_put(GTK_FIXED(fixed_main), old_name, 200, 100);
    gtk_fixed_put(GTK_FIXED(fixed_main), new_name, 425, 100);

    // Définir une taille spécifique pour chaque bouton
    gtk_widget_set_size_request(button_add, 200, 50);
    gtk_widget_set_size_request(rename_button, 200, 50);
    gtk_widget_set_size_request(iteration_title, 100, 50);
    gtk_widget_set_size_request(reload, 200, 50); 
    gtk_widget_set_size_request(button_stats, 200, 50);
    gtk_widget_set_size_request(button_back, 200, 50);
    gtk_widget_set_size_request(button_user_profile, 200, 50);
    gtk_widget_set_size_request(delete, 200, 50);
    gtk_widget_set_size_request(iterations_spin, 300, 50);
    gtk_widget_set_size_request(delete_entry, 450, 50);
    gtk_widget_set_size_request(old_name, 225, 50);
    gtk_widget_set_size_request(new_name, 225, 50);


    // Crée une flowbox pour faire une liste de routine
    GtkWidget *flow_box = gtk_flow_box_new();
    gtk_widget_set_size_request(flow_box, 200, 450);
    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(flow_box), 1);
    
    GtkWidget *titleFLOWBOX = gtk_label_new("Liste des actions");
    gtk_flow_box_append(GTK_FLOW_BOX(flow_box), titleFLOWBOX);

    GtkWidget *scrolled_window_with_box = gtk_scrolled_window_new();
    gtk_widget_set_size_request(scrolled_window_with_box, 200, 450);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window_with_box), flow_box);

    // Positionner la boîte à l'intérieur du conteneur fixed
    gtk_fixed_put(GTK_FIXED(fixed_main), scrolled_window_with_box, 325, 200);

    // Connecter les signaux pour les clics sur les boutons
    g_signal_connect(button_stats, "clicked", G_CALLBACK(interface_stat), NULL);
    g_signal_connect(button_add, "clicked", G_CALLBACK(on_generate_button_clicked), flow_box);
    g_signal_connect(button_user_profile, "clicked", G_CALLBACK(user_profile_window), "user1.json");
    g_signal_connect(delete, "clicked", G_CALLBACK(delete_routine), delete_entry);
    g_signal_connect(reload, "clicked", G_CALLBACK(reload_routines), flow_box);
    g_signal_connect(rename_button, "clicked", G_CALLBACK(rename_gtk), old_name);

    g_signal_connect(iterations_spin, "value-changed", G_CALLBACK(on_spin_button_value_changed), GINT_TO_POINTER(1));

    set_iterations_from_json(iterations_spin, "routine.json", 1);
    
    // Charge les routines enregistrer
    load_routines_from_json(GTK_FLOW_BOX(flow_box), "action.json");

    // Détail de la fenêtre principale
    gtk_window_set_title(GTK_WINDOW(window), "Page Principale");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 700);
    gtk_window_set_child(GTK_WINDOW(window), fixed_main);

    // Afficher la fenêtre
    gtk_window_present(GTK_WINDOW(window));
}


int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    
    app = gtk_application_new("org.gtk.interface1", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    return status;
}
