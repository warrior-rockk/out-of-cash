/*
=========================================================
 Room Number:   07
 Room Name:     07_scienceRoom
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room07.h"

//Funtion to return the name of hotspot by color code
void r07_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r07_door:
                strcpy(s, "Puerta");
            break;
        case r07_blackBoard:
                strcpy(s, "Pizarra");
            break;
        case r07_notes:
                strcpy(s, "Apuntes");
            break;
        case r07_brain:
                strcpy(s, "Cerebro");
            break;
        case r07_washer1:
                strcpy(s, "Pica");
            break;
        case r07_testTube:
                strcpy(s, "Probetas");
            break;
        case r07_sheets:
                strcpy(s, "Hojas");
            break;
        case r07_washer2:
                strcpy(s, "Pica");
            break;
        case r07_glass:
                strcpy(s, "Vaso");
            break;
        case r07_knife:
                strcpy(s, "Bisturí");
            break;
        case r07_labMaterial:
                strcpy(s, "Material laboratorio");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r07_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r07_door:
            return GO;
            break;
        case r07_blackBoard:
            return LOOK;
            break;
        case r07_notes:
            return LOOK;
            break;
        case r07_brain:
            return LOOK;
            break;
        case r07_washer1:
            return LOOK;
            break;
        case r07_testTube:
            return LOOK;
            break;
        case r07_sheets:
            return LOOK;
            break;
        case r07_washer2:
            return LOOK;
            break;
        case r07_glass:
            return LOOK;
            break;
        case r07_knife:
            return LOOK;
            break;
        case r07_labMaterial:
            return LOOK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r07_get_object_info(uint8_t numObject)
{
    if (numObject < R07_ROOM_NUM_OBJS)
        return &r07_object[numObject];
    else
        return NULL;
}

//function to init room
void r07_room_init()
{
    change_player_dir(DIR_RIGHT);

    game_fade_in();
}

//global funcion to update room
void r07_room_update()
{
    //update room objects
    r07_update_room_objects();

    //update dialog line selection
    r07_update_dialog_selection();
    
    //update room script
    r07_update_room_script();
}

//update room objects
void r07_update_room_objects()
{

}

//update dialog selection
void r07_update_dialog_selection()
{

}

//update room script
void r07_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r07_door:
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
                            default:
                                change_room_pos(SCHOOL_ROOM_NUM, 428, 87);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r07_blackBoard:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Pizarra");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_notes:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Apuntes");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_brain:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Cerebro");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_washer1:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Pica");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_testTube:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Probetas");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_sheets:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Hojas");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_washer2:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Pica");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_glass:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Vaso");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_knife:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Bisturí");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_labMaterial:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Material laboratorio");
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
