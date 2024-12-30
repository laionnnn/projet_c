#include <gtk/gtk.h>
#include <json-c/json.h>
#include <string.h>
#include <stdio.h>


void rename_routine(const char *old_name, const char *new_name) {

    const char *filename = "routine.json"; 
    struct json_object *parsed_json, *routines_array;
    
    // Charger le fichier JSON
    parsed_json = json_object_from_file(filename);
    if (!parsed_json) {
        g_warning("Erreur de chargement du fichier JSON.");
        return;
    }

    // Récupérer le tableau des routines
    if (!json_object_object_get_ex(parsed_json, "routines", &routines_array)) {
        g_warning("Aucune routine trouvée dans le fichier JSON.");
        json_object_put(parsed_json); // Libérer la mémoire
        return;
    }

    int array_len = json_object_array_length(routines_array);
    gboolean routine_found = FALSE;

    // Chercher la routine avec l'ancien nom
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

    // Si la routine a été trouvée et renommée, sauvegarder les changements
    if (routine_found) {
        if (json_object_to_file(filename, parsed_json) < 0) {
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


void rename_gtk(GtkButton *button, gpointer user_data){
    GtkEntry *old_name_entry = GTK_ENTRY(user_data);
    const char *old_name = gtk_editable_get_text(GTK_EDITABLE(old_name_entry));
    
    // Récupérer le nouveau nom de la routine
    GtkEntry *new_name_entry = GTK_ENTRY(g_object_get_data(G_OBJECT(button), "new_name_entry"));
    const char *new_name = gtk_editable_get_text(GTK_EDITABLE(new_name_entry));

    // Appeler la fonction de renommage
    rename_routine(old_name, new_name);
}
