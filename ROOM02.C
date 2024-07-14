/*
=========================================================
 Room Number:   02
 Room Name:     corridor

=========================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room02.h"

//Funtion to return the name of object by color code
void r02_get_object(uint8_t colorCode, char *s)
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

//function to return default object verb
enum verbs r02_get_default_object_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r02_get_object_info(uint8_t numObject)
{
    if (numObject < R02_ROOM_NUM_OBJS)
        return &r02_object[numObject];
    else
        return NULL;
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
    if (roomScript.active)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case habitacion:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                roomScript.step+= say("Es la entrada a mi habitacion");
                                break;
                            default:
                                end_script();
                                break;
                        }
                        break;
                    case GO:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                move_player(mouse_x, mouse_y);
                                roomScript.step++;
                                break;
                            case 1:
                                roomScript.step+=!is_player_moving();
                                break;
                            case 2:
                                //change_room(0);
                                change_room_pos(0, 201, 145);
                                end_script();
                                break;
                        }
                        break;
                }
                break;
        }
    }
}
