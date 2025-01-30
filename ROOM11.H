/*
=========================================================
 Room Number:   11
 Room Name:     11_PEOffice
=========================================================
*/

#ifndef H_ROOM11
#define H_ROOM11

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R11DATA.H"

//define room properties
#define R11_START_POS_X         76
#define R11_START_POS_Y         99
#define R11_ROOM_NUM_OBJS       2
#define R11_MUSIC_ID            10
#define R11_FADE                false
#define R11_LIGHTS_OFF          false

//define room data (compose room properties and function pointers)
#define R11_DATA R11_START_POS_X, R11_START_POS_Y, R11_ROOM_NUM_OBJS, R11_MUSIC_ID, R11_FADE , R11_LIGHTS_OFF , &r11_room_init, &r11_room_update, &r11_get_hotspot_name, &r11_get_default_hotspot_verb, &r11_get_object_info

//define object array alias
#define R11_TEACHER_OBJ_ID        0
#define R11_PLY_BACK_OAT_OBJ_ID   1

//define object data (objId, x, y, animId, active, layer)
#define R11_OBJ_0           r11d_objReading1,   211, 64,  1, true, 0
#define R11_OBJ_1           r11d_objBackOat,    198, 120,  0, false, 1

//define room animations
#define R11_NUM_ANIMATIONS  1

#define R11_ANIM_READING    r11d_objReading1, r11d_objReading4, 2, ANIM_PING_PONG
#define R11_ANIM_TALK       r11d_objTalk1,    r11d_objTalk9, 1, ANIM_PING_PONG
#define R11_ANIM_TAKE       r11d_objTake,     r11d_objTake, 3, ANIM_ONCE
#define R11_ANIM_SURPRISE   r11d_objSurprise, r11d_objSurprise, 3, ANIM_ONCE
#define R11_ANIM_IDLE       r11d_objTalk7,    r11d_objTalk7, 1, ANIM_LOOP

//define custom scripts (>256)
#define R11_SHOW_DISEASE_SCRIPT     257

//hotspot code room enumeration
enum r11_hotspotCode{
    r11_door    = 32,
    r11_earthGlobe    = 33,
    r11_things    = 34,
    r11_cup    = 35,
    r11_teacher    = 36,
};

//declare and define room objects array
static tObject r11_object[R11_ROOM_NUM_OBJS] =
{
    {R11_OBJ_0},
    {R11_OBJ_1},
};

//declare room objects animations array
static tAnimation r11_animations[R11_NUM_ANIMATIONS];

//declare room dialog actor
static tActorTalk r11_dialogActor = {211, 10, 82, false};

//declare room functions called from game
void r11_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r11_get_default_hotspot_verb(uint8_t colorCode);
tObject* r11_get_object_info(uint8_t numObject);
void r11_room_init();
void r11_room_update();

//declare internal functions
void r11_update_room_objects();
void r11_update_room_script();
void r11_update_dialog_selection();
#endif