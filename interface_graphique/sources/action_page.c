#include <gtk/gtk.h>
#include <json-c/json.h>
#include <stdio.h>
#include <string.h>
#include "../header/structure.h"


// Fonction pour sauvegarder les modifications des données
void save_action_data(GtkWidget *widget, gpointer user_data) {
    ActionData *data = (ActionData *)user_data;

    const char *description = gtk_editable_get_text(GTK_EDITABLE(data->description_entry));
    const char *constraints = gtk_editable_get_text(GTK_EDITABLE(data->constraints_entry));
    int iterations = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(data->iterations_spin));

    FILE *file = fopen(data->json_file, "r");
    if (!file) {
        g_print("Erreur : impossible d'ouvrir %s.\n", data->json_file);
        return;
    }

    char buffer[4096];
    size_t read_size = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[read_size] = '\0';
    fclose(file);

    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (!parsed_json) {
        g_print("Erreur : JSON invalide.\n");
        return;
    }

    struct json_object *action_array;
    if (json_object_object_get_ex(parsed_json, "actions", &action_array)) {
        int array_len = json_object_array_length(action_array);
        for (int i = 0; i < array_len; i++) {
            struct json_object *action = json_object_array_get_idx(action_array, i);

            struct json_object *id_obj;
            if (json_object_object_get_ex(action, "id", &id_obj) && json_object_get_int(id_obj) == data->action_id) {
                // Met à jour les champs de l'action
                json_object_object_add(action, "description", json_object_new_string(description));
                json_object_object_add(action, "constraints", json_object_new_string(constraints));
                json_object_object_add(action, "iteration_compleat", json_object_new_int(iterations));
                break;
            }
        }
    }

    file = fopen(data->json_file, "w");
    if (file) {
        fprintf(file, "%s", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
        fclose(file);
        g_print("Action mise à jour avec succès dans %s.\n", data->json_file);
    } else {
        g_print("Erreur : impossible d'écrire dans %s.\n", data->json_file);
    }

    json_object_put(parsed_json);
}

// Fonction pour créer la fenêtre GTK pour modifier l'action
void action_window(GtkWidget *widget, gpointer user_data) {
    int action_id = GPOINTER_TO_INT(user_data); // Récupère l'ID associé

    const char *json_file = "action.json";

    // Lecture et parsing du fichier JSON
    FILE *file = fopen(json_file, "r");
    if (!file) {
        g_print("Erreur : impossible d'ouvrir le fichier %s.\n", json_file);
        return;
    }

    char buffer[4096];
    size_t read_size = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[read_size] = '\0';
    fclose(file);

    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (!parsed_json) {
        g_print("Erreur : fichier JSON invalide ou mal formé.\n");
        return;
    }

    // Recherche de l'action avec l'ID correspondant
    struct json_object *action_array, *action;
    struct json_object *description_obj, *constraints_obj, *iterations_obj;

    const char *description = "", *constraints = "";
    int iterations = 0;

    if (json_object_object_get_ex(parsed_json, "actions", &action_array)) {
        int array_len = json_object_array_length(action_array);
        for (int i = 0; i < array_len; i++) {
            action = json_object_array_get_idx(action_array, i);

            struct json_object *id_obj;
            if (json_object_object_get_ex(action, "id", &id_obj) && json_object_get_int(id_obj) == action_id) {
                if (json_object_object_get_ex(action, "description", &description_obj))
                    description = json_object_get_string(description_obj);
                if (json_object_object_get_ex(action, "constraints", &constraints_obj))
                    constraints = json_object_get_string(constraints_obj);
                if (json_object_object_get_ex(action, "iteration_compleat", &iterations_obj))
                    iterations = json_object_get_int(iterations_obj);
                break;
            }
        }
    } else {
        g_print("Erreur : tableau 'actions' non trouvé.\n");
        json_object_put(parsed_json);
        return;
    }

    // Création de la fenêtre pour afficher/modifier les détails
    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Modifier Action");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    GtkWidget *grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    ActionData *act_data = g_malloc(sizeof(ActionData));
    act_data->json_file = json_file;
    act_data->action_id = action_id;

    GtkWidget *label_description = gtk_label_new("Description :");
    gtk_grid_attach(GTK_GRID(grid), label_description, 0, 0, 1, 1);

    GtkWidget *description_entry = gtk_entry_new();
    gtk_editable_set_text(GTK_EDITABLE(description_entry), description);
    gtk_grid_attach(GTK_GRID(grid), description_entry, 1, 0, 2, 1);
    act_data->description_entry = description_entry;

    GtkWidget *label_constraints = gtk_label_new("Contraintes :");
    gtk_grid_attach(GTK_GRID(grid), label_constraints, 0, 1, 1, 1);

    GtkWidget *constraints_entry = gtk_entry_new();
    gtk_editable_set_text(GTK_EDITABLE(constraints_entry), constraints);
    gtk_grid_attach(GTK_GRID(grid), constraints_entry, 1, 1, 2, 1);
    act_data->constraints_entry = constraints_entry;

    GtkWidget *label_iterations = gtk_label_new("Itérations complètes :");
    gtk_grid_attach(GTK_GRID(grid), label_iterations, 0, 2, 1, 1);

    GtkWidget *iterations_spin = gtk_spin_button_new_with_range(0, 1000, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(iterations_spin), iterations);
    gtk_grid_attach(GTK_GRID(grid), iterations_spin, 1, 2, 2, 1);
    act_data->iterations_spin = iterations_spin;

    GtkWidget *save_button = gtk_button_new_with_label("Enregistrer");
    gtk_grid_attach(GTK_GRID(grid), save_button, 1, 3, 1, 1);

    g_signal_connect(save_button, "clicked", G_CALLBACK(save_action_data), act_data);

    gtk_window_present(GTK_WINDOW(window));

    json_object_put(parsed_json); // Libérer la mémoire JSON
}
