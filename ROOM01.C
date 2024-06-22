/*
=========================================================
 Room Number:   01
 Room Name:     bedRoom

=========================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"
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

//funcion to update room
void r01_room_update()
{
    //if nothing selected
    if (!roomAction.active)
    {
        //reset sequence vars
        roomAction.step = 0;
        roomAction.lastStep = 0;
        roomAction.stepTime = 0;
    }
    else
    {
        //sequence timer
        if (gameTick)
        {
          roomAction.stepTime++;
        }
        //reset step timer on step change
        if (roomAction.step != roomAction.lastStep)
        {
            roomAction.stepTime = 0;
            roomAction.lastStep = roomAction.step;
        }

        //sequence actions
        switch (roomAction.object)
        {
            case Minicadena:
                switch(roomAction.verb)
                {
                    case LOOK:
                        switch (roomAction.step)
                        {
                            case 0:
                                roomAction.step+= say("Es mi minicadena ultimo modelo");
                                break;
                            case 1:
                                roomAction.step+= say("Otra cosa");
                                break;
                            default:
                                end_script();
                                break;
                        }
                        break;
                    case TAKE:
                        switch (roomAction.step)
                        {
                            case 0:
                                roomAction.step+= say("No puedo llevarmelo. Pesa mucho");
                                break;
                            default:
                                end_script();
                                break;
                        }
                        break;
                    default:
                        default_verb_action(roomAction.verb);
                        end_script();
                        break;
                }
                break;
            case Puerta:
                switch(roomAction.verb)
                {
                    case GO:
                        change_room(1);
                        end_script();
                        break;
                    default:
                        default_verb_action(roomAction.verb);
                        end_script();
                        break;    
                }
                break;
            default:
                default_verb_action(roomAction.verb);
                end_script();
                break;
        }
    }
}

