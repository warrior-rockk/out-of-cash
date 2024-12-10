/*
=========================================================
 Room Number:   07
 Room Name:     07_scienceRoom
=========================================================
*/

#ifndef H_ROOM07
#define H_ROOM07

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R07DATA.H"

//define room properties
#define R07_START_POS_X         58
#define R07_START_POS_Y         80
#define R07_ROOM_NUM_OBJS       3
#define R07_MUSIC_ID            0
#define R07_FADE                false
#define R07_LIGHTS_OFF                false

//define room data (compose room properties and function pointers)
#define R07_DATA R07_START_POS_X, R07_START_POS_Y, R07_ROOM_NUM_OBJS, R07_MUSIC_ID, R07_FADE , R07_LIGHTS_OFF , &r07_room_init, &r07_room_update, &r07_get_hotspot_name, &r07_get_default_hotspot_verb, &r07_get_object_info

//define object array alias
#define R07_TABLE_OBJ_ID 0
#define R07_BRAIN_OBJ_ID 1
#define R07_KNIFE_OBJ_ID 2

//define object data (objId, x, y, animId, active, layer)
#define R07_OBJ_0           r07d_objTable,   159, 126,  0, true, 1
#define R07_OBJ_1           r07d_objBrain,   66, 131,  0, true, 1
#define R07_OBJ_2           r07d_objKnife,   254, 71,  0, true, 0

//define room animations
#define R07_NUM_ANIMATIONS  0

//hotspot code room enumeration
enum r07_hotspotCode{
    r07_door    = 32,
    r07_blackBoard    = 33,
    r07_notes    = 34,
    r07_brain    = 35,
    r07_washer1    = 36,
    r07_testTube    = 37,
    r07_sheets    = 38,
    r07_washer2    = 39,
    r07_glass    = 40,
    r07_knife    = 41,
    r07_labMaterial    = 42,
};

//declare and define room objects array
static tObject r07_object[R07_ROOM_NUM_OBJS] =
{
    {R07_OBJ_0},
    {R07_OBJ_1},
    {R07_OBJ_2},
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
