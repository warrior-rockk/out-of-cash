/*
=========================================================
 Room Number:   02
 Room Name:     02_corridor
=========================================================
*/

#ifndef H_ROOM02
#define H_ROOM02

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R02DATA.H"

//define room properties
#define R02_START_POS_X         179
#define R02_START_POS_Y         117
#define R02_ROOM_NUM_OBJS       1
#define R02_MUSIC_ID            0
#define R02_FADE                false
#define R02_LIGHTS_OFF                false

//define room data (compose room properties and function pointers)
#define R02_DATA R02_START_POS_X, R02_START_POS_Y, R02_ROOM_NUM_OBJS, R02_MUSIC_ID, R02_FADE , R02_LIGHTS_OFF , &r02_room_init, &r02_room_update, &r02_get_hotspot_name, &r02_get_default_hotspot_verb, &r02_get_object_info

//define object array alias
#define R02_BATHDOOR_OBJ_ID 0

//define object data (objId, x, y, animId, active, layer)
#define R02_OBJ_0           r02d_objBathDoor,   141, 33,  0, false, 0

//define room animations
#define R02_NUM_ANIMATIONS  0

//hotspot code room enumeration
enum r02_hotspotCode{
    r02_mirror    = 139,
    r02_bathDoor    = 127,
    r02_flowers    = 156,
    r02_elephant    = 174,
    r02_kitchen    = 153,
    r02_door    = 40,
    r02_picture    = 155,
    r02_bedRoomDoor    = 236,
    r02_street    = 122,
    r02_lamp    = 144,
};

//declare and define room objects array
static tObject r02_object[R02_ROOM_NUM_OBJS] =
{
    {R02_OBJ_0},
};

//declare room objects animations array
static tAnimation r02_animations[R02_NUM_ANIMATIONS];

//declare room dialog actor
static tActorTalk r02_dialogActor = {0, 0, 70, false};

//declare room functions called from game
void r02_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r02_get_default_hotspot_verb(uint8_t colorCode);
tObject* r02_get_object_info(uint8_t numObject);
void r02_room_init();
void r02_room_update();

//declare internal functions
void r02_update_room_objects();
void r02_update_room_script();
void r02_update_dialog_selection();
#endif