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
void r01_get_object(int colorCode, char *s)
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
        case Puerta:
            strcpy(s, "Puerta");
            break;
        default:
            strcpy(s, "");
    }
}

//function to perform object action
void r01_do_object_action(enum verbs verb, int colorCode)
{
    //check the object
    switch(colorCode)
    {
        case Guitarra:
            switch (verb)
            {
                case GO:
                    exit(2);
                case LOOK:
                    exit(3);
             }
            break;
        case Minicadena:
            switch (verb)
            {
                case GO:
                    exit(4);
                case LOOK:
                    say("Es mi minicadena ultimo modelo");
            }
            break;
       case Puerta:
            switch (verb)
            {
                case GO:
                    change_room(1);
                    break;
                case LOOK:
                    exit(6);
            }
            break;
    }
}

