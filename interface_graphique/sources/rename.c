#include <gtk/gtk.h>
#include <json-c/json.h>
#include <string.h>
#include <stdio.h>


void rename_json(const char *old_name, const char *new_name) {

    const char *filename = "action.json"; 
    struct json_object *parsed_json, *routines_array;
    
    // Charger le fichier JSON
    parsed_json = json_object_from_file(filename);
    if (!parsed_json) {
        g_warning("Erreur de chargement du fichier JSON.");
        return;
    }

    // Récupère les données
    if (!json_object_object_get_ex(parsed_json, "actions", &routines_array)) {
        g_warning("Aucune routine trouvée dans le fichier JSON.");
        json_object_put(parsed_json); // Libérer la mémoire
        return;
    }

    int array_len = json_object_array_length(routines_array);
    gboolean routine_found = FALSE;

    // Cherche l'ancien nom
    for (int i = 0; i < array_len; i++) {
        struct json_object *routine = json_object_array_get_idx(routines_array, i);
        struct json_object *name_obj;
        if (json_object_object_get_ex(routine, "name", &name_obj)) {
            const char *current_name = json_object_get_string(name_obj);

            if (strcmp(current_name, old_name) == 0) {
                // Si le nom correspond, on le remplace par le nouveau nom
                json_object_object_add(routine, "name", json_object_new_string(new_name));
                routine_found = TRUE;
                break;
            }
        }
    }

    //sauvegarder
    if (routine_found) {
        if (json_object_to_file_ext(filename, parsed_json, JSON_C_TO_STRING_PRETTY) < 0) {
            g_warning("Erreur lors de l'enregistrement du fichier JSON.");
        } else {
            g_print("Routine renommée avec succès : %s -> %s\n", old_name, new_name);
        }
    } else {
        g_warning("Aucune routine avec ce nom n'a été trouvée.");
    }

    // Libérer la mémoire JSON
    json_object_put(parsed_json);
}


void rename_gtk(GtkButton *button, gpointer user_data) {
    // Vérifier si user_data est bien un GtkEntry
    if (!GTK_IS_ENTRY(user_data)) {
        g_warning("user_data n'est pas un GtkEntry valide.");
        return;
    }

    GtkEntry *old_name_entry = GTK_ENTRY(user_data);
    const char *old_name = gtk_editable_get_text(GTK_EDITABLE(old_name_entry));

    if (!old_name || *old_name == '\0') {
        g_warning("L'ancien nom est vide ou invalide.");
        return;
    }

    // Récupérer le GtkEntry pour le nouveau nom
    GtkEntry *new_name_entry = GTK_ENTRY(g_object_get_data(G_OBJECT(button), "new_name_entry"));

    // Vérifier si le GtkEntry du nouveau nom est valide
    if (!GTK_IS_ENTRY(new_name_entry)) {
        g_warning("Le widget 'new_name_entry' n'est pas un GtkEntry valide.");
        return;
    }

    const char *new_name = gtk_editable_get_text(GTK_EDITABLE(new_name_entry));

    if (!new_name || *new_name == '\0') {
        g_warning("Le nouveau nom est vide ou invalide.");
        return;
    }

    // Appeler la fonction pour renommer (supposée correcte)
    rename_json(old_name, new_name);

    // Message de confirmation (optionnel)
    g_message("Renommage effectué : %s -> %s", old_name, new_name);
}
