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

#include "IDATA.h"

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
        case Spider:
            strcpy(s, "Ara¤a");
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

//global funcion to update room
void r01_room_update()
{
    //update room objects
    r01_update_room_objects();

    //update room script
    r01_update_room_script();
}

//update room objects
void r01_update_room_objects()
{
    //update objects

    //Stereo
    object_play_animation(&r01_object[R01_STEREO_OBJ_ID], r01d_objStereo01, r01_animations, R01_ANIM_PLAY_STEREO);
}

//updates room script
void r01_update_room_script()
{
    //dialog script test
    if (dialog.active)
    {
        if (dialog.state == DIALOG_ST_SELECT)
        {
            switch (dialog.dialogId)
            {
                case 1:
                    switch (dialog.node)
                    {
                        case 0:
                            stop_dialog();
                        break;
                        case 1:
                            dialog_add("¨Como est s ara¤a?", 2);
                            dialog_add("¨Puedo jugar contigo?", 3);
                            dialog_add("Lo siento. Me voy...", 0);
                        break;
                        case 2:
                            dialog_add("Tampoco hace falta que seas tan borde", 1);
                            dialog_add("Vale, vale. Ya me callo", 0);
                        break;
                        case 3:
                            if (is_game_flag(GOT_CASSETTE))
                                dialog_add("Te iba a dar este casete...", 1);
                            dialog_add("Pues adios", 0);
                        break;
                    }
                break;
            }
        }
    }

    if (roomScript.active && roomScript.dialogScript)
    {
        if (roomScript.step == 0)
        {
            //say the response choice
            begin_script();
            script_say(dialog.lineText[dialog.selLine - 1]);
        }
        else
        {
            switch (dialog.dialogId)
            {
                case 1:
                    switch (dialog.node)
                    {
                        case 1:
                            switch (dialog.selLine)
                            {
                                case 1:
                                    switch (roomScript.step)
                                    {
                                        case 1:
                                            script_wait(2);
                                        break;
                                        case 2:
                                            script_say("A ti que te importa");
                                        break;
                                        default:
                                            script_next_dialog_node();
                                            end_script();
                                        break;
                                    }
                                break;
                                case 2:
                                    switch (roomScript.step)
                                    {
                                        case 1:
                                            script_wait(2);
                                        break;
                                        case 2:
                                            script_say("Ya he jugado bastante");
                                        break;
                                        default:
                                            script_next_dialog_node();
                                            end_script();
                                        break;
                                    }
                                break;
                            }
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
            }
        }
    }

    //script update
    if (roomScript.active && !roomScript.invScript && !roomScript.dialogScript)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case Spider:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es mi ara¤a de He-man");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case TALK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_start_dialog(1);
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;
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
                            case id_cassette:
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
                                        say("Ya esta dentro");
                                        script_remove_inv_object(id_cassette);
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
                                script_take_object(&r01_object[R01_CASSETTE_OBJ_ID].active, GOT_CASSETTE, id_cassette);
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
                                script_take_object(&r01_object[R01_GUITAR_OBJ_ID].active, GOT_GUITAR, id_guitar);
                                end_script();
                                break;
                        }
                        break;
                }
                break;
        }
    }
}

