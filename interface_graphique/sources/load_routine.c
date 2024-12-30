#include <gtk/gtk.h>
#include <json-c/json.h>
#include "../header/load_routine.h"
#include "../header/add_window.h"


// Fonction qui permet de charger les routines existantes
void load_routines_from_json(GtkFlowBox *flow_box, const char *filename) {

    // Ouvre le fichier json
    FILE *file = fopen(filename, "r");
    if (!file) {
        g_warning("Fichier JSON non trouvé : %s", filename);
        return;
    }

    // Parser le json
    struct json_object *parsed_json;
    parsed_json = json_object_from_file(filename);
    fclose(file);

    if (!parsed_json) {
        g_warning("Erreur lors de l'analyse du fichier JSON.");
        return;
    }

    // Parcours du tableau json, crée un bouton pour chaque ID
    struct json_object *routines_array;
    if (json_object_object_get_ex(parsed_json, "routines", &routines_array)) {
        int array_len = json_object_array_length(routines_array);
        for (int i = 0; i < array_len; i++) {
            struct json_object *routine = json_object_array_get_idx(routines_array, i);
            const char *name = json_object_get_string(json_object_object_get(routine, "name"));

            // Créer un bouton pour chaque routine
            GtkWidget *button = gtk_button_new_with_label(name);

            // Connecter le bouton à la fonction d'ouvrir une fênetre
            g_signal_connect(button, "clicked", G_CALLBACK(open_new_window), GINT_TO_POINTER(i));

            gtk_flow_box_append(GTK_FLOW_BOX(flow_box), button);
            gtk_widget_set_visible(button, TRUE);
        }
    }

    json_object_put(parsed_json);  // Libérer la mémoire JSON
}


// Fonction qui permet d'actualiser 
void reload_routines(GtkWidget *widget, gpointer user_data) {
    GtkFlowBox *flow_box = GTK_FLOW_BOX(user_data); 
    const char *filename = "routine.json"; 
    gtk_flow_box_remove_all(flow_box);
    GtkWidget *titleFLOWBOX = gtk_label_new("Liste des routines");
    gtk_widget_set_size_request(titleFLOWBOX, 190, 50); 
    gtk_flow_box_append(GTK_FLOW_BOX(flow_box), titleFLOWBOX);
    load_routines_from_json(flow_box, filename);
}
