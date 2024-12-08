/*
=========================================================
 Room Number:   04
 Room Name:     04_kitchen
=========================================================
*/

#ifndef H_ROOM04
#define H_ROOM04

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R04DATA.H"

//define room properties
#define R04_START_POS_X         84
#define R04_START_POS_Y         99
#define R04_ROOM_NUM_OBJS       3
#define R04_MUSIC_ID            0
#define R04_FADE                false
#define R04_LIGHTS_OFF          false

//define room data (compose room properties and function pointers)
#define R04_DATA R04_START_POS_X, R04_START_POS_Y, R04_ROOM_NUM_OBJS, R04_MUSIC_ID, R04_FADE , R04_LIGHTS_OFF , &r04_room_init, &r04_room_update, &r04_get_hotspot_name, &r04_get_default_hotspot_verb, &r04_get_object_info

//define object array alias
#define R04_FATHER_OBJ_ID 0
#define R04_STARCLOCK_OBJ_ID 1
#define R04_SPATULA_OBJ_ID 2

//define object data (objId, x, y, animId, active, layer)
#define R04_OBJ_0           r04d_objFatherRead,   165, 130,  1, true, 1
#define R04_OBJ_1           r04d_objStarClock,   138, 34,  0, true, 1
#define R04_OBJ_2           r04d_objSpatula,   220, 57,  0, true, 1

//define room animations
#define R04_NUM_ANIMATIONS  1
#define R04_ANIM_FATHER_TALK    r04d_objFatherIdle, r04d_objFatherTalk, 1, ANIM_LOOP

//hotspot code room enumeration
enum r04_hotspotCode{
    r04_corridor    = 164,
    r04_fridge    = 99,
    r04_father    = 176,
    r04_trash    = 148,
    r04_paper    = 191,
    r04_oven    = 139,
    r04_spatula    = 205,
    r04_cheesse    = 81,
    r04_clock      = 32,
};

//declare and define room objects array
static tObject r04_object[R04_ROOM_NUM_OBJS] =
{
    {R04_OBJ_0},
    {R04_OBJ_1},
    {R04_OBJ_2},
};

//declare room objects animations array
static tAnimation r04_animations[R04_NUM_ANIMATIONS];

//declare room dialog actor (msgX, msgY, textColor, talking)
static tActorTalk r04_dialogActor = {220, 96, 70, false};

//declare room functions called from game
void r04_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r04_get_default_hotspot_verb(uint8_t colorCode);
tObject* r04_get_object_info(uint8_t numObject);
void r04_room_init();
void r04_room_update();

//declare internal functions
void r04_update_room_objects();
void r04_update_room_script();
void r04_update_dialog_selection();
#endif
