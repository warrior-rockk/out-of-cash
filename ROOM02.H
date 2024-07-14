#ifndef H_ROOM02
#define H_ROOM02

#include <allegro.h>

#define R02_ROOM_NUM_OBJS   0

//room enumerations
enum r02_objectCode{
    espejo      = 139,
    cuadro      = 155,
    habitacion  = 236
};

//declare room objects data
static const uint8_t r02_num_objects = R02_ROOM_NUM_OBJS;
static tObject r02_object[R02_ROOM_NUM_OBJS];

//declare room functions
void r02_get_object(uint8_t colorCode, char *s);
enum verbs r02_get_default_object_verb(uint8_t colorCode);
uint8_t r02_get_num_room_objects();
tObject* r02_get_object_info(uint8_t numObject);
void r02_room_init();
void r02_room_update();


#endif
