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
#define R13_START_POS_X         0
#define R13_START_POS_Y         0
#define R13_ROOM_NUM_OBJS       0
#define R13_MUSIC_ID            0
#define R13_FADE                false
#define R13_LIGHTS_OFF                false

//define room data (compose room properties and function pointers)
#define R13_DATA R13_START_POS_X, R13_START_POS_Y, R13_ROOM_NUM_OBJS, R13_MUSIC_ID, R13_FADE , R13_LIGHTS_OFF , &r13_room_init, &r13_room_update, &r13_get_hotspot_name, &r13_get_default_hotspot_verb, &r13_get_object_info

//define room animations
#define R13_NUM_ANIMATIONS  0

//hotspot code room enumeration
enum r13_hotspotCode{
    dummy = 0,
};

//declare and define room objects array
static tObject r13_object[R13_ROOM_NUM_OBJS] =
{
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
