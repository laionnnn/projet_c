#include <gtk/gtk.h>
#include <json-c/json.h>

#include "../header/generate_button.h"
#include "../header/profile.h"


static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    
    // Créer les boutons pour la page principale
    GtkWidget *button_add = gtk_button_new_with_label("Ajouter une routine");
    GtkWidget *button_stats = gtk_button_new_with_label("Statistique");
    GtkWidget *button_user_profile = gtk_button_new_with_label("Profile");
    GtkWidget *routine_research = gtk_search_entry_new();
    GtkWidget *button_back = gtk_button_new_with_label("Retour à la page principale");

    // Créer un conteneur GtkFixed
    GtkWidget *fixed_main = gtk_fixed_new();

    // Positionner les boutons à des endroits spécifiques
    gtk_fixed_put(GTK_FIXED(fixed_main), button_add, 650, 0);  // Position à (650, 0)
    gtk_fixed_put(GTK_FIXED(fixed_main), button_stats, 0, 0);   // Position à (0, 0)
    gtk_fixed_put(GTK_FIXED(fixed_main), button_user_profile, 0, 50);  // Position à (0, 50)
    gtk_fixed_put(GTK_FIXED(fixed_main), routine_research, 200, 0);  // Position à (200, 0)

    // Définir une taille spécifique pour chaque bouton
    gtk_widget_set_size_request(button_add, 200, 50); 
    gtk_widget_set_size_request(button_stats, 200, 50);
    gtk_widget_set_size_request(button_back, 200, 50);
    gtk_widget_set_size_request(button_user_profile, 200, 50);
    gtk_widget_set_size_request(routine_research, 450, 50);


    // Créer une petite GtkBox à l'intérieur du conteneur fixed
    GtkWidget *flow_box = gtk_flow_box_new();
    gtk_widget_set_size_request(flow_box, 200, 450);

    // Ajouter des widgets à la boîte (comme une étiquette)
    GtkWidget *titleFLOWBOX = gtk_label_new("Liste des routines");
    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(flow_box), 1);
    gtk_flow_box_append(GTK_FLOW_BOX(flow_box), titleFLOWBOX);

    // Définir la boîte comme enfant de la fenêtre défilante
    GtkWidget *scrolled_window_with_box = gtk_scrolled_window_new();
    gtk_widget_set_size_request(scrolled_window_with_box, 200, 550);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window_with_box), flow_box);

    // Positionner la boîte à l'intérieur du conteneur fixed
    gtk_fixed_put(GTK_FIXED(fixed_main), scrolled_window_with_box, 325, 100);

    // Connecter les signaux pour les clics sur les boutons
    g_signal_connect(button_add, "clicked", G_CALLBACK(on_generate_button_clicked), flow_box);
    g_signal_connect(button_user_profile, "clicked", G_CALLBACK(create_user_profile_window), "user1.json");

    // Définir le contenu de la fenêtre (le GtkStack)
    gtk_window_set_title(GTK_WINDOW(window), "Page Principale");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 700);
    gtk_window_set_child(GTK_WINDOW(window), fixed_main);

    // Enfin, afficher la fenêtre
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
