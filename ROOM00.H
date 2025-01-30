/*
=========================================================
 Room Number:   00
 Room Name:     00_street
=========================================================
*/

#ifndef H_ROOM00
#define H_ROOM00

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R00DATA.H"

//define room properties
#define R00_START_POS_X         160
#define R00_START_POS_Y         100
#define R00_ROOM_NUM_OBJS       0
#define R00_MUSIC_ID            1
#define R00_FADE                false
#define R00_LIGHTS_OFF                false

//define room data (compose room properties and function pointers)
#define R00_DATA R00_START_POS_X, R00_START_POS_Y, R00_ROOM_NUM_OBJS, R00_MUSIC_ID, R00_FADE , R00_LIGHTS_OFF , &r00_room_init, &r00_room_update, &r00_get_hotspot_name, &r00_get_default_hotspot_verb, &r00_get_object_info

//define room animations
#define R00_NUM_ANIMATIONS  0

//define custom scripts >256
#define R00_INTRO_SCRIPT 257

//hotspot code room enumeration
enum r00_hotspotCode{
    r00_door    = 32,
    r00_sign    = 33,
    r00_stationery    = 34,
    r00_school    = 35,
    r00_shop    = 36,
};


//declare and define room objects array
static tObject r00_object[R00_ROOM_NUM_OBJS] =
{
};

//declare room objects animations array
static tAnimation r00_animations[R00_NUM_ANIMATIONS];

//declare room functions called from game
void r00_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r00_get_default_hotspot_verb(uint8_t colorCode);
tObject* r00_get_object_info(uint8_t numObject);
void r00_room_init();
void r00_room_update();

//declare internal functions
void r00_update_room_objects();
void r00_update_room_script();
void r00_update_dialog_selection();
#endif
