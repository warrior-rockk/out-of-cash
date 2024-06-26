#ifndef H_ROOM02
#define H_ROOM02

//room enumerations
enum r02_objectCode{
    espejo      = 139,
    cuadro      = 155,
    habitacion  = 236
};

//declare room functions
void r02_get_object(int colorCode, char *s);
void r02_room_init();
void r02_room_update();
#endif
