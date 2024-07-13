#ifndef H_ROOM01
#define H_ROOM01

#include <allegro.h>

//room enumerations
enum r01_objectCode{
    Guitarra    = 150,
    Minicadena  = 225,
    Puerta      = 236,
    Casete     = 216
};

//declare room functions
void r01_get_object(uint8_t colorCode, char *s);
enum verbs r01_get_default_object_verb(uint8_t colorCode);
void r01_room_init();
void r01_room_update();

#endif
