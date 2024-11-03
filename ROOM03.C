/*
=========================================================
 Room Number:   03
 Room Name:     03_bathroom
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room03.h"

//Funtion to return the name of hotspot by color code
void r03_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r03_gel:
            if (r03_object[R03_GEL_OBJ_ID].active)
            {
                strcpy(s, "Gel");
                break;
            }
            else
                strcpy(s, "");
            //break;
        case r03_closet:
                strcpy(s, "Armario");
            break;
        case r03_washbowl:
                strcpy(s, "Lavabo");
            break;
        case r03_mirror:
                strcpy(s, "Espejo");
            break;
        case r03_towel:
                strcpy(s, "Toalla");
            break;
        case r03_bathMat:
                strcpy(s, "Alfombrilla");
            break;
        case r03_switch:
                strcpy(s, "Interruptor");
            break;
        case r03_door:
                strcpy(s, "Puerta");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r03_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r03_closet:
            if (is_game_flag(BATH_CLOSET_OPEN))
                return CLOSE;
            else
                return OPEN;
            break;
        case r03_washbowl:
            return USE;
            break;
        case r03_mirror:
            return LOOK;
            break;
        case r03_towel:
            return LOOK;
            break;
        case r03_gel:
            return LOOK;
            break;
        case r03_bathMat:
            return LOOK;
            break;
        case r03_switch:
            return USE;
            break;
        case r03_door:
            if (is_game_flag(BATH_DOOR_OPEN))
                return CLOSE;
            else
                return OPEN;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r03_get_object_info(uint8_t numObject)
{
    if (numObject < R03_ROOM_NUM_OBJS)
        return &r03_object[numObject];
    else
        return NULL;
}

//function to init room
void r03_room_init()
{
    set_room_lights_off(2, is_game_flag(BATH_LIGHT_OFF));    
    game_fade_in();
}

//global funcion to update room
void r03_room_update()
{
    //update room objects
    r03_update_room_objects();

    //update dialog line selection
    r03_update_dialog_selection();
    
    //update room script
    r03_update_room_script();
}

//update room objects
void r03_update_room_objects()
{
    r03_object[R03_GEL_OBJ_ID].active = is_game_flag(BATH_CLOSET_OPEN) && !is_game_flag(GOT_GEL);
    r03_object[R03_BATHCLOSETOPEN_OBJ_ID].active = is_game_flag(BATH_CLOSET_OPEN);
    r03_object[R03_BATHDOOROPEN_OBJ_ID].active = is_game_flag(BATH_DOOR_OPEN);
}

//update dialog selection
void r03_update_dialog_selection()
{

}

//update room script
void r03_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r03_gel:
                if (is_game_flag(BATH_CLOSET_OPEN) && !is_game_flag(GOT_GEL))
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("Un bote de gel de ducha");
                                    break;
                                case 1:
                                    script_say("Parece muy viscoso...");
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                        case TAKE:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_move_player_to_target();
                                    break;
                                case 1:
                                    script_take_object(&r03_object[R03_GEL_OBJ_ID].active, GOT_GEL, id_soap);
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                    break;
                }
            case r03_closet:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("El cl sico armario del ba¤o donde acabas acumulando cientos de productos");
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
                                if (is_game_flag(BATH_CLOSET_OPEN))
                                {
                                    script_say("Ya est  abierto");
                                    end_script();
                                }
                                else                                
                                    script_move_player_to_target();
                                break;
                            case 1:
                                set_game_flag(BATH_CLOSET_OPEN);
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
                                if (!is_game_flag(BATH_CLOSET_OPEN))
                                {
                                    script_say("Ya est  cerrado");
                                    end_script();
                                }
                                else                                
                                    script_move_player_to_target();

                                break;
                            case 1:
                                clear_game_flag(BATH_CLOSET_OPEN);
                                end_script();
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r03_washbowl:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("No olviden lavarse las manos antes de reincorporarse al trabajo...");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r03_mirror:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (!is_game_flag(CORRIDOR_MIRROR_MSG))
                                {
                                    set_game_flag(BATH_MIRROR_MSG);
                                    script_say("El programador del juego ha sido tan vago como para no programar los reflejos...");
                                    end_script();
                                }
                                else
                                    script_say("Otro espejo con reflejo sin programar...");
                                break;
                            case 1:
                                script_wait(10);
                                break;
                            case 2:
                                script_say("No se le puede pedir mas...");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r03_towel:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Esta toalla lleva en la familia muchos a¤os");
                                break;
                            case 1:
                                script_say("Deberiamos pensar en lavarla...");
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;
            case r03_bathMat:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("La alfombrilla para secarte los pies despu‚s de la ducha");
                                break;
                            case 1:
                                script_wait(10);
                            case 2:
                                script_say("No le des vueltas. No hay nada debajo...");
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r03_switch:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Hay algo placentero en el sonido de un interruptor accion ndose");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player_to_target();
                                break;
                            case 1:
                                script_player_take_state();
                                break;
                            case 2:
                                toogle_game_flag(BATH_LIGHT_OFF);
                                set_room_lights_off(2, is_game_flag(BATH_LIGHT_OFF));
                                end_script();
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r03_door:
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
                                change_room_pos(1, 154, 46);
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
                                script_say("La puerta del ba¤o que da al pasillo");
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

        }
    }
}
