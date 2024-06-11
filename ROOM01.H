#ifndef H_ROOM01
#define H_ROOM01

//room enumerations
enum r01_objectCode{
    Guitarra    = 150,
    Minicadena  = 225,
    Puerta      = 236
};

//declare room functions
void r01_get_object(int colorCode, char *s);
void r01_do_object_action(int action, int colorCode);

#endif
