/*
=========================================================
 Room Number:   06
 Room Name:     06_school
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room06.h"

//Funtion to return the name of hotspot by color code
void r06_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r06_door:
                strcpy(s, "Door");
            break;
        case r06_maintLockerLock:
            if (!is_game_flag(MAINT_LOCKER_DOOR_OPEN_FLAG))
            {
                strcpy(s, "Lock");
                break;
            }
            else
                strcpy(s, "");
        case r06_maintLockerDoor:
                strcpy(s, "Door");
            break;
        case r06_maintLockerBathMat:
            if (is_game_flag(BATH_MAT_IN_DOOR_FLAG) || is_game_flag(BATH_MAT_OUT_DOOR_FLAG))
                strcpy(s, "mat");
            else
                strcpy(s, "");
            break;
        case r06_maintLockerKey:
            if (is_game_flag(KEY_ON_BATH_MAT_FLAG) && is_game_flag(BATH_MAT_OUT_DOOR_FLAG))
                strcpy(s, "Key");
            else
                strcpy(s, "");
            break;
        case r06_paint:
                strcpy(s, "Chart");
            break;
        case r06_computerRoomDoor:
                strcpy(s, "Door");
            break;
        case r06_window:
                strcpy(s, "Window");
            break;
        case r06_scienceRoomDoor:
                strcpy(s, "Door");
            break;
        case r06_board:
                strcpy(s, "Plank");
            break;
        case r06_schoolBathDoor:
                strcpy(s, "Door");
            break;
        case r06_lockerDoor:
                strcpy(s, "Door");
            break;
        case r06_orla:
                strcpy(s, "Fringe");
            break;
        case r06_bench:
                strcpy(s, "Bank");
            break;
        case r06_PEOfficeRoom:
                strcpy(s, "Door");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r06_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r06_door:
            return GO;
            break;
        case r06_maintLockerLock:
            if (!is_game_flag(MAINT_LOCKER_DOOR_OPEN_FLAG))
            {
                return LOOK;
                break;
            }
        case r06_maintLockerDoor:
            if (is_game_flag(MAINT_LOCKER_DOOR_OPEN_FLAG))
                return GO;
            else
                return OPEN;
            break;
        case r06_maintLockerBathMat:
            return LOOK;
            break;
        case r06_maintLockerKey:
            return TAKE;
            break;
        case r06_paint:
            return LOOK;
            break;
        case r06_computerRoomDoor:
            return GO;
            break;
        case r06_window:
            return LOOK;
            break;
        case r06_scienceRoomDoor:
            return GO;
            break;
        case r06_board:
            return LOOK;
            break;
        case r06_schoolBathDoor:
            return GO;
            break;
        case r06_lockerDoor:
            return GO;
            break;
        case r06_orla:
            return LOOK;
            break;
        case r06_bench:
            return LOOK;
            break;
        case r06_PEOfficeRoom:
            return GO;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r06_get_object_info(uint8_t numObject)
{
    if (numObject < R06_ROOM_NUM_OBJS)
        return &r06_object[numObject];
    else
        return NULL;
}

//function to init room
void r06_room_init()
{
    change_player_dir(DIR_RIGHT);

    if (is_game_flag(COMPUTER_DOOR_OPEN_FLAG))
    {
        start_script(R06_COMPUTER_DOOR_CLOSE_SCRIPT);
    }
    else if (is_game_flag(SCIENCE_DOOR_OPEN_FLAG))
    {
        start_script(R06_SCIENCE_DOOR_CLOSE_SCRIPT);
    }
    else if (is_game_flag(BATHROOM_DOOR_OPEN_FLAG))
    {
        start_script(R06_BATHROOM_DOOR_CLOSE_SCRIPT);
    }
    else if (is_game_flag(LOCKER_DOOR_OPEN_FLAG))
    {
        start_script(R06_LOCKER_DOOR_CLOSE_SCRIPT);
    }
    else if (is_game_flag(PEOFFICE_DOOR_OPEN_FLAG))
    {
        start_script(R06_PEOFFICE_DOOR_CLOSE_SCRIPT);
    }
    
    game_fade_in();
}

//global funcion to update room
void r06_room_update()
{
    //update room objects
    r06_update_room_objects();

    //update dialog line selection
    r06_update_dialog_selection();
    
    //update room script
    r06_update_room_script();
}

//update room objects
void r06_update_room_objects()
{
    r06_object[R06_BATHMATIN_OBJ_ID].active     = is_game_flag(BATH_MAT_IN_DOOR_FLAG);
    r06_object[R06_BATHMATOUT_OBJ_ID].active    = is_game_flag(BATH_MAT_OUT_DOOR_FLAG);

    if (is_game_flag(MAINT_LOCKER_DOOR_OPEN_FLAG))
        r06_object[R06_BATHMATOUT_OBJ_ID].objId = r06d_objBathMatFull;
    else
        r06_object[R06_BATHMATOUT_OBJ_ID].objId = r06d_objBathMatOut;
    
    r06_object[R06_KEY_OBJ_ID].active = is_game_flag(BATH_MAT_OUT_DOOR_FLAG) && is_game_flag(KEY_ON_BATH_MAT_FLAG);

    r06_object[R06_MAINTDOOROPEN_OBJ_ID].active = is_game_flag(MAINT_LOCKER_DOOR_OPEN_FLAG) && is_game_flag(MAINT_LOCKER_LIGHT_ON_FLAG);
    r06_object[R06_MAINTDOOROPENLIGHT_OBJ_ID].active = is_game_flag(MAINT_LOCKER_DOOR_OPEN_FLAG) && !is_game_flag(MAINT_LOCKER_LIGHT_ON_FLAG);

    //doors
    r06_object[R06_COMPUTER_DOOR_OBJ_ID].active = is_game_flag(COMPUTER_DOOR_OPEN_FLAG);
    r06_object[R06_SCIENCE_DOOR_OBJ_ID].active = is_game_flag(SCIENCE_DOOR_OPEN_FLAG);
    r06_object[R06_BATHROOM_DOOR_OBJ_ID].active = is_game_flag(BATHROOM_DOOR_OPEN_FLAG);
    r06_object[R06_LOCKER_DOOR_OBJ_ID].active = is_game_flag(LOCKER_DOOR_OPEN_FLAG);
    r06_object[R06_PE_OFFICE_DOOR_OBJ_ID].active = is_game_flag(PEOFFICE_DOOR_OPEN_FLAG);
}

//update dialog selection
void r06_update_dialog_selection()
{

}

//update room script
void r06_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r06_door:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("The door of the institute");
                                break;
                            default:
                                script_say("The sadness that makes me see her in the morning and the joy of seeing her when I leave");
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
                            default:
                                change_room_pos(STREET_ROOM_NUM, 59, 115);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r06_maintLockerLock:
                if (!is_game_flag(MAINT_LOCKER_DOOR_OPEN_FLAG))
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    if (!is_game_flag(KEY_ON_BATH_MAT_FLAG))
                                        script_say("I see through the lock that the key is stuck inside.");
                                    else
                                        script_say("It seems that the key has fallen onto the mat on the other side");
                                    break;
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                        case USE_WITH:
                            switch(roomScript.invObject)
                            {
                                case id_knife:
                                    switch (roomScript.step)
                                    {
                                        case 0:
                                            begin_script();
                                            if (!is_game_flag(BATH_MAT_IN_DOOR_FLAG))
                                            {
                                                if (is_game_flag(BATH_MAT_OUT_DOOR_FLAG))
                                                {
                                                    script_say("The mat is too far out and doesn't reach where the key can fall.");
                                                    end_script();
                                                }
                                                else
                                                {
                                                    script_say("If I put the scalpel through the lock it will fall to the floor and I won't be able to get the key back.");
                                                    end_script();
                                                }
                                            }
                                            else if(is_game_flag(KEY_ON_BATH_MAT_FLAG))
                                            {
                                                script_say("The key has already fallen on the mat");
                                                end_script();
                                            }
                                            else
                                                script_move_player_to_target();
                                            break;
                                        case 1:
                                            script_play_sound(sd_doorLockerOpen);
                                        break;
                                        case 2:
                                            script_player_take_state();
                                            break;
                                        case 3:
                                            script_play_sound(sd_keyFall);
                                        break;
                                        case 4:
                                            set_game_flag(KEY_ON_BATH_MAT_FLAG);
                                            script_say("Eureka! The key has fallen on the mat");
                                        default:
                                            end_script();
                                            break;
                                    }
                                break;
                                case id_key:
                                    switch (roomScript.step)
                                    {
                                        case 0:
                                            begin_script();
                                            script_move_player_to_target();
                                            break;
                                        case 1:
                                            play_sound(sd_doorLockerOpen);
                                            roomScript.step++;
                                        break;
                                        case 2:
                                            script_player_take_state();
                                            break;
                                        case 3:
                                            set_game_flag(MAINT_LOCKER_DOOR_UNLOCKED_FLAG);
                                            script_remove_inv_object(id_key);
                                        default:
                                            end_script();
                                            break;
                                    }
                                break;
                                case id_spatula:
                                    switch (roomScript.step)
                                    {
                                        case 0:
                                            begin_script();
                                            script_say("The spatula is too big and won't fit through the keyhole");
                                        break;
                                        default:
                                            end_script();
                                        break;
                                    }
                                break;
                            }
                        break;
                    }
                    break;
                }
            case r06_maintLockerDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It's the maintenance closet door.");
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
                            case 1:
                                if (is_game_flag(MAINT_LOCKER_DOOR_UNLOCKED_FLAG) && is_game_flag(MAINT_LOCKER_DOOR_OPEN_FLAG))
                                    change_room(MAINT_LOCKER_ROOM_NUM);
                                else
                                    script_say("The door is closed");
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
                            default:
                                if (!is_game_flag(GOT_KEY_FLAG))
                                    script_say("The door is closed y no tengo la llave");
                                else if (!is_game_flag(MAINT_LOCKER_DOOR_UNLOCKED_FLAG))
                                    script_say("The door is closed con llave");
                                else if (is_game_flag(MAINT_LOCKER_DOOR_OPEN_FLAG))
                                    script_say("It is now open");
                                else
                                {
                                    play_sound(sd_doorOpen);
                                    set_game_flag(MAINT_LOCKER_DOOR_OPEN_FLAG);
                                }
                                end_script();
                                break;
                        }
                    break;
                    case CLOSE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player_to_target();
                                break;
                            default:
                                if (!is_game_flag(MAINT_LOCKER_DOOR_OPEN_FLAG))
                                    script_say("It is already closed");
                                else
                                {
                                    clear_game_flag(MAINT_LOCKER_DOOR_OPEN_FLAG);
                                    play_sound(sd_doorClose);
                                }
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch (roomScript.invObject)
                        {
                            case id_bathMat:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_move_player_to_target();
                                        break;
                                    case 1:
                                        r06_object[R06_BATHMATOUT_OBJ_ID].active = true;
                                        set_game_flag(BATH_MAT_OUT_DOOR_FLAG);
                                        script_remove_inv_object(id_bathMat);
                                        break;
                                    case 2:
                                        script_player_take_state();
                                        break;
                                    default:
                                        end_script();
                                        break;
                                }
                            break;
                            case id_califications:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_say("They are my notes");
                                    break;
                                    default:
                                        script_say("I wouldn't want to damage them");
                                        end_script();
                                    break;
                                }
                            break;
                            case id_sheet:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_say("It's too thin");
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                            case id_answers:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_say("These answers are too valuable to use here!");
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                            case id_photocopy:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_say("It's too valuable to use here!");
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                        }
                    break;
                }
                break;
            case r06_maintLockerBathMat:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("I put the mat under the door");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case MOVE:
                         switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (is_game_flag(GOT_KEY_FLAG))
                                {
                                    script_say("It's fine where it is ");
                                    end_script();
                                }
                                else
                                    script_move_player_to_target();
                                break;
                            case 1:
                                toggle_game_flag(BATH_MAT_IN_DOOR_FLAG);
                                toggle_game_flag(BATH_MAT_OUT_DOOR_FLAG);
                                r06_object[R06_BATHMATIN_OBJ_ID].active = is_game_flag(BATH_MAT_IN_DOOR_FLAG);
                                r06_object[R06_BATHMATOUT_OBJ_ID].active = is_game_flag(BATH_MAT_OUT_DOOR_FLAG);
                                end_script();
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;
            case r06_maintLockerKey:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("The key to the maintenance warehouse door rests on the mat");
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
                                clear_game_flag(KEY_ON_BATH_MAT_FLAG);
                                script_take_object(&r06_object[R06_KEY_OBJ_ID].active, GOT_KEY_FLAG, id_key);
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;        
            case r06_paint:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A picture of a photograph of the institute surrounded by trees and gardens");
                                break;
                            default:
                                script_say("Now everything is cement");
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r06_computerRoomDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It is the door to the computer classroom");
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
                                set_game_flag(COMPUTER_DOOR_OPEN_FLAG);
                                roomScript.hsY = get_player_pos_y();
                                script_player_take_state();
                            break;
                            default:
                                change_room(COMPUTER_ROOM_NUM);
                                end_script();
                            break;
                        }
                    break;

                }
                break;            
            case r06_window:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It is the window of the computer classroom");
                                break;
                            default:
                                script_say("This way you can see if there is a computer available");
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r06_scienceRoomDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It is the door to the science classroom");
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
                                set_game_flag(SCIENCE_DOOR_OPEN_FLAG);
                                roomScript.hsY = get_player_pos_y();
                                script_player_take_state();
                            break;
                            default:
                                change_room(SCIENCE_ROOM_NUM);
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r06_board:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                switch (get_game_var(BULLETIN_BOARD_VAR))
                                {
                                    case 0:
                                        script_say("The institute notice board");
                                        break;
                                    case 1:
                                        script_say("Private mathematics classes are given. Contact 555-5555");
                                        break;
                                    case 2:
                                        script_say("Rock music group looking for solo guitarist with own equipment");
                                        break;
                                    case 3:
                                        script_say("Vote Carlos for class representative. When there is only one candidate, solo hay una elecci¢n");
                                        break;
                                }
                                break;
                            default:
                                if (get_game_var(BULLETIN_BOARD_VAR) < 3)
                                    inc_game_var(BULLETIN_BOARD_VAR);
                                else
                                    set_game_var(BULLETIN_BOARD_VAR, 0);
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r06_schoolBathDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It is the door that leads to the bathrooms");
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
                                set_game_flag(BATHROOM_DOOR_OPEN_FLAG);
                                roomScript.hsY = get_player_pos_y();
                                script_player_take_state();
                            break;
                            default:
                                change_room(SCHOOL_BATH_ROOM_NUM);
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r06_lockerDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It's the door that goes to the locker room");
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
                                roomScript.hsY = get_player_pos_y();
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
                                change_room(LOCKER_ROOM_NUM);
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r06_orla:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It is the border of the generation of teachers of '57");
                                break;
                            default:
                                script_say("A herd of dinosaurs is what they are...");
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r06_bench:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("I don't think I've ever sat on this bench.");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r06_PEOfficeRoom:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It is the door that leads to the physical education teacher's office");
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
                                set_game_flag(PEOFFICE_DOOR_OPEN_FLAG);
                                roomScript.hsY = get_player_pos_y();
                                script_player_take_state();
                            break;
                            default:
                                change_room(PE_OFFICE_ROOM_NUM);
                                end_script();
                            break;
                        }
                    break;
                }
                break;
                case R06_COMPUTER_DOOR_CLOSE_SCRIPT:
                    switch(roomScript.step)
                    {
                        case 0:
                            script_wait(1);
                        break;
                        case 1:
                            roomScript.hsY = get_player_pos_y();
                            script_player_take_state();
                        break;
                        case 2:
                            play_sound_rnd(sd_doorClose);
                            clear_game_flag(COMPUTER_DOOR_OPEN_FLAG);
                            roomScript.step++;
                        break;
                        default:
                            end_script();
                        break;
                    }
                break;
                case R06_SCIENCE_DOOR_CLOSE_SCRIPT:
                    switch(roomScript.step)
                    {
                        case 0:
                            script_wait(1);
                        break;
                        case 1:
                            roomScript.hsY = get_player_pos_y();
                            script_player_take_state();
                        break;
                        case 2:
                            play_sound_rnd(sd_doorClose);
                            clear_game_flag(SCIENCE_DOOR_OPEN_FLAG);
                            roomScript.step++;
                        break;
                        default:
                            end_script();
                        break;
                    }
                break;
                case R06_BATHROOM_DOOR_CLOSE_SCRIPT:
                    switch(roomScript.step)
                    {
                        case 0:
                            script_wait(1);
                        break;
                        case 1:
                            roomScript.hsY = get_player_pos_y();
                            script_player_take_state();
                        break;
                        case 2:
                            play_sound_rnd(sd_doorClose);
                            clear_game_flag(BATHROOM_DOOR_OPEN_FLAG);
                            roomScript.step++;
                        break;
                        default:
                            end_script();
                        break;
                    }
                break;
                case R06_LOCKER_DOOR_CLOSE_SCRIPT:
                    switch(roomScript.step)
                    {
                        case 0:
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
                            end_script();
                        break;
                    }
                break;
                case R06_PEOFFICE_DOOR_CLOSE_SCRIPT:
                    switch(roomScript.step)
                    {
                        case 0:
                            script_wait(1);
                        break;
                        case 1:
                            roomScript.hsY = get_player_pos_y();
                            script_player_take_state();
                        break;
                        case 2:
                            play_sound_rnd(sd_doorClose);
                            clear_game_flag(PEOFFICE_DOOR_OPEN_FLAG);
                            roomScript.step++;
                        break;
                        default:
                            end_script();
                        break;
                    }
                break;
        }
    }
}
