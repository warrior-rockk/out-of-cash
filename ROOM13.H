/*
=========================================================
 Room Number:   13
 Room Name:     13_ending
=========================================================
*/

#ifndef H_ROOM13
#define H_ROOM13

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R13DATA.H"

//define room properties
#define R13_START_POS_X         -20
#define R13_START_POS_Y         160
#define R13_ROOM_NUM_OBJS       5
#define R13_MUSIC_ID            14
#define R13_FADE                false
#define R13_LIGHTS_OFF          false

//define room data (compose room properties and function pointers)
#define R13_DATA R13_START_POS_X, R13_START_POS_Y, R13_ROOM_NUM_OBJS, R13_MUSIC_ID, R13_FADE , R13_LIGHTS_OFF , &r13_room_init, &r13_room_update, &r13_get_hotspot_name, &r13_get_default_hotspot_verb, &r13_get_object_info

//define object array alias
#define R13_CROWD_OBJ_ID        0
#define R13_SPEAKERS_OBJ_ID     1
#define R13_GUITAR_1_OBJ_ID     2
#define R13_GUITAR_2_OBJ_ID     3
#define R13_DRUMS_OBJ_ID        4

//define object data (objId, x, y, animId, active, layer)
#define R13_OBJ_0           r13d_objCrowd1,       160, 185,  1, true, 1
#define R13_OBJ_1           r13d_objSpeakers1,    160, 97,  2, true, 0
#define R13_OBJ_2           r13d_objGuitar11,     88,  65,  3, true, 0
#define R13_OBJ_3           r13d_objGuitar21,     244, 62,  4, true, 0
#define R13_OBJ_4           r13d_objDrums1,       167, 32,  5, true, 0

//define room animations
#define R13_NUM_ANIMATIONS  5

#define R13_ANIM_CROWD      r13d_objCrowd1,     r13d_objCrowd2,     4, ANIM_LOOP
#define R13_ANIM_SPEAKERS   r13d_objSpeakers1,  r13d_objSpeakers4,  1, ANIM_PING_PONG
#define R13_ANIM_GUITAR_1   r13d_objGuitar11,   r13d_objGuitar12,   2, ANIM_LOOP
#define R13_ANIM_GUITAR_2   r13d_objGuitar21,   r13d_objGuitar22,   2, ANIM_LOOP
#define R13_ANIM_DRUMS      r13d_objDrums1,     r13d_objDrums4,     1, ANIM_LOOP

//define custom scripts >256
#define R13_ENDING_SCRIPT   257

//hotspot code room enumeration
enum r13_hotspotCode{
    dummy = 0,
};

//declare and define room objects array
static tObject r13_object[R13_ROOM_NUM_OBJS] =
{
    {R13_OBJ_0},
    {R13_OBJ_1},
    {R13_OBJ_2},
    {R13_OBJ_3},
    {R13_OBJ_4},
};

//declare room objects animations array
static tAnimation r13_animations[R13_NUM_ANIMATIONS];

//declare room functions called from game
void r13_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r13_get_default_hotspot_verb(uint8_t colorCode);
tObject* r13_get_object_info(uint8_t numObject);
void r13_room_init();
void r13_room_update();

//declare internal functions
void r13_update_room_objects();
void r13_update_room_script();
void r13_update_dialog_selection();
#endif
