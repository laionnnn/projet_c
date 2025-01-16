#include <json-c/json.h>
#include <gtk/gtk.h>
#include <stdio.h>


void set_iterations_from_json(GtkSpinButton *spin_button, const char *json_file, int routine_id) {
    // Ouvrir le fichier JSON
    FILE *file = fopen(json_file, "r");
    if (!file) {
        g_print("Erreur : impossible d'ouvrir le fichier %s.\n", json_file);
        return;
    }

    // Lire le contenu du fichier JSON
    char buffer[4096];
    size_t read_size = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[read_size] = '\0'; // Terminer la chaîne de caractères
    fclose(file);

    // Parser le fichier JSON
    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (!parsed_json) {
        g_print("Erreur : JSON invalide ou mal formé.\n");
        return;
    }

    // Accéder au tableau "routines"
    struct json_object *routines_array;
    if (json_object_object_get_ex(parsed_json, "routines", &routines_array)) {
        int array_len = json_object_array_length(routines_array);

        // Parcourir le tableau des routines
        for (int i = 0; i < array_len; i++) {
            struct json_object *routine = json_object_array_get_idx(routines_array, i);

            // Vérifier si l'ID correspond
            struct json_object *id_obj;
            if (json_object_object_get_ex(routine, "id", &id_obj) && json_object_get_int(id_obj) == routine_id) {
                struct json_object *iteration_obj;

                // Obtenir la valeur "iteration" et la définir dans le GtkSpinButton
                if (json_object_object_get_ex(routine, "iteration", &iteration_obj)) {
                    int iteration = json_object_get_int(iteration_obj);
                    gtk_spin_button_set_value(spin_button, iteration);
                    g_print("Valeur d'itération mise à jour: %d\n", iteration);
                } else {
                    g_print("Erreur : champ 'iteration' introuvable dans la routine ID = %d.\n", routine_id);
                }
                break;
            }
        }
    } else {
        g_print("Erreur : tableau 'routines' introuvable dans le JSON.\n");
    }

    // Libérer la mémoire du JSON
    json_object_put(parsed_json);
}

void update_json_iteration(const char *json_file, int routine_id, int new_iteration) {
    // Lire le fichier JSON
    FILE *file = fopen(json_file, "r");
    if (!file) {
        g_print("Erreur : impossible d'ouvrir le fichier %s.\n", json_file);
        return;
    }

    char buffer[4096];
    size_t read_size = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[read_size] = '\0';
    fclose(file);

    // Parser le JSON
    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (!parsed_json) {
        g_print("Erreur : fichier JSON invalide.\n");
        return;
    }

    // Rechercher la routine avec l'ID donné
    struct json_object *routines_array;
    if (json_object_object_get_ex(parsed_json, "routines", &routines_array)) {
        int array_len = json_object_array_length(routines_array);
        for (int i = 0; i < array_len; i++) {
            struct json_object *routine = json_object_array_get_idx(routines_array, i);

            struct json_object *id_obj;
            if (json_object_object_get_ex(routine, "id", &id_obj) && json_object_get_int(id_obj) == routine_id) {
                // Mettre à jour la valeur d'itération
                json_object_object_add(routine, "iteration", json_object_new_int(new_iteration));
                break;
            }
        }
    } else {
        g_print("Erreur : clé 'routines' non trouvée dans le fichier JSON.\n");
        json_object_put(parsed_json);
        return;
    }

    // Écrire les modifications dans le fichier JSON
    file = fopen(json_file, "w");
    if (file) {
        fprintf(file, "%s", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
        fclose(file);
        g_print("Fichier JSON mis à jour avec succès.\n");
    } else {
        g_print("Erreur : impossible d'écrire dans le fichier %s.\n", json_file);
    }

    json_object_put(parsed_json); // Libérer la mémoire
}

// Fonction appelée lorsque la valeur du GtkSpinButton change
void on_spin_button_value_changed(GtkSpinButton *spin_button, gpointer user_data) {
    int new_iteration = gtk_spin_button_get_value_as_int(spin_button);
    int routine_id = GPOINTER_TO_INT(user_data);

    // Mettre à jour le fichier JSON
    update_json_iteration("routine.json", routine_id, new_iteration);
}