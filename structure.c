#include <stdlib.h>

struct user_profile{
    char* last_name;
    char* first_name;
    int age;
    char sexe;
    char* statue;
    char* password;
};

typedef struct user_profile User_Profile;


struct score{
    int points;
    int malus;
    int bonus;
};

typedef struct score Score;

struct action {
    char* name;
    char* description;
    char* constraint;
};

typedef struct action Action;

struct routine {
    char *name;
    char *description;
    char *iteration_goal;
    char *time;
    Score *score;  //
    Action *actions; // Array of actions
    int action_count; 
};

typedef struct routine Routine;

struct user_data {
    User_Profile user_profile;
    Routine *routines; // Array of routines
    int routine_count; // Count of routines
};

typedef struct user_data User_Data;