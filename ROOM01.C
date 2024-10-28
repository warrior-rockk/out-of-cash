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

//#include "IDATA.h"

//Funtion to return the name of hotspot by color code
void r01_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r01_guitar:
            if (r01_object[R01_GUITAR_OBJ_ID].active)
                strcpy(s, "Guitarra");
            break;
        case r01_stereo:
            strcpy(s, "Minicadena");
            break;
        case r01_door:
            strcpy(s, "Puerta");
            break;
        case r01_cassette:
            if (r01_object[R01_CASSETTE_OBJ_ID].active)
                strcpy(s, "Casete");
            break;
        case r01_spider:
            strcpy(s, "Ara"CHAR_NY"a");
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
        case r01_door:
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

    //update dialog line selection
    r01_update_dialog_selection();
    
    //update room script
    r01_update_room_script();
}

//update room objects
void r01_update_room_objects()
{
    //update objects

    //talk animation test
    r01_object[R01_STEREO_OBJ_ID].active = r01_dialogActor.talking;
    
    //Stereo
    object_play_animation(&r01_object[R01_STEREO_OBJ_ID], r01d_objStereo01, r01_animations, R01_ANIM_PLAY_STEREO);
}

//function to update dialog line selection
void r01_update_dialog_selection()
{
    if (dialog.active && dialog.state == DIALOG_ST_SELECT)
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

//updates room script
void r01_update_room_script()
{
    //if script active is dialog type
    if (roomScript.active && roomScript.type == DIALOG_SCRIPT_TYPE)
    {
        //fixed step: say response line
        if (roomScript.step == 0)
        {
            begin_script();
            script_say(dialog.lineText[dialog.selLine - 1]);
        }
        else
        {
            //encode dialog id, node and selLine on integer value
            //1 digit for dialog id, 2 digit for dialog node and 1 digit for selLinef
            switch (((dialog.dialogId - 1) * 1000) + ((dialog.node - 1) * 100) + dialog.selLine)
            {

                case 1:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_wait(2);
                        break;
                        case 2:
                            script_say_actor("A ti que te importa", &r01_dialogActor);
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
                            script_say_actor("Ya he jugado bastante", &r01_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                default:
                    script_next_dialog_node();
                    end_script();
                break;
            }
        }
    }

    //if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r01_spider:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es mi ara"CHAR_NY"a de He-man");
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
                                r01_dialogActor.msgX = roomScript.hsX;
                                r01_dialogActor.msgY = roomScript.hsY;
                                script_start_dialog(1);
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;
            case r01_stereo:
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
            case r01_door:
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
            case r01_cassette:
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
            case r01_guitar:
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

