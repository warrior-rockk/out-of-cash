/*
=========================================================
 Room Number:   10
 Room Name:     10_maintCloset
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room10.h"

//Funtion to return the name of hotspot by color code
void r10_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r10_door:
                strcpy(s, "Puerta");
            break;
        case r10_switch:
                strcpy(s, "Interruptor");
            break;
        case r10_spiderWeb:
                strcpy(s, "Telaraña");
            break;
        case r10_closet:
                strcpy(s, "Armario");
            break;
        case r10_paintBucket:
                strcpy(s, "Cubo de pintura");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r10_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r10_door:
            return GO;
            break;
        case r10_switch:
            return USE;
            break;
        case r10_spiderWeb:
            return LOOK;
            break;
        case r10_closet:
            return OPEN;
            break;
        case r10_paintBucket:
            return LOOK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r10_get_object_info(uint8_t numObject)
{
    if (numObject < R10_ROOM_NUM_OBJS)
        return &r10_object[numObject];
    else
        return NULL;
}

//function to init room
void r10_room_init()
{
    game_fade_in();
}

//global funcion to update room
void r10_room_update()
{
    //update room objects
    r10_update_room_objects();

    //update dialog line selection
    r10_update_dialog_selection();
    
    //update room script
    r10_update_room_script();
}

//update room objects
void r10_update_room_objects()
{

}

//update dialog selection
void r10_update_dialog_selection()
{

}

//update room script
void r10_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r10_door:
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
            case r10_switch:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Interruptor");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r10_spiderWeb:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Telaraña");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r10_closet:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Armario");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r10_paintBucket:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Cubo de pintura");
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