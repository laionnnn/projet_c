#include <json-c/json.h>
#include <stdio.h>


// Fonction qui ajoute au json la nouvelle routine
void add_routine_to_json(const char *filename, const char *name) {
    struct json_object *parsed_json, *routines_array, *new_routine;
    int next_id = 1;

    // Charge le json
    parsed_json = json_object_from_file(filename);
    if (!parsed_json) {
        // Si le fichier n'existe pas, crée un nouveau json
        parsed_json = json_object_new_object();
        routines_array = json_object_new_array();
        json_object_object_add(parsed_json, "routines", routines_array);
    } else {
        // Récupère le tableau
        if (!json_object_object_get_ex(parsed_json, "routines", &routines_array)) {
            routines_array = json_object_new_array();
            json_object_object_add(parsed_json, "routines", routines_array);
        }
    }

    // configure l'ID pour ne pas avoir le même
    int array_len = json_object_array_length(routines_array);
    if (array_len > 0) {
        struct json_object *last_routine = json_object_array_get_idx(routines_array, array_len - 1);
        struct json_object *last_id;
        if (json_object_object_get_ex(last_routine, "id", &last_id)) {
            next_id = json_object_get_int(last_id) + 1;
        }
    }

    // Crée une routine
    new_routine = json_object_new_object();
    json_object_object_add(new_routine, "id", json_object_new_int(next_id));
    json_object_object_add(new_routine, "name", json_object_new_string(name));

    // Ajoute la routine au tableau
    json_object_array_add(routines_array, new_routine);

    // Sauvegarde le fichier en lisible
    if (json_object_to_file_ext(filename, parsed_json, JSON_C_TO_STRING_PRETTY) < 0) {
        fprintf(stderr, "Erreur : Impossible de sauvegarder dans le fichier JSON\n");
    } else {
        printf("Routine ajoutée avec succès : %s (ID : %d)\n", name, next_id);
    }

    // Libérer la mémoire JSON
    json_object_put(parsed_json);
}
