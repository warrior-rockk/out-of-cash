#ifndef H_ROOM01
#define H_ROOM01

#include <allegro.h>

//room enumerations
enum r01_objectCode{
    Guitarra    = 150,
    Minicadena  = 225,
    Puerta      = 236
};

//declare room functions
void r01_get_object(uint8_t colorCode, char *s);
void r01_room_init();
void r01_room_update();

#endif
