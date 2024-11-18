/*
=========================================================
 Room Number:   09
 Room Name:     09_locker
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room09.h"

//Funtion to return the name of hotspot by color code
void r09_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r09_door:
                strcpy(s, "Puerta");
            break;
        case r09_bench:
                strcpy(s, "Banco");
            break;
        case r09_locker1:
                strcpy(s, "Taquilla");
            break;
        case r09_locker2:
                strcpy(s, "Taquilla");
            break;
        case r09_locker3:
                strcpy(s, "Taquilla");
            break;
        case r09_locker4:
                strcpy(s, "Taquilla");
            break;
        case r09_jeans:
                strcpy(s, "Pantalones");
            break;
        case r09_shirt:
                strcpy(s, "Camiseta");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r09_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r09_door:
            return GO;
            break;
        case r09_bench:
            return LOOK;
            break;
        case r09_locker1:
            return OPEN;
            break;
        case r09_locker2:
            return OPEN;
            break;
        case r09_locker3:
            return OPEN;
            break;
        case r09_locker4:
            return OPEN;
            break;
        case r09_jeans:
            return LOOK;
            break;
        case r09_shirt:
            return LOOK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r09_get_object_info(uint8_t numObject)
{
    if (numObject < R09_ROOM_NUM_OBJS)
        return &r09_object[numObject];
    else
        return NULL;
}

//function to init room
void r09_room_init()
{
    game_fade_in();
}

//global funcion to update room
void r09_room_update()
{
    //update room objects
    r09_update_room_objects();

    //update dialog line selection
    r09_update_dialog_selection();
    
    //update room script
    r09_update_room_script();
}

//update room objects
void r09_update_room_objects()
{

}

//update dialog selection
void r09_update_dialog_selection()
{

}

//update room script
void r09_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r09_door:
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
            case r09_bench:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Banco");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r09_locker1:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Taquilla");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r09_locker2:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Taquilla");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r09_locker3:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Taquilla");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r09_locker4:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Taquilla");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r09_jeans:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Pantalones");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r09_shirt:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Camiseta");
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