#include "generate_action.h"
#include "add_window.h"
#include <gtk/gtk.h>



// Function that generate new flow box when you click on a button
#include "generate_action.h"
#include <gtk/gtk.h>

// Function that generates a new list box row when a button is clicked
void on_generate_add_action(GtkButton *button, GtkBox *actions_box) {
    static int count = 0;

    count++;

    // Create a new flow box
    GtkWidget *new_flow_box = gtk_flow_box_new();

    // Add child widgets to the flow box
   
    char child_label[50];
    snprintf(child_label, sizeof(child_label), "Child %d", count);
    GtkWidget *child_button = gtk_button_new_with_label(child_label);
    gtk_flow_box_insert(GTK_FLOW_BOX(new_flow_box), child_button, -1);

    // Append the new flow box to the actions box
    gtk_box_append(GTK_BOX(actions_box), new_flow_box);

    // Make the new flow box visible
    gtk_widget_set_visible(new_flow_box, TRUE);
}
