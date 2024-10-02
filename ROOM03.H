/*
=========================================================
 Room Number:   03
 Room Name:     bathRoom

=========================================================
*/
#ifndef H_ROOM03
#define H_ROOM03

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R03DATA.H"

//define room properties
#define R03_START_POS_X         190
#define R03_START_POS_Y         106
#define R03_ROOM_NUM_OBJS       0
#define R03_MUSIC_ID            0
#define R03_FADE                true

//define room data (compose room properties and function pointers)
#define R03_DATA R03_START_POS_X, R03_START_POS_Y, R03_ROOM_NUM_OBJS, R03_MUSIC_ID, R03_FADE, &r03_room_init, &r03_room_update, &r03_get_hotspot_name, &r03_get_default_hotspot_verb, &r03_get_object_info

//define object array alias
/*#define R03_CASSETTE_OBJ_ID 0
#define R03_GUITAR_OBJ_ID   1
#define R03_STEREO_OBJ_ID   2
#define R03_TABLE_OBJ_ID    3

//define object data
#define R03_OBJ_0           r03d_objCassette,   279, 89,  0, true, 0
#define R03_OBJ_1           r03d_objGuitar,     100, 50,  0, true, 0
#define R03_OBJ_2           r03d_objStereo01,   282, 56,  1, true, 0
#define R03_OBJ_3           r03d_objTable,      54,  144, 0, true, 1

//define room animations
#define R03_NUM_ANIMATIONS  1
#define R03_ANIM_PLAY_STEREO    r03d_objStereo01, r03d_objStereo04, 2, ANIM_LOOP
*/

//hotspot code room enumeration
enum r03_hotspotCode{
    r03_Closet = 150,
    r03_door   = 138
};

/*
//declare and define room objects array
static tObject r03_object[R03_ROOM_NUM_OBJS] =
{
    {R03_OBJ_0},
    {R03_OBJ_1},
    {R03_OBJ_2},
    {R03_OBJ_3},
};

//declare room objects animations array
static tAnimation R03_animations[R03_NUM_ANIMATIONS];

//declare room dialog actor
static tActorTalk R03_dialogActor = {0, 0, 70, false};
*/

//declare room functions called from game
void r03_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r03_get_default_hotspot_verb(uint8_t colorCode);
tObject* r03_get_object_info(uint8_t numObject);
void r03_room_init();
void r03_room_update();

//declare internal functions
void r03_update_room_objects();
void r03_update_room_script();
//void r03_update_dialog_selection();
#endif