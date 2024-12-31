#include <gtk/gtk.h>
#include <json-c/json.h>
#include <stdio.h>
#include <string.h>

// Structure to hold routine fields and file info
typedef struct {
    GtkWidget *name_entry;
    GtkWidget *description_entry;
    GtkWidget *goal_entry;
    GtkWidget *time_entry;
    const char *json_file;
} RoutineData;

// Function to fetch and populate routine data
void fetch_routine_data(const char *filename, RoutineData *data) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        g_print("Error: Cannot open %s.\n", filename);
        return;
    }

    char buffer[4096];
    size_t read_size = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[read_size] = '\0';
    fclose(file);

    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (!parsed_json) {
        g_print("Error: Invalid JSON.\n");
        return;
    }

    struct json_object *routine_array;
    if (json_object_object_get_ex(parsed_json, "routine", &routine_array)) {
        struct json_object *routine = json_object_array_get_idx(routine_array, 0); // First routine
        struct json_object *name_obj, *description_obj, *goal_obj, *time_obj;

        if (json_object_object_get_ex(routine, "name", &name_obj))
            gtk_editable_set_text(GTK_EDITABLE(data->name_entry), json_object_get_string(name_obj));

        if (json_object_object_get_ex(routine, "description", &description_obj))
            gtk_editable_set_text(GTK_EDITABLE(data->description_entry), json_object_get_string(description_obj));

        if (json_object_object_get_ex(routine, "iteration_goal", &goal_obj))
            gtk_editable_set_text(GTK_EDITABLE(data->goal_entry), json_object_get_string(goal_obj));

        if (json_object_object_get_ex(routine, "time", &time_obj))
            gtk_editable_set_text(GTK_EDITABLE(data->time_entry), json_object_get_string(time_obj));
    }

    json_object_put(parsed_json);
}

// Function to save routine data back to the JSON file
void save_routine_data(GtkWidget *widget, gpointer user_data) {
    RoutineData *data = (RoutineData *)user_data;

    const char *name = gtk_editable_get_text(GTK_EDITABLE(data->name_entry));
    const char *description = gtk_editable_get_text(GTK_EDITABLE(data->description_entry));
    const char *goal = gtk_editable_get_text(GTK_EDITABLE(data->goal_entry));
    const char *time = gtk_editable_get_text(GTK_EDITABLE(data->time_entry));

    FILE *file = fopen(data->json_file, "r");
    if (!file) {
        g_print("Error: Cannot open %s.\n", data->json_file);
        return;
    }

    char buffer[4096];
    size_t read_size = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[read_size] = '\0';
    fclose(file);

    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (!parsed_json) {
        g_print("Error: Invalid JSON.\n");
        return;
    }

    struct json_object *routine_array;
    if (json_object_object_get_ex(parsed_json, "routine", &routine_array)) {
        struct json_object *routine = json_object_array_get_idx(routine_array, 0); // First routine
        json_object_object_add(routine, "name", json_object_new_string(name));
        json_object_object_add(routine, "description", json_object_new_string(description));
        json_object_object_add(routine, "iteration_goal", json_object_new_string(goal));
        json_object_object_add(routine, "time", json_object_new_string(time));
    }

    file = fopen(data->json_file, "w");
    if (file) {
        fprintf(file, "%s", json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PRETTY));
        fclose(file);
        g_print("Routine updated successfully in %s.\n", data->json_file);
    }

    json_object_put(parsed_json);
}

// Function to create the GTK window
void create_routine_window(GtkApplication *app, gpointer user_data) {
    const char *json_file = (const char *)user_data;

    RoutineData *data = g_malloc(sizeof(RoutineData));
    data->json_file = json_file;

    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Modify Routine");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    GtkWidget *grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    GtkWidget *label_name = gtk_label_new("Name:");
    gtk_grid_attach(GTK_GRID(grid), label_name, 0, 0, 1, 1);

    data->name_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), data->name_entry, 1, 0, 2, 1);

    GtkWidget *label_description = gtk_label_new("Description:");
    gtk_grid_attach(GTK_GRID(grid), label_description, 0, 1, 1, 1);

    data->description_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), data->description_entry, 1, 1, 2, 1);

    GtkWidget *label_goal = gtk_label_new("Iteration Goal:");
    gtk_grid_attach(GTK_GRID(grid), label_goal, 0, 2, 1, 1);

    data->goal_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), data->goal_entry, 1, 2, 2, 1);

    GtkWidget *label_time = gtk_label_new("Time:");
    gtk_grid_attach(GTK_GRID(grid), label_time, 0, 3, 1, 1);

    data->time_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), data->time_entry, 1, 3, 2, 1);

    GtkWidget *save_button = gtk_button_new_with_label("Save");
    gtk_grid_attach(GTK_GRID(grid), save_button, 1, 4, 1, 1);
    g_signal_connect(save_button, "clicked", G_CALLBACK(save_routine_data), data);

    fetch_routine_data(json_file, data);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("com.example.routineeditor", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(create_routine_window), "data.json");
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
