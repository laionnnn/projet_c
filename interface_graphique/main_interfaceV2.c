#include <gtk/gtk.h>
#include "header/switch_page.h"
#include "header/generate_button.h"
#include "header/profile.h"


static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);

    // Create buttons for the main page
    GtkWidget *button_add = gtk_button_new_with_label("Ajouter une routine");
    GtkWidget *button_stats = gtk_button_new_with_label("Statisque");
    GtkWidget *button_user_profile = gtk_button_new_with_label("Profile");
    GtkWidget *routine_research = gtk_search_entry_new();
    GtkWidget *button_back = gtk_button_new_with_label("Retour à la page principale");

    // Create GtkFixed container
    GtkWidget *fixed_main = gtk_fixed_new();
    GtkWidget *fixed_stats = gtk_fixed_new();

    // Set buttons at specific positions and sizes
    gtk_fixed_put(GTK_FIXED(fixed_main), button_add, 650, 0);  // Position at (650, 0)
    gtk_fixed_put(GTK_FIXED(fixed_main), button_stats, 0, 0);  // Position at (0, 0)
    gtk_fixed_put(GTK_FIXED(fixed_main), button_user_profile, 0, 50);  // Position at (0, 0)
    gtk_fixed_put(GTK_FIXED(fixed_stats), button_back, 0, 0);  // Position at (0, 0)
    gtk_fixed_put(GTK_FIXED(fixed_main), routine_research, 200, 0);  // Position at (75, 50)

    // Set a specific size for each button
    gtk_widget_set_size_request(button_add, 200, 50);  // Set width and height
    gtk_widget_set_size_request(button_stats, 200, 50);
    gtk_widget_set_size_request(button_back, 200, 50);
    gtk_widget_set_size_request(button_user_profile, 200, 50);
    gtk_widget_set_size_request(routine_research, 450, 50);

    // Create the stack to switch between pages
    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_stack_set_transition_duration(GTK_STACK(stack), 500);

    // Create a smaller GtkBox inside the fixed container
    GtkWidget *flow_box = gtk_flow_box_new();
    gtk_widget_set_size_request(flow_box, 200, 450);  // Size of the box
    
    // Add widgets to the box (like an entry or additional buttons)
    GtkWidget *titleFLOWBOX = gtk_label_new("Liste des routines");
    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(flow_box), 1);
    gtk_flow_box_append(GTK_FLOW_BOX(flow_box), titleFLOWBOX);

    // Setting box as scrolled_window child and setting size
    GtkWidget *scrolled_window_with_box = gtk_scrolled_window_new();
    gtk_widget_set_size_request(scrolled_window_with_box, 200, 550);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window_with_box), flow_box);



    // Position the box inside the fixed container
    gtk_fixed_put(GTK_FIXED(fixed_main), scrolled_window_with_box, 325, 100);  // Position at (350, 200)


    // Add the main and add pages to the stack
    gtk_stack_add_named(GTK_STACK(stack), fixed_main, "main");
    gtk_stack_add_named(GTK_STACK(stack), fixed_stats, "stats_page");

    // Connect signals for button clicks
    g_signal_connect(button_back, "clicked", G_CALLBACK(on_back_button_clicked), stack);
    g_signal_connect(button_stats, "clicked", G_CALLBACK(on_stats_button_clicked), stack);
    g_signal_connect(button_add, "clicked", G_CALLBACK(on_generate_button_clicked), flow_box);

     g_signal_connect(button_user_profile, "clicked", G_CALLBACK(open_user_profile),NULL);


    // Set the window content (stack will hold the pages)
    gtk_window_set_title(GTK_WINDOW(window), "Page Principale");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 700);
    gtk_window_set_child(GTK_WINDOW(window), stack);

    // Show the window
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    
    app = gtk_application_new("org.gtk.interface1", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    return status;
}
