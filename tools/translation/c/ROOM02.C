/*
=========================================================
 Room Number:   02
 Room Name:     02_corridor
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room02.h"

//Funtion to return the name of hotspot by color code
void r02_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r02_mirror:
                strcpy(s, "Mirror");
            break;
        case r02_bathDoor:
                strcpy(s, "Door");
            break;
        case r02_flowers:
                strcpy(s, "Flowers");
            break;
        case r02_elephant:
                strcpy(s, "Figure");
            break;
        case r02_kitchen:
                strcpy(s, "Kitchen");
            break;
        case r02_door:
                strcpy(s, "Door");
            break;
        case r02_picture:
                strcpy(s, "Picture");
            break;
        case r02_bedRoomDoor:
                strcpy(s, "Room");
            break;
        case r02_street:
                strcpy(s, "Street");
            break;
        case r02_lamp:
                strcpy(s, "Lamp");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r02_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r02_mirror:
            return LOOK;
            break;
        case r02_bathDoor:
            if (is_game_flag(BATH_DOOR_OPEN_FLAG))
                return GO;
            else
                return OPEN;
            break;
        case r02_flowers:
            return LOOK;
            break;
        case r02_elephant:
            return LOOK;
            break;
        case r02_kitchen:
            return LOOK;
            break;
        case r02_door:
            return LOOK;
            break;
        case r02_picture:
            return LOOK;
            break;
        case r02_bedRoomDoor:
            return LOOK;
            break;
        case r02_street:
            return LOOK;
            break;
        case r02_lamp:
            return LOOK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r02_get_object_info(uint8_t numObject)
{
    if (numObject < R02_ROOM_NUM_OBJS)
        return &r02_object[numObject];
    else
        return NULL;
}

//function to init room
void r02_room_init()
{
    r02_object[R02_DOORFRAME_OBJ_ID].active = false;
    
    game_fade_in();
}

//global funcion to update room
void r02_room_update()
{
    //update room objects
    r02_update_room_objects();

    //update dialog line selection
    r02_update_dialog_selection();
    
    //update room script
    r02_update_room_script();
}

//update room objects
void r02_update_room_objects()
{
    r02_object[R02_BATHDOOR_OBJ_ID].active = is_game_flag(BATH_DOOR_OPEN_FLAG);
}

//update dialog selection
void r02_update_dialog_selection()
{

}

//update room script
void r02_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r02_mirror:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (!is_game_flag(CORRIDOR_MIRROR_MSG_FLAG))
                                {
                                    set_game_flag(CORRIDOR_MIRROR_MSG_FLAG);
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
            case r02_bathDoor:
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
                                change_room(BATH_ROOM_NUM);
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
                                script_say("It´s the door that leads to the bathroom");
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
                                if (is_game_flag(BATH_DOOR_OPEN_FLAG))
                                {
                                    script_say("Already open");
                                    end_script();
                                }
                                else                                
                                    script_move_player(153, 53);
                                break;
                            case 1:
                                script_player_take_state();
                                play_sound(sd_doorOpen);
                                set_game_flag(BATH_DOOR_OPEN_FLAG);
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
                                    script_move_player(153, 53);
                                break;
                            case 1:
                                script_player_take_state();
                                play_sound(sd_doorClose);
                                clear_game_flag(BATH_DOOR_OPEN_FLAG);
                            break;
                            default:
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r02_flowers:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A vase with flowers whose fragrance existed a long time ago");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r02_elephant:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It´s a figure of an elephant");
                                break;
                            case 1:
                                begin_script();
                                script_say("My mother always said that having an elephant with its trunk facing the entrance, attracts money");
                                break;
                            case 2:
                                script_wait(10);
                                break;
                            case 3:
                                begin_script();
                                script_say("And here you have me... With no money for the concert...");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r02_kitchen:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("This is the kitchen");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case GO:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player(221, 117);
                            break;
                            case 1:
                                r02_object[R02_DOORFRAME_OBJ_ID].active = true;
                                script_move_player_no_clip(250, 117);
                            break;
                            case 2:
                                change_room(KITCHEN_ROOM_NUM);
                                end_script();
                            break;
                        }
                        break;                    
                }
                break;            
            case r02_door:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It may seem strange, but I've been in this house my whole life and I don't know where that door leads");
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
                                script_say("Cannot open. It has always been closed");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r02_picture:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("This painting is the only thing of value in the whole house");
                                break;
                            case 1:
                                script_say("I think my father painted it");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r02_bedRoomDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("The door to the bedroom");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case GO:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player_to_target();
                                break;
                            case 1:
                                change_room_pos(BEDROOM_ROOM_NUM, 201, 136);
                                end_script();
                                break;
                        }
                        break;                    
                }
                break;            
            case r02_street:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("The door to the street");
                                break;
                            case 1:
                                script_say("­­To freedom!!");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case GO:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player_to_target();
                                break;
                            case 1:
                                if (is_game_flag(FATHER_SAY_MONEY_FLAG))
                                    script_move_player_no_clip(roomScript.hsX, 230);
                                else
                                {
                                    script_say("I should think about how to get the concert money before I leave home");
                                    end_script();
                                }
                                break;
                            default:
                                change_room_pos(STREET_ROOM_NUM, 160, 100);
                                end_script();
                            break;
                        }
                        break;                    
                }
                break;            
            case r02_lamp:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A lamp to create a cozy corner");
                                break;
                            case 1:
                                script_say("We never turn it on");
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