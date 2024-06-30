#ifndef H_GAME
#define H_GAME

#include <stdbool.h>
#include "allegro.h"

//Definitions
//Screen
#define RES_X    320
#define RES_Y    240

//Game
#define NUM_GAME_ROOMS          2

//Status bar
#define STATUS_BAR_X            RES_X / 2
#define STATUS_BAR_Y            166

//HUD
#define HUD_Y                   179
#define VERB_SEL_ROW_1_X        2
#define VERB_SEL_ROW_2_X        40
#define VERB_SEL_ROW_3_X        78
#define VERB_SEL_COL_1_Y        4
#define VERB_SEL_COL_2_Y        22
#define VERB_SEL_COL_3_Y        40

//Text
#define SAY_X                   RES_X / 2
#define SAY_Y                   162 / 2

//Debug
#define DEBUG_Y                 10
#define DEBUG_FONT_HEIGHT       8

//Fade
#define FADE_DEFAULT_SPEED   6

//enums
enum gameState{
    LOGO_STATE,
    TITLE_STATE,
    INTRO_STATE,
    PLAYING_STATE,
    PAUSE_STATE,
    MENU_STATE
};

//structures

//game structure
struct game
{
    enum gameState state;
    int actualRoom;
    int lastRoom;
    bool fadeIn;
} game;

//message structure
struct msg
{
    char msg[MAX_SENTENCE_LENGTH];
    int msgTime;
    bool msgFinished;
    bool msgActive;
} msg;

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
    void (*room_get_object)(uint8_t, char *s);
    //function pointer to init room
    void (*room_init)(void);
    //function pointer to update room
    void (*room_update)(void);
} tRoom;

//hud structure
struct hud
{
    //HUD image
    BITMAP *image;
    //HUD hotspot image
    BITMAP *hsImage;
    //selected verbs images and screen positions
    BITMAP *verbSelImage[NUM_VERBS];
    int posXVerbSelImage[NUM_VERBS];
    int posYVerbSelImage[NUM_VERBS];
} hud;

//cursor structure
struct cursor
{
    //cursor image
    BITMAP *image;
    //name of the pointed object
    char objectName[OBJECT_NAME_MAX_CHARS];
    //selected action/verb
    enum verbs selectedVerb;
    //flags
    bool enabled;
    bool click;
    bool leftClick;
    bool memClick;
    bool memLeftClick;
} cursor;

//game config structure
struct gameConfig
{
    uint8_t textSpeed;
} gameConfig;

//keys struct
struct gameKeys{
    bool pausePressed;
} gameKeys;

//player struct
struct player{
    BITMAP *image[11];
    int x;
    int y;
    int vX;
    int vY;
    int destX;
    int destY;
    bool moving;
    int frame;
} player;

//global vars
static volatile int tick;
tRoom room[NUM_GAME_ROOMS];
PALETTE gamePalette;
BITMAP *buffer;
DATAFILE *dataFile;
DATAFILE *playerDataFile;
bool gameTick;

//function declarations
void main_init();
void incTick(void);
void abort_on_error(const char *msg);
void load_resources();

void game_init();
void game_update();
void game_exit();
void game_do_fade_in();
void game_write();
void cursor_init();
void tick_init();
void debug_init();
void tick_update();
void cursor_update();
void check_room_changed();
void room_action_update();
void room_draw();
void hud_draw();
void status_bar_draw();
void cursor_draw();
void debug_draw();
void msg_init();
void msg_update();
void msg_draw();

void player_update();
void player_draw();

#endif
