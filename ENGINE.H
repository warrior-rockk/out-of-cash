//Adventure game engine global header
#ifndef H_ENGINE
#define H_ENGINE

#include <stdbool.h>
#include "gameflags.h"
#include "anim.h"

//Definitions
#define NUM_VERBS               10
#define NUM_RAND_ANSWERS        3
//Status bar
#define OBJECT_NAME_MAX_CHARS   25

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
    bool invScript; //temporal
    int object; //change to hotspot
    int invObject;
    enum verbs verb;
    int step;
    int lastStep;
    int stepTime;
    int hsX;
    int hsY;
} roomScript;

//object structure
typedef struct tObject
{
    //object id (corresponds to index of objects datafile header)
    int objId;
    //position
    int x;
    int y;
    //properties
    bool active;
} tObject;

//global debug vars structure (only ints on this iteration)
struct debugVars
{
    int var[DEBUG_MAX_VARS];
    char varName[DEBUG_MAX_VARS][10];
    int numVars;
} debugVars;

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
#endif