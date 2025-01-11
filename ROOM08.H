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
//includ0e room datafile header data
#include "R08DATA.H"

//define room properties
#define R08_START_POS_X         245
#define R08_START_POS_Y         100
#define R08_ROOM_NUM_OBJS       1
#define R08_MUSIC_ID            0
#define R08_FADE                false
#define R08_LIGHTS_OFF          false

//define room data (compose room properties and function pointers)
#define R08_DATA R08_START_POS_X, R08_START_POS_Y, R08_ROOM_NUM_OBJS, R08_MUSIC_ID, R08_FADE , R08_LIGHTS_OFF , &r08_room_init, &r08_room_update, &r08_get_hotspot_name, &r08_get_default_hotspot_verb, &r08_get_object_info

//define object array alias
#define R08_NERD_OBJ_ID        0

//define object data (objId, x, y, animId, active, layer)
#define R08_OBJ_0           r08d_objPlay1,   115, 100,  1, true, 0

//define room animations
#define R08_NUM_ANIMATIONS  1

#define R08_ANIM_IDLE           r08d_objIdle, r08d_objIdle, 1, ANIM_LOOP
#define R08_ANIM_PLAYING        r08d_objPlay1, r08d_objPlay6, 6, ANIM_PING_PONG
#define R08_ANIM_TALK           r08d_objTalk1, r08d_objTalk9, 1, ANIM_PING_PONG
#define R08_ANIM_TALK_PLAYING   r08d_objTalkPlay1, r08d_objTalkPlay6, 1, ANIM_PING_PONG

//define custom scripts (>256)
#define R08_COSTUME_COMPLETE_SCRIPT 257

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
    {R08_OBJ_0},
};

//declare room objects animations array
static tAnimation r08_animations[R08_NUM_ANIMATIONS];

//declare room dialog actor
static tActorTalk r08_dialogActor = {118, 66, 98, false};

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