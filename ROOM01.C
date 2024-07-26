/*
=========================================================
 Room Number:   01
 Room Name:     bedRoom

=========================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room01.h"

#include "inv.h"

//Funtion to return the name of hotspot by color code
void r01_get_hotspot_name(uint8_t colorCode, char *s)
{
        
    //check the object
    switch(colorCode)
    {
        case Guitarra:
            if (r01_object[R01_GUITAR_OBJ_ID].active)
                strcpy(s, "Guitarra");
            break;
        case Minicadena:
            strcpy(s, "Minicadena");
            break;
        case Puerta:
            strcpy(s, "Puerta");
            break;
        case Casete:
            if (r01_object[R01_CASSETTE_OBJ_ID].active)
                strcpy(s, "Casete");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r01_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case Puerta:
            return OPEN;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r01_get_object_info(uint8_t numObject)
{
    if (numObject < R01_ROOM_NUM_OBJS)
        return &r01_object[numObject];
    else
        return NULL;
}

//function to init room
void r01_room_init()
{
    game_fade_in();
    if (is_game_flag(GOT_CASSETTE))
    {
        r01_object[R01_CASSETTE_OBJ_ID].active = false;
        say("Habia cogido el casete");
    }
}

//funcion to update room
void r01_room_update()
{
    //if nothing selected
    if (roomScript.active && !roomScript.invScript)
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
                                script_say("Es mi minicadena ultimo modelo");
                                break;
                            case 1:
                                script_wait(4);
                                break;
                            case 2:
                                script_say("Otra cosa");
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
                                script_say("No puedo llevarmelo. Pesa mucho");
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
                                script_move_player(roomScript.hsX,200);
                                break;
                            case 1:
                                change_room_pos(1,174,38);
                                end_script();
                                break;
                        }
                        break;
                }
                break;
            case Casete:
                switch(roomScript.verb)
                {
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player_to_target();
                                break;
                            case 1:
                                script_take_object(&r01_object[R01_CASSETTE_OBJ_ID].active, GOT_CASSETTE, dInv_Cassette);
                                end_script();
                                break;
                        }
                        break;
                }
                break;
        }
    }
}

