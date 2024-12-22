/*
=========================================================
 Room Number:   10
 Room Name:     10_maintCloset
=========================================================
*/

#ifndef H_ROOM10
#define H_ROOM10

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R10DATA.H"

//define room properties
#define R10_START_POS_X         134
#define R10_START_POS_Y         95
#define R10_ROOM_NUM_OBJS       3
#define R10_MUSIC_ID            0
#define R10_FADE                false
#define R10_LIGHTS_OFF          true

//define room data (compose room properties and function pointers)
#define R10_DATA R10_START_POS_X, R10_START_POS_Y, R10_ROOM_NUM_OBJS, R10_MUSIC_ID, R10_FADE , R10_LIGHTS_OFF , &r10_room_init, &r10_room_update, &r10_get_hotspot_name, &r10_get_default_hotspot_verb, &r10_get_object_info

//define object array alias
#define R10_MAINTCLOSETOPEN_OBJ_ID  0
#define R10_PAINTBUCKET_OBJ_ID      1
#define R10_DOOROPEN_OBJ_ID         2

//define object data (objId, x, y, animId, active, layer)
#define R10_OBJ_0           r10d_objMaintClosetOpen,   174, 98,  0, false, 0
#define R10_OBJ_1           r10d_objPaintBucket,       167, 115,  0, false, 0
#define R10_OBJ_2           r10d_objDoorOpen,          131, 75,  0, true, 0

//define room animations
#define R10_NUM_ANIMATIONS  0

//hotspot code room enumeration
enum r10_hotspotCode{
    r10_door    = 32,
    r10_switch    = 33,
    r10_spiderWeb    = 34,
    r10_closet    = 35,
    r10_paintBucket    = 36,
};

//declare and define room objects array
static tObject r10_object[R10_ROOM_NUM_OBJS] =
{
    {R10_OBJ_0},
    {R10_OBJ_1},
    {R10_OBJ_2},
};

//declare room objects animations array
static tAnimation r10_animations[R10_NUM_ANIMATIONS];

//declare room functions called from game
void r10_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r10_get_default_hotspot_verb(uint8_t colorCode);
tObject* r10_get_object_info(uint8_t numObject);
void r10_room_init();
void r10_room_update();

//declare internal functions
void r10_update_room_objects();
void r10_update_room_script();
void r10_update_dialog_selection();
#endif