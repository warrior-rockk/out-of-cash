#ifndef H_GAME
#define H_GAME

//Definitions
//Screen
#define RES_X    320
#define RES_Y    240

#define NUM_VERBS   3

//Status bar
#define STATUS_BAR_X            RES_X / 2
#define STATUS_BAR_Y            166
#define OBJECT_NAME_MAX_CHARS   25

//HUD
#define HUD_Y   179

//Text
#define SAY_X                   RES_X / 2
#define SAY_Y                   162 / 2
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

//global functions
void change_room(int roomNum);
void say(char *message);
void mytrace(char *s, ...);

#endif