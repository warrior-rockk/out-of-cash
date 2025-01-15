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
                strcpy(s, "Telara¤a");
            break;
        case r10_paintBucket:
            if (r10_object[R10_PAINTBUCKET_OBJ_ID].active)
            {
                strcpy(s, "Cubo de pintura");
                break;
            }
            else
                strcpy(s, "");
        case r10_broom:
            if (is_game_flag(MAINT_CLOSET_OPEN_FLAG))
            {
                strcpy(s, "Escoba");
                break;
            }
            else
                strcpy(s, "");
        case r10_box:
            if (is_game_flag(MAINT_CLOSET_OPEN_FLAG))
            {
                strcpy(s, "Caja");
                break;
            }
            else
                strcpy(s, "");
        case r10_closet:
                strcpy(s, "Armario");
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
        case r10_paintBucket:
            if (r10_object[R10_PAINTBUCKET_OBJ_ID].active)
            {
                return LOOK;
                break;
            }
        case r10_broom:
            if (is_game_flag(MAINT_CLOSET_OPEN_FLAG))
            {
                return LOOK;
                break;
            }
        case r10_box:
            if (is_game_flag(MAINT_CLOSET_OPEN_FLAG))
            {
                return LOOK;
                break;
            }        
        case r10_closet:
            if (!is_game_flag(MAINT_CLOSET_OPEN_FLAG))
                return OPEN;
            else
                return CLOSE;
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
    set_room_light_off(!is_game_flag(MAINT_LOCKER_LIGHT_ON_FLAG));
    
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
    r10_object[R10_MAINTCLOSETOPEN_OBJ_ID].active = is_game_flag(MAINT_CLOSET_OPEN_FLAG) && is_game_flag(MAINT_LOCKER_LIGHT_ON_FLAG);
    r10_object[R10_BOX_OBJ_ID].active = is_game_flag(MAINT_CLOSET_OPEN_FLAG) && is_game_flag(MAINT_LOCKER_LIGHT_ON_FLAG);
    r10_object[R10_PAINTBUCKET_OBJ_ID].active = !is_game_flag(GOT_PAINT_BUCKET_FLAG) && is_game_flag(MAINT_CLOSET_OPEN_FLAG) && is_game_flag(MAINT_LOCKER_LIGHT_ON_FLAG);

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
                                script_say("Por esa puerta se va al pasillo del instituto");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case GO:
                    case USE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player_to_target();
                                break;
                            default:
                                change_room_pos(SCHOOL_ROOM_NUM, 124, 86);
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
                                script_say("¨Cual ser  la funci¢n de este interruptor?");
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
                                script_play_sound(sd_switch);
                            break;
                            case 2:
                                script_player_take_state();
                                break;
                            case 3:
                                toggle_game_flag(MAINT_LOCKER_LIGHT_ON_FLAG);
                                set_room_light_off(!is_game_flag(MAINT_LOCKER_LIGHT_ON_FLAG));
                                end_script();
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
                                script_say("Quien dir¡a que pudiera haber ara¤as en este cuarto de mantenimiento tan aseado");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;  
            case r10_paintBucket:
                if (r10_object[R10_PAINTBUCKET_OBJ_ID].active)
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("Un cubo de pintura negra");
                                    break;
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
                                    script_take_object(&r10_object[R10_PAINTBUCKET_OBJ_ID].active, GOT_PAINT_BUCKET_FLAG, id_paintBucket);
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                    break;
                }
            case r10_box:
                if (is_game_flag(MAINT_CLOSET_OPEN_FLAG))
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("No entiendo porque hay tantas cajas vac¡as en este juego...");
                                    break;
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                    break;
                }
            case r10_broom:
                if (is_game_flag(MAINT_CLOSET_OPEN_FLAG))
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("No me hagas mucho caso pero dir¡a que es una escoba");
                                    break;
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                    break;
                }
            case r10_closet:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Parece el armario donde el personal de mantenimiento guarda el material");
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
                                if (is_game_flag(MAINT_CLOSET_OPEN_FLAG))
                                {
                                    script_say("Ya est  abierto");
                                    end_script();
                                }
                                else                                
                                    script_move_player_to_target();
                                break;
                            case 1:
                                script_play_sound(sd_closetOpen);
                            break;
                            case 2:
                                script_player_take_state();
                                break;
                            case 3:
                                set_game_flag(MAINT_CLOSET_OPEN_FLAG);
                                end_script();
                                break;
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
                                if (!is_game_flag(MAINT_CLOSET_OPEN_FLAG))
                                {
                                    script_say("Ya est  cerrado");
                                    end_script();
                                }
                                else                                
                                    script_move_player_to_target();
                                break;
                            case 1:
                                script_play_sound(sd_closetClose);
                            break;
                            case 2:
                                script_player_take_state();
                                break;
                            case 3:
                                clear_game_flag(MAINT_CLOSET_OPEN_FLAG);
                                end_script();
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