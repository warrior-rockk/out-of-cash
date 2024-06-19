#ifndef H_GAME
#define H_GAME

#include "allegro.h"

//Definitions
//Screen
#define RES_X    320
#define RES_Y    240

//Status bar
#define STATUS_BAR_X            RES_X / 2
#define STATUS_BAR_Y            166

//HUD
#define HUD_Y   179

//Text
#define SAY_X                   RES_X / 2
#define SAY_Y                   162 / 2

//structures

//message structure
typedef struct tMsg
{
    char msg[MAX_SENTENCE_LENGTH];
    int msgTime;
    int msgFinished;
    int msgActive;
} tMsg;
//room structure
typedef struct tRoom
{
    //room image
    BITMAP  *image;
    //room hotspot image
    BITMAP  *hsImage;
    //room song
    MIDI    *song;
    //function pointer to get object
    void (*room_get_object)(int, char *s);
    //function pointer to do object action
    void (*room_do_object_action)(enum verbs, int);
    //function pointer to update room
    void (*room_update)(void);
} tRoom;

//hud structure
typedef struct tHUD
{
    //HUD image
    BITMAP *image;
    //HUD hotspot image
    BITMAP *hsImage;
} tHUD;

//cursor structure
typedef struct tCursor
{
    //cursor image
    BITMAP *image;
    //name of the pointed object
    char objectName[OBJECT_NAME_MAX_CHARS];
    //selected action/verb
    enum verbs selectedVerb;
    //flags
    int enabled;
    int click;
    int leftClick;
    int memClick;
    int memLeftClick;
} tCursor;

//game config structure
typedef struct tGameConfig
{
    int textSpeed;
} tGameConfig;

//global structure vars
tRoom room[2];
tHUD hud;
tCursor cursor;
tGameConfig gameConfig;
tMsg msg;

//global vars
PALETTE gamePalette;
BITMAP *buffer;
DATAFILE *dataFile;

//interrupt timer variable
static volatile int tick;
int gameTick;
int actualRoom;

//function declarations
void abort_on_error();
void load_resources();

void game_init();
void cursor_init();
void tick_init();
void tick_update();
void cursor_update();
void room_draw();
void hud_draw();
void status_bar_draw();
void cursor_draw();
void debug_draw();
void msg_init();
void msg_update();
void msg_draw();

#endif
