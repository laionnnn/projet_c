#ifndef RENAME_H
#define RENAME_H

#include <gtk/gtk.h>
#include <json-c/json.h>


void rename_json(const char *filename, const char *old_name, const char *new_name);

void rename_gtk(GtkButton *button, gpointer user_data);

#endif