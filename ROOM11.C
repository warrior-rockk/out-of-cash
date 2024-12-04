/*
=========================================================
 Room Number:   11
 Room Name:     11_PEOffice
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room11.h"

//Funtion to return the name of hotspot by color code
void r11_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r11_door:
                strcpy(s, "Puerta");
            break;
        case r11_earthGlobe:
                strcpy(s, "Bola del mundo");
            break;
        case r11_things:
                strcpy(s, "Cosas");
            break;
        case r11_cup:
                strcpy(s, "Taza");
            break;
        case r11_teacher:
                strcpy(s, "Profesor");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r11_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r11_door:
            return GO;
            break;
        case r11_earthGlobe:
            return LOOK;
            break;
        case r11_things:
            return LOOK;
            break;
        case r11_cup:
            return LOOK;
            break;
        case r11_teacher:
            return TALK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r11_get_object_info(uint8_t numObject)
{
    if (numObject < R11_ROOM_NUM_OBJS)
        return &r11_object[numObject];
    else
        return NULL;
}

//function to init room
void r11_room_init()
{
    game_fade_in();
}

//global funcion to update room
void r11_room_update()
{
    //update room objects
    r11_update_room_objects();

    //update dialog line selection
    r11_update_dialog_selection();
    
    //update room script
    r11_update_room_script();
}

//update room objects
void r11_update_room_objects()
{

}

//update dialog selection
void r11_update_dialog_selection()
{

}

//update room script
void r11_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r11_door:
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
            case r11_earthGlobe:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Bola del mundo");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r11_things:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Cosas");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r11_cup:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Taza");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r11_teacher:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Profesor");
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