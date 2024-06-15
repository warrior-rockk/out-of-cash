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

//global room variable
enum r01_objectCode roomObject = 0;
enum verbs roomVerb = 0;
int step = 0;
int stepTime = 0;
int stepLastTime = 0;

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
                    roomObject = colorCode;
                    roomVerb = verb;
                    break;
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

//funcion to update room
void r01_room_update()
{
    //reset sequence if nothing
    if (roomObject <= 0 || roomVerb <= 0)
    {
        step = 0;
        stepTime = 0;
        stepLastTime = 0;
    }
    else
    {
        //sequence timer
        if (gameTick > 0)
        {
          stepTime++;
        }
        //do sequence step
        switch (step)
        {
            case 0:
                say("Es mi minicadena ultimo modelo");
                if (stepTime >= 2)
                {
                     step++;
                     stepTime = 0;
                }
                break;
            case 1:
                say("Otra cosa");
                if (stepTime >= 2)
                {
                   step++;
                   stepTime = 0;
                }
                break;
            case 2:
                 roomObject = 0;
                 roomVerb = 0;
                 change_room(1);
                 break;
        }
    }
}

