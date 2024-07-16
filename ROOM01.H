#ifndef H_ROOM01
#define H_ROOM01

#include <allegro.h>
#include "objects.h"

#define R01_ROOM_NUM_OBJS   2

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
    [0].objId = dObjCassette,
    [0].x = 279,
    [0].y = 89,
    [0].active = true,
    [1].objId = dObjGuitar,
    [1].x = 100,
    [1].y = 50,
    [1].active = true
};

//declare room functions
void r01_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r01_get_default_hotspot_verb(uint8_t colorCode);
tObject* r01_get_object_info(uint8_t numObject);
void r01_room_init();
void r01_room_update();

#endif
