/*
=========================================================
 Room Number:   12
 Room Name:     12_schoolBath
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room12.h"

//Funtion to return the name of hotspot by color code
void r12_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r12_door:
                strcpy(s, "Door");
            break;
        case r12_mirror:
                strcpy(s, "Mirror");
            break;
        case r12_towelDispenser:
                strcpy(s, "Paper dispenser");
            break;
        case r12_washbowl:
                strcpy(s, "Sink");
            break;
        case r12_closedDoor:
                strcpy(s, "Door");
            break;
        case r12_hole:
                strcpy(s, "Hole");
            break;
        case r12_holeDoor:
                strcpy(s, "Door");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r12_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r12_door:
            return GO;
            break;
        case r12_mirror:
            return LOOK;
            break;
        case r12_towelDispenser:
            return LOOK;
            break;
        case r12_washbowl:
            return LOOK;
            break;
        case r12_closedDoor:
            return OPEN;
            break;
        case r12_hole:
            return LOOK;
            break;
        case r12_holeDoor:
            return OPEN;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r12_get_object_info(uint8_t numObject)
{
    if (numObject < R12_ROOM_NUM_OBJS)
        return &r12_object[numObject];
    else
        return NULL;
}

//function to init room
void r12_room_init()
{
    r12_dialogActor.talking = false;

    if (is_game_flag(BATHROOM_DOOR_OPEN_FLAG))
        start_script(R12_DOOR_CLOSE_SCRIPT);
        
    game_fade_in();
}

//global funcion to update room
void r12_room_update()
{
    //update room objects
    r12_update_room_objects();

    //update dialog line selection
    r12_update_dialog_selection();
    
    //update room script
    r12_update_room_script();
}

//update room objects
void r12_update_room_objects()
{
    r12_object[R12_DOOROPEN_OBJ_ID].active  = is_game_flag(SCHOOL_BATH_DOOR_OPEN_FLAG);
    r12_object[R12_FRONTDOOR_OBJ_ID].active = is_game_flag(SCHOOL_BATH_DOOR_OPEN_FLAG);
    r12_object[R12_DOOR_OBJ_ID].active      = is_game_flag(BATHROOM_DOOR_OPEN_FLAG);
}

//update dialog selection
void r12_update_dialog_selection()
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
                        if (!is_game_flag(DIALOG_KNOW_ANSWERS))
                            dialog_add("What do you mean by grade and subject?",2);
                        else
                            dialog_add("I really need the answers of Maths topics of first grade", 3);
                        if (!is_game_flag(DIALOG_KNOW_ANSWERS) || is_game_flag(HISTORY_APPROVED_FLAG))
                            dialog_add("What are you doing in there?",2);
                        else if (is_game_flag(ASKED_BY_HISTORY_ANSWERS))
                            dialog_add("Do you already have the answers for History first grade?", 1);
                        else
                            dialog_add("I need first grade History answers", 2);
                        if (!is_game_flag(ASK_BY_WC_FLAG))
                            dialog_add("Is this wc occupied?",1);
                        else
                            dialog_add("s this wc still occupied?",1);
                        dialog_add("Bye",0);
                    break;
                    case 2:
                        dialog_add("But this is not very legal, isn't?",2);
                        dialog_add("How I can trust that the answers are correct?",2);
                        dialog_add("Terrific! I need the answers of Maths of first grade", 3);
                        if (!is_game_flag(HISTORY_APPROVED_FLAG))
                            dialog_add("­Perfecto! I need first grade History answers", 2);
                        dialog_add("Thanks, but no thanks.", 1);
                    break;
                    case 3:
                        dialog_add("But I don't have any money, bro",1);
                        if (is_game_flag(ASKED_BY_MATH_ANSWERS))
                        {
                            dialog_add("Is there anything you can accept in exchange for the answers?", 1);
                            dialog_add("Very expensive...I wait for sales", 0);
                        }
                        else
                            dialog_add("Very expensive...I wait for sales", 0);
                    break;
                }
            break;
        }
    }
}

//update room script
void r12_update_room_script()
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
            //1 digit for dialog id, 2 digit for dialog node and 1 digit for selLine
            switch (((dialog.dialogId - 1) * 1000) + ((dialog.node - 1) * 100) + dialog.selLine)
            {
                case 1:
                    if (!is_game_flag(DIALOG_KNOW_ANSWERS))
                    {
                       switch (roomScript.step)
                       {
                           case 1:
                               script_say_actor("Tell me grade and subject and I'll get you answers to the exams", &r12_dialogActor);
                           break;
                           case 2:
                               script_say_actor("100% guaranteed or we refund the money, bro", &r12_dialogActor);
                           break;
                           default:
                               set_game_flag(DIALOG_KNOW_ANSWERS);
                               script_next_dialog_node();
                               end_script();
                           break;
                       }
                    }
                    else
                        dialog_jump(2, 3, 3);
                break;
                case 2:
                    if (!is_game_flag(DIALOG_KNOW_ANSWERS) || is_game_flag(HISTORY_APPROVED_FLAG))
                    {
                        switch (roomScript.step)
                        {
                            case 1:
                                script_say_actor("Dude, I'm all about making people happy", &r12_dialogActor);
                            break;
                            case 2:
                                script_say_actor("I get the answers for the exams of the high school", &r12_dialogActor);
                                break;
                            case 3:
                                script_say_actor("In exchange for a small economic compensation, of course", &r12_dialogActor);
                            break;
                            case 4:
                                script_say_actor("You have to live from something, dude", &r12_dialogActor);
                            break;
                            default:
                                set_game_flag(DIALOG_KNOW_ANSWERS);
                                script_next_dialog_node();
                                end_script();
                            break;
                        }
                    }
                    else
                        dialog_jump(2, 4, 1);
                break;
                case 3:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("This wc is reserved for business tasks", &r12_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Look for another one for your affairs, bro", &r12_dialogActor);
                        break;
                        default:
                            set_game_flag(ASK_BY_WC_FLAG);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 101:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Dude, legality is a very subjective and blurred concept in today's consumer society", &r12_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Besides, these answers are not the worst thing that you can buy you in a high school bathroom, bro", &r12_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 102:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Man, if you're on a wc looking for answers to exams is that you're desperate", &r12_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Right now, I'm your best option", &r12_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 103:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Oki doki, it's 10 bucks", &r12_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 104:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Sorry dude, I'm out of first grade History answers", &r12_dialogActor);
                        break;
                        case 2:
                            script_say_actor("It seems that it is one of the difficult subjects and they have already bought me all the ones they have", &r12_dialogActor);
                        break;
                        default:
                            set_game_flag(ASKED_BY_HISTORY_ANSWERS);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 201:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Bad luck kid", &r12_dialogActor);
                        break;
                        case 2:
                            script_say_actor("No money, no answers", &r12_dialogActor);
                        break;
                        default:
                            set_game_flag(ASKED_BY_MATH_ANSWERS);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 202:
                    if (is_game_flag(ASKED_BY_MATH_ANSWERS))
                    {
                        switch (roomScript.step)
                        {
                            case 1:
                                script_say_actor("Hmmm…", &r12_dialogActor);
                            break;
                            case 2:
                                script_say_actor("You know, my main motivation is money", &r12_dialogActor);
                            break;
                            case 3:
                                script_say_actor("But don't think I'm so shallow", &r12_dialogActor);
                            break;
                            case 4:
                                script_say_actor("I also have very exquisite tastes", &r12_dialogActor);
                            break;
                            case 5:
                                script_say_actor("I like movies", &r12_dialogActor);
                            break;
                            case 6:
                                script_say_actor("Comics", &r12_dialogActor);
                            break;
                            case 7:
                                script_say_actor("And especially manga and anime", &r12_dialogActor);
                            break;
                            case 8:
                                script_say_actor("If you could get me some of that, maybe we can come to an agreement", &r12_dialogActor);
                            break;
                            default:
                                set_game_flag(INFO_ANIME_FLAG);
                                script_next_dialog_node();
                                end_script();
                            break;
                        }
                    }
                    else
                    {
                        script_next_dialog_node();
                        end_script();
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
            case r12_door:
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
                                set_game_flag(BATHROOM_DOOR_OPEN_FLAG);
                                roomScript.hsY = get_player_pos_y();
                                script_player_take_state();
                            break;
                            default:
                                change_room_pos(SCHOOL_ROOM_NUM, 607, 84);
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r12_mirror:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (!is_game_flag(SCHOOLBATH_MIRROR_MSG_FLAG))
                                {
                                    set_game_flag(SCHOOLBATH_MIRROR_MSG_FLAG);
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
            case r12_towelDispenser:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A Paper dispenser");
                                break;
                            default:
                                script_say("As unuseful as its ability to dry");
                                end_script();
                                break;
                        }
                    break;
                    case USE:
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("I prefer don't");
                                break;
                            default:
                                script_say("This paper cuts rather than dries");
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r12_washbowl:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Will anyone wash their hands in this school?");
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
                                script_move_player(138, roomScript.hsY);
                            break;
                            case 1:
                                change_player_dir(DIR_BACK);
                                play_player_animation(ANIM_PLY_WASH_HANDS);
                                script_play_sound_wait(sd_washHands);
                            break;
                            default:
                                stop_player_animation();
                                change_player_dir(DIR_RIGHT);
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
                                        script_say("I should not wet oat grains with water");
                                        break;
                                    default:
                                        script_say("I should use something more viscous");
                                        end_script();
                                        break;
                                }
                            break;
                        }
                    break;
                }
                break;            
            case r12_closedDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A toilet with all the hygienic conditions you could expect");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case OPEN:
                    case USE:
                    case GO:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player_to_target();
                            break;
                            case 1:
                                script_play_sound(sd_doorOpen);
                            break;
                            case 2:
                                set_game_flag(SCHOOL_BATH_DOOR_OPEN_FLAG);
                                script_player_take_state();
                            break;
                            case 3:
                                script_move_player_no_clip(258, 92);
                            break;
                            case 4:
                                script_play_sound_wait(sd_urinating);
                            break;
                            case 5:
                                script_play_sound(sd_toiletFlush);
                            break;
                            case 6:
                                script_wait(40);
                            break;
                            case 7:
                                script_move_player_no_clip(170, 92);
                            break;
                            case 8:
                                script_say("Ugh... I was going to wait to finish the adventure but I couldn't wait anymore");
                            break;
                            case 9:
                                script_play_sound(sd_doorClose);
                            break;
                            case 10:
                                change_player_dir(DIR_RIGHT);
                                script_player_take_state();
                            break;
                            default:
                                clear_game_flag(SCHOOL_BATH_DOOR_OPEN_FLAG);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r12_hole:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Looks like there's someone inside this toilet...");
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
                                if (is_game_flag(MATH_APPROVED_FLAG))
                                {
                                    script_say("I don't need anything more from this guy");
                                    end_script();
                                }
                                else
                                    script_move_player(148, 133);
                                break;
                            case 1:
                                change_player_dir(DIR_RIGHT);
                                script_say("Hello?");
                            break;
                            case 2:
                                script_say_actor("Course and subject?", &r12_dialogActor);
                                break;
                            default:
                                script_start_dialog(1);
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                    case GIVE:
                        switch (roomScript.invObject)
                        {
                            case id_photocopy:
                                if (!is_game_flag(INFO_ANIME_FLAG))
                                {
                                    script_say("¨Why should I give him this photocopy of Dragon Ball?");
                                    end_script();
                                }
                                else
                                {
                                    switch (roomScript.step)
                                    {
                                        case 0:
                                            begin_script();
                                            script_say("Sorry...");
                                        break;
                                        case 1:
                                            script_say_actor("What do you want, dude?", &r12_dialogActor);
                                        break;
                                        case 2:
                                            script_say("You said you liked manga, right?");
                                        break;
                                        case 3:
                                            script_say("Well, I have this exclusive photocopy of Dragon Ball for you");
                                        break;
                                        case 4:
                                            script_say_actor("A PHOTOCOPY OF DRAGON BALL?", &r12_dialogActor);
                                        break;
                                        case 5:
                                            script_say_actor("Dude, you're rocks!. I love Dragon Ball!", &r12_dialogActor);
                                        break;
                                        case 6:
                                            script_say_actor("Give me and give you the answers to the Maths exam", &r12_dialogActor);
                                            r12_object[R12_HAND_OBJ_ID].active = true;
                                        break;
                                        case 7:
                                            script_move_player(207, 114);
                                        break;
                                        case 8:
                                            script_player_take_state();
                                        break;
                                        case 9:
                                            r12_object[R12_HAND_OBJ_ID].active = false;
                                            script_remove_inv_object(id_photocopy);
                                        break;
                                        case 10:
                                            script_say_actor("Wow thank you! In addition is from Goku's!", &r12_dialogActor);
                                        break;
                                        case 11:
                                            script_say_actor("Here are the answers", &r12_dialogActor);
                                            r12_object[R12_HANDEXAM_OBJ_ID].active = true;
                                        break;
                                        case 12:
                                            script_take_object(&r12_object[R12_HANDEXAM_OBJ_ID].active, MATH_APPROVED_FLAG, id_answers);
                                            r12_object[R12_HAND_OBJ_ID].active = true;
                                        break;
                                        case 13:
                                            script_say("Thank you!");
                                        break;
                                        case 14:
                                            if (is_game_flag(MATH_APPROVED_FLAG) && is_game_flag(HISTORY_APPROVED_FLAG) && is_game_flag(PE_APPROVED_FLAG))
                                                play_sound(sd_completed);
                                            else
                                                play_sound(sd_approved);
                                            roomScript.step++;
                                        break;
                                        case 15:
                                            r12_object[R12_HAND_OBJ_ID].active = false;
                                            if (is_game_flag(MATH_APPROVED_FLAG) && is_game_flag(HISTORY_APPROVED_FLAG) && is_game_flag(PE_APPROVED_FLAG))
                                            {
                                                script_say("Great! I've already passed everything!");
                                            }
                                            else
                                            {
                                                script_say("With these answers I have already passed the maths exam");
                                            }
                                        break;
                                        default:
                                            end_script();
                                            break;
                                    }
                                }
                            break;
                            case id_coin:
                                begin_script();
                                script_say("I must keep as much money as I can to buy the ticket");
                                end_script();
                            break;
                            default:
                                begin_script();
                                switch (rand() % 4)
                                {
                                    case 0:
                                        script_say_actor("Dude! What do I want this for?", &r12_dialogActor);
                                    break;
                                    case 1:
                                        script_say_actor("Pass, bro", &r12_dialogActor);
                                    break;
                                    case 2:
                                        script_say_actor("No way", &r12_dialogActor);
                                    break;
                                    case 3:
                                        script_say_actor("No, thanks", &r12_dialogActor);
                                    break;
                                    case 4:
                                        script_say_actor("For you, dude", &r12_dialogActor);
                                    break;
                                }
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r12_holeDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("The door of this toilet has a suspicious hole...");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case OPEN:
                    case USE:
                    case GO:
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
                                script_say_actor("Busy!", &r12_dialogActor);
                                play_player_animation(ANIM_PLY_SURPRISE);
                            break;
                            case 3:
                                stop_player_animation();
                                script_say("Sorry!");
                            break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
            break;
            case R12_DOOR_CLOSE_SCRIPT:
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
                        clear_game_flag(BATHROOM_DOOR_OPEN_FLAG);
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