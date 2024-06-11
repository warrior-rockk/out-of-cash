#ifndef H_ROOM01
#define H_ROOM01

//room enumerations
enum objectCode{
    Guitarra    = 150,
    Minicadena  = 225,
};

//declare functions
void get_object(int colorCode, char *s);
void do_object_action(tCursorActions action, int colorCode);

#endif
