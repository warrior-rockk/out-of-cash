/*
=========================================================
 Room Number:   13
 Room Name:     13_ending
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room13.h"

//Funtion to return the name of hotspot by color code
void r13_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r13_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r13_get_object_info(uint8_t numObject)
{
    if (numObject < R13_ROOM_NUM_OBJS)
        return &r13_object[numObject];
    else
        return NULL;
}

//function to init room
void r13_room_init()
{
    game_fade_in();
}

//global funcion to update room
void r13_room_update()
{
    //update room objects
    r13_update_room_objects();

    //update dialog line selection
    r13_update_dialog_selection();
    
    //update room script
    r13_update_room_script();
}

//update room objects
void r13_update_room_objects()
{

}

//update dialog selection
void r13_update_dialog_selection()
{

}

//update room script
void r13_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {

        }
    }
}
