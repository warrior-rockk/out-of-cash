/*
=========================================================
 Room Number:   01
 Room Name:     01_bedRoom
=========================================================
*/

#ifndef H_ROOM01
#define H_ROOM01

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R01DATA.H"

//define room properties
#define R01_START_POS_X         170
#define R01_START_POS_Y         100
#define R01_ROOM_NUM_OBJS       4
#define R01_MUSIC_ID            0
#define R01_FADE                false
#define R01_LIGHTS_OFF                false

//define room data (compose room properties and function pointers)
#define R01_DATA R01_START_POS_X, R01_START_POS_Y, R01_ROOM_NUM_OBJS, R01_MUSIC_ID, R01_FADE , R01_LIGHTS_OFF , &r01_room_init, &r01_room_update, &r01_get_hotspot_name, &r01_get_default_hotspot_verb, &r01_get_object_info

//define object array alias
#define R01_CASSETTE_OBJ_ID 0
#define R01_GUITAR_OBJ_ID 1
#define R01_STEREO01_OBJ_ID 2
#define R01_TABLE_OBJ_ID    3

//define object data (objId, x, y, animId, active, layer)
#define R01_OBJ_0           r01d_objCassette,   280, 88,  0, true, 0
#define R01_OBJ_1           r01d_objGuitar,   103, 45,  0, true, 0
#define R01_OBJ_2           r01d_objStereo01,   282, 56,  1, false, 0
#define R01_OBJ_3           r01d_objTable,   54, 144,  1, true, 1

//define room animations
#define R01_NUM_ANIMATIONS  1
#define R01_ANIM_PLAY_STEREO    r01d_objStereo01, r01d_objStereo04, 2, ANIM_LOOP

//hotspot code room enumeration
enum r01_hotspotCode{
    r01_guitar    = 150,
    r01_stereo    = 225,
    r01_door    = 236,
    r01_cassette    = 216,
    r01_spider    = 234,
    r01_drums    = 182,
    r01_thing    = 200,
    r01_glasses    = 239,
    r01_cd    = 147,
    r01_poster    = 128,
    r01_draws    = 71,
    r01_sofa    = 201,
    r01_computer    = 179,
    r01_toys    = 52,
    r01_printer    = 113,
    r01_book1    = 104,
    r01_book2    = 105,
    r01_book3    = 106,
    r01_book4    = 107,
};

//declare and define room objects array
static tObject r01_object[R01_ROOM_NUM_OBJS] =
{
    {R01_OBJ_0},
    {R01_OBJ_1},
    {R01_OBJ_2},
    {R01_OBJ_3},
};

//declare room objects animations array
static tAnimation r01_animations[R01_NUM_ANIMATIONS];

//declare room dialog actor
static tActorTalk r01_dialogActor = {0, 0, 70, false};

//declare room functions called from game
void r01_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r01_get_default_hotspot_verb(uint8_t colorCode);
tObject* r01_get_object_info(uint8_t numObject);
void r01_room_init();
void r01_room_update();

//declare internal functions
void r01_update_room_objects();
void r01_update_room_script();
void r01_update_dialog_selection();
#endif
