#ifndef H_ROOM01
#define H_ROOM01

#include <allegro.h>
#include "objects.h"

#define R01_ROOM_NUM_OBJS   2

//room enumerations
enum r01_objectCode{
    Guitarra    = 150,
    Minicadena  = 225,
    Puerta      = 236,
    Casete      = 216
};

//declare room object data
static const uint8_t r01_num_objects = R01_ROOM_NUM_OBJS;
static tObject r01_object[R01_ROOM_NUM_OBJS] =
{
    [0].objId = dObjCassette,
    [0].x = 279,
    [0].y = 89,
    [1].objId = dObjGuitar,
    [1].x = 100,
    [1].y = 50
};

//declare room functions
void r01_get_object(uint8_t colorCode, char *s);
enum verbs r01_get_default_object_verb(uint8_t colorCode);
uint8_t r01_get_num_room_objects();
tObject* r01_get_object_info(uint8_t numObject);
void r01_room_init();
void r01_room_update();

#endif
