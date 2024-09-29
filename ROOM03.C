/*
=========================================================
 Room Number:   03
 Room Name:     bathRoom

=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room03.h"

#include "IDATA.h"

//Funtion to return the name of hotspot by color code
void r03_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r03_Closet:
            strcpy(s, "Armario");
            break;
        case r03_door:
            strcpy(s, "Puerta");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r03_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r03_Closet:
            return OPEN;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r03_get_object_info(uint8_t numObject)
{
    if (numObject < R03_ROOM_NUM_OBJS)
        return NULL; //&r03_object[numObject];
    else
        return NULL;
}

//function to init room
void r03_room_init()
{
    //update room objects state
    /*
    r03_object[r03_CASSETTE_OBJ_ID].active  = !is_game_flag(GOT_CASSETTE);
    r03_object[r03_GUITAR_OBJ_ID].active    = !is_game_flag(GOT_GUITAR);
    r03_object[r03_STEREO_OBJ_ID].active    = is_game_flag(STEREO_ON);
    */
    game_fade_in();
}

//global funcion to update room
void r03_room_update()
{
    //update room objects
    r03_update_room_objects();
    
    //update room script
    r03_update_room_script();
}

//update room objects
void r03_update_room_objects()
{
    //update objects

    //Stereo
    //object_play_animation(&r03_object[r03_STEREO_OBJ_ID], r03d_objStereo01, r03_animations, r03_ANIM_PLAY_STEREO);
}

//updates room script
void r03_update_room_script()
{
    //if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r03_Closet:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("El armario del ba"CHAR_NY"o");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
            break;
            case r03_door:
                switch(roomScript.verb)
                {
                    case GO:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player_to_target();
                                break;
                            case 1:
                                change_room_pos(1, 154, 46);
                                end_script();
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
            break;
        }
    }
}