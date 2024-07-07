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
void r01_get_object(uint8_t colorCode, char *s)
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

//function to init room
void r01_room_init()
{
    game_fade_in();
    say("Acabo de entrar aqui y aqui");
}

//funcion to update room
void r01_room_update()
{
    //if nothing selected
    if (roomScript.active)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case Minicadena:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                roomScript.step+= say("Es mi minicadena ultimo modelo");
                                break;
                            case 1:
                                roomScript.step+= say("Otra cosa");
                                break;
                            default:
                                end_script();
                                break;
                        }
                        break;
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                roomScript.step+= say("No puedo llevarmelo. Pesa mucho");
                                break;
                            default:
                                end_script();
                                break;
                        }
                        break;
                }
                break;
            case Puerta:
                switch(roomScript.verb)
                {
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
                                change_room_pos(1,174,38);
                                end_script();
                                break;
                        }
                        break;
                }
                break;
        }
    }
}

