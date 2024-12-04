#ifndef SWITCH_PAGE_H
#define SWITCH_PAGE_H

#include <gtk/gtk.h>

// Function switch pages
void on_stats_button_clicked(GtkWidget *button, GtkStack *stack);
void on_back_button_clicked(GtkWidget *button, GtkStack *stack);

#endif