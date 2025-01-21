//Adventure game engine global header
#ifndef H_ENGINE
#define H_ENGINE

#include <stdbool.h>
#include "gameflag.h"
#include "anim.h"

//include game resources references
#include "IDATA.h"
#include "SDATA.h"

//Definitions
#define NUM_VERBS               10
#define NUM_RAND_ANSWERS        6

//dialogs
#define MAX_DIALOG_LINE_LENGTH      100
#define MAX_DIALOG_LINE_SCROLL      52  //49
#define DIALOG_TEXT_SCROLL_DELAY    3   //300ms
#define NUM_MAX_DIALOG_LINES        5
#define DIALOG_ST_SELECT            0
#define DIALOG_ST_SCRIPT            1

//Status bar
#define OBJECT_NAME_MAX_CHARS   25

//Scripts
#define ROOM_SCRIPT_TYPE        0
#define DIALOG_SCRIPT_TYPE      1
#define INVENTORY_SCRIPT_TYPE   2

//Debug
#define DEBUG_MAX_VARS          10

//Directions
#define DIR_NONE                0
#define DIR_RIGHT               1
#define DIR_LEFT                2
#define DIR_BACK                3
#define DIR_FRONT               4

//room numbers
#define STREET_ROOM_NUM         0
#define BEDROOM_ROOM_NUM        1
#define CORRIDOR_ROOM_NUM       2
#define BATH_ROOM_NUM           3
#define KITCHEN_ROOM_NUM        4
#define STATIONERY_ROOM_NUM     5
#define SCHOOL_ROOM_NUM         6
#define SCIENCE_ROOM_NUM        7
#define COMPUTER_ROOM_NUM       8
#define LOCKER_ROOM_NUM         9
#define MAINT_LOCKER_ROOM_NUM   10
#define PE_OFFICE_ROOM_NUM      11
#define SCHOOL_BATH_ROOM_NUM    12
#define ENDING_ROOM_NUM         13

//Fade speeds
#define FADE_SLOW_SPEED         2
#define FADE_DEFAULT_SPEED      6
#define FADE_FAST_SPEED         12

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
    TALK,
    USE_WITH
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
    "Hablar a",
    "Usar" //USE_WITH
};

//global room script structure
struct roomScript
{
    int16_t object;
    int16_t invObject;
    enum verbs verb;
    int16_t step;
    int16_t lastStep;
    int16_t stepTime;
    int16_t hsX;
    int16_t hsY;
    uint8_t type;
    bool active;
    bool scriptAssigned;
} roomScript;

//object room structure
typedef struct tObject
{
    //object id (corresponds to index of objects image datafile header)
    int16_t objId;
    //position
    int16_t x;
    int16_t y;
    //animation id
    uint8_t animationId;
    //properties
    bool active;
    uint8_t layer;
} tObject;

//dialog structure
struct dialog
{
    //unique room identification of dialog (for multi-dialog on room)
    uint8_t dialogId;
    //line texts array of actual dialog node
    char lineText[NUM_MAX_DIALOG_LINES][MAX_DIALOG_LINE_LENGTH];
    //destination node for each linea
    uint8_t lineDestNode[NUM_MAX_DIALOG_LINES];
    //num of lines on node
    uint8_t nodeNumLines;
    //actual node
    uint8_t node;
    //actual line selection
    uint8_t selLine;
    //actual line highlighted
    uint8_t highlightLine;
    //dialog active flag
    bool active;
    //dialog state (selecting line or executing dialog script)
    uint8_t state;
} dialog;

//talk structure for actors
typedef struct tActorTalk
{
    int16_t msgX;
    int16_t msgY;
    uint8_t textColor;
    bool talking;
} tActorTalk;

#ifdef DEBUGMODE
//debug structure
struct debug
{
    //global debug vars structure (only ints on this iteration)
    int16_t var[DEBUG_MAX_VARS];
    char varName[DEBUG_MAX_VARS][20];
    int16_t numVars;
    uint8_t numCursorRoomObject;
    //show walk room image
    bool showWalkImage;
    //show hotspot room image
    bool showHotspotImage;
    //cursor room objects
    bool cursorRoomObjects;
    //debug info
    bool showDebugInfo;
    //obtain all inventory items
    bool allInvObjects;
} debug;
#endif

//global functions
void init_room_script();
int say(char *message);
int say_actor(char *message, tActorTalk *actorTalk);

void script_say(char *message);
void script_say_actor(char *message, tActorTalk *actorTalk);
void script_wait(int time);
void script_move_player(int x, int y);
void script_move_player_to_target();
void script_move_player_no_clip(int x, int y);
void script_take_object(bool *objActive, enum gameFlags gameFlag, uint8_t invObjectNum);
void script_play_player_animation(int startFrame, int endFrame, int speed, uint8_t mode0);
void script_player_take_state();
void script_object_play_animation(tObject *object, uint8_t idleFrame, tAnimation *animation, int startFrame, int endFrame, int speed, uint8_t mode);
void script_remove_inv_object(int numObject);
void script_add_inv_object(uint8_t numObject);
void script_combine_inv_object(uint8_t numObject1, uint8_t numObject2, uint8_t numObjectAdd);
void script_start_dialog(uint8_t dialogId);
void script_next_dialog_node();
void script_play_sound(int16_t soundId);
void script_play_sound_rnd(int16_t soundId);
void script_play_sound_wait(int16_t soundId);

void dialog_add(char *textLine, uint8_t destNode);
void dialog_jump(uint8_t node, uint8_t selLine, uint8_t destNode);
void stop_dialog();

void set_game_flag(enum gameFlags flagNum);
void clear_game_flag(enum gameFlags flagNum);
void toggle_game_flag(enum gameFlags flagNum);
bool is_game_flag(enum gameFlags flagNum);

void inc_game_var(enum gameVars varNum);
void dec_game_var(enum gameVars varNum);
void set_game_var(enum gameVars varNum, uint16_t value);
uint16_t get_game_var(enum gameVars varNum);

void change_room(int roomNum);
void change_room_pos(int roomNum, int x, int y);
uint8_t get_actual_room();
void set_room_light_off(bool lightsOff);
uint16_t get_last_room();

void game_fade_in();
void game_fade_out(uint8_t fadeSpeed);
void default_verb_action(enum verbs roomVerb);
void mytrace(char *s, ...);
void begin_script();
void end_script();
void start_script(uint16_t scriptNumber);
void show_debug(char *varName, int var);

void set_player_position(int x, int y);
void move_player(int x, int y, bool noclip);
void move_player_to_target();
bool is_player_moving();
void change_player_dir(uint8_t dir);
void player_take_state();
void play_player_animation(int startFrame, int endFrame, int speed, uint8_t mode);
void stop_player_animation();

bool object_play_animation(tObject *object, uint8_t idleFrame, tAnimation *animation, int startFrame, int endFrame, int speed, uint8_t mode);
void object_pos_on_player(tObject *object);

void play_sound(int16_t soundId);
void play_sound_rnd(uint16_t soundId);
void stop_sound();
void pause_sound();
void resume_sound();

#endif