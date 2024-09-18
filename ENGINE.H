//Adventure game engine global header
#ifndef H_ENGINE
#define H_ENGINE

#include <stdbool.h>
#include "gameflags.h"
#include "anim.h"

//Definitions
#define NUM_VERBS               10
#define NUM_RAND_ANSWERS        3

//dialogs
#define NUM_MAX_DIALOG_LINES    5
#define DIALOG_ST_SELECT        0
#define DIALOG_ST_SCRIPT        1

//Status bar
#define OBJECT_NAME_MAX_CHARS   25

//Scripts
#define ROOM_SCRIPT_TYPE        0
#define DIALOG_SCRIPT_TYPE      1
#define INVENTORY_SCRIPT_TYPE   2

//Texts
#define MAX_SENTENCE_LENGTH     50

//Debug
#define DEBUG_MAX_VARS          10

//Directions
#define DIR_NONE                0
#define DIR_RIGHT               1
#define DIR_LEFT                2

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
    bool active;
    bool scriptAssigned;
    uint8_t type;
    int object;
    int invObject;
    enum verbs verb;
    int step;
    int lastStep;
    int stepTime;
    int hsX;
    int hsY;
} roomScript;

//object room structure
typedef struct tObject
{
    //object id (corresponds to index of objects image datafile header)
    int objId;
    //position
    int x;
    int y;
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
    char lineText[NUM_MAX_DIALOG_LINES][MAX_SENTENCE_LENGTH];
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

#ifdef DEBUGMODE
//debug structure
struct debug
{
    //global debug vars structure (only ints on this iteration)
    int var[DEBUG_MAX_VARS];
    char varName[DEBUG_MAX_VARS][10];
    int numVars;
    //show walk room image
    bool showWalkImage;
} debug;
#endif

//global functions
void init_room_script();
int say(char *message);

void script_say(char *message);
void script_wait(int time);
void script_move_player(int x, int y);
void script_move_player_to_target();
void script_take_object(bool *objActive, uint8_t gameFlag, uint8_t invObjectNum);
void script_play_player_animation(int startFrame, int endFrame, int speed);
void script_player_take_state();
void script_remove_inv_object(int numObject);
void script_start_dialog(uint8_t dialogId);
void script_next_dialog_node();

void dialog_add(char *textLine, uint8_t destNode);
void stop_dialog();

void set_game_flag(uint8_t flagNum);
void clear_game_flag(uint8_t flagNum);
void toogle_game_flag(uint8_t flagNum);
bool is_game_flag(uint8_t flagNum);

void change_room(int roomNum);
void change_room_pos(int roomNum, int x, int y);
void game_fade_in();
void game_fade_out();
void default_verb_action(enum verbs roomVerb);
void mytrace(char *s, ...);
void begin_script();
void end_script();
void show_debug(char *varName, int var);
void move_player(int x, int y);
void move_player_to_target();
bool is_player_moving();
void change_player_dir(uint8_t dir);

void object_play_animation(tObject *object, uint8_t idleFrame, tAnimation *animation, int startFrame, int endFrame, int speed, uint8_t mode);


#endif