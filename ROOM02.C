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

//function to init room
void r02_room_init()
{
    game_fade_in();
    say("Ya estoy aqui");
}

//funcion to update room
void r02_room_update()
{
    //if nothing selected
    if (roomAction.active)
    {
        //sequence actions
        switch (roomAction.object)
        {
            case habitacion:
                switch(roomAction.verb)
                {
                    case LOOK:
                        switch (roomAction.step)
                        {
                            case 0:
                                begin_script();
                                roomAction.step+= say("Es la entrada a mi habitacion");
                                break;
                            default:
                                end_script();
                                break;
                        }
                        break;
                    case GO:
                        begin_script();
                        change_room(0);
                        end_script();
                        break;
                }
                break;
        }
    }
}
