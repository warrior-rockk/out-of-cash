#ifndef H_GAME
#define H_GAME

#include <stdbool.h>
#include <allegro.h>
#include "engine.h"
#include "inv.h"
#include "player.h"

//Definitions
//Screen
#define RES_X    320
#define RES_Y    240

//Draw layers
#define BACK_LAYER  0
#define FRONT_LAYER 1

//Game colors
#define BLACK_COLOR 1

//Game

#define MAX_GAME_FLAGS          32
#define SAVEGAME_FILE_VERSION   1
#define SAVEGAME_SLOTS          5
#define SAVEGAME_DATE_CHARS     20      //19 chars + zero terminator

//Status bar
#define STATUS_BAR_X            RES_X / 2
#define STATUS_BAR_Y            179
#define STATUS_BAR_TEXT_Y       166

//Cursor
#define DBL_CLICK_MAX_TIME      4       //400ms

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

//gui
#define GUI_COLOR_OFFSET        20      //color offset for hotspot buttons
#define GUI_NUM_OPTIONS         7
#define GUI_CONTENT_X           105
#define GUI_CONTENT_Y           18

#define GUI_BUTTONS_X           11
#define GUI_BUTTONS_Y           17
#define GUI_BUTTONS_SPACING     25
#define GUI_BUTTONS_EXIT        132
#define GUI_BUTTON_EXIT_TITLE_Y 37
#define GUI_BUTTON_EXIT_DOS_Y   78

#define GUI_SLIDER_MIN_X        138
#define GUI_SLIDER_MAX_X        247
#define GUI_SLIDER_1_Y          31
#define GUI_SLIDER_2_Y          62
#define GUI_SLIDER_3_Y          90
#define GUI_SLIDER_4_Y          118
#define GUI_SLIDER_1_COLOR      30
#define GUI_SLIDER_2_COLOR      31
#define GUI_SLIDER_3_COLOR      32
#define GUI_SLIDER_4_COLOR      33

#define GUI_SAVE_SLOT_1_COLOR   40
#define GUI_SAVE_SLOT_2_COLOR   41
#define GUI_SAVE_SLOT_3_COLOR   42
#define GUI_SAVE_SLOT_4_COLOR   43
#define GUI_SAVE_SLOT_5_COLOR   44
#define GUI_LOAD_SLOT_1_COLOR   50
#define GUI_LOAD_SLOT_2_COLOR   51
#define GUI_LOAD_SLOT_3_COLOR   52
#define GUI_LOAD_SLOT_4_COLOR   53
#define GUI_LOAD_SLOT_5_COLOR   54
#define GUI_SLOTS_X             2
#define GUI_SLOTS_Y             13
#define GUI_SLOTS_SEL_Y         9
#define GUI_SLOTS_Y_SPACING     21
#define GUI_SEL_SLOT_TEXT_COLOR 179

//Text
#define MAX_MSG_LENGTH          200
#define MAX_MSG_LINE_LENGTH     20
#define MSG_LINE_SPACING        10
#define SAY_X                   RES_X / 2
#define SAY_Y                   162 / 2
#define TEXT_ACTOR_MARGIN       10

//Text colors
#define GAME_TEXT_COLOR         255,255,255

//Debug
#define DEBUG_Y                 10
#define DEBUG_FONT_HEIGHT       8

//Fade
#define FADE_DEFAULT_SPEED      6
#define FADE_FAST_SPEED         12

//enums

//game state
enum gameState{
    LOGO_STATE,
    TITLE_STATE,
    INTRO_STATE,
    PLAYING_STATE,
    DIALOG_STATE,
    PAUSE_STATE,
    MENU_STATE,
    EXIT_STATE
};

//gui state
enum guiState{
    GUI_LOAD_STATE,
    GUI_SAVE_STATE,
    GUI_OPTIONS_STATE,
    GUI_ABOUT_STATE,
    GUI_EXIT_STATE,
    GUI_EXIT_TITLE_STATE,
    GUI_EXIT_DOS_STATE,
    GUI_MAIN_STATE
};

//structures

//actual game room structure
struct actualRoom
{
    //room datafile
    DATAFILE *dataFile;
    //room image
    BITMAP  *image;
    //room hotspot image
    BITMAP  *hsImage;
    //room walk/scalemap image
    BITMAP  *wImage;
    //room music
    uint8_t musicId;
    DATAFILE_INDEX *musicDataFileIndex;
    DATAFILE *musicDataFile;
    MIDI    *music;
} actualRoom;

//game structure
struct game
{
    enum gameState state;
    int16_t actualRoom;
    int16_t nextRoom;
    //enter room position assigned by change_room_pos()
    int16_t room_pos_x;
    int16_t room_pos_y;
    long roomMusicPos;
    bool fadeIn;
    bool fadeOut;
    bool exit;
    uint8_t flags[MAX_GAME_FLAGS];  //32 bytes = 255 bit flags
} game;

//game config structure
struct gameConfig
{
    #define CONFIG_TEXT_SPEED_MIN   1
    #define CONFIG_TEXT_SPEED_MAX   255
    uint8_t textSpeed;
    #define CONFIG_PLY_SPEED_MIN    1
    #define CONFIG_PLY_SPEED_MAX    100
    uint8_t playerSpeed;
    uint8_t musicVolume;
    uint8_t soundVolume;
} gameConfig;

//message structure
struct msg
{
    char msg[MAX_MSG_LENGTH];
    int16_t msgTime;
    bool msgFinished;
    bool msgActive;
    tActorTalk *actorTalk;
} msg;

//hud structure
struct hud
{
    //HUD image
    BITMAP *image;
    //HUD hotspot image
    BITMAP *hsImage;
    //selected verbs images and screen positions
    BITMAP *verbSelImage[NUM_VERBS];
    int16_t posXVerbSelImage[NUM_VERBS];
    int16_t posYVerbSelImage[NUM_VERBS];
    //scroll buttons
    bool selUpButton;
    bool selDownButton;
    //hud dialog hotspot image
    BITMAP *dialogHsImage;
} hud;

//gui structure
struct gui
{
    //gui base image
    BITMAP *image;
    //gui hotspot image
    BITMAP *hsImage;
    //TEMPORALY: fix when update gui datafile
    BITMAP *hsImageMain;
    BITMAP *hsImageOptions;
    BITMAP *hsImageExit;
    BITMAP *hsImageSave;
    BITMAP *hsImageLoad;
    BITMAP *imageSlotSel;
    //gui position
    int16_t x;
    int16_t y;
    //gui state
    uint8_t state;
    uint8_t slotSel;
} gui;

//cursor structure
struct cursor
{
    //name of the pointed object (change for hotspot)
    char objectName[OBJECT_NAME_MAX_CHARS];
    char invObjName[OBJECT_NAME_MAX_CHARS];
    //selected action/verb
    enum verbs selectedVerb;
    //selected use with object inventory
    int16_t invObject;
    //counters
    int16_t dblClickTimer;
    //flags
    bool enabled;
    bool click;
    bool dblClick;
    bool rightClick;
    bool memClick;
    bool memRightClick;
    bool memDblClick;
    bool evalueDblClick;
    bool clicking;
    bool rightClicking;
} cursor;

typedef struct tKey{
    uint16_t keyId;
    bool pressed;
    bool memPressed;
} tKey;

#define GAME_KEYS_NUM 9
static tKey gameKeys[GAME_KEYS_NUM] =
{
    #define G_KEY_PAUSE     0
    #define G_KEY_EXIT      1
    #define G_KEY_W         2
    #define G_KEY_H         3
    #define G_KEY_O         4
    #define G_KEY_UP        5
    #define G_KEY_DOWN      6
    #define G_KEY_LEFT      7
    #define G_KEY_RIGHT     8

    {KEY_SPACE, false, false},
    {KEY_ESC, false, false},
    {KEY_W, false, false},
    {KEY_H, false, false},
    {KEY_O, false, false},
    {KEY_UP, false, false},
    {KEY_DOWN, false, false},
    {KEY_LEFT, false, false},
    {KEY_RIGHT, false, false},
};

//savegame structure
struct savegame
{
    uint8_t version;
    char saveDate[SAVEGAME_DATE_CHARS];
    struct gameConfig gameConfigData;
    struct game gameData;
    struct inventory invData;
    struct cursor cursorData;
    struct roomScript roomScriptData;
    struct msg msgData;
    struct player playerData;
};

//global vars
static volatile int tick;
static BITMAP *cursorImage;
PALETTE gamePalette;
BITMAP *buffer;
DATAFILE *gameDataFile;
DATAFILE *playerDataFile;
DATAFILE *inventoryDataFile;
DATAFILE *soundDataFile;
bool gameTick;

//function declarations
void main_init();
void main_update();
void main_draw();

void incTick(void);
void abort_on_error(const char *format, ...);

void game_init();
void game_update();
void game_exit();
void game_load_resources();
void game_do_fade_in();
void game_write(char *text, int x, int y, uint8_t color);
void game_save(uint8_t slot);
bool game_save_exists(uint8_t slot, char *s);
void game_load(uint8_t slot);
void game_keys_handler();

void cursor_init();
void cursor_button_handler();
void cursor_update();
void cursor_draw();
void cursor_action_room();
void cursor_action_HUD();
void cursor_action_menu();
void cursor_action_dialog();

void tick_init();
void tick_update();

void check_room_changed();
void room_load(uint8_t roomNumber);
DATAFILE* room_load_datafile(uint8_t roomNumber);
void room_action_update();
void room_draw();
void room_front_layer_draw();
void room_objects_draw(uint8_t layer);
void room_update_lights(uint8_t roomNumber, bool turnOff);

void hud_init();
void hud_draw();
void status_bar_draw();

void debug_init();
void debug_draw();

void msg_init();
void msg_update();
void msg_draw();
int get_msg_length(char *text, int *lines);

void gui_init();
void gui_update();
void gui_draw();

void dialog_init();
void dialog_draw();
#endif
