#include <gtk/gtk.h>
#include <stdio.h>
#include "../header/stat.h"
#include <string.h>
#include <json-c/json.h>
#include <time.h>

void interface_stat(GtkWidget *widget, gpointer user_data) {

    //----------recuperation date----------

    time_t now;
    struct tm *local_time;

    time(&now);
    local_time = localtime(&now);
    int actual_date[3] = {local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900};


    //----------recuperation donnee----------



    struct json_object *parsed_json, *routines_array, *routine;
    char *filename = "routine.json";

     // Charger le fichier JSON
    parsed_json = json_object_from_file(filename);
    if (!parsed_json) {
        g_warning("Erreur lors de la lecture du fichier JSON.");
        return;
    }

    // Récupérer le tableau des routines
    if (!json_object_object_get_ex(parsed_json, "routines", &routines_array)) {
        g_warning("Aucune routine trouvée dans le fichier JSON.");
        json_object_put(parsed_json);
        return;
    }
    int routine_index = 0;
    routine = json_object_array_get_idx(routines_array, routine_index);

    //donnees simples

    const char* name = json_object_get_string(json_object_object_get(routine, "name"));
    int iteration_compleate = json_object_get_int(json_object_object_get(routine, "iteration"));


    //dates

    const char* creation_date_str = json_object_get_string(json_object_object_get(routine, "creationDate")); 
    int creation_date[3];
    sscanf(creation_date_str, "%d-%d-%d", &creation_date[0], &creation_date[1], &creation_date[2]);


    const char* end_date_str = json_object_get_string(json_object_object_get(routine, "EndDate"));
    int end_date[3];
    sscanf(end_date_str, "%d-%d-%d", &end_date[0], &end_date[1], &end_date[2]);

    
    //actions
    

    struct json_object *parsed_json2, *action_array, *actions;
    char *filename2 = "action.json";

    char *nom[20];
    float iteration_compleate_action[20];

    // Charger le fichier JSON
    parsed_json2 = json_object_from_file(filename2);
    if (!parsed_json2) {
        g_warning("Erreur lors de la lecture du fichier JSON.");
        return;
    }

    // Récupérer le tableau des actions
    if (!json_object_object_get_ex(parsed_json2, "actions", &action_array)) {
        g_warning("Aucune routine trouvée dans le fichier JSON.");
        json_object_put(parsed_json2);
        return;
    }

    int nb_actions = json_object_array_length(action_array);

    for(int i=0; i<nb_actions; i++){
        
        
        actions = json_object_array_get_idx(action_array, i);        
        nom[i] = json_object_get_string(json_object_object_get(actions, "name"));
        iteration_compleate_action[i] = (float)json_object_get_int(json_object_object_get(actions, "id"));

    }


    //----------calculs----------

    float nb_day_since_start = dif_date(creation_date,actual_date);

    //----------interface----------

    // Créer une nouvelle fenêtre
    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Exemple GtkLevelBar");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 700);

    // Créer un conteneur horizontal principal
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), main_box);

    // Créer le premier conteneur vertical
    GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_append(GTK_BOX(main_box), left_box);

    // Créer le second conteneur vertical
    GtkWidget *midl_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_append(GTK_BOX(main_box), midl_box);

    // Créer le dernier conteneur vertical
    GtkWidget *right_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_append(GTK_BOX(main_box), right_box);


    //-------------------------------label titre-------------------------------

    // Créer un GtkLabel pour le texte
    GtkWidget *label = gtk_label_new("ROUTINE 1");
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER); // Centrer le label

    gtk_box_append(GTK_BOX(left_box), label);

    //-------------------------------description-------------------------------

    // Créer un GtkLabel pour le texte
    GtkWidget *label2 = gtk_label_new("test d'une routine du matin");
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER); // Centrer le label

    gtk_box_append(GTK_BOX(left_box), label2);

    //-------------------------------date début-------------------------------

    // Créer un GtkLabel pour le texte
    GtkWidget *label3 = gtk_label_new(g_strdup_printf("date création : %d/%d/%d",creation_date[0],creation_date[1],creation_date[2]));
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER); // Centrer le label

    gtk_box_append(GTK_BOX(left_box), label3);

    //-------------------------------date fin-------------------------------

    // Créer un GtkLabel pour le texte
    GtkWidget *label4 = gtk_label_new(g_strdup_printf("date de fin : %d/%d/%d",end_date[0],end_date[1],end_date[2]));
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER); // Centrer le label

    gtk_box_append(GTK_BOX(left_box), label4);

    //-------------------------------date actuel-------------------------------

    // Créer un GtkLabel pour le texte
    GtkWidget *label5 = gtk_label_new(g_strdup_printf("date de actuel : %d/%d/%d",actual_date[0],actual_date[1],actual_date[2]));
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER); // Centrer le label

    gtk_box_append(GTK_BOX(left_box), label5);

    //-------------------------------label avancement-------------------------------

    // Créer un GtkLabel pour le texte
    GtkWidget *label6 = gtk_label_new("avancement : ");
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER); // Centrer le label

    gtk_box_append(GTK_BOX(left_box), label6);

    //-------------------------------level bar avancement-------------------------------

    // Créer une GtkLevelBar
    int avancement = calcul_persent_compleate(creation_date,actual_date,end_date);
    GtkWidget *levelbar = gtk_level_bar_new();
    gtk_level_bar_set_min_value(GTK_LEVEL_BAR(levelbar), 0);  // Valeur minimale
    gtk_level_bar_set_max_value(GTK_LEVEL_BAR(levelbar), 100); // Valeur maximale
    gtk_level_bar_set_value(GTK_LEVEL_BAR(levelbar), avancement);      // Valeur initiale

    // Limiter la taille de la barre
    gtk_widget_set_size_request(levelbar, 200, 20); // Largeur: 200px, Hauteur: 20px

    // Centrer la barre dans la boîte
    gtk_widget_set_halign(levelbar, GTK_ALIGN_CENTER); // Alignement horizontal
    gtk_widget_set_valign(levelbar, GTK_ALIGN_CENTER); // Alignement vertical

    // Ajouter le label et la barre à la boîte
    
    gtk_box_append(GTK_BOX(left_box), levelbar);

    //-------------------------------réussite-------------------------------

    // Créer un GtkLabel pour le texte
    GtkWidget *label7 = gtk_label_new(g_strdup_printf("jour ok : %d", iteration_compleate));
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER); // Centrer le label

    gtk_box_append(GTK_BOX(left_box), label7);

    //-------------------------------fail-------------------------------

    int fail = nb_day_since_start - iteration_compleate;
    // Créer un GtkLabel pour le texte
    GtkWidget *label8 = gtk_label_new(g_strdup_printf("jour fail : %d", fail));
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER); // Centrer le label

    gtk_box_append(GTK_BOX(left_box), label8);

    //-------------------------------level bar avancement-------------------------------
    float fail_porcent = iteration_compleate / nb_day_since_start * 100;
    // Créer une GtkLevelBar
    
    GtkWidget *levelbar2 = gtk_level_bar_new();
    gtk_level_bar_set_min_value(GTK_LEVEL_BAR(levelbar2), 0);  // Valeur minimale
    gtk_level_bar_set_max_value(GTK_LEVEL_BAR(levelbar2), 100); // Valeur maximale
    gtk_level_bar_set_value(GTK_LEVEL_BAR(levelbar2), fail_porcent);      // Valeur initiale

    // Limiter la taille de la barre
    gtk_widget_set_size_request(levelbar2, 200, 20); // Largeur: 200px, Hauteur: 20px

    // Centrer la barre dans la boîte
    gtk_widget_set_halign(levelbar2, GTK_ALIGN_CENTER); // Alignement horizontal
    gtk_widget_set_valign(levelbar2, GTK_ALIGN_CENTER); // Alignement vertical

    // Ajouter le label et la barre à la boîte
    
    gtk_box_append(GTK_BOX(left_box), levelbar2);


    //-------------------------------éléments routine-------------------------------

    int num_labels = nb_actions;

    if (num_labels > 0){

        // Ajouter x labels au conteneur
        for (int i = 0; i < num_labels; i++) {
            // Créer un nouveau label
            char label_text[50];
            snprintf(label_text, sizeof(label_text), nom[i]);
            GtkWidget *label = gtk_label_new(label_text);

            // Centrer le label horizontalement
            gtk_widget_set_halign(label, GTK_ALIGN_CENTER);

            // Ajouter le label au conteneur
            
            if(i<7){

                gtk_box_append(GTK_BOX(midl_box), label);

            };


            if(i>=7){

                gtk_box_append(GTK_BOX(right_box), label);

            };

            GtkWidget *levelbar2 = gtk_level_bar_new();
            gtk_level_bar_set_min_value(GTK_LEVEL_BAR(levelbar2), 0);  // Valeur minimale
            gtk_level_bar_set_max_value(GTK_LEVEL_BAR(levelbar2), 100); // Valeur maximale
            gtk_level_bar_set_value(GTK_LEVEL_BAR(levelbar2), iteration_compleate_action[i]/nb_day_since_start*100);      // Valeur initiale

            // Limiter la taille de la barre
            gtk_widget_set_size_request(levelbar2, 200, 20); // Largeur: 200px, Hauteur: 20px

            // Centrer la barre dans la boîte
            gtk_widget_set_halign(levelbar2, GTK_ALIGN_CENTER); // Alignement horizontal
            gtk_widget_set_valign(levelbar2, GTK_ALIGN_CENTER); // Alignement vertical

            // Ajouter le label et la barre à la boîte

            if(i<7){

                gtk_box_append(GTK_BOX(midl_box), levelbar2);

            };


            if(i>=7){

                gtk_box_append(GTK_BOX(right_box), levelbar2);

            };


        };

    };

    //-------------------------------affichage fenetre-------------------------------

    // Afficher la fenêtre
    gtk_widget_show(window);

}