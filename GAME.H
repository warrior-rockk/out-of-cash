#ifndef H_GAME
#define H_GAME

#include <stdbool.h>
#include <allegro.h>
#include "engine.h"
#include "inv.h"
#include "player.h"

//Definitions
#define MAJOR_VERSION   1
#define MINOR_VERSION   4

//Screen
#define RES_X  320
#define RES_Y  240
#define C_X    (RES_X >> 1)
#define C_Y    (HUD_Y >> 1)

//Draw layers
#define BACK_LAYER  0
#define FRONT_LAYER 1

//Game colors
#define TRANSPARENT_COLOR   1
#define BLACK_COLOR         251
#define WHITE_COLOR         31
#define PURPLE_COLOR        118
#define BORDER_COLOR        BLACK_COLOR

//logos
#define GAME_WARCOM_LOGO_POS_X      C_X + 10
#define GAME_WARCOM_LOGO_POS_Y      102
#define GAME_WARCOM_TEXT_POS_Y      190
#define GAME_TITLE_POS_Y            70
#define GAME_TITLE_ESP_POS_Y        120
#define GAME_TITLE_FOOTER_POS_Y     175

//Game
#define MAX_GAME_FLAGS          32
#define MAX_GAME_VARS           10
#define SAVEGAME_FILE_VERSION   1
#define SAVEGAME_SLOTS          5
#define SAVEGAME_DATE_CHARS     20      //19 chars + zero terminator

//Status bar
#define STATUS_BAR_X            (RES_X / 2)
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
#define GUI_CONTENT_H           118
#define GUI_CONTENT_W           171

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
#define GUI_DEBUG_ROOM_INI_COLOR 60
#define GUI_DEBUG_ROOM_END_COLOR 72
#define GUI_SLOTS_X             2
#define GUI_SLOTS_Y             13
#define GUI_SLOTS_SEL_Y         9
#define GUI_SLOTS_Y_SPACING     21
#define GUI_SEL_SLOT_TEXT_COLOR 179

//Text
#define MAX_MSG_LENGTH          200
#define MAX_MSG_LINE_LENGTH     20
#define MSG_LINE_SPACING        10
#define TEXT_ACTOR_MARGIN       10
#define TEXT_MIN_TIME_BYPASS    4 //400ms

//Text colors
#define GAME_TEXT_COLOR         255,0,255

//Debug
#define DEBUG_Y                 10
#define DEBUG_FONT_HEIGHT       8

//Sfx
#define SFX_FREQ_RND_PERCENT    20 //(+/- % freq variation)
#define SFX_GAME_VOICE          0
#define SFX_ROOM_VOICE          1
#define SFX_NUM_VOICES          2

//enums

//game state
enum gameState{
    LOGO_STATE,
    DOS_LOGO_STATE,
    PROLOGUE_STATE,
    TITLE_STATE,
    INTRO_STATE,
    PLAYING_STATE,
    DIALOG_STATE,
    PAUSE_STATE,
    MENU_STATE,
    EXIT_STATE,
    END_STATE,
    RESTART_STATE,
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

//playtime counter struct
struct playTime{
    uint16_t centSeconds;
    uint8_t minutes;
    uint16_t hours;
} playTime;

//room borders structs
typedef struct tBorders
{
    int16_t left;
    int16_t right;
    int16_t up;
    int16_t down;
} tBorders;

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
    //room borders
    tBorders roomBorders;
    tBorders hsWalkBorders;
    //room music
    uint8_t musicId;
    DATAFILE_INDEX *musicDataFileIndex;
    DATAFILE *musicDataFile;
} actualRoom;

//game structure
struct game
{
    enum gameState state;
    enum gameState prevState;
    int16_t actualRoom;
    int16_t nextRoom;
    int16_t lastRoom;
    //enter room position assigned by change_room_pos()
    int16_t room_pos_x;
    int16_t room_pos_y;
    long roomMusicPos;
    bool actualRoomLightOff;
    bool fadeIn;
    bool fadeOut;
    bool exit;
    uint8_t fadeSpeed;
    uint8_t flags[MAX_GAME_FLAGS];  //32 bytes = 255 bit flags
    uint16_t vars[MAX_GAME_VARS];
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
    int16_t x;
    int16_t y;
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

#define GAME_KEYS_NUM 19
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
    #define G_KEY_D         9
    #define G_KEY_I         10
    #define G_KEY_F         11
    #define G_KEY_Q         12
    #define G_KEY_E         13
    #define G_KEY_A         14
    #define G_KEY_S         15
    #define G_KEY_Z         16
    #define G_KEY_X         17
    #define G_KEY_C         18

    {KEY_SPACE, false, false},
    {KEY_ESC, false, false},
    {KEY_W, false, false},
    {KEY_H, false, false},
    {KEY_O, false, false},
    {KEY_UP, false, false},
    {KEY_DOWN, false, false},
    {KEY_LEFT, false, false},
    {KEY_RIGHT, false, false},
    {KEY_D, false, false},
    {KEY_I, false, false},
    {KEY_F, false, false},
    {KEY_Q, false, false},
    {KEY_E, false, false},
    {KEY_A, false, false},
    {KEY_S, false, false},
    {KEY_Z, false, false},
    {KEY_X, false, false},
    {KEY_C, false, false},
};

//sfx voices structure
typedef struct tSfx
{
    int position;
    int sampleId;
    bool playing;
    bool paused;
    bool finished;
    bool stop;
    bool pause;
} tSfx;

//savegame structure
struct savegame
{
    uint8_t version;
    char saveDate[SAVEGAME_DATE_CHARS];
    struct playTime playTime;
    struct gameConfig gameConfigData;
    struct game gameData;
    struct inventory invData;
    struct cursor cursorData;
    struct roomScript roomScriptData;
    struct msg msgData;
    struct player playerData;
    tSfx sfx;
};

//scroll structure
struct roomScroll
{
    int16_t x;
    int16_t y;
} roomScroll;

//sequence struct
struct seq
{
    uint16_t timeCounter;
    uint8_t step;
} seq;

//credits struct
#define CREDITS_NUM             23
#define CREDITS_LINE_SPACING    14
#define CREDITS_GROUP_SPACING   22
struct credits
{
    char line[CREDITS_NUM][50];
    uint8_t color[CREDITS_NUM];
    int16_t pos_y[CREDITS_NUM];
} credits;

//global vars
static volatile int tick, fps, frameCount;
static BITMAP *cursorImage;
PALETTE gamePalette;
FONT *gameFont[6];
int actualFont;
BITMAP *buffer;
DATAFILE *gameDataFile;
DATAFILE *playerDataFile;
DATAFILE *inventoryDataFile;
DATAFILE *soundDataFile;
bool gameTick;
tSfx sfx[SFX_NUM_VOICES];

//function declarations
void main_init();
void main_update();
void main_draw();

static void incTick(void);
static void update_fps(void);
void abort_on_error(const char *format, ...);

void game_init();
void game_update();
void game_exit();
void game_load_resources();
void game_free_resources();
void game_do_fade_in();
void game_write(char *text, int x, int y, uint8_t fontIndex, uint8_t color, uint8_t backColor);
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
void cursor_select_verb(enum verbs selectedVerb);

void tick_init();
void tick_update();

void check_room_changed();
void calculate_image_borders();
void room_load(uint8_t roomNumber);
DATAFILE* room_load_datafile(uint8_t roomNumber);
void room_action_update();
void room_draw();
void room_front_layer_draw();
void room_objects_draw(uint8_t layer);
void room_update_scroll();

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
void gui_destroy();
void gui_update();
void gui_draw();

void dialog_init();
void dialog_draw();

void sfx_init();
void sfx_destroy();
void sfx_update();
void sfx_play(uint16_t soundId, uint8_t voice, bool rndFreq);

void play_music(uint16_t musicId, int loop);
void stop_music();

void credits_init();
void credits_draw();

void playTime_init();
void playTime_update();
#endif
