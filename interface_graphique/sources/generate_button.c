#include <gtk/gtk.h>
#include "../header/add_window.h"
#include "../header/generate_button.h"
#include "../header/add_routine_json.h"
#include "../header/action_page.h"


// Fonction qui génère un nouveau bouton et qui l'ajoute dans la flowbox
void on_generate_button_clicked(GtkButton *button, GtkFlowBox *flow_box) {
    static int count = 0;

    char label_text[50];
    snprintf(label_text, sizeof(label_text), "Action %d", count);
    
    GtkWidget *new_button = gtk_button_new_with_label(label_text);
    gtk_widget_set_size_request(new_button, 190, 50); 
    gtk_button_set_can_shrink(GTK_BUTTON(new_button), FALSE);

    g_signal_connect(new_button, "clicked", G_CALLBACK(action_window), GINT_TO_POINTER(count));

    gtk_flow_box_append(GTK_FLOW_BOX(flow_box), new_button);
    add_action_to_json("action.json", label_text,"","",0);

    gtk_widget_set_visible(new_button, TRUE);
        
    count++;

}