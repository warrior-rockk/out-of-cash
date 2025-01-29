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
        case r09_shirt:
            if (!r09_object[R09_SHIRT_OBJ_ID].active)
                strcpy(s, "");
            else
            {
                strcpy(s, "Camiseta");
                break;
            }
        case r09_books:
            if (!is_game_flag(LOCKER_1_OPEN_FLAG))
                strcpy(s, "");
            else
            {
                strcpy(s, "Libros");
                break;
            }
        case r09_locker1:
                strcpy(s, "Taquilla");
            break;
        case r09_poster:
            if (!is_game_flag(LOCKER_2_OPEN_FLAG))
                strcpy(s, "");
            else
            {
                strcpy(s, "Poster");
                break;
            }
        case r09_shoes:
            if (!is_game_flag(LOCKER_2_OPEN_FLAG))
                strcpy(s, "");
            else
            {
                strcpy(s, "Zapatillas");
                break;
            }
        case r09_bag:
            if (!is_game_flag(LOCKER_2_OPEN_FLAG))
                strcpy(s, "");
            else
            {
                strcpy(s, "Mochila");
                break;
            }
        case r09_locker2:
                strcpy(s, "Taquilla");
            break;
        case r09_jeans:
            if (!r09_object[R09_JEANS_OBJ_ID].active)
                strcpy(s, "");
            else
            {
                strcpy(s, "Pantalones");
                break;
            }
        case r09_box:
            if (!is_game_flag(LOCKER_3_OPEN_FLAG))
                strcpy(s, "");
            else
            {
                strcpy(s, "Caja");
                break;
            }
        case r09_locker3:
                strcpy(s, "Taquilla");
            break;
        case r09_locker4:
                strcpy(s, "Taquilla");
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
        case r09_shirt:
            if (r09_object[R09_SHIRT_OBJ_ID].active)
            {
                return LOOK;
                break;
            }
        case r09_books:
            if (is_game_flag(LOCKER_1_OPEN_FLAG))
            {
                return LOOK;
                break;
            }
        case r09_locker1:
            if (is_game_flag(LOCKER_1_OPEN_FLAG))
                return CLOSE;
            else
                return OPEN;
            break;
        case r09_poster:
            if (is_game_flag(LOCKER_2_OPEN_FLAG))
            {
                return LOOK;
                break;
            }
        case r09_shoes:
            if (is_game_flag(LOCKER_2_OPEN_FLAG))
            {
                return LOOK;
                break;
            }
        case r09_bag:
            if (is_game_flag(LOCKER_2_OPEN_FLAG))
            {
                return LOOK;
                break;
            }
        case r09_locker2:
            if (is_game_flag(LOCKER_2_OPEN_FLAG))
                return CLOSE;
            else
                return OPEN;
            break;
        case r09_jeans:
            if (r09_object[R09_SHIRT_OBJ_ID].active)
            {
                return LOOK;
                break;
            }
        case r09_box:
            if (is_game_flag(LOCKER_3_OPEN_FLAG))
            {
                return LOOK;
                break;
            }
        case r09_locker3:
            if (is_game_flag(LOCKER_3_OPEN_FLAG))
                return CLOSE;
            else
                return OPEN;
            break;
        case r09_locker4:
            return OPEN;
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
    r09_object[R09_LOCKER1OPEN_OBJ_ID].active = is_game_flag(LOCKER_1_OPEN_FLAG);
    r09_object[R09_LOCKER2OPEN_OBJ_ID].active = is_game_flag(LOCKER_2_OPEN_FLAG);
    r09_object[R09_LOCKER3OPEN_OBJ_ID].active = is_game_flag(LOCKER_3_OPEN_FLAG);

    r09_object[R09_SHIRT_OBJ_ID].active = is_game_flag(LOCKER_1_OPEN_FLAG) && !is_game_flag(GOT_SHIRT_FLAG);
    r09_object[R09_JEANS_OBJ_ID].active = is_game_flag(LOCKER_3_OPEN_FLAG) && !is_game_flag(GOT_JEANS_FLAG);
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
                                script_say("Es la puerta que da al pasillo del instituto");
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
                                change_room_pos(SCHOOL_ROOM_NUM, 686, 82);
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
                                script_say("Un banco para sentarse y poder cambiarse");
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
                                script_say("Me gusta estar de pie");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r09_shirt:
                if (r09_object[R09_SHIRT_OBJ_ID].active)
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("Una camiseta roja muy parecida a la m¡a");
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
                                    script_take_object(&r09_object[R09_SHIRT_OBJ_ID].active, GOT_SHIRT_FLAG, id_shirt);
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                    break;
                }
            case r09_books:
                if (is_game_flag(LOCKER_1_OPEN_FLAG))
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("Parecen libros de algunas asignaturas");
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
                                    script_say("No tengo ning£n inter‚s en tener esos libros");
                                    break;
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                    break;
                }    
            case r09_locker1:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Una taquilla com£n de instituto");
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
                                if (!is_game_flag(LOCKER_1_OPEN_FLAG))
                                    script_move_player_to_target();
                                else
                                {
                                    script_say("Ya est  abierta");
                                    end_script();
                                }
                                break;
                            case 1:
                                play_sound(sd_lockerOpen);
                                roomScript.step++;
                            break;
                            case 2:
                                script_player_take_state();
                                break;
                            default:
                                set_game_flag(LOCKER_1_OPEN_FLAG);
                                end_script();
                                break;
                        }
                    break;
                    case CLOSE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (is_game_flag(LOCKER_1_OPEN_FLAG))
                                    script_move_player_to_target();
                                else
                                {
                                    script_say("Ya est  cerrada");
                                    end_script();
                                }
                                break;
                            case 1:
                                script_player_take_state();
                                break;
                            default:
                                clear_game_flag(LOCKER_1_OPEN_FLAG);
                                play_sound(sd_lockerClose);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r09_poster:
                if (is_game_flag(LOCKER_2_OPEN_FLAG))
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("Un bonito poster de los Village People");
                                    break;
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                    break;
                }
            case r09_shoes:
                if (is_game_flag(LOCKER_2_OPEN_FLAG))
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("Buaj...Estas zapatillas huelen fatal");
                                    break;
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                    break;
                }    
            case r09_bag:
                if (is_game_flag(LOCKER_2_OPEN_FLAG))
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("La mochila de alg£n estudiante");
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
                                    script_say("¨Por qui‚n me tomas? No soy un ladr¢n");
                                    break;
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                    break;
                }
            case r09_locker2:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Una taquilla est ndar de instituto");
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
                                if (!is_game_flag(LOCKER_2_OPEN_FLAG))
                                    script_move_player_to_target();
                                else
                                {
                                    script_say("Ya est  abierta");
                                    end_script();
                                }
                                break;
                            case 1:
                                play_sound(sd_lockerOpen);
                                roomScript.step++;
                            break;
                            case 2:
                                script_player_take_state();
                                break;
                            default:
                                set_game_flag(LOCKER_2_OPEN_FLAG);
                                end_script();
                                break;
                        }
                    break;
                    case CLOSE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (is_game_flag(LOCKER_2_OPEN_FLAG))
                                    script_move_player_to_target();
                                else
                                {
                                    script_say("Ya est  cerrada");
                                    end_script();
                                }
                                break;
                            case 1:
                                script_player_take_state();
                                break;
                            default:
                                clear_game_flag(LOCKER_2_OPEN_FLAG);
                                play_sound(sd_lockerClose);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r09_jeans:
                if (r09_object[R09_JEANS_OBJ_ID].active)
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("Unos pantalones vaqueros perfectamente doblados");
                                    break;
                                default:
                                    script_say("Yo uso la misma marca");
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
                                    script_take_object(&r09_object[R09_JEANS_OBJ_ID].active, GOT_JEANS_FLAG, id_jeans);
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                    break;
                }
            case r09_box:
                if (is_game_flag(LOCKER_3_OPEN_FLAG))
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("¨Quien guardar¡a una caja vac¡a en una taquilla?");
                                    break;
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                    break;
                }
            case r09_locker3:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Una taquilla normal de instituto");
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
                                if (!is_game_flag(LOCKER_3_OPEN_FLAG))
                                    script_move_player_to_target();
                                else
                                {
                                    script_say("Ya est  abierta");
                                    end_script();
                                }
                                break;
                            case 1:
                                play_sound(sd_lockerOpen);
                                roomScript.step++;
                            break;
                            case 2:
                                script_player_take_state();
                                break;
                            default:
                                set_game_flag(LOCKER_3_OPEN_FLAG);
                                end_script();
                                break;
                        }
                    break;
                    case CLOSE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (is_game_flag(LOCKER_3_OPEN_FLAG))
                                    script_move_player_to_target();
                                else
                                {
                                    script_say("Ya est  cerrada");
                                    end_script();
                                }
                                break;
                            case 1:
                                script_player_take_state();
                                break;
                            default:
                                clear_game_flag(LOCKER_3_OPEN_FLAG);
                                play_sound(sd_lockerClose);
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
                                script_say("Una taquilla cl sica de instituto");
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
                                script_move_player_to_target();
                            break;
                            case 1:
                                script_say("Esta bloqueada. No se puede abrir");
                            break;
                            default:
                                script_say("Y tampoco tengo mucho inter‚s en abrirla");
                                end_script();
                            break;
                        }
                    break;
                    case CLOSE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Ya est  cerrada");
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