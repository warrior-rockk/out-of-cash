/*
=========================================================
 Room Number:   00
 Room Name:     00_street
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room00.h"

//Funtion to return the name of hotspot by color code
void r00_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r00_door:
                strcpy(s, "Puerta");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r00_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r00_door:
            return GO;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r00_get_object_info(uint8_t numObject)
{
    if (numObject < R00_ROOM_NUM_OBJS)
        return &r00_object[numObject];
    else
        return NULL;
}

//function to init room
void r00_room_init()
{
    game_fade_in();
}

//global funcion to update room
void r00_room_update()
{
    //update room objects
    r00_update_room_objects();

    //update dialog line selection
    r00_update_dialog_selection();
    
    //update room script
    r00_update_room_script();
}

//update room objects
void r00_update_room_objects()
{

}

//update dialog selection
void r00_update_dialog_selection()
{

}

//update room script
void r00_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r00_door:
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
                                change_room(CORRIDOR_ROOM_NUM);
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
