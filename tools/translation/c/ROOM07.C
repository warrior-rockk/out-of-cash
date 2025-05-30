/*
=========================================================
 Room Number:   07
 Room Name:     07_scienceRoom
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room07.h"

//Funtion to return the name of hotspot by color code
void r07_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r07_door:
                strcpy(s, "Door");
            break;
        case r07_blackBoard:
                strcpy(s, "Blackboard");
            break;
        case r07_notes:
                strcpy(s, "Notes");
            break;
        case r07_brain:
            if (!is_game_flag(GOT_BRAIN_FLAG))
                strcpy(s, "Brain");
            else
                strcpy(s, "");
            break;
        case r07_washer1:
                strcpy(s, "Sink");
            break;
        case r07_testTube:
                strcpy(s, "Test tubes");
            break;
        case r07_sheets:
                strcpy(s, "Sheets");
            break;
        case r07_washer2:
                strcpy(s, "Sink");
            break;
        case r07_glass:
                strcpy(s, "Cup");
            break;
        case r07_knife:
            if (!is_game_flag(GOT_KNIFE_FLAG))
                strcpy(s, "Scalpel");
            else
                strcpy(s, "");
            break;
        case r07_labMaterial:
                strcpy(s, "Laboratory material");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r07_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r07_door:
            return GO;
            break;
        case r07_blackBoard:
            return LOOK;
            break;
        case r07_notes:
            return LOOK;
            break;
        case r07_brain:
            return LOOK;
            break;
        case r07_washer1:
            return LOOK;
            break;
        case r07_testTube:
            return LOOK;
            break;
        case r07_sheets:
            return LOOK;
            break;
        case r07_washer2:
            return LOOK;
            break;
        case r07_glass:
            return LOOK;
            break;
        case r07_knife:
            return LOOK;
            break;
        case r07_labMaterial:
            return LOOK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r07_get_object_info(uint8_t numObject)
{
    if (numObject < R07_ROOM_NUM_OBJS)
        return &r07_object[numObject];
    else
        return NULL;
}

//function to init room
void r07_room_init()
{
    change_player_dir(DIR_RIGHT);

    if (is_game_flag(SCIENCE_DOOR_OPEN_FLAG))
        start_script(R07_DOOR_CLOSE_SCRIPT);
        
    game_fade_in();
}

//global funcion to update room
void r07_room_update()
{
    //update room objects
    r07_update_room_objects();

    //update dialog line selection
    r07_update_dialog_selection();
    
    //update room script
    r07_update_room_script();
}

//update room objects
void r07_update_room_objects()
{
    r07_object[R07_KNIFE_OBJ_ID].active = !is_game_flag(GOT_KNIFE_FLAG);
    r07_object[R07_BRAIN_OBJ_ID].active = !is_game_flag(GOT_BRAIN_FLAG);
    r07_object[R07_DOOR_OBJ_ID].active  =  is_game_flag(SCIENCE_DOOR_OPEN_FLAG);
}

//update dialog selection
void r07_update_dialog_selection()
{

}

//update room script
void r07_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r07_door:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It´s the door that leads to the high school hallway");
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
                                change_room_pos(SCHOOL_ROOM_NUM, 428, 84);
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r07_blackBoard:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("I think that in that formula they have forgotten that they carry one");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_notes:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Notes sobre alguna clase de ciencias que no logro comprender");
                                break;
                            default:
                                script_say("At least the handwriting is nice");
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_brain:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A human brain floating in formaldehyde");
                                break;
                            case 1:
                                script_say("Sad analogy of the effeversity of thought");
                                break;
                            case 2:
                                script_wait(10);
                                break;
                            default:
                                script_say("I readed it on a napkin");
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
                                script_take_object(&r07_object[R07_BRAIN_OBJ_ID].active, GOT_BRAIN_FLAG, id_brain);
                                break;
                            case 2:
                                script_say("Buajj....");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r07_washer1:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("You can smell yet the last experiment they poured into the drain");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_testTube:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("I have always been fascinated by laboratory material");
                                break;
                            default:
                                script_say("I think it comes from the frustration that my parents would not let me play with Quimicefa");
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_sheets:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Sheets y hojas llenadas de garabatos que significaran algo para alguien");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_washer2:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("This sink is pristine");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_glass:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A laboratory flask for mixing");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r07_knife:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("This scalpel is very sharp");
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
                                script_move_player(231, 110);
                                break;
                            case 1:
                                script_take_object(&r07_object[R07_KNIFE_OBJ_ID].active, GOT_KNIFE_FLAG, id_knife);
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r07_labMaterial:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Miscellaneous laboratory material with no apparent interest");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
             case R07_DOOR_CLOSE_SCRIPT:
                switch(roomScript.step)
                {
                    case 0:
                        change_player_dir(DIR_LEFT);
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
                        change_player_dir(DIR_RIGHT);
                        end_script();
                    break;
                }
            break;
        }
    }
}
