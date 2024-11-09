/*
=========================================================
 Room Number:   06
 Room Name:     06_school01
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room06.h"

//Funtion to return the name of hotspot by color code
void r06_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r06_door:
                strcpy(s, "Puerta");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r06_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r06_door:
            return GO;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r06_get_object_info(uint8_t numObject)
{
    if (numObject < R06_ROOM_NUM_OBJS)
        return &r06_object[numObject];
    else
        return NULL;
}

//function to init room
void r06_room_init()
{
    game_fade_in();
}

//global funcion to update room
void r06_room_update()
{
    //update room objects
    r06_update_room_objects();

    //update dialog line selection
    r06_update_dialog_selection();
    
    //update room script
    r06_update_room_script();
}

//update room objects
void r06_update_room_objects()
{

}

//update dialog selection
void r06_update_dialog_selection()
{

}

//update room script
void r06_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r06_door:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Puerta");
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
                                script_move_player_to_target();
                                break;
                            case 1:
                                change_room(SCHOOL_2_ROOM_NUM);
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