#ifndef ADD_TO_JSON_H
#define ADD_TO_JSON_H

#include <json-c/json.h>
#include <stdio.h>

void add_to_json(const char *filename, const char *name, const char *description, const char *constraints, int iteration_compleat);

#endif