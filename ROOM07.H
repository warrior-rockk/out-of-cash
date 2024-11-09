/*
=========================================================
 Room Number:   07
 Room Name:     07_school02
=========================================================
*/

#ifndef H_ROOM07
#define H_ROOM07

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R07DATA.H"

//define room properties
#define R07_START_POS_X         160
#define R07_START_POS_Y         80
#define R07_ROOM_NUM_OBJS       0
#define R07_MUSIC_ID            0
#define R07_FADE                false
#define R07_LIGHTS_OFF                false

//define room data (compose room properties and function pointers)
#define R07_DATA R07_START_POS_X, R07_START_POS_Y, R07_ROOM_NUM_OBJS, R07_MUSIC_ID, R07_FADE , R07_LIGHTS_OFF , &r07_room_init, &r07_room_update, &r07_get_hotspot_name, &r07_get_default_hotspot_verb, &r07_get_object_info

//define room animations
#define R07_NUM_ANIMATIONS  0

//hotspot code room enumeration
enum r07_hotspotCode{
    r07_door    = 32,
};

//declare and define room objects array
static tObject r07_object[R07_ROOM_NUM_OBJS] =
{
};

//declare room objects animations array
static tAnimation r07_animations[R07_NUM_ANIMATIONS];

//declare room functions called from game
void r07_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r07_get_default_hotspot_verb(uint8_t colorCode);
tObject* r07_get_object_info(uint8_t numObject);
void r07_room_init();
void r07_room_update();

//declare internal functions
void r07_update_room_objects();
void r07_update_room_script();
void r07_update_dialog_selection();
#endif