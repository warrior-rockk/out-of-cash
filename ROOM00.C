/*
=========================================================
 Room Number:   00
 Room Name:     00_street
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room00.h"

//Funtion to return the name of hotspot by color code
void r00_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r00_door:
                strcpy(s, "Door");
            break;
        case r00_sign:
                strcpy(s, "Poster");
            break;
        case r00_stationery:
                strcpy(s, "Stationery");
            break;
        case r00_school:
                strcpy(s, "High School");
            break;
        case r00_shop:
                strcpy(s, "Store");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r00_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r00_door:
            return GO;
            break;
        case r00_sign:
            return LOOK;
            break;
        case r00_stationery:
            return GO;
            break;
        case r00_school:
            return GO;
            break;
        case r00_shop:
            return LOOK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r00_get_object_info(uint8_t numObject)
{
    if (numObject < R00_ROOM_NUM_OBJS)
        return &r00_object[numObject];
    else
        return NULL;
}

//function to init room
void r00_room_init()
{
    if (is_game_flag(INTRO_FLAG))
    {
        start_script(R00_INTRO_SCRIPT);
    }
    else if (get_last_room() == SCHOOL_ROOM_NUM)
        change_player_dir(DIR_RIGHT);
    else
        change_player_dir(DIR_LEFT);

    game_fade_in();
}

//global funcion to update room
void r00_room_update()
{
    //update room objects
    r00_update_room_objects();

    //update dialog line selection
    r00_update_dialog_selection();
    
    //update room script
    r00_update_room_script();
}

//update room objects
void r00_update_room_objects()
{

}

//update dialog selection
void r00_update_dialog_selection()
{

}

//update room script
void r00_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r00_door:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It's the front door to my house");
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
                            default:
                                change_room(CORRIDOR_ROOM_NUM);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r00_sign:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player(76, 125);
                            break;
                            case 1:
                                change_player_dir(DIR_BACK);
                                script_say("Zurraspa Productions presents:");
                            break;
                            case 2:
                                script_say("\"The Repeat Offenders\" in concert");
                                break;
                            case 3:
                                script_say("Introducing their last live album");
                                break;
                            case 4:
                                script_say("Entrance fee: 30 bucks");
                                break;    
                            case 5:
                                change_player_dir(DIR_RIGHT);
                                script_say("I have to get the money somehow");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r00_stationery:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("That's where you go to stationery");
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
                                change_room(STATIONERY_ROOM_NUM);
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r00_school:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("That's where you to my high school");
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
                                change_room(SCHOOL_ROOM_NUM);
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r00_shop:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("My trusted computer store");
                                break;
                            case 1:
                                script_say("Here I buy my Pentium 100 for a good price");
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
                                script_say("Nah, I already spent all my money on the Pentium");
                                break;
                            case 1:
                                script_say("Also I need everything I get to go to the concert");
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case R00_INTRO_SCRIPT:
                switch (roomScript.step)
                {
                    case 0:
                        begin_script();
                        script_wait(10);
                    break;
                    case 1:
                        script_move_player(160, 120);
                    break;
                    case 2:
                        script_wait(10);
                    break;
                    case 3:
                        play_player_animation(ANIM_PLY_SURPRISE);
                        script_wait(10);
                    break;
                    case 4:
                        script_say("Did I read correctly?");
                    break;
                    case 5:
                        script_move_player(80, 120);
                    break;
                    case 6:
                        change_player_dir(DIR_BACK);
                        script_say("Concert of \"The Repeat Offenders\"!");
                    break;
                    case 7:
                        script_say("Cool!");
                    break;
                    case 8:
                        script_say("Introducing new album");
                    break;
                    case 9:
                        script_say("Cool!!");
                    break;
                    case 10:
                        script_say("30 bucks for ticket");
                    break;
                    case 11:
                        change_player_dir(DIR_RIGHT);
                        script_say("Not cool!");
                    break;
                    case 12:
                        script_say("30 bucks for ticket? I don't have that much money");
                    break;
                    case 13:
                        script_wait(2);
                    break;
                    case 14:
                        script_say("Well, not so much and not so little... I'm out of cash!");
                    break;
                    case 15:
                        script_say("But I have to go to that concert at all costs");
                    break;
                    case 16:
                        script_say("I have to get the money somehow!");
                    break;
                    default:
                        clear_game_flag(INTRO_FLAG);
                        end_script();
                    break;
                }
            break;
        }
    }
}
