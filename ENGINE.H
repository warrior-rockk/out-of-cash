//Adventure game engine global header
#ifndef H_ENGINE
#define H_ENGINE

//Definitions
#define NUM_VERBS   3

//Status bar
#define OBJECT_NAME_MAX_CHARS   25

//Texts
#define MAX_SENTENCE_LENGTH     50

//Enumerations
enum verbs {
    GO,
    LOOK,
    TAKE
};

//Global variables
extern int gameTick;
static const char verbName[3][10] = {
    "Ir a",
    "Mirar",
    "Coger"
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
void default_verb_action(enum verbs roomVerb);
void mytrace(char *s, ...);
void begin_script();
void end_script();
void show_debug(char *varName, int var);
#endif