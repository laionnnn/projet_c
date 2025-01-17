#include <gtk/gtk.h>

typedef struct {
    GtkWidget *description_entry;
    GtkWidget *constraints_entry;
    GtkWidget *iterations_spin; // Utilisation d'un GtkSpinButton
    const char *json_file;
    int action_id; // Identifiant de l'action
} ActionData;

typedef struct {
    GtkWidget *name_entry;
    GtkWidget *familyname_entry;
    GtkWidget *age_entry;
    GtkWidget *sexe_entry;
    GtkWidget *status_entry;
    const char *json_file;
} UserProfileData;