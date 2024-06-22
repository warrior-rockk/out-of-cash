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
    enum verbs verb;
    int step;
    int lastStep;
    int stepTime;
} roomAction;

//global functions
int say(char *message);
void change_room(int roomNum);
void default_verb_action(enum verbs roomVerb);
void mytrace(char *s, ...);
void end_script();
#endif