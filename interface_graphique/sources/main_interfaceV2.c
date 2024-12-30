#include <gtk/gtk.h>
#include <json-c/json.h>
#include "../header/generate_button.h"
#include "../header/profile.h"
#include "../header/load_routine.h"
#include "../header/delete.h"



static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    
    // Créer les boutons pour la page principale
    GtkWidget *button_add = gtk_button_new_with_label("Ajouter une routine");
    GtkWidget *button_stats = gtk_button_new_with_label("Statistique");
    GtkWidget *button_user_profile = gtk_button_new_with_label("Profile");
    GtkWidget *routine_research = gtk_search_entry_new();
    GtkWidget *button_back = gtk_button_new_with_label("Retour à la page principale");
    GtkWidget *delete_entry = gtk_entry_new();
    GtkWidget *save = gtk_button_new_with_label("Enregistrer");
    GtkWidget *reload = gtk_button_new_with_label("Actualiser");


    // Ajoute le texte pour delete_entry
    gtk_entry_set_placeholder_text(GTK_ENTRY(delete_entry), "Supprimer une routine");

    // Créer un conteneur GtkFixed
    GtkWidget *fixed_main = gtk_fixed_new();

    // Positionner les boutons à des endroits spécifiques
    gtk_fixed_put(GTK_FIXED(fixed_main), button_add, 650, 0);  
    gtk_fixed_put(GTK_FIXED(fixed_main), reload, 650, 50);  
    gtk_fixed_put(GTK_FIXED(fixed_main), button_stats, 0, 0);
    gtk_fixed_put(GTK_FIXED(fixed_main), button_user_profile, 0, 50);
    gtk_fixed_put(GTK_FIXED(fixed_main), routine_research, 200, 0);
    gtk_fixed_put(GTK_FIXED(fixed_main), delete_entry, 200, 50);
    gtk_fixed_put(GTK_FIXED(fixed_main), save, 550, 50);

    // Définir une taille spécifique pour chaque bouton
    gtk_widget_set_size_request(button_add, 200, 50); 
    gtk_widget_set_size_request(reload, 200, 50); 
    gtk_widget_set_size_request(button_stats, 200, 50);
    gtk_widget_set_size_request(button_back, 200, 50);
    gtk_widget_set_size_request(button_user_profile, 200, 50);
    gtk_widget_set_size_request(save, 100, 50);
    gtk_widget_set_size_request(routine_research, 450, 50);
    gtk_widget_set_size_request(delete_entry, 350, 50);


    // Crée une flowbox pour faire une liste de routine
    GtkWidget *flow_box = gtk_flow_box_new();
    gtk_widget_set_size_request(flow_box, 200, 450);

    
    GtkWidget *titleFLOWBOX = gtk_label_new("Liste des routines");
    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(flow_box), 1);
    gtk_flow_box_append(GTK_FLOW_BOX(flow_box), titleFLOWBOX);

    GtkWidget *scrolled_window_with_box = gtk_scrolled_window_new();
    gtk_widget_set_size_request(scrolled_window_with_box, 200, 550);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window_with_box), flow_box);

    // Positionner la boîte à l'intérieur du conteneur fixed
    gtk_fixed_put(GTK_FIXED(fixed_main), scrolled_window_with_box, 325, 100);

    // Connecter les signaux pour les clics sur les boutons
    g_signal_connect(button_add, "clicked", G_CALLBACK(on_generate_button_clicked), flow_box);
    g_signal_connect(button_user_profile, "clicked", G_CALLBACK(user_profile_window), "user1.json");
    g_signal_connect(save, "clicked", G_CALLBACK(delete_routine), delete_entry);
    g_signal_connect(reload, "clicked", G_CALLBACK(reload_routines), flow_box);

    // Charge les routines enregistrer
    load_routines_from_json(GTK_FLOW_BOX(flow_box), "routine.json");

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
