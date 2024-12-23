#include <gtk/gtk.h>
#include "../header/add_window.h"
#include "../header/generate_button.h"


// Function that generate new button when you click on a button
void on_generate_button_clicked(GtkButton *button, GtkFlowBox *flow_box) {
    static int count = 0;

    count++;

    char label_text[50];
    snprintf(label_text, sizeof(label_text), "Routine %d", count);

    
    GtkWidget *new_button = gtk_button_new_with_label(label_text);

    
    
    g_signal_connect(new_button, "clicked", G_CALLBACK(open_new_window), GINT_TO_POINTER(count));

    gtk_flow_box_append(GTK_FLOW_BOX(flow_box), new_button);

    //gtk_fixed_put(GTK_FIXED(fixed), new_button, 10, 10 + count * 50);

    gtk_widget_set_visible(new_button, TRUE);
}