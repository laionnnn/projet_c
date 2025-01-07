#include <gtk/gtk.h>
#include <stdio.h>
#include "../header/stat.h"

//variable de test
int creation_date[3] = {30,10,2024};
int actual_date[3] = {3,12,2024};
int end_date[3] = {8,12,2024};
int iteration_compleate = 20;

int hour[3] = {2,10,20};
int return_date[3];
int second = 7820;
char *nom[] = {"fonction1", "fonction2", "fonction3", "fonction4","uin","uin","uin","uin","uin"};
float iteration_compleate_action[9] = {2,3,4,5,2,3,4,5,2};




//fin variable test

void
interface_stat(GtkWidget *widget, gpointer user_data) {

    float nb_day_since_start = dif_date(creation_date,actual_date);

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

    int num_labels = sizeof(nom)/sizeof(nom[1]);

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

};