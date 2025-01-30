/*
=========================================================
 Room Number:   06
 Room Name:     06_school
=========================================================
*/

#ifndef H_ROOM06
#define H_ROOM06

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R06DATA.H"

//define room properties
#define R06_START_POS_X         57
#define R06_START_POS_Y         103
#define R06_ROOM_NUM_OBJS       5
#define R06_MUSIC_ID            3
#define R06_FADE                true
#define R06_LIGHTS_OFF          false

//define room data (compose room properties and function pointers)
#define R06_DATA R06_START_POS_X, R06_START_POS_Y, R06_ROOM_NUM_OBJS, R06_MUSIC_ID, R06_FADE , R06_LIGHTS_OFF , &r06_room_init, &r06_room_update, &r06_get_hotspot_name, &r06_get_default_hotspot_verb, &r06_get_object_info

//define object array alias
#define R06_MAINTDOOROPEN_OBJ_ID        0
#define R06_MAINTDOOROPENLIGHT_OBJ_ID   1
#define R06_BATHMATIN_OBJ_ID            2
#define R06_BATHMATOUT_OBJ_ID           3
#define R06_KEY_OBJ_ID                  4

//define object data (objId, x, y, animId, active, layer)
#define R06_OBJ_0           r06d_objMaintDoorOpen,      115, 77,  0, false, 0
#define R06_OBJ_1           r06d_objMaintDoorOpenLight, 115, 77,  0, false, 0
#define R06_OBJ_2           r06d_objBathMatIn,          128, 105,  0, false, 0
#define R06_OBJ_3           r06d_objBathMatOut,         128, 107,  0, false, 0
#define R06_OBJ_4           r06d_objKey,                136, 107,  0, false, 0

//define room animations
#define R06_NUM_ANIMATIONS  0

//hotspot code room enumeration
enum r06_hotspotCode{
    r06_door    = 32,
    r06_maintLockerDoor    = 33,
    r06_maintLockerLock    = 44,
    r06_maintLockerBathMat = 45,
    r06_maintLockerKey     = 46,
    r06_paint    = 34,
    r06_computerRoomDoor    = 35,
    r06_window    = 36,
    r06_scienceRoomDoor    = 37,
    r06_board    = 38,
    r06_schoolBathDoor    = 39,
    r06_lockerDoor    = 40,
    r06_orla    = 41,
    r06_bench    = 42,
    r06_PEOfficeRoom    = 43,
};

//declare and define room objects array
static tObject r06_object[R06_ROOM_NUM_OBJS] =
{
    {R06_OBJ_0},
    {R06_OBJ_1},
    {R06_OBJ_2},
    {R06_OBJ_3},
    {R06_OBJ_4},
};

//declare room objects animations array
static tAnimation r06_animations[R06_NUM_ANIMATIONS];

//declare room functions called from game
void r06_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r06_get_default_hotspot_verb(uint8_t colorCode);
tObject* r06_get_object_info(uint8_t numObject);
void r06_room_init();
void r06_room_update();

//declare internal functions
void r06_update_room_objects();
void r06_update_room_script();
void r06_update_dialog_selection();
#endif
