#include <gtk/gtk.h>
#include <json-c/json.h>
#include "../header/structure.h"


// Fonction pour mettre à jour le fichier JSON
void update_user_profile(GtkWidget *widget, gpointer data) {
    UserProfileData *profile_data = (UserProfileData *)data;

    // Récupérer les valeurs des champs d'entrée
    const char *name = gtk_editable_get_text(GTK_EDITABLE(profile_data->name_entry));
    const char *family_name = gtk_editable_get_text(GTK_EDITABLE(profile_data->familyname_entry));
    const char *age = gtk_editable_get_text(GTK_EDITABLE(profile_data->age_entry));
    const char *sexe = gtk_editable_get_text(GTK_EDITABLE(profile_data->sexe_entry));
    const char *status = gtk_editable_get_text(GTK_EDITABLE(profile_data->status_entry));

    // Ouvrir et lire le fichier JSON
    FILE *file = fopen(profile_data->json_file, "r");
    if (!file) {
        g_print("Erreur : impossible d'ouvrir le fichier %s.\n", profile_data->json_file);
        return;
    }

    char buffer[4096];
    size_t read_size = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[read_size] = '\0';
    fclose(file);

    // Parser le contenu JSON
    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (!parsed_json) {
        g_print("Erreur : fichier JSON invalide ou mal formé.\n");
        return;
    }

    
    struct json_object *user_profile_array;
    if (json_object_object_get_ex(parsed_json, "user_profile", &user_profile_array)) {
        struct json_object *user_profile = json_object_array_get_idx(user_profile_array, 0);
        if (user_profile) {
            // Modifier les champs dans `user_profile`
            json_object_object_add(user_profile, "name", json_object_new_string(name));
            json_object_object_add(user_profile, "family_name", json_object_new_string(family_name));
            json_object_object_add(user_profile, "age", json_object_new_string(age));
            json_object_object_add(user_profile, "sexe", json_object_new_string(sexe));
            json_object_object_add(user_profile, "statue", json_object_new_string(status));
            g_print("Profil utilisateur mis à jour avec succès.\n");
        }
    }

    // Écrire les modifications dans le fichier JSON
    file = fopen(profile_data->json_file, "w");
    if (!file) {
        g_print("Erreur : impossible d'ouvrir le fichier %s en écriture.\n", profile_data->json_file);
        json_object_put(parsed_json);
        return;
    }

    fprintf(file, "%s", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
    fclose(file);
    json_object_put(parsed_json);

    g_print("Les modifications ont été enregistrées dans %s.\n", profile_data->json_file);
}

// Crée une page GTK
void user_profile_window(const char *data, gpointer user_data) {
    const char *json_file = user_data;

    UserProfileData *profile_data = g_malloc(sizeof(UserProfileData));
    profile_data->json_file = json_file;

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

    // Obtenir les données utilisateur
    struct json_object *user_profile_array, *user_profile;
    struct json_object *name_obj, *family_name_obj, *age_obj, *sexe_obj, *status_obj;

    const char *n = "", *family_n = "", *ages = "", *sexeMF = "", *statuss = "";

    if (json_object_object_get_ex(parsed_json, "user_profile", &user_profile_array)) {
        user_profile = json_object_array_get_idx(user_profile_array, 0);
        if (user_profile) {
            if (json_object_object_get_ex(user_profile, "name", &name_obj))
                n = json_object_get_string(name_obj);
            if (json_object_object_get_ex(user_profile, "family_name", &family_name_obj))
                family_n = json_object_get_string(family_name_obj);
            if (json_object_object_get_ex(user_profile, "age", &age_obj))
                ages = json_object_get_string(age_obj);
            if (json_object_object_get_ex(user_profile, "sexe", &sexe_obj))
                sexeMF = json_object_get_string(sexe_obj);
            if (json_object_object_get_ex(user_profile, "statue", &status_obj))
                statuss = json_object_get_string(status_obj);
        }
    }

    // Crée les boutons/entrées
    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Modifier le Profile");
    gtk_window_set_default_size(GTK_WINDOW(window), 210, 205);
    gtk_window_set_resizable(window, FALSE);

    GtkWidget *grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);

    profile_data->name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(profile_data->name_entry), n);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Prénom:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), profile_data->name_entry, 1, 0, 1, 1);

    profile_data->familyname_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(profile_data->familyname_entry), family_n);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Nom:"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), profile_data->familyname_entry, 1, 1, 1, 1);

    profile_data->age_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(profile_data->age_entry), ages);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Age:"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), profile_data->age_entry, 1, 2, 1, 1);

    profile_data->sexe_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(profile_data->sexe_entry), sexeMF);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Sexe:"), 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), profile_data->sexe_entry, 1, 3, 1, 1);

    profile_data->status_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(profile_data->status_entry), statuss);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Status:"), 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), profile_data->status_entry, 1, 4, 1, 1);

    GtkWidget *button = gtk_button_new_with_label("Enregistrer");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 6, 2, 1);
    g_signal_connect(button, "clicked", G_CALLBACK(update_user_profile), profile_data);

    gtk_window_present(GTK_WINDOW(window));
}
