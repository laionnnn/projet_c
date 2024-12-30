#include <json-c/json.h>
#include <stdio.h>

void add_routine_to_json(const char *filename, const char *name) {
    struct json_object *parsed_json, *routines_array, *new_routine;
    int next_id = 1;

    // Charger le fichier JSON
    parsed_json = json_object_from_file(filename);
    if (!parsed_json) {
        // Si le fichier n'existe pas, créer une structure JSON de base
        parsed_json = json_object_new_object();
        routines_array = json_object_new_array();
        json_object_object_add(parsed_json, "routines", routines_array);
    } else {
        // Récupérer le tableau de routines
        if (!json_object_object_get_ex(parsed_json, "routines", &routines_array)) {
            routines_array = json_object_new_array();
            json_object_object_add(parsed_json, "routines", routines_array);
        }
    }

    // Déterminer le prochain ID (basé sur le nombre d'éléments existants)
    int array_len = json_object_array_length(routines_array);
    if (array_len > 0) {
        struct json_object *last_routine = json_object_array_get_idx(routines_array, array_len - 1);
        struct json_object *last_id;
        if (json_object_object_get_ex(last_routine, "id", &last_id)) {
            next_id = json_object_get_int(last_id) + 1;
        }
    }

    // Créer la nouvelle routine
    new_routine = json_object_new_object();
    json_object_object_add(new_routine, "id", json_object_new_int(next_id));
    json_object_object_add(new_routine, "name", json_object_new_string(name));

    // Ajouter la nouvelle routine au tableau
    json_object_array_add(routines_array, new_routine);

    // Sauvegarder dans le fichier
    if (json_object_to_file(filename, parsed_json) < 0) {
        fprintf(stderr, "Erreur : Impossible de sauvegarder dans le fichier JSON\n");
    } else {
        printf("Routine ajoutée avec succès : %s (ID : %d)\n", name, next_id);
    }

    // Libérer la mémoire JSON
    json_object_put(parsed_json);
}
