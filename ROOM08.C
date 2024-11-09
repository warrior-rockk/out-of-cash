/*
=========================================================
 Room Number:   08
 Room Name:     08_school03
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room08.h"

//Funtion to return the name of hotspot by color code
void r08_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r08_door:
                strcpy(s, "Puerta");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r08_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r08_door:
            return GO;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r08_get_object_info(uint8_t numObject)
{
    if (numObject < R08_ROOM_NUM_OBJS)
        return &r08_object[numObject];
    else
        return NULL;
}

//function to init room
void r08_room_init()
{
    game_fade_in();
}

//global funcion to update room
void r08_room_update()
{
    //update room objects
    r08_update_room_objects();

    //update dialog line selection
    r08_update_dialog_selection();
    
    //update room script
    r08_update_room_script();
}

//update room objects
void r08_update_room_objects()
{

}

//update dialog selection
void r08_update_dialog_selection()
{

}

//update room script
void r08_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r08_door:
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
                }
                break;            

        }
    }
}