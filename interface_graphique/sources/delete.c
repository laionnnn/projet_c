#include <gtk/gtk.h>
#include <json-c/json.h>
#include <string.h>
#include <stdio.h>

void delete_routine(GtkButton *button, gpointer user_data) {
    const char *filename = "action.json";

    // Récupère le texte
    const char *routine_name = gtk_editable_get_text(GTK_EDITABLE(user_data));

    struct json_object *parsed_json, *routines_array, *routine;
    int found = 0;

    // Charger le json
    parsed_json = json_object_from_file(filename);
    if (!parsed_json) {
        g_warning("Impossible de lire le fichier JSON : %s", filename);
        return;
    }

    // Récupère le tableau
    if (!json_object_object_get_ex(parsed_json, "actions", &routines_array)) {
        g_warning("Tableau de routines non trouvé.");
        json_object_put(parsed_json);
        return;
    }

    // Parcourir le tableau et supprimer l'élément correspondant
    int array_len = json_object_array_length(routines_array);
    for (int i = 0; i < array_len; i++) {
        routine = json_object_array_get_idx(routines_array, i);
        const char *name = json_object_get_string(json_object_object_get(routine, "name"));

        if (strcmp(name, routine_name) == 0) {
            json_object_array_del_idx(routines_array, i, 1);
            found = 1;
            break;
        }
    }

    if (found) {
        // Sauvegarder le fichier modifié en version lisible
        if (json_object_to_file_ext(filename, parsed_json, JSON_C_TO_STRING_PRETTY) < 0) {
            fprintf(stderr, "Erreur lors de la sauvegarde du fichier JSON.\n");
        } else {
            printf("Routine supprimée avec succès : %s\n", routine_name);
        }
    } else {
        g_warning("Routine non trouvée : %s", routine_name);
    }


    // Libérer la mémoire JSON
    json_object_put(parsed_json);
}
