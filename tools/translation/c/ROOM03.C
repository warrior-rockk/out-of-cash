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
                strcpy(s, "Closet");
            break;
        case r03_washbowl:
                strcpy(s, "Sink");
            break;
        case r03_mirror:
                strcpy(s, "Mirror");
            break;
        case r03_towel:
                strcpy(s, "Towel");
            break;
        case r03_bathMat:
            if (r03_object[R03_BATHMAT_OBJ_ID].active)
                strcpy(s, "Bath Mat");
            else
                strcpy(s, "");
            break;
        case r03_switch:
                strcpy(s, "Switch");
            break;
        case r03_door:
                strcpy(s, "Door");
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
        case r03_gel:
            if (r03_object[R03_GEL_OBJ_ID].active)
            {
                return LOOK;
                break;
            }
        case r03_closet:
            if (is_game_flag(BATH_CLOSET_OPEN_FLAG))
                return GO;
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
        case r03_bathMat:
            return LOOK;
            break;
        case r03_switch:
            return USE;
            break;
        case r03_door:
            if (is_game_flag(BATH_DOOR_OPEN_FLAG))
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
    set_room_light_off(is_game_flag(BATH_LIGHT_OFF_FLAG));
        
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
    r03_object[R03_GEL_OBJ_ID].active = is_game_flag(BATH_CLOSET_OPEN_FLAG) && !is_game_flag(GOT_GEL_FLAG) && !is_game_flag(BATH_LIGHT_OFF_FLAG);
    r03_object[R03_BATHCLOSETOPEN_OBJ_ID].active = is_game_flag(BATH_CLOSET_OPEN_FLAG) && !is_game_flag(BATH_LIGHT_OFF_FLAG);
    r03_object[R03_BATHDOOROPEN_OBJ_ID].active = is_game_flag(BATH_DOOR_OPEN_FLAG);
    r03_object[R03_BATHMAT_OBJ_ID].active = !is_game_flag(GOT_BATH_MAT_FLAG) && !is_game_flag(BATH_LIGHT_OFF_FLAG);
    r03_object[R03_BATH_OBJ_ID].active = !is_game_flag(BATH_LIGHT_OFF_FLAG);
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
                if (is_game_flag(BATH_CLOSET_OPEN_FLAG) && !is_game_flag(GOT_GEL_FLAG))
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("A bottle of shower gel");
                                    break;
                                case 1:
                                    script_say("It looks very viscous...");
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
                                    script_take_object(&r03_object[R03_GEL_OBJ_ID].active, GOT_GEL_FLAG, id_gel);
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
                                script_say("The classic closet of the bathroom where you end up accumulating hundreds of products");
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
                                if (is_game_flag(BATH_CLOSET_OPEN_FLAG))
                                {
                                    script_say("Already open");
                                    end_script();
                                }
                                else                                
                                    script_move_player(148, 71);
                                break;
                            case 1:
                                change_player_dir(DIR_RIGHT);
                                script_play_sound(sd_closetOpen);
                            break;
                            case 2:
                                script_player_take_state();
                            break;
                            case 3:
                                set_game_flag(BATH_CLOSET_OPEN_FLAG);
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
                                if (!is_game_flag(BATH_CLOSET_OPEN_FLAG))
                                {
                                    script_say("Already closed");
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
                                clear_game_flag(BATH_CLOSET_OPEN_FLAG);
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
                                script_say("Don't forget to wash your hands before returning to work...");
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
                                script_say("I don't have dirty hands");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch (roomScript.invObject)
                        {
                            case id_oat:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_say("You should not wet oat grains with water");
                                        break;
                                    default:
                                        script_say("You should use something more viscous");
                                        end_script();
                                        break;
                                }
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
                                if (!is_game_flag(BATH_MIRROR_MSG_FLAG))
                                {
                                    set_game_flag(BATH_MIRROR_MSG_FLAG);
                                    inc_game_var(MIRROR_MSG_COUNT_VAR);
                                }
                                switch (get_game_var(MIRROR_MSG_COUNT_VAR))
                                {
                                    case 1:
                                        script_say("The game programmer has been so lazy as not to program the reflexes...");
                                        break;
                                    case 2:
                                        script_say("Another mirror with unprogrammed reflection...");
                                        break;
                                    case 3:
                                        script_say("With how little it costs to program the reflexes...");
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
            case r03_towel:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("This towel has been in the family for many years");
                                break;
                            case 1:
                                script_say("We should think about washing it...");
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
                                script_say("The mat to dry your feet after the shower");
                                break;
                            case 1:
                                script_say("It's also a nest of microbes and mold");
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
                                script_take_object(&r03_object[R03_BATHMAT_OBJ_ID].active, GOT_BATH_MAT_FLAG, id_bathMat);
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
                                script_say("There is something pleasurable about the sound of an actuating switch being");
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
                                toggle_game_flag(BATH_LIGHT_OFF_FLAG);
                                set_room_light_off(is_game_flag(BATH_LIGHT_OFF_FLAG));
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
                                if (!is_game_flag(BATH_DOOR_OPEN_FLAG))
                                {
                                    script_say("The door is closed");
                                    end_script();
                                }
                                else
                                    script_move_player_to_target();
                                break;
                            case 1:
                                change_room_pos(CORRIDOR_ROOM_NUM, 154, 46);
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
                                script_say("The bathroom door leading to the corridor");
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
                                if (is_game_flag(BATH_DOOR_OPEN_FLAG))
                                {
                                    script_say("Already open");
                                    end_script();
                                }
                                else                                
                                    script_move_player_to_target();
                                break;
                            case 1:
                                set_game_flag(BATH_DOOR_OPEN_FLAG);
                                play_sound(sd_doorOpen);
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
                                if (!is_game_flag(BATH_DOOR_OPEN_FLAG))
                                {
                                    script_say("Already closed");
                                    end_script();
                                }
                                else                                
                                    script_move_player_to_target();

                                break;
                            case 1:
                                clear_game_flag(BATH_DOOR_OPEN_FLAG);
                                play_sound(sd_doorClose);
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
