//Adventure game engine global header
#ifndef H_ENGINE
#define H_ENGINE

#include <stdbool.h>

//Definitions
#define NUM_VERBS   9

//Status bar
#define OBJECT_NAME_MAX_CHARS   25

//Texts
#define MAX_SENTENCE_LENGTH     50

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

//global room action structure
extern struct roomAction
{
    int active;
    int object;
    int scriptAssigned;
    enum verbs verb;
    int step;
    int lastStep;
    int stepTime;
} roomAction;

//global debug vars structure
extern struct debugVars
{
    int var[5];
    char varName[5][10];
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
#endif