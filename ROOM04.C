/*
=========================================================
 Room Number:   04
 Room Name:     04_kitchen
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room04.h"

//Funtion to return the name of hotspot by color code
void r04_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r04_fridge:
                strcpy(s, "Nevera");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r04_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r04_fridge:
            return LOOK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r04_get_object_info(uint8_t numObject)
{
    if (numObject < R04_ROOM_NUM_OBJS)
        return &r04_object[numObject];
    else
        return NULL;
}

//function to init room
void r04_room_init()
{
    game_fade_in();
}

//global funcion to update room
void r04_room_update()
{
    //update room objects
    r04_update_room_objects();

    //update dialog line selection
    r04_update_dialog_selection();
    
    //update room script
    r04_update_room_script();
}

//update room objects
void r04_update_room_objects()
{

}

//update dialog selection
void r04_update_dialog_selection()
{

}

//update room script
void r04_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r04_fridge:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Nevera");
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
