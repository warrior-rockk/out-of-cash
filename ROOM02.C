/*
=========================================================
 Room Number:   02
 Room Name:     02_corridor
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room02.h"

//Funtion to return the name of hotspot by color code
void r02_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r02_mirror:
                strcpy(s, "Espejo");
            break;
        case r02_bathDoor:
                strcpy(s, "Puerta");
            break;
        case r02_flowers:
                strcpy(s, "Flores");
            break;
        case r02_elephant:
                strcpy(s, "Figura");
            break;
        case r02_kitchen:
                strcpy(s, "Cocina");
            break;
        case r02_door:
                strcpy(s, "Puerta");
            break;
        case r02_picture:
                strcpy(s, "Cuadro");
            break;
        case r02_bedRoomDoor:
                strcpy(s, "Habitaci¢n");
            break;
        case r02_street:
                strcpy(s, "Calle");
            break;
        case r02_lamp:
                strcpy(s, "L mpara");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r02_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r02_mirror:
            return LOOK;
            break;
        case r02_bathDoor:
            return OPEN;
            break;
        case r02_flowers:
            return LOOK;
            break;
        case r02_elephant:
            return LOOK;
            break;
        case r02_kitchen:
            return LOOK;
            break;
        case r02_door:
            return LOOK;
            break;
        case r02_picture:
            return LOOK;
            break;
        case r02_bedRoomDoor:
            return LOOK;
            break;
        case r02_street:
            return LOOK;
            break;
        case r02_lamp:
            return LOOK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r02_get_object_info(uint8_t numObject)
{
    if (numObject < R02_ROOM_NUM_OBJS)
        return &r02_object[numObject];
    else
        return NULL;
}

//function to init room
void r02_room_init()
{
    game_fade_in();
}

//global funcion to update room
void r02_room_update()
{
    //update room objects
    r02_update_room_objects();

    //update dialog line selection
    r02_update_dialog_selection();
    
    //update room script
    r02_update_room_script();
}

//update room objects
void r02_update_room_objects()
{
    r02_object[R02_BATHDOOR_OBJ_ID].active = is_game_flag(BATH_DOOR_OPEN);
}

//update dialog selection
void r02_update_dialog_selection()
{

}

//update room script
void r02_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r02_mirror:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Espejo");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r02_bathDoor:
                switch(roomScript.verb)
                {
                    case GO:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (!is_game_flag(BATH_DOOR_OPEN))
                                {
                                    script_say("La puerta est  cerrada");
                                    end_script();
                                }
                                else
                                    script_move_player_to_target();
                                break;
                            case 1:
                                change_room(2);
                                end_script();
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("La puerta del ba¤o");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case OPEN:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (is_game_flag(BATH_DOOR_OPEN))
                                {
                                    script_say("Ya est  abierta");
                                    end_script();
                                }
                                else                                
                                    script_move_player_to_target();
                                break;
                            case 1:
                                set_game_flag(BATH_DOOR_OPEN);
                                end_script();
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case CLOSE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (!is_game_flag(BATH_DOOR_OPEN))
                                {
                                    script_say("Ya est  cerrada");
                                    end_script();
                                }
                                else                                
                                    script_move_player_to_target();

                                break;
                            case 1:
                                clear_game_flag(BATH_DOOR_OPEN);
                                end_script();
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r02_flowers:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Flores");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r02_elephant:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Figura");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r02_kitchen:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Cocina");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r02_door:
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
            case r02_picture:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Cuadro");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r02_bedRoomDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("HabitaciÃ³n");
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
                                change_room_pos(0, 201, 145);
                                end_script();
                                break;
                        }
                        break;                    
                }
                break;            
            case r02_street:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Calle");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r02_lamp:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("LÃ¡mpara");
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