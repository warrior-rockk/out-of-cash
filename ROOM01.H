#ifndef H_ROOM01
#define H_ROOM01

#include <allegro.h>
#include "R01DATA.H"
#include "anim.h"

//define num room objects
#define R01_ROOM_NUM_OBJS   4

//define room data (start positions and room function pointers)
#define R01_DATA            170, 100, R01_ROOM_NUM_OBJS, &r01_room_init, &r01_room_update, &r01_get_hotspot_name, &r01_get_default_hotspot_verb, &r01_get_object_info

//define object array alias
#define R01_CASSETTE_OBJ_ID 0
#define R01_GUITAR_OBJ_ID   1
#define R01_STEREO_OBJ_ID   2
#define R01_TABLE_OBJ_ID    3

//define object data
#define R01_OBJ_0           r01d_objCassette,   279, 89,  true, 0
#define R01_OBJ_1           r01d_objGuitar,     100, 50,  true, 0
#define R01_OBJ_2           r01d_objStereo01,   282, 56,  true, 0
#define R01_OBJ_3           r01d_objTable,      54,  144, true, 1

//define room animations
#define R01_ANIM_PLAY_STEREO    r01d_objStereo01, r01d_objStereo04, 2, ANIM_LOOP

//hotspot code room enumeration
enum r01_hotspotCode{
    Guitarra    = 150,
    Minicadena  = 225,
    Puerta      = 236,
    Casete      = 216
};

//declare and define room objects array
static tObject r01_object[R01_ROOM_NUM_OBJS] =
{
    {R01_OBJ_0},
    {R01_OBJ_1},
    {R01_OBJ_2},
    {R01_OBJ_3},
};

//declare room animations objects
static tAnimation r01_stereoAnim;

//declare room functions
void r01_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r01_get_default_hotspot_verb(uint8_t colorCode);
tObject* r01_get_object_info(uint8_t numObject);
void r01_room_init();
void r01_room_update();
void r01_update_room_objects();
void r01_update_room_script();

#endif
