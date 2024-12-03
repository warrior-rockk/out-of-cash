/*
=========================================================
 Room Number:   12
 Room Name:     12_schoolBath
=========================================================
*/

#ifndef H_ROOM12
#define H_ROOM12

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R12DATA.H"

//define room properties
#define R12_START_POS_X         77
#define R12_START_POS_Y         80
#define R12_ROOM_NUM_OBJS       0
#define R12_MUSIC_ID            0
#define R12_FADE                false
#define R12_LIGHTS_OFF                false

//define room data (compose room properties and function pointers)
#define R12_DATA R12_START_POS_X, R12_START_POS_Y, R12_ROOM_NUM_OBJS, R12_MUSIC_ID, R12_FADE , R12_LIGHTS_OFF , &r12_room_init, &r12_room_update, &r12_get_hotspot_name, &r12_get_default_hotspot_verb, &r12_get_object_info

//define room animations
#define R12_NUM_ANIMATIONS  0

//hotspot code room enumeration
enum r12_hotspotCode{
    r12_door    = 32,
    r12_mirror    = 33,
    r12_towelDispenser    = 34,
    r12_washbowl    = 35,
    r12_closedDoor    = 36,
    r12_hole    = 37,
    r12_holeDoor    = 38,
};

//declare and define room objects array
static tObject r12_object[R12_ROOM_NUM_OBJS] =
{
};

//declare room objects animations array
static tAnimation r12_animations[R12_NUM_ANIMATIONS];

//declare room functions called from game
void r12_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r12_get_default_hotspot_verb(uint8_t colorCode);
tObject* r12_get_object_info(uint8_t numObject);
void r12_room_init();
void r12_room_update();

//declare internal functions
void r12_update_room_objects();
void r12_update_room_script();
void r12_update_dialog_selection();
#endif