/*
=========================================================
 Room Number:   01
 Room Name:     bedRoom

=========================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "room01.h"

//Funtion to return the name of object by color code
void get_object(int colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case Guitarra:
            strcpy(s, "Guitarra");
            break;
        case Minicadena:
            strcpy(s, "Minicadena");
            break;
        default:
            strcpy(s, "");
    }
}

//function to perform object action
void do_object_action(tCursorActions action, int colorCode)
{
    //check the object
    switch(colorCode)
    {
        case Guitarra:
            switch (action)
            {
                case IR:
                    exit(2);
                case MIRAR:
                    exit(3);
            }
            break;
        case Minicadena:
            switch (action)
            {
                case IR:
                    exit(4);
                case MIRAR:
                    exit(5);
            }
            break;
    }
}

