/*
=========================================================
 Room Number:   02
 Room Name:     corridor

=========================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
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

//function to perform object action
void r02_do_object_action(int action, int colorCode)
{
    //check the object
    switch(colorCode)
    {
        case espejo:
            switch (action)
            {
                case GO:
                    exit(2);
                case LOOK:
                    exit(3);
            }
            break;
        case cuadro:
            switch (action)
            {
                case GO:
                    exit(4);
                case LOOK:
                    exit(5);
            }
            break;
        case habitacion:
            switch (action)
            {
                case GO:
                    change_room(0);
                    break;
                case LOOK:
                    exit(7);
            }
            break;
    }
}