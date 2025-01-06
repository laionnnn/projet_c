#ifndef LOAD_ROUTINE_H
#define LOAD_ROUTINE_H

#include <gtk/gtk.h>
#include <json-c/json.h>

void load_routines_from_json(GtkFlowBox *flow_box, const char *filename);

void load_actions_for_routine(GtkFlowBox *flow_box, const char *filename, int routine_index);

void reload_routines(GtkWidget *widget, gpointer user_data);

#endif