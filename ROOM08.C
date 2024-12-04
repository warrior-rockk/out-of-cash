/*
=========================================================
 Room Number:   08
 Room Name:     08_computerRoom
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
        case r08_window:
                strcpy(s, "Ventana");
            break;
        case r08_computer3:
                strcpy(s, "Ordenador");
            break;
        case r08_manual:
                strcpy(s, "Manual");
            break;
        case r08_computer1:
                strcpy(s, "Ordenador");
            break;
        case r08_nerd:
                strcpy(s, "Friki");
            break;
        case r08_computer2:
                strcpy(s, "Ordenador");
            break;
        case r08_chair:
                strcpy(s, "Silla");
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
        case r08_window:
            return LOOK;
            break;
        case r08_computer3:
            return LOOK;
            break;
        case r08_manual:
            return LOOK;
            break;
        case r08_computer1:
            return LOOK;
            break;
        case r08_nerd:
            return TALK;
            break;
        case r08_computer2:
            return LOOK;
            break;
        case r08_chair:
            return LOOK;
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
                                script_say("Es la puerta que da al pasillo");
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
                                change_room_pos(SCHOOL_ROOM_NUM, 272, 84);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r08_window:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Esta ventana al exterior impide que la gente haga uso fraudulentos con los ordenadores");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r08_computer3:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Ordenador");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r08_manual:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Un manual de Q-Basic para MS-DOS");
                                break;
                            case 1:
                                script_say("Aprenda a programar desde el juego Gorillas al Snake");
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r08_computer1:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Ordenador");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r08_nerd:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Friki");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r08_computer2:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Ordenador");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r08_chair:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("àjala en el futuro hagan sillas de ordenador m s c¢modas y que sirvan para largas sesiones de juego");
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