#ifndef H_ROOM02
#define H_ROOM02

#include <allegro.h>

#define R02_ROOM_NUM_OBJS   0

#define R02_DATA             179, 117, R02_ROOM_NUM_OBJS, &r02_room_init, &r02_room_update, &r02_get_hotspot_name, &r02_get_default_hotspot_verb, &r02_get_object_info

//room enumerations
enum r02_hotspotCode{
    espejo      = 139,
    cuadro      = 155,
    habitacion  = 236
};

//declare room objects data
static tObject r02_object[R02_ROOM_NUM_OBJS];

//declare room functions
void r02_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r02_get_default_hotspot_verb(uint8_t colorCode);
tObject* r02_get_object_info(uint8_t numObject);
void r02_room_init();
void r02_room_update();


#endif
