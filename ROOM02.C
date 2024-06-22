/*
=========================================================
 Room Number:   02
 Room Name:     corridor

=========================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"
#include "room02.h"

//Funtion to return the name of object by color code
void r02_get_object(int colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case espejo:
            strcpy(s, "Espejo");
            break;
        case cuadro:
            strcpy(s, "Cuadro");
            break;
        case habitacion:
            strcpy(s, "Habitacion");
            break;
        default:
            strcpy(s, "");
    }
}

//funcion to update room
void r02_room_update()
{
    ;
}