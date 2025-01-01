#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

/* Used 
void modifier_user_profile(const char *nom_fichier, const char *champ, const char *nouvelle_valeur) {
    FILE *file;
    char buffer[2048];

    // Ouverture du fichier JSON
    file = fopen(nom_fichier, "r");
    if (file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s.\n", nom_fichier);
        return;
    }

    // Lecture du contenu du fichier JSON
    fread(buffer, sizeof(buffer) - 1, 1, file);
    fclose(file);

    // Parsing du JSON
    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (parsed_json == NULL) {
        printf("Erreur : fichier JSON invalide.\n");
        return;
    }

    // Récupération de la section "user_profile"
    struct json_object *user_profile_array;
    if (!json_object_object_get_ex(parsed_json, "user_profile", &user_profile_array)) {
        printf("Erreur : la section 'user_profile' est introuvable.\n");
        json_object_put(parsed_json);
        return;
    }

    // Parcourir le tableau "user_profile"
    struct json_object *user_profile_obj = json_object_array_get_idx(user_profile_array, 0); // Supposons qu'il y ait un seul élément
    if (user_profile_obj != NULL) {
        // Modification de la valeur du champ
        struct json_object *champ_obj;
        if (json_object_object_get_ex(user_profile_obj, champ, &champ_obj)) {
            json_object_object_add(user_profile_obj, champ, json_object_new_string(nouvelle_valeur));
            printf("Le champ '%s' dans 'user_profile' a été mis à jour en '%s'.\n", champ, nouvelle_valeur);
        } else {
            printf("Erreur : le champ '%s' est introuvable dans 'user_profile'.\n", champ);
        }
    }

    // Sauvegarde du fichier JSON mis à jour
    file = fopen(nom_fichier, "w");
    if (file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s en écriture.\n", nom_fichier);
        json_object_put(parsed_json);
        return;
    }

    fprintf(file, "%s", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
    fclose(file);

    // Libération de la mémoire
    json_object_put(parsed_json);

    printf("Modification terminée dans le fichier %s.\n", nom_fichier);
}

*/

/*
Used as rename :
void modifier_routinename(const char *nom_fichier, const char *champ, const char *nouvelle_valeur) {
    FILE *file;
    char buffer[4096];

    // Ouverture du fichier JSON
    file = fopen(nom_fichier, "r");
    if (file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s.\n", nom_fichier);
        return;
    }

    // Lecture du contenu du fichier JSON
    fread(buffer, sizeof(buffer) - 1, 1, file);
    fclose(file);

    // Parsing du JSON
    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (parsed_json == NULL) {
        printf("Erreur : fichier JSON invalide.\n");
        return;
    }

    // Récupération de la section "routine"
    struct json_object *routine_array;
    if (!json_object_object_get_ex(parsed_json, "routine", &routine_array)) {
        printf("Erreur : la section 'routine' est introuvable.\n");
        json_object_put(parsed_json);
        return;
    }

    // Parcourir le tableau "routine"
    for (int i = 0; i < json_object_array_length(routine_array); i++) {
        struct json_object *routine_obj = json_object_array_get_idx(routine_array, i);

        struct json_object *nested_routine_array;
        if (json_object_object_get_ex(routine_obj, "routine", &nested_routine_array)) {
            // Parcourir les routines imbriquées
            for (int j = 0; j < json_object_array_length(nested_routine_array); j++) {
                struct json_object *nested_routine_obj = json_object_array_get_idx(nested_routine_array, j);

                struct json_object *name_obj;
                if (json_object_object_get_ex(nested_routine_obj, champ, &name_obj)) {
                    // Modification du champ
                    json_object_object_add(nested_routine_obj, champ, json_object_new_string(nouvelle_valeur));
                    printf("Le champ '%s' a été mis à jour en '%s'.\n", champ, nouvelle_valeur);
                }
            }
        }
    }

    // Sauvegarde du fichier JSON mis à jour
    file = fopen(nom_fichier, "w");
    if (file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s en écriture.\n", nom_fichier);
        json_object_put(parsed_json);
        return;
    }

    fprintf(file, "%s", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
    fclose(file);

    // Libération de la mémoire
    json_object_put(parsed_json);

    printf("Modification terminée dans le fichier %s.\n", nom_fichier);
}
*/



// Fonction pour charger et afficher les données de l'action
void fetch_action_data(const char *filename, ActionData *data) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        g_print("Erreur : impossible d'ouvrir %s.\n", filename);
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

    struct json_object *routines_array;
    if (json_object_object_get_ex(parsed_json, "routines", &routines_array)) {
        int routines_len = json_object_array_length(routines_array);

        for (int i = 0; i < routines_len; i++) {
            struct json_object *routine = json_object_array_get_idx(routines_array, i);
            struct json_object *routine_id_obj, *actions_array;

            // Vérifier si la routine correspond à l'ID donné
            if (json_object_object_get_ex(routine, "id", &routine_id_obj) &&
                json_object_get_int(routine_id_obj) == data->routine_id) {

                // Récupérer le tableau des actions
                if (json_object_object_get_ex(routine, "actions", &actions_array)) {
                    int actions_len = json_object_array_length(actions_array);

                    for (int j = 0; j < actions_len; j++) {
                        struct json_object *action = json_object_array_get_idx(actions_array, j);
                        struct json_object *action_id_obj;

                        // Vérifier si l'action correspond à l'ID donné
                        if (json_object_object_get_ex(action, "id", &action_id_obj) &&
                            json_object_get_int(action_id_obj) == data->action_id) {

                            // Extraire les informations de l'action
                            struct json_object *name_obj, *description_obj, *constraints_obj;

                            if (json_object_object_get_ex(action, "name", &name_obj))
                                gtk_editable_set_text(GTK_EDITABLE(data->name_entry), json_object_get_string(name_obj));

                            if (json_object_object_get_ex(action, "description", &description_obj))
                                gtk_editable_set_text(GTK_EDITABLE(data->description_entry), json_object_get_string(description_obj));

                            if (json_object_object_get_ex(action, "constraints", &constraints_obj))
                                gtk_editable_set_text(GTK_EDITABLE(data->constraints_entry), json_object_get_string(constraints_obj));

                            g_print("Action chargée : Routine ID=%d, Action ID=%d\n", data->routine_id, data->action_id);
                            break; // Quitter la boucle des actions
                        }
                    }
                }
                break; // Quitter la boucle des routines
            }
        }
    } else {
        g_print("Erreur : aucune routine trouvée dans le fichier JSON.\n");
    }

    json_object_put(parsed_json);
}


void modifier_routine(const char *nom_fichier, const char *champ, const char *nouvelle_valeur) {
    FILE *file;
    char buffer[4096];

    // Ouverture du fichier JSON
    file = fopen(nom_fichier, "r");
    if (file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s.\n", nom_fichier);
        return;
    }

    // Lecture du contenu du fichier JSON
    fread(buffer, sizeof(buffer) - 1, 1, file);
    fclose(file);

    // Parsing du JSON
    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (parsed_json == NULL) {
        printf("Erreur : fichier JSON invalide.\n");
        return;
    }

    // Récupération de la section "routine"
    struct json_object *routine_array;
    if (!json_object_object_get_ex(parsed_json, "routine", &routine_array)) {
        printf("Erreur : la section 'routine' est introuvable.\n");
        json_object_put(parsed_json);
        return;
    }

    // Parcourir le tableau "routine"
    for (int i = 0; i < json_object_array_length(routine_array); i++) {
        struct json_object *routine_obj = json_object_array_get_idx(routine_array, i);

        struct json_object *champ_obj;
        if (json_object_object_get_ex(routine_obj, champ, &champ_obj)) {
            // Modification du champ spécifié
            json_object_object_add(routine_obj, champ, json_object_new_string(nouvelle_valeur));
            printf("Le champ '%s' de la routine %d a été mis à jour en '%s'.\n", champ, i, nouvelle_valeur);
        } else {
            printf("Erreur : le champ '%s' est introuvable dans la routine %d.\n", champ, i);
        }
    }

    // Sauvegarde du fichier JSON mis à jour
    file = fopen(nom_fichier, "w");
    if (file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s en écriture.\n", nom_fichier);
        json_object_put(parsed_json);
        return;
    }

    fprintf(file, "%s", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
    fclose(file);

    // Libération de la mémoire
    json_object_put(parsed_json);

    printf("Modification terminée dans le fichier %s.\n", nom_fichier);
}

// Function to modify a specific field of an action
void modifier_action(const char *nom_fichier, const char *field, const char *nouvelle_valeur) {
    FILE *file;
    char buffer[4096];

    // Open the JSON file
    file = fopen(nom_fichier, "r");
    if (file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s.\n", nom_fichier);
        return;
    }

    // Read the JSON file content
    size_t read_size = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[read_size] = '\0'; // Null-terminate the buffer
    fclose(file);

    // Parse JSON content
    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (parsed_json == NULL) {
        printf("Erreur : fichier JSON invalide ou mal formé.\n");
        return;
    }

    // Access "routine" array
    struct json_object *routine_array;
    if (!json_object_object_get_ex(parsed_json, "routine", &routine_array)) {
        printf("Erreur : la section 'routine' est introuvable.\n");
        json_object_put(parsed_json);
        return;
    }

    // Iterate through "routine" array
    for (int i = 0; i < json_object_array_length(routine_array); i++) {
        struct json_object *routine_obj = json_object_array_get_idx(routine_array, i);

        // Access "action" array
        struct json_object *action_array;
        if (json_object_object_get_ex(routine_obj, "action", &action_array)) {
            printf("Routine trouvée. Modification des actions...\n");

            // Iterate through "action" array
            for (int j = 0; j < json_object_array_length(action_array); j++) {
                struct json_object *action_obj = json_object_array_get_idx(action_array, j);

                // Modify the specified field
                struct json_object *field_obj;
                if (json_object_object_get_ex(action_obj, field, &field_obj)) {
                    json_object_object_add(action_obj, field, json_object_new_string(nouvelle_valeur));
                    printf("Champ '%s' de l'action modifié en '%s'.\n", field, nouvelle_valeur);
                } else {
                    printf("Erreur : le champ '%s' est introuvable dans l'action.\n", field);
                }
            }
        }
    }

    // Save updated JSON back to the file
    file = fopen(nom_fichier, "w");
    if (file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s en écriture.\n", nom_fichier);
        json_object_put(parsed_json);
        return;
    }

    fprintf(file, "%s", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
    fclose(file);

    // Free memory
    json_object_put(parsed_json);

    printf("Modification terminée dans le fichier %s.\n", nom_fichier);
}


int main() {
    const char *nom_fichier = "data.json";
    modifier_user_profile(nom_fichier, "name","aaaaa");
    modifier_user_profile(nom_fichier, "familyname","qwerewq");
    modifier_user_profile(nom_fichier, "age","123");
    modifier_user_profile(nom_fichier, "sex","m");
    modifier_user_profile(nom_fichier, "status","eeeee");
    modifier_user_profile(nom_fichier, "na","qqqqq");

    modifier_routine(nom_fichier, "name","bbb");
    modifier_routine(nom_fichier, "description","aaa");
    modifier_routine(nom_fichier, "iteration_goal","bbbbb");
    modifier_routine(nom_fichier, "time","111111");

    
    
    modifier_action(nom_fichier, "name", "new_action_2");
    modifier_action(nom_fichier, "description", "abc");
    modifier_action(nom_fichier, "constraints", "def");
    return 0;
}
