//Adventure game engine global header
#ifndef H_ENGINE
#define H_ENGINE

#include <stdbool.h>

//Definitions
#define NUM_VERBS               9
#define NUM_RAND_ANSWERS        3
//Status bar
#define OBJECT_NAME_MAX_CHARS   25

//Texts
#define MAX_SENTENCE_LENGTH     50

//Debug
#define DEBUG_MAX_VARS          5

//Enumerations
enum verbs {
    GO,
    TAKE,
    MOVE,
    LOOK,
    USE,
    GIVE,
    OPEN,
    CLOSE,
    TALK
};

//Global variables
extern bool gameTick;
static const char verbName[NUM_VERBS][10] = {
    "Ir a",
    "Coger",
    "Mover",
    "Mirar",
    "Usar",
    "Dar",
    "Abrir",
    "Cerrar",
    "Hablar a"
};

//global room script structure
struct roomScript
{
    bool active;
    bool scriptAssigned;
    int object;
    enum verbs verb;
    int step;
    int lastStep;
    int stepTime;
} roomScript;

//global debug vars structure (only ints on this iteration)
struct debugVars
{
    int var[DEBUG_MAX_VARS];
    char varName[DEBUG_MAX_VARS][10];
    int numVars;
} debugVars;

//global functions
int say(char *message);
void change_room(int roomNum);
void game_fade_in();
void game_fade_out();
void default_verb_action(enum verbs roomVerb);
void mytrace(char *s, ...);
void begin_script();
void end_script();
void show_debug(char *varName, int var);
void move_player(int x, int y);
bool is_player_moving();
#endif