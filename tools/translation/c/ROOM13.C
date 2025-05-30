/*
=========================================================
 Room Number:   13
 Room Name:     13_ending
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room13.h"

//Funtion to return the name of hotspot by color code
void r13_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r13_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r13_get_object_info(uint8_t numObject)
{
    if (numObject < R13_ROOM_NUM_OBJS)
        return &r13_object[numObject];
    else
        return NULL;
}

//function to init room
void r13_room_init()
{
    game_fade_in();
    r13_object[R13_CROWD_OBJ_ID].layer = 1;
    start_script(R13_ENDING_SCRIPT);
}

//global funcion to update room
void r13_room_update()
{
    //update room objects
    r13_update_room_objects();

    //update dialog line selection
    r13_update_dialog_selection();
    
    //update room script
    r13_update_room_script();
}

//update room objects
void r13_update_room_objects()
{
    object_play_animation(&r13_object[R13_CROWD_OBJ_ID], r13d_objCrowd1, r13_animations, R13_ANIM_CROWD);
    object_play_animation(&r13_object[R13_SPEAKERS_OBJ_ID], r13d_objSpeakers1, r13_animations, R13_ANIM_SPEAKERS);

    if (!is_game_flag(END_STOP_GUITARS_FLAG))
    {
       object_play_animation(&r13_object[R13_GUITAR_1_OBJ_ID], r13d_objGuitar11, r13_animations, R13_ANIM_GUITAR_1);
       object_play_animation(&r13_object[R13_GUITAR_2_OBJ_ID], r13d_objGuitar21, r13_animations, R13_ANIM_GUITAR_2);
    }
    else
    {
        object_play_animation(&r13_object[R13_GUITAR_1_OBJ_ID], r13d_objGuitar11, r13_animations, r13d_objGuitar11, r13d_objGuitar11, 1, ANIM_LOOP);
        object_play_animation(&r13_object[R13_GUITAR_2_OBJ_ID], r13d_objGuitar21, r13_animations, r13d_objGuitar21, r13d_objGuitar21, 1, ANIM_LOOP);
    }

    if (!is_game_flag(END_STOP_DRUMS_FLAG))
        object_play_animation(&r13_object[R13_DRUMS_OBJ_ID], r13d_objDrums1, r13_animations, R13_ANIM_DRUMS);
    else
        object_play_animation(&r13_object[R13_DRUMS_OBJ_ID], r13d_objDrums1, r13_animations, r13d_objDrums1, r13d_objDrums1, 1, ANIM_LOOP);

    if (is_game_flag(PLAYER_ROCKING_FLAG))
        play_player_animation(ANIM_PLY_ROCKING);
}

//update dialog selection
void r13_update_dialog_selection()
{

}

//update room script
void r13_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case R13_ENDING_SCRIPT:
                switch(roomScript.step)
                {
                    case 0:
                        begin_script();
                        script_wait(20);
                    break;
                    case 1:
                        script_move_player_no_clip(120, 160);
                    break;
                    case 2:
                        script_wait(10);
                    break;
                    case 3:
                        play_player_animation(ANIM_PLY_HAPPY);
                        script_wait(10);
                    break;
                    case 4:
                        script_move_player_no_clip(350, 160);
                    break;
                    case 5:
                        script_wait(10);
                        r13_object[R13_CROWD_OBJ_ID].layer = 0;
                        set_player_position(350, 253);
                    break;
                    case 6:
                        script_move_player_no_clip(79, 253);
                    break;
                    case 7:
                        change_player_dir(DIR_BACK);
                        script_wait(10);
                    break;
                    case 8:
                        set_game_flag(PLAYER_ROCKING_FLAG);
                        script_wait(30);
                    break;
                    case 9:
                        set_game_flag(START_CREDITS_FLAG);
                        roomScript.step++;
                    break;
                    case 10:
                        if (is_game_flag(END_CREDITS_FLAG))
                            roomScript.step++;
                    break;
                    case 11:
                        game_fade_out(FADE_SLOW_SPEED);
                        roomScript.step++;
                    break;
                    case 12:
                        script_wait(10);
                    break;
                    case 13:
                        change_room_pos(COMPUTER_ROOM_NUM, 350, 200);
                        end_script();
                    break;
                    default:
                        end_script();
                    break;
                }
            break;
        }
    }
}
