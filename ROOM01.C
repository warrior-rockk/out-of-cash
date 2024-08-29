/*
=========================================================
 Room Number:   01
 Room Name:     bedRoom

=========================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room01.h"

#include "inv.h"

//Funtion to return the name of hotspot by color code
void r01_get_hotspot_name(uint8_t colorCode, char *s)
{
        
    //check the object
    switch(colorCode)
    {
        case Guitarra:
            if (r01_object[R01_GUITAR_OBJ_ID].active)
                strcpy(s, "Guitarra");
            break;
        case Minicadena:
            strcpy(s, "Minicadena");
            break;
        case Puerta:
            strcpy(s, "Puerta");
            break;
        case Casete:
            if (r01_object[R01_CASSETTE_OBJ_ID].active)
                strcpy(s, "Casete");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r01_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case Puerta:
            return OPEN;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r01_get_object_info(uint8_t numObject)
{
    if (numObject < R01_ROOM_NUM_OBJS)
        return &r01_object[numObject];
    else
        return NULL;
}

//function to init room
void r01_room_init()
{
    //update room objects state
    r01_object[R01_CASSETTE_OBJ_ID].active  = !is_game_flag(GOT_CASSETTE);
    r01_object[R01_GUITAR_OBJ_ID].active    = !is_game_flag(GOT_GUITAR);
    r01_object[R01_STEREO_OBJ_ID].active    = is_game_flag(STEREO_ON);
    
    game_fade_in();
}

//funcion to update room
void r01_room_update()
{
    //objects update
    if (r01_object[R01_STEREO_OBJ_ID].active)
        play_animation(&r01_stereo_anim, ANIM_PLAY_STEREO);
    else
        r01_stereo_anim.frame = dObjStereo01;
    r01_object[R01_STEREO_OBJ_ID].objId = r01_stereo_anim.frame;
    
    //script update
    if (roomScript.active && !roomScript.invScript)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case Minicadena:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es mi minicadena ultimo modelo");
                                break;
                            case 1:
                                script_wait(4);
                                break;
                            case 2:
                                script_say("Otra cosa");
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
                                script_say("No puedo llevarmelo. Pesa mucho");
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
                                if (!is_game_flag(USED_CASSETTE))
                                {
                                    script_say("No hay ningun casete dentro");
                                    end_script();
                                }
                                else
                                    script_move_player_to_target();
                                break;
                            case 1:
                                //script_play_player_animation(10, 10, 5);
                                script_player_take_state();
                                break;
                            case 2:
                                toogle_game_flag(STEREO_ON);
                                r01_object[R01_STEREO_OBJ_ID].active = is_game_flag(STEREO_ON);
                                end_script();
                                break;
                            default:
                                end_script();
                                break;
                        }
                        break;
                    case USE_WITH:
                        switch (roomScript.invObject)
                        {
                            case dInv_Cassette:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_move_player_to_target();
                                        break;
                                    case 1:
                                        //script_play_player_animation(10, 10, 5);
                                        script_player_take_state();
                                        break;
                                    case 2:
                                        say("Ya esta dentro");
                                        script_remove_inv_object(dInv_Cassette);
                                        set_game_flag(USED_CASSETTE);
                                        end_script();
                                        break;
                                }
                                break;
                        }
                        break;
                }
                break;
            case Puerta:
                switch(roomScript.verb)
                {
                    case GO:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player(roomScript.hsX,200);
                                break;
                            case 1:
                                change_room_pos(1,174,38);
                                end_script();
                                break;
                        }
                        break;
                }
                break;
            case Casete:
                switch(roomScript.verb)
                {
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player_to_target();
                                break;
                            case 1:
                                script_take_object(&r01_object[R01_CASSETTE_OBJ_ID].active, GOT_CASSETTE, dInv_Cassette);
                                end_script();
                                break;
                        }
                        break;
                }
                break;
            case Guitarra:
                switch(roomScript.verb)
                {
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player_to_target();
                                break;
                            case 1:
                                script_take_object(&r01_object[R01_GUITAR_OBJ_ID].active, GOT_GUITAR, dInv_Guitar);
                                end_script();
                                break;
                        }
                        break;
                }
                break;
        }
    }
}

