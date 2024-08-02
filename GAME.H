#ifndef H_GAME
#define H_GAME

#include <stdbool.h>
#include <allegro.h>
#include "engine.h"

//Definitions
//Screen
#define RES_X    320
#define RES_Y    240

//Game
#define NUM_GAME_ROOMS          2

//Status bar
#define STATUS_BAR_X            RES_X / 2
#define STATUS_BAR_Y            166

//Cursor
#define DBL_CLICK_MAX_TIME      4 //400ms

//HUD
#define HUD_Y                   162
#define HUD_SCROLL_X            114
#define HUD_INVENTORY_X         130

#define VERB_SEL_ROW_1_X        2
#define VERB_SEL_ROW_2_X        40
#define VERB_SEL_ROW_3_X        78
#define VERB_SEL_COL_1_Y        21
#define VERB_SEL_COL_2_Y        39
#define VERB_SEL_COL_3_Y        57

#define SEL_UP_DOWN_X           119
#define SEL_UP_Y                25
#define SEL_DOWN_Y              54

//Text
#define SAY_X                   RES_X / 2
#define SAY_Y                   162 / 2
#define TEXT_ACTOR_MARGIN       10

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
    //enter room position assigned by change_room_pos()
    int room_pos_x;
    int room_pos_y;
    bool fadeIn;
    uint8_t flags[32];  //32 bytes = 255 bit flags
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
    //room walk/scalemap image
    BITMAP  *wImage;
    //room front layer
    BITMAP *fImage;
    //room song
    MIDI    *song;
    //default start player position on room
    int start_pos_x;
    int start_pos_y;
    //function pointer to get hotspot name
    void (*room_get_hotspot_name)(uint8_t, char *s);
    //function pointer to get default hotspot verb
    enum verbs (*room_get_default_hotspot_verb)(uint8_t);
    //room num objects
    uint8_t room_num_objects;
    //function pointer to get object info
    tObject* (*room_get_object_info)(uint8_t numObject);
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
    //scroll buttons
    bool selUpButton;
    bool selDownButton;
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
    //counters
    int dblClickTimer;
    //flags
    bool enabled;
    bool click;
    bool dblClick;
    bool rightClick;
    bool memClick;
    bool memRightClick;
    bool memDblClick;
    bool evalueDblClick;
} cursor;

//game config structure
struct gameConfig
{
    uint8_t textSpeed;
    fixed   playerSpeed;
} gameConfig;

//keys struct
struct gameKeys{
    bool pausePressed;
} gameKeys;

//global vars
static volatile int tick;
tRoom room[NUM_GAME_ROOMS];
PALETTE gamePalette;
BITMAP *buffer;
DATAFILE *dataFile;
DATAFILE *playerDataFile;
DATAFILE *objectsDataFile;
DATAFILE *inventoryDataFile;
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
void game_write(char *text, int x, int y);
void game_save();
void game_load();
void cursor_init();
void tick_init();
void debug_init();
void tick_update();
void cursor_button_handler();
void cursor_update();
void check_room_changed();
void room_action_update();
void room_draw();
void room_front_draw();
void hud_draw();
void status_bar_draw();
void cursor_draw();
void debug_draw();
void msg_init();
void msg_update();
void msg_draw();



#endif
