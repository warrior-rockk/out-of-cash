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
#define R09_START_POS_X         229
#define R09_START_POS_Y         129
#define R09_ROOM_NUM_OBJS       0
#define R09_MUSIC_ID            0
#define R09_FADE                false
#define R09_LIGHTS_OFF                false

//define room data (compose room properties and function pointers)
#define R09_DATA R09_START_POS_X, R09_START_POS_Y, R09_ROOM_NUM_OBJS, R09_MUSIC_ID, R09_FADE , R09_LIGHTS_OFF , &r09_room_init, &r09_room_update, &r09_get_hotspot_name, &r09_get_default_hotspot_verb, &r09_get_object_info

//define room animations
#define R09_NUM_ANIMATIONS  0

//hotspot code room enumeration
enum r09_hotspotCode{
    r09_door    = 32,
    r09_bench    = 33,
    r09_locker1    = 34,
    r09_locker2    = 35,
    r09_locker3    = 36,
    r09_locker4    = 37,
    r09_jeans    = 38,
    r09_shirt    = 39,
};

//declare and define room objects array
static tObject r09_object[R09_ROOM_NUM_OBJS] =
{
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