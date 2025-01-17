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
#define R01_ROOM_NUM_OBJS       7
#define R01_MUSIC_ID            0
#define R01_FADE                false
#define R01_LIGHTS_OFF          false

//define room data (compose room properties and function pointers)
#define R01_DATA R01_START_POS_X, R01_START_POS_Y, R01_ROOM_NUM_OBJS, R01_MUSIC_ID, R01_FADE , R01_LIGHTS_OFF , &r01_room_init, &r01_room_update, &r01_get_hotspot_name, &r01_get_default_hotspot_verb, &r01_get_object_info

//define object array alias
#define R01_CASSETTE_OBJ_ID 0
#define R01_GUITAR_OBJ_ID   1
#define R01_STEREO01_OBJ_ID 2
#define R01_TABLE_OBJ_ID    3
#define R01_COIN_OBJ_ID     4
#define R01_BOOK_OBJ_ID     5
#define R01_COMPUTER_OBJ_ID 6

//define object data (objId, x, y, animId, active, layer)
#define R01_OBJ_0           r01d_objCassette,   251, 87,  0, true, 0
#define R01_OBJ_1           r01d_objGuitar,     103, 45,  0, false, 0
#define R01_OBJ_2           r01d_objStereo01,   251, 57,  1, false, 0
#define R01_OBJ_3           r01d_objTable,      86, 143,  0, true, 1
#define R01_OBJ_4           r01d_objCoin,       94, 96,  0, true, 0
#define R01_OBJ_5           r01d_objBook,       54, 9,  0, true, 0
#define R01_OBJ_6           r01d_objCompBoot1,  261, 121,  2, false, 0

//define room animations
#define R01_NUM_ANIMATIONS  2
#define R01_ANIM_PLAY_STEREO    r01d_objStereo01, r01d_objStereo03, 2, ANIM_LOOP

#define R01_ANIM_ON_COMPUTER    r01d_objCompBoot5, r01d_objCompBoot5, 35, ANIM_ONCE
#define R01_ANIM_BIOS_COMPUTER  r01d_objCompBoot1, r01d_objCompBoot4, 7, ANIM_ONCE
#define R01_ANIM_W95_COMPUTER   r01d_objCompBoot6, r01d_objCompBoot6, 1, ANIM_LOOP
#define R01_ANIM_ERROR_COMPUTER r01d_objCompBoot7, r01d_objCompBoot7, 1, ANIM_LOOP

//define custom script > 256
#define R01_GAME_START_SCRIPT    257

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
    r01_book2    = 107,
    r01_book3    = 106,
    r01_book4    = 105,
    r01_window   = 47,
};

//declare and define room objects array
static tObject r01_object[R01_ROOM_NUM_OBJS] =
{
    {R01_OBJ_0},
    {R01_OBJ_1},
    {R01_OBJ_2},
    {R01_OBJ_3},
    {R01_OBJ_4},
    {R01_OBJ_5},
    {R01_OBJ_6},
};

//declare room objects animations array
static tAnimation r01_animations[R01_NUM_ANIMATIONS];

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
