#ifndef H_ROOM02
#define H_ROOM02

#include <allegro.h>

//define room properties
#define R02_START_POS_X         179
#define R02_START_POS_Y         117
#define R02_ROOM_NUM_OBJS       0
#define R02_MUSIC_ID            0
#define R02_FADE                false
#define R02_LIGHTS_OFF          false

//define room data (compose room properties and function pointers)
#define R02_DATA R02_START_POS_X, R02_START_POS_Y, R02_ROOM_NUM_OBJS, R02_MUSIC_ID, R02_FADE, R02_LIGHTS_OFF, r02_room_init, &r02_room_update, &r02_get_hotspot_name, &r02_get_default_hotspot_verb, &r02_get_object_info

//room enumerations
enum r02_hotspotCode{
    espejo      = 139,
    cuadro      = 155,
    habitacion  = 236,
    r02_bathDoor    =   127
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
