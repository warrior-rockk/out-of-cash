#ifndef H_ROOM01
#define H_ROOM01

#include <allegro.h>
#include "objects.h"
#include "anim.h"

#define R01_ROOM_NUM_OBJS   3

#define R01_CASSETTE_OBJ_ID  0
#define R01_GUITAR_OBJ_ID    1
#define R01_STEREO_OBJ_ID    2

//room enumerations
enum r01_hotspotCode{
    Guitarra    = 150,
    Minicadena  = 225,
    Puerta      = 236,
    Casete      = 216
};

//declare room objects data
static tObject r01_object[R01_ROOM_NUM_OBJS] =
{
    [R01_CASSETTE_OBJ_ID].objId = dObjCassette,
    [R01_CASSETTE_OBJ_ID].x = 279,
    [R01_CASSETTE_OBJ_ID].y = 89,
    [R01_CASSETTE_OBJ_ID].active = true,

    [R01_GUITAR_OBJ_ID].objId = dObjGuitar,
    [R01_GUITAR_OBJ_ID].x = 100,
    [R01_GUITAR_OBJ_ID].y = 50,
    [R01_GUITAR_OBJ_ID].active = true,

    [R01_STEREO_OBJ_ID].objId = dObjStereo01,   //3 to 6: animation
    [R01_STEREO_OBJ_ID].x = 282,
    [R01_STEREO_OBJ_ID].y = 56,
    [R01_STEREO_OBJ_ID].active = false
};

tAnimation r01_stereo_anim;

//declare room functions
void r01_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r01_get_default_hotspot_verb(uint8_t colorCode);
tObject* r01_get_object_info(uint8_t numObject);
void r01_room_init();
void r01_room_update();

#endif
