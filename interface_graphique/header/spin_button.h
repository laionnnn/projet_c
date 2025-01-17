#ifndef SPIN_BUTTON_H
#define SPIN_BUTTON_H

#include <json-c/json.h>
#include <stdio.h>

void set_iterations_from_json(GtkSpinButton *spin_button, const char *json_file, int routine_id);

void update_json_iteration(const char *json_file, int routine_id, int new_iteration);

#endif