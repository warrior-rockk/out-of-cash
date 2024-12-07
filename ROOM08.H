/*
=========================================================
 Room Number:   08
 Room Name:     08_computerRoom
=========================================================
*/

#ifndef H_ROOM08
#define H_ROOM08

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R08DATA.H"

//define room properties
#define R08_START_POS_X         245
#define R08_START_POS_Y         100
#define R08_ROOM_NUM_OBJS       0
#define R08_MUSIC_ID            0
#define R08_FADE                false
#define R08_LIGHTS_OFF                false

//define room data (compose room properties and function pointers)
#define R08_DATA R08_START_POS_X, R08_START_POS_Y, R08_ROOM_NUM_OBJS, R08_MUSIC_ID, R08_FADE , R08_LIGHTS_OFF , &r08_room_init, &r08_room_update, &r08_get_hotspot_name, &r08_get_default_hotspot_verb, &r08_get_object_info

//define room animations
#define R08_NUM_ANIMATIONS  0

//hotspot code room enumeration
enum r08_hotspotCode{
    r08_door    = 32,
    r08_window    = 33,
    r08_computer3    = 34,
    r08_manual    = 35,
    r08_computer1    = 36,
    r08_nerd    = 37,
    r08_computer2    = 38,
    r08_chair    = 39,
};

//declare and define room objects array
static tObject r08_object[R08_ROOM_NUM_OBJS] =
{
};

//declare room objects animations array
static tAnimation r08_animations[R08_NUM_ANIMATIONS];

//declare room functions called from game
void r08_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r08_get_default_hotspot_verb(uint8_t colorCode);
tObject* r08_get_object_info(uint8_t numObject);
void r08_room_init();
void r08_room_update();

//declare internal functions
void r08_update_room_objects();
void r08_update_room_script();
void r08_update_dialog_selection();
#endif