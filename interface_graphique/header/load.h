#ifndef LOAD_H
#define LOAD_H

#include <gtk/gtk.h>
#include <json-c/json.h>

void load_from_json(GtkFlowBox *flow_box, const char *filename);

void reload_routines(GtkWidget *widget, gpointer user_data);

#endif