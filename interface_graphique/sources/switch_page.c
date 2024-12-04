#include <gtk/gtk.h>
#include "switch_page.h"

void on_stats_button_clicked(GtkWidget *button, GtkStack *stack) {
    gtk_stack_set_visible_child_name(stack, "stats_page");
}

void on_back_button_clicked(GtkWidget *button, GtkStack *stack) {
    gtk_stack_set_visible_child_name(stack, "main");
}

