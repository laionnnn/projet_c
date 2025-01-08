#include <json-c/json.h>
#include <stdio.h>


// Fonction qui ajoute au json la nouvelle routine
void add_action_to_json(const char *filename, const char *name, const char *description, const char *constraints, int iteration_compleat) {
    struct json_object *parsed_json, *actions_array, *new_action;
    int next_id = 0;

    // Charge le fichier JSON
    parsed_json = json_object_from_file(filename);
    if (!parsed_json) {
        // Si le fichier n'existe pas, crée un nouveau JSON
        parsed_json = json_object_new_object();
        actions_array = json_object_new_array();
        json_object_object_add(parsed_json, "actions", actions_array);
    } else {
        // Récupère le tableau "actions"
        if (!json_object_object_get_ex(parsed_json, "actions", &actions_array)) {
            actions_array = json_object_new_array();
            json_object_object_add(parsed_json, "actions", actions_array);
        }
    }

    // Configure le prochain ID unique
    int array_len = json_object_array_length(actions_array);
    if (array_len > 0) {
        struct json_object *last_action = json_object_array_get_idx(actions_array, array_len - 1);
        struct json_object *last_id;
        if (json_object_object_get_ex(last_action, "id", &last_id)) {
            next_id = json_object_get_int(last_id) + 1;
        }
    }

    // Crée une nouvelle action
    new_action = json_object_new_object();
    json_object_object_add(new_action, "id", json_object_new_int(next_id));
    json_object_object_add(new_action, "name", json_object_new_string(name));
    json_object_object_add(new_action, "description", json_object_new_string(description));
    json_object_object_add(new_action, "constraints", json_object_new_string(constraints));
    json_object_object_add(new_action, "iteration_compleat", json_object_new_int(iteration_compleat));

    // Ajoute l'action au tableau "actions"
    json_object_array_add(actions_array, new_action);

    // Sauvegarde le fichier JSON de manière lisible
    if (json_object_to_file_ext(filename, parsed_json, JSON_C_TO_STRING_PRETTY) < 0) {
        fprintf(stderr, "Erreur : Impossible de sauvegarder dans le fichier JSON\n");
    } else {
        printf("Action ajoutée avec succès : %s (ID : %d)\n", name, next_id);
    }

    // Libère la mémoire JSON
    json_object_put(parsed_json);
}
