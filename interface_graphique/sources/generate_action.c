#include "../header/add_window.h"
#include "../header/generate_action.h"
#include <gtk/gtk.h>

// Fonction qui crée une nouvelle action et qui l'ajoute dans la flowbox
void on_action_button_clicked(GtkButton *button, GtkFlowBox *flow_box) {
    static int count = 0;

    count++;

    char label_text[50];
    snprintf(label_text, sizeof(label_text), "Action %d", count);

    GtkWidget *new_button = gtk_button_new_with_label(label_text);

    GtkWidget *check_button = gtk_check_button_new();
    
    gtk_flow_box_append(GTK_FLOW_BOX(flow_box), new_button);
    gtk_flow_box_append(GTK_FLOW_BOX(flow_box), check_button);

    gtk_widget_set_visible(new_button, TRUE);
}
