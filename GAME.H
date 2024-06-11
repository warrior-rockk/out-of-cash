#ifndef H_GAME
#define H_GAME

//Definitions

//Screen
#define RES_X    320
#define RES_Y    240

//Status bar
#define STATUS_BAR_X            RES_X / 2
#define STATUS_BAR_Y            166
#define OBJECT_NAME_MAX_CHARS   25

//HUD
#define HUD_Y   179

//Enumerations

//Cursor
typedef enum {
    IR      = 0,
    MIRAR   = 1,
    COGER   = 2
} tCursorActions;

//Global variables
static char verbs[3][10] = {
    "Ir a",
    "Mirar",
    "Coger"
};

#endif