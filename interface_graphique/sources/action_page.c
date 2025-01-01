#include <gtk/gtk.h>
#include <json-c/json.h>
#include <stdio.h>
#include <string.h>

// Structure pour stocker les champs des actions et les informations du fichier JSON
typedef struct {
    GtkWidget *name_entry;
    GtkWidget *description_entry;
    GtkWidget *constraints_entry;
    const char *json_file;
    int routine_id;   // Identifiant de la routine
    int action_id;    // Identifiant de l'action
} ActionData;

// Fonction pour sauvegarder les modifications des données de l'action
void save_action_data(GtkWidget *widget, gpointer user_data) {
    ActionData *data = (ActionData *)user_data;

    const char *name = gtk_editable_get_text(GTK_EDITABLE(data->name_entry));
    const char *description = gtk_editable_get_text(GTK_EDITABLE(data->description_entry));
    const char *constraints = gtk_editable_get_text(GTK_EDITABLE(data->constraints_entry));

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

    struct json_object *routine_array;
    if (json_object_object_get_ex(parsed_json, "routine", &routine_array)) {
        struct json_object *routine = json_object_array_get_idx(routine_array, 0); // Première routine
        struct json_object *action_array;

        if (json_object_object_get_ex(routine, "action", &action_array)) {
            struct json_object *action = json_object_array_get_idx(action_array, data->action_id); // Action à l'index donné
            json_object_object_add(action, "name", json_object_new_string(name));
            json_object_object_add(action, "description", json_object_new_string(description));
            json_object_object_add(action, "constraints", json_object_new_string(constraints));
        }
    }

    file = fopen(data->json_file, "w");
    if (file) {
        fprintf(file, "%s", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
        fclose(file);
        g_print("Action mise à jour avec succès dans %s.\n", data->json_file);
    }

    json_object_put(parsed_json);
}

// Fonction pour créer la fenêtre GTK pour modifier l'action
void action_window(GtkWidget *widget, gpointer user_data) {
    const char *json_file = user_data;

    ActionData *data = g_malloc(sizeof(ActionData));
    data->json_file = json_file;
    data->routine_id = 1; // Exemple : Routine ID
    data->action_id = 1;  // Exemple : Action ID

    // Charger le fichier JSON
    FILE *file = fopen(json_file, "r");
    if (!file) {
        g_print("Erreur : impossible d'ouvrir %s.\n", json_file);
        return;
    }

    char buffer[4096];
    size_t read_size = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[read_size] = '\0';
    fclose(file);

    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (!parsed_json || !json_object_is_type(parsed_json, json_type_object)) {
        g_print("Erreur : JSON invalide ou mal formé.\n");
        return;
    }

    const char *n = "", *desc = "", *cons = "";

    struct json_object *routines_array;
    if (json_object_object_get_ex(parsed_json, "routines", &routines_array)) {
        int routines_len = json_object_array_length(routines_array);

        for (int i = 0; i < routines_len; i++) {
            struct json_object *routine = json_object_array_get_idx(routines_array, i);
            struct json_object *routine_id_obj, *actions_array;

            // Vérifier que la routine correspond
            if (json_object_object_get_ex(routine, "id", &routine_id_obj) &&
                json_object_get_int(routine_id_obj) == data->routine_id) {

                // Récupérer les actions de la routine
                if (json_object_object_get_ex(routine, "actions", &actions_array)) {
                    int actions_len = json_object_array_length(actions_array);

                    for (int j = 0; j < actions_len; j++) {
                        struct json_object *action = json_object_array_get_idx(actions_array, j);
                        struct json_object *action_id_obj;

                        // Vérifier que l'action correspond
                        if (json_object_object_get_ex(action, "id", &action_id_obj) &&
                            json_object_get_int(action_id_obj) == data->action_id) {

                            // Extraire les informations de l'action
                            struct json_object *name_obj, *description_obj, *constraints_obj;

                            if (json_object_object_get_ex(action, "name", &name_obj))
                                n = json_object_get_string(name_obj);

                            if (json_object_object_get_ex(action, "description", &description_obj))
                                desc = json_object_get_string(description_obj);

                            if (json_object_object_get_ex(action, "constraints", &constraints_obj))
                                cons = json_object_get_string(constraints_obj);

                            g_print("Action chargée : Routine ID=%d, Action ID=%d\n", data->routine_id, data->action_id);
                            break; // Quitter la boucle des actions
                        }
                    }
                }
                break; // Quitter la boucle des routines
            }
        }
    }

    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Modifier Action");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    GtkWidget *grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    GtkWidget *label_name = gtk_label_new("Nom :");
    gtk_grid_attach(GTK_GRID(grid), label_name, 0, 0, 1, 1);

    data->name_entry = gtk_entry_new();
    gtk_editable_set_text(GTK_EDITABLE(data->name_entry), n);
    gtk_grid_attach(GTK_GRID(grid), data->name_entry, 1, 0, 2, 1);

    GtkWidget *label_description = gtk_label_new("Description :");
    gtk_grid_attach(GTK_GRID(grid), label_description, 0, 1, 1, 1);

    data->description_entry = gtk_entry_new();
    gtk_editable_set_text(GTK_EDITABLE(data->description_entry), desc);
    gtk_grid_attach(GTK_GRID(grid), data->description_entry, 1, 1, 2, 1);

    GtkWidget *label_constraints = gtk_label_new("Contraintes :");
    gtk_grid_attach(GTK_GRID(grid), label_constraints, 0, 2, 1, 1);

    data->constraints_entry = gtk_entry_new();
    gtk_editable_set_text(GTK_EDITABLE(data->constraints_entry), cons);
    gtk_grid_attach(GTK_GRID(grid), data->constraints_entry, 1, 2, 2, 1);

    GtkWidget *save_button = gtk_button_new_with_label("Enregistrer");
    gtk_grid_attach(GTK_GRID(grid), save_button, 1, 3, 1, 1);
    g_signal_connect(save_button, "clicked", G_CALLBACK(save_action_data), data);

    gtk_window_present(GTK_WINDOW(window));
}
