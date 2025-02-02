/*
=========================================================
 Room Number:   09
 Room Name:     09_locker
=========================================================
*/

#ifndef H_ROOM09
#define H_ROOM09

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R09DATA.H"

//define room properties
#define R09_START_POS_X         230
#define R09_START_POS_Y         109
#define R09_ROOM_NUM_OBJS       7
#define R09_MUSIC_ID            7
#define R09_FADE                false
#define R09_LIGHTS_OFF                false

//define room data (compose room properties and function pointers)
#define R09_DATA R09_START_POS_X, R09_START_POS_Y, R09_ROOM_NUM_OBJS, R09_MUSIC_ID, R09_FADE , R09_LIGHTS_OFF , &r09_room_init, &r09_room_update, &r09_get_hotspot_name, &r09_get_default_hotspot_verb, &r09_get_object_info

//define object array alias
#define R09_BENCH_OBJ_ID        0
#define R09_LOCKER1OPEN_OBJ_ID  1
#define R09_LOCKER2OPEN_OBJ_ID  2
#define R09_LOCKER3OPEN_OBJ_ID  3
#define R09_SHIRT_OBJ_ID        4
#define R09_JEANS_OBJ_ID        5
#define R09_DOOR_OBJ_ID         6

//define object data (objId, x, y, animId, active, layer)
#define R09_OBJ_0           r09d_objBench,         149, 154,  0, true, 1
#define R09_OBJ_1           r09d_objLocker1Open,   79,  85,  0, false, 0
#define R09_OBJ_2           r09d_objLocker2Open,   139, 83,  0, false, 0
#define R09_OBJ_3           r09d_objLocker3Open,   189, 79,  0, false, 0
#define R09_OBJ_4           r09d_objShirt,         84,  58,  0, false, 0
#define R09_OBJ_5           r09d_objJeans,         175, 76,  0, false, 0
#define R09_OBJ_6           r09d_objDoor,          241, 95,  0, false, 0

//define room animations
#define R09_NUM_ANIMATIONS  0

//define custom scripts (>256)
#define R09_DOOR_CLOSE_SCRIPT   257

//hotspot code room enumeration
enum r09_hotspotCode{
    r09_door    = 32,
    r09_bench    = 33,
    r09_locker1    = 34,
    r09_locker2    = 36,
    r09_locker3    = 37,
    r09_locker4    = 35,
    r09_jeans    = 38,
    r09_shirt    = 39,
    r09_books    = 40,
    r09_poster   = 41,
    r09_shoes    = 42,
    r09_bag      = 43,
    r09_box      = 44,
};

//declare and define room objects array
static tObject r09_object[R09_ROOM_NUM_OBJS] =
{
    {R09_OBJ_0},
    {R09_OBJ_1},
    {R09_OBJ_2},
    {R09_OBJ_3},
    {R09_OBJ_4},
    {R09_OBJ_5},
    {R09_OBJ_6},
};

//declare room objects animations array
static tAnimation r09_animations[R09_NUM_ANIMATIONS];

//declare room functions called from game
void r09_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r09_get_default_hotspot_verb(uint8_t colorCode);
tObject* r09_get_object_info(uint8_t numObject);
void r09_room_init();
void r09_room_update();

//declare internal functions
void r09_update_room_objects();
void r09_update_room_script();
void r09_update_dialog_selection();
#endif