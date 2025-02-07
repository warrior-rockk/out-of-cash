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
            if (is_game_flag(BATH_DOOR_OPEN_FLAG))
                return GO;
            else
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
    r02_object[R02_DOORFRAME_OBJ_ID].active = false;
    
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
    r02_object[R02_BATHDOOR_OBJ_ID].active = is_game_flag(BATH_DOOR_OPEN_FLAG);
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
                                if (!is_game_flag(CORRIDOR_MIRROR_MSG_FLAG))
                                {
                                    set_game_flag(CORRIDOR_MIRROR_MSG_FLAG);
                                    inc_game_var(MIRROR_MSG_COUNT_VAR);
                                }
                                switch (get_game_var(MIRROR_MSG_COUNT_VAR))
                                {
                                    case 1:
                                        script_say("El programador del juego ha sido tan vago como para no programar los reflejos...");
                                        break;
                                    case 2:
                                        script_say("Otro espejo con reflejo sin programar...");
                                        break;
                                    case 3:
                                        script_say("Con lo poco que cuesta programar los reflejos...");
                                        break;
                                }
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
                                if (!is_game_flag(BATH_DOOR_OPEN_FLAG))
                                {
                                    script_say("La puerta est  cerrada");
                                    end_script();
                                }
                                else
                                    script_move_player_to_target();
                                break;
                            case 1:
                                change_room(BATH_ROOM_NUM);
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
                                script_say("Es la puerta que da al ba¤o");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case OPEN:
                    case USE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (is_game_flag(BATH_DOOR_OPEN_FLAG))
                                {
                                    script_say("Ya est  abierta");
                                    end_script();
                                }
                                else                                
                                    script_move_player(153, 53);
                                break;
                            case 1:
                                script_player_take_state();
                                play_sound(sd_doorOpen);
                                set_game_flag(BATH_DOOR_OPEN_FLAG);
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
                                if (!is_game_flag(BATH_DOOR_OPEN_FLAG))
                                {
                                    script_say("Ya est  cerrada");
                                    end_script();
                                }
                                else                                
                                    script_move_player(153, 53);
                                break;
                            case 1:
                                script_player_take_state();
                                play_sound(sd_doorClose);
                                clear_game_flag(BATH_DOOR_OPEN_FLAG);
                            break;
                            default:
                                end_script();
                            §break;
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
                                script_say("Un jarr¢n con flores cuya fragancia se existingu¢ hace mucho tiempo");
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
                                script_say("Es una figura de un elefante");
                                break;
                            case 1:
                                begin_script();
                                script_say("Mi madre siempre decia que tener un elefante con la trompa orientada a la entrada, atra¡a el dinero");
                                break;
                            case 2:
                                script_wait(10);
                                break;
                            case 3:
                                begin_script();
                                script_say("Y aqu¡ me tienes... Sin dinero para el concierto...");
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
                                script_say("Es la cocina");
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
                                script_move_player(221, 117);
                            break;
                            case 1:
                                r02_object[R02_DOORFRAME_OBJ_ID].active = true;
                                script_move_player_no_clip(250, 117);
                            break;
                            case 2:
                                change_room(KITCHEN_ROOM_NUM);
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
                                script_say("Puede parecer extra¤o, pero llevo en esta casa toda mi vida y no s‚ a donde lleva esa puerta");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case OPEN:
                    case USE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("No se puede abrir. Siempre ha estado cerrada");
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
                                script_say("Este cuadro es la £nica cosa de valor en toda la casa");
                                break;
                            case 1:
                                script_say("Creo que lo pint¢ mi padre");
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
                                script_say("La puerta que da a la habitaci¢n");
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
                                change_room_pos(BEDROOM_ROOM_NUM, 201, 136);
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
                                script_say("La puerta que da a la calle");
                                break;
                            case 1:
                                script_say("­­A la libertad!!");
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
                                if (is_game_flag(FATHER_SAY_MONEY_FLAG))
                                    change_room_pos(STREET_ROOM_NUM, 160, 100);
                                else
                                    script_say("Deber¡a pensar en como conseguir el dinero del concierto antes de irme de casa");
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
                                script_say("Una l mpara para crear un rinc¢n acogedor");
                                break;
                            case 1:
                                script_say("Nunca la encendemos");
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