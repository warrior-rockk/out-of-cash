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
                strcpy(s, "Gate");
            break;
        case r00_sign:
                strcpy(s, "Event Image");
            break;
        case r00_stationery:
                strcpy(s, "Papeler¡a");
            break;
        case r00_school:
                strcpy(s, "Institute");
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
                                script_say("Zurraspa Producciones presents:");
                            break;
                            case 2:
                                script_say("\"Repeat Offenders\" in concert");
                                break;
                            case 3:
                                script_say("Presenting their £last live album");
                                break;
                            case 4:
                                script_say("Entrance fee: 5000 pesetas");
                                break;    
                            case 5:
                                change_player_dir(DIR_RIGHT);
                                script_say("I have to get the money anyway");
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
                                script_say("That's where you go to thetrash!");
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
                                script_say("Sohe goes to my high school");
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
                                script_say("My Trusted Computer Store");
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
                                script_say(" I already spent all my money on the Pentium, I already spent all my money on the Pentium");
                                break;
                            case 1:
                                script_say(" everything I get I need to go to the concert");
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
                        script_say("Do I do you good?");
                    break;
                    case 5:
                        script_move_player(80, 120);
                    break;
                    case 6:
                        change_player_dir(DIR_BACK);
                        script_say("-Concert of \"Repeat Offenders\"!");
                    break;
                    case 7:
                        script_say("-Mola!");
                    break;
                    case 8:
                        script_say("Introducing New Album");
                    break;
                    case 9:
                        script_say("­-Mola!!");
                    break;
                    case 10:
                        script_say("5000 peels the entrance");
                    break;
                    case 11:
                        change_player_dir(DIR_RIGHT);
                        script_say("-It's not cool!");
                    break;
                    case 12:
                        script_say("¨5000 peels the entrance? Yo no tengo tanto dinero");
                    break;
                    case 13:
                        script_wait(2);
                    break;
                    case 14:
                        script_say(" not so much and not so little... I'm penniless!, not so much and not so little... I'm penniless!");
                    break;
                    case 15:
                        script_say("But I have to go to that concert at all costs");
                    break;
                    case 16:
                        script_say("­I have to get the money anyway!");
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
