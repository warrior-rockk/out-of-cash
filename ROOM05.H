/*
=========================================================
 Room Number:   05
 Room Name:     05_stationery
=========================================================
*/

#ifndef H_ROOM05
#define H_ROOM05

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R05DATA.H"

//define room properties
#define R05_START_POS_X         65
#define R05_START_POS_Y         120
#define R05_ROOM_NUM_OBJS       0
#define R05_MUSIC_ID            0
#define R05_FADE                false
#define R05_LIGHTS_OFF                false

//define room data (compose room properties and function pointers)
#define R05_DATA R05_START_POS_X, R05_START_POS_Y, R05_ROOM_NUM_OBJS, R05_MUSIC_ID, R05_FADE , R05_LIGHTS_OFF , &r05_room_init, &r05_room_update, &r05_get_hotspot_name, &r05_get_default_hotspot_verb, &r05_get_object_info

//define room animations
#define R05_NUM_ANIMATIONS  0

//hotspot code room enumeration
enum r05_hotspotCode{
    r05_door    = 32,
};

//declare and define room objects array
static tObject r05_object[R05_ROOM_NUM_OBJS] =
{
};

//declare room objects animations array
static tAnimation r05_animations[R05_NUM_ANIMATIONS];

//declare room functions called from game
void r05_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r05_get_default_hotspot_verb(uint8_t colorCode);
tObject* r05_get_object_info(uint8_t numObject);
void r05_room_init();
void r05_room_update();

//declare internal functions
void r05_update_room_objects();
void r05_update_room_script();
void r05_update_dialog_selection();
#endif