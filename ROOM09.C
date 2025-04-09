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
                strcpy(s, "Door");
            break;
        case r09_bench:
                strcpy(s, "Bench");
            break;
        case r09_shirt:
            if (!r09_object[R09_SHIRT_OBJ_ID].active)
            {
                strcpy(s, "Locker");
                break;
            }
            else
            {
                strcpy(s, "T-shirt");
                break;
            }
        case r09_books:
            if (!is_game_flag(LOCKER_1_OPEN_FLAG))
                strcpy(s, "");
            else
            {
                strcpy(s, "Books");
                break;
            }
        case r09_locker1:
                strcpy(s, "Locker");
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
                strcpy(s, "Shoes");
                break;
            }
        case r09_bag:
            if (!is_game_flag(LOCKER_2_OPEN_FLAG))
                strcpy(s, "");
            else
            {
                strcpy(s, "Bag");
                break;
            }
        case r09_locker2:
                strcpy(s, "Locker");
            break;
        case r09_jeans:
            if (!r09_object[R09_JEANS_OBJ_ID].active)
            {
                strcpy(s, "Locker");
                break;
            }
            else
            {
                strcpy(s, "Trousers");
                break;
            }
        case r09_box:
            if (!is_game_flag(LOCKER_3_OPEN_FLAG))
                strcpy(s, "");
            else
            {
                strcpy(s, "Box");
                break;
            }
        case r09_locker3:
                strcpy(s, "Locker");
            break;
        case r09_locker4:
                strcpy(s, "Locker");
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
                return LOOK;
            else if (is_game_flag(LOCKER_1_OPEN_FLAG))
                return CLOSE;
            else
                return OPEN;
            break;
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
                return LOOK;
            else if (is_game_flag(LOCKER_3_OPEN_FLAG))
                return CLOSE;
            else
                return OPEN;
            break;
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
    if (is_game_flag(LOCKER_DOOR_OPEN_FLAG))
        start_script(R09_DOOR_CLOSE_SCRIPT);
        
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

    r09_object[R09_DOOR_OBJ_ID].active      = is_game_flag(LOCKER_DOOR_OPEN_FLAG);
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
                                script_say("It is the door that leads to the high school hallway");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case GO:
                    case USE:
                    case OPEN:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player_to_target();
                            break;
                            case 1:
                                play_sound_rnd(sd_doorOpen);
                                roomScript.step++;
                            break;
                            case 2:
                                set_game_flag(LOCKER_DOOR_OPEN_FLAG);
                                roomScript.hsY = get_player_pos_y();
                                script_player_take_state();
                            break;
                            default:
                                change_room_pos(SCHOOL_ROOM_NUM, 686, 84);
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
                                script_say("A bench to sit on and be able to dress");
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
                                script_say("I like to stand on my foot");
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
                                    script_say("A red t-shirt very similar to mine");
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
            case r09_locker1:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A regular high school locker");
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
                                    script_say("Already open");
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
                                    script_say("Already closed");
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
                                    script_say("They look like books of some subjects");
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
                                    script_say("I have no interest in having those books");
                                    break;
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                    break;
                }    
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
                                    script_say("A nice Village People poster");
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
                                    script_say("Buaj...These sneakers smell awful");
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
                                    script_say("Some student's bag");
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
                                    script_say("Which do you take me for? I am not a thief");
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
                                script_say("A high school standard locker");
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
                                    script_say("Already open");
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
                                    script_say("Already closed");
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
                                    script_say("Perfectly folded jeans");
                                    break;
                                default:
                                    script_say("I use the same brand");
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
                else
                {
                    begin_script();
                    roomScript.object = r09_locker3;
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
                                    script_say("Who keeps an empty box in a locker?");
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
                                script_say("A normal high school locker");
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
                                    script_say("Already open");
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
                                    script_say("Already closed");
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
                                script_say("A classic high school locker");
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
                                script_say("It's locked. Cannot be opened");
                            break;
                            default:
                                script_say("And I don't have much interest in opening it either");
                                end_script();
                            break;
                        }
                    break;
                    case CLOSE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Already closed");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
            break;
            case R09_DOOR_CLOSE_SCRIPT:
                switch(roomScript.step)
                {
                    case 0:
                        change_player_dir(DIR_RIGHT);
                        script_wait(1);
                    break;
                    case 1:
                        roomScript.hsY = get_player_pos_y();
                        script_player_take_state();
                    break;
                    case 2:
                        play_sound_rnd(sd_doorClose);
                        clear_game_flag(LOCKER_DOOR_OPEN_FLAG);
                        roomScript.step++;
                    break;
                    default:
                        change_player_dir(DIR_LEFT);
                        end_script();
                    break;
                }
            break;            
                        

        }
    }
}