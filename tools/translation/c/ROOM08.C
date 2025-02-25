/*
=========================================================
 Room Number:   08
 Room Name:     08_computerRoom
=========================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room08.h"

//Funtion to return the name of hotspot by color code
void r08_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r08_door:
                strcpy(s, "Door");
            break;
        case r08_window:
                strcpy(s, "Window");
            break;
        case r08_computer3:
                strcpy(s, "Computer");
            break;
        case r08_manual:
                strcpy(s, "Manual");
            break;
        case r08_computer1:
                strcpy(s, "Computer");
            break;
        case r08_nerd:
                strcpy(s, "Nerd");
            break;
        case r08_computer2:
                strcpy(s, "Computer");
            break;
        case r08_chair:
                strcpy(s, "Chair");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r08_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r08_door:
            return GO;
            break;
        case r08_window:
            return LOOK;
            break;
        case r08_computer3:
            return LOOK;
            break;
        case r08_manual:
            return LOOK;
            break;
        case r08_computer1:
            return LOOK;
            break;
        case r08_nerd:
            return TALK;
            break;
        case r08_computer2:
            return LOOK;
            break;
        case r08_chair:
            return LOOK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r08_get_object_info(uint8_t numObject)
{
    if (numObject < R08_ROOM_NUM_OBJS)
        return &r08_object[numObject];
    else
        return NULL;
}

//function to init room
void r08_room_init()
{
    r08_dialogActor.talking = false;
    clear_game_flag(START_CREDITS_FLAG);
    
    game_fade_in();

    if (is_game_flag(PLAYER_ROCKING_FLAG))
        start_script(R08_EPILOGUE_SCRIPT);
    else if (is_game_flag(COMPUTER_DOOR_OPEN_FLAG))
        start_script(R08_DOOR_CLOSE_SCRIPT);
        
}

//global funcion to update room
void r08_room_update()
{
    //update room objects
    r08_update_room_objects();

    //update dialog line selection
    r08_update_dialog_selection();
    
    //update room script
    r08_update_room_script();
}

//update room objects
void r08_update_room_objects()
{
    //nerd object
    if (is_game_flag(NERD_ERROR_2_FLAG))
    {
        r08_object[R08_NERD_OBJ_ID].x = 115;
        r08_object[R08_NERD_OBJ_ID].y = 100;

        if (r08_dialogActor.talking)
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_ERROR_TALK);
        }
        else
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_ERROR_IDLE);
        }
    }
    else if (is_game_flag(NERD_ERROR_FLAG))
    {
        r08_object[R08_NERD_OBJ_ID].x = 115;
        r08_object[R08_NERD_OBJ_ID].y = 100;

        object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_ERROR);
    }
    else if (is_game_flag(NERD_COSTUME_FLAG))
    {
        r08_object[R08_NERD_OBJ_ID].x = 135;
        r08_object[R08_NERD_OBJ_ID].y = 106;

        if (r08_dialogActor.talking)
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_COSTUME_TALK);
        }
        else
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_COSTUME_IDLE);
        }
    }
    else if (is_game_flag(NERD_COSTUME_PLAYING_FLAG))
    {
        r08_object[R08_NERD_OBJ_ID].x = 115;
        r08_object[R08_NERD_OBJ_ID].y = 100;
        
        if (r08_dialogActor.talking)
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objPlay1, r08_animations, R08_ANIM_COSTUME_PLAY_TALK);
        else
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objPlay1, r08_animations, R08_ANIM_COSTUME_PLAYING);
    }
    else if (is_game_flag(NERD_SIDE_FLAG))
    {
        r08_object[R08_NERD_OBJ_ID].x = 115;
        r08_object[R08_NERD_OBJ_ID].y = 100;
        
        if (r08_dialogActor.talking)
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_TALK);
        }
        else
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_IDLE);
        }
    }
    else
    {
        r08_object[R08_NERD_OBJ_ID].x = 115;
        r08_object[R08_NERD_OBJ_ID].y = 100;

        if (r08_dialogActor.talking)
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objPlay1, r08_animations, R08_ANIM_TALK_PLAYING);
        }
        else
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objPlay1, r08_animations, R08_ANIM_PLAYING);
        }
    }

    r08_object[R08_DOOR_OBJ_ID].active =  is_game_flag(COMPUTER_DOOR_OPEN_FLAG);
}

//update dialog selection
void r08_update_dialog_selection()
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
                        if (!is_game_flag(NERD_HELP_FLAG))
                            dialog_add("What game are you playing?",2);
                        else
                            dialog_add("So, you will help me to pass the history exam?",6);
                        dialog_add("Are you using the computer room to play games?",1);
                        dialog_add("I don't bother you", 0);
                    break;
                    case 2:
                        dialog_add("The ultimate strategy game is Civilization",2);
                        dialog_add("You seem to be very good at strategy games",3);
                        dialog_add("I prefer point and click games", 2);
                        dialog_add("I don't want to distract you", 1);
                    break;
                    case 3:
                        dialog_add("Don't you have a bit of an obsession with historical wars?", 3);
                        dialog_add("If you're so good at the history, Couldn't you help me?",4);
                        dialog_add("Very interesting", 2);
                    break;
                    case 4:
                        dialog_add("If you help me, you can tell people that we're friends",0);
                        dialog_add("If you help me, I will go for an afternoon snack with milk and biscuits at your house",0);
                        dialog_add("If you help me, I wil teach you how to do cool levels for DOOM",0);
                        dialog_add("Well, forget it...", 0);
                    break;
                    case 6:
                        dialog_add("What do I need for the costume?",0);
                        dialog_add("Great, Thank you!",0);
                    break;
                }
            break;
        }
    }
}

//update room script
void r08_update_room_script()
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
                    switch (roomScript.step)
                    {
                        case 1:
                            if (!is_game_flag(NERD_HELP_FLAG))
                                script_say_actor("I'm playing Age of Empires!", &r08_dialogActor);
                            else
                                dialog_jump(5, 1, 6);
                        break;
                        case 2:
                            script_say_actor("The Ultimate Strategy Game", &r08_dialogActor);
                        break;
                        case 3:
                            script_say_actor("I'm using all my war knowledge to make perfect game", &r08_dialogActor);
                        break;
                        case 4:
                            script_say_actor("I love to play that i'm a warlord and crush my enemies", &r08_dialogActor);
                        break;
                        case 5:
                            set_game_flag(NERD_SIDE_FLAG);                            
                            script_say_actor("My therapist says it channels the hatred I have inside", &r08_dialogActor);
                        break;
                        case 6:
                            script_wait(3);
                        break;
                        case 7:
                            script_say_actor("If you want you can play with me", &r08_dialogActor);
                        break;
                        case 8:
                            script_say_actor("Or come to my house and I will show you more games I have", &r08_dialogActor);
                        break;
                        case 9:
                            script_say_actor("Or we can have a snack and play Dragons and Dungeons", &r08_dialogActor);
                        break;
                        case 10:
                            script_say_actor("I have a campaign that I think is the bes...", &r08_dialogActor);
                        break;
                        case 11:
                            script_say("ENOUGH!");
                        break;
                        case 12:
                            script_say("No interest in that, thanks.");
                        break;
                        case 13:
                            script_say_actor("Whatever", &r08_dialogActor);
                        break;
                        default:
                            clear_game_flag(NERD_SIDE_FLAG);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 2:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("And you told your parents to buy you the computer to study", &r08_dialogActor);
                        break;
                        case 2:
                            script_wait(2);
                        break;
                        case 3:
                            script_say("Touché");
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
                            set_game_flag(NERD_SIDE_FLAG);
                            script_say_actor("I love strategy games", &r08_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Everything to do with history and wars", &r08_dialogActor);
                        break;
                        case 3:
                            script_say_actor("And destroy enemy armies with my great power", &r08_dialogActor);
                        break;
                        case 4:
                            script_say_actor("And don't think I'm just playing. I love reading history books and reading feats of great battles", &r08_dialogActor);
                        break;
                        default:
                            clear_game_flag(NERD_SIDE_FLAG);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 101:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("I also love it", &r08_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Everything to do with history and wars", &r08_dialogActor);
                        break;
                        case 3:
                            set_game_flag(NERD_SIDE_FLAG);
                            script_say_actor("And I don't just play, I love reading history books and reading feats of great battles", &r08_dialogActor);
                        break;
                        default:
                            clear_game_flag(NERD_SIDE_FLAG);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 103:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Who plays that kind of games these days?", &r08_dialogActor);
                        break;
                        case 2:
                            script_wait(5);
                        break;
                        case 3:
                            play_player_animation(ANIM_PLY_LOOK_FRONT);
                            script_wait(10);
                        break;
                        case 4:
                            play_player_animation(ANIM_PLY_SMILE_FRONT);
                            script_wait(10);
                        break;
                        default:
                            stop_player_animation();
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 201:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Don't believe it.", &r08_dialogActor);
                        break;
                        case 2:
                            script_say_actor("I think it's a very healthy hobby", &r08_dialogActor);
                        break;
                        case 3:
                            script_say_actor("And it's not like I'm going to the school armed with a rifle", &r08_dialogActor);
                        break;
                        case 4:
                            set_game_flag(NERD_SIDE_FLAG);
                            script_wait(20);
                        break;
                        case 5:
                            clear_game_flag(NERD_SIDE_FLAG);
                            script_say_actor("No, no... I won't be okay...", &r08_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 202:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say("I need to pass the history exam");
                        break;
                        case 2:
                            script_say_actor("Of course my friend! We can meet at my house and teach you everything you need to know", &r08_dialogActor);
                        break;
                        case 3:
                            script_say("Hmm... I was thinking better about another way to help");
                        break;
                        case 4:
                            set_game_flag(NERD_SIDE_FLAG);
                            script_say_actor("What do you mean?"", &r08_dialogActor);
                        break;
                        case 5:
                            script_say("I was thinking about you taking the exam for me");
                        break;
                        case 6:
                            script_wait(20);
                        break;
                        case 7:
                            script_say_actor("But…", &r08_dialogActor);
                        break;
                        case 8:
                            script_wait(10);
                        break;
                        case 9:
                            script_say_actor("I don't wanna get in trouble...", &r08_dialogActor);
                        break;
                        case 10:
                            script_say("Don't worry! I've got it all figured out. You dress up as me and pass the exam");
                        break;
                        case 11:
                            script_say("No one notices!");
                        break;
                        case 12:
                            script_say_actor("I don't know... I don't see it...", &r08_dialogActor);
                        break;
                        default:
                            clear_game_flag(NERD_SIDE_FLAG);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 301:
                case 302:
                case 303:
                    switch (roomScript.step)
                    {
                        case 1:
                            set_game_flag(NERD_SIDE_FLAG);
                            script_say_actor("­Oh! Really?", &r08_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Okay, I will help you!", &r08_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Get me something to disguise myself as you and I will take the exam", &r08_dialogActor);
                        break;
                        default:
                            clear_game_flag(NERD_SIDE_FLAG);
                            set_game_flag(NERD_HELP_FLAG);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 401:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Yes, I help you", &r08_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Get me something to disguise myself as you and I will take the exam", &r08_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 501:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("You know...", &r08_dialogActor);
                        break;
                        case 2:
                            if (!is_game_flag(BRAIN_COSTUME_FLAG))
                                script_say_actor("Get something for the hair", &r08_dialogActor);
                            else
                                roomScript.step++;
                        break;
                        case 3:
                            if (!is_game_flag(SHIRT_COSTUME_FLAG))
                            {
                                if (is_game_flag(BRAIN_COSTUME_FLAG))
                                    script_say_actor("Get a t-shirt like yours", &r08_dialogActor);
                                else
                                    script_say_actor("a t-shirt like yours", &r08_dialogActor);
                            }
                            else
                                roomScript.step++;
                        break;
                        case 4:
                            if (!is_game_flag(JEANS_COSTUME_FLAG))
                            {
                                if (is_game_flag(BRAIN_COSTUME_FLAG) || is_game_flag(SHIRT_COSTUME_FLAG))
                                    script_say_actor("Get some pants similar to yours", &r08_dialogActor);
                                else
                                    script_say_actor("and some pants similar to yours", &r08_dialogActor);
                            }
                            else
                                roomScript.step++;
                        break;
                        case 5:
                            script_say_actor("And with that we'll have it ready", &r08_dialogActor);
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
            case r08_door:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It is the door leading to the corridor");
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
                                change_room_pos(SCHOOL_ROOM_NUM, 272, 84);
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r08_window:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("This window to the outside prevents people from fraudulently using computers");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r08_computer3:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("The institute's computers are still 486");
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
                                script_say("I have no time for games");
                            break;
                            case 1:
                                script_say("I have to pass the remaining subjects to get the money");
                            break;
                            case 2:
                                script_say("In addition, that computer has the Barrotes virus");
                            break;
                            default:
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r08_manual:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A Q-Basic manual for MS-DOS");
                            break;
                            case 1:
                                script_say("Learn to program from the game Gorillas to Snake");
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
                                script_say("No, I don't need it.");
                            break;
                            case 1:
                                script_say("I've already started programming in C");
                            break;
                            default:
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r08_computer1:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Looks like he is playing some kind of strategy game");
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
                                script_say("I can't use it");
                            break;
                            case 1:
                                script_say("The nerd is playing");
                            break;
                            default:
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r08_nerd:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (is_game_flag(NERD_COSTUME_PLAYING_FLAG))
                                    script_say("He's supposedly disguised as me");
                                else
                                    script_say("This kid is the high school weirdo");
                                break;
                            case 1:
                                if (is_game_flag(NERD_COSTUME_PLAYING_FLAG))
                                {
                                    script_say("I think this is going to be material for my nightmares");
                                    end_script();
                                }
                                else
                                script_say("He is always involved in his world of books and role-playing games");
                            break;
                            case 2:
                                script_say("Doesn't seem to have many friends");
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
                                if (!is_game_flag(HISTORY_APPROVED_FLAG))
                                    script_move_player(214, 126);
                                else
                                {
                                    script_say("It's been helpful enough for me");
                                    end_script();
                                }
                                break;
                            case 1:
                                change_player_dir(DIR_LEFT);
                                script_start_dialog(1);
                            break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                    case GIVE:
                        switch (roomScript.invObject)
                        {
                            case id_brain:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (!is_game_flag(NERD_HELP_FLAG))
                                        {
                                            script_say_actor("And what do I do with that?", &r08_dialogActor);
                                            end_script();
                                        }
                                        else
                                            script_say_actor("It could serve as hair, but the color is very light", &r08_dialogActor);
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                            case id_blackBrain:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (!is_game_flag(NERD_HELP_FLAG))
                                        {
                                            script_say_actor("Why are you giving me this?", &r08_dialogActor);
                                            end_script();
                                        }
                                        else
                                            script_move_player(186, 130);
                                    break;
                                    case 1:
                                        change_player_dir(DIR_LEFT);
                                        script_player_take_state();
                                        object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_TAKE);
                                    break;
                                    case 2:
                                        script_remove_inv_object(id_blackBrain);
                                        set_game_flag(BRAIN_COSTUME_FLAG);
                                    break;
                                    case 3:
                                        script_say_actor("Perfect! We'll use this for the costume", &r08_dialogActor);
                                    break;
                                    case 4:
                                        start_script(R08_COSTUME_COMPLETE_SCRIPT);
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                            case id_starShirt:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (!is_game_flag(NERD_HELP_FLAG))
                                        {
                                            script_say_actor("Why are you giving me this?", &r08_dialogActor);
                                            end_script();
                                        }
                                        else
                                            script_move_player(186, 130);
                                    break;
                                    case 1:
                                        change_player_dir(DIR_LEFT);
                                        script_player_take_state();
                                        object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_TAKE);
                                    break;
                                    case 2:
                                        script_remove_inv_object(id_starShirt);
                                        set_game_flag(SHIRT_COSTUME_FLAG);
                                    break;
                                    case 3:
                                        script_say_actor("All right! This will serve for the costume", &r08_dialogActor);
                                    break;
                                    case 4:
                                        start_script(R08_COSTUME_COMPLETE_SCRIPT);
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                            case id_jeans:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (!is_game_flag(NERD_HELP_FLAG))
                                        {
                                            script_say_actor("Why are you giving me this?", &r08_dialogActor);
                                            end_script();
                                        }
                                        else
                                            script_move_player(186, 130);                                            
                                    break;
                                    case 1:
                                        change_player_dir(DIR_LEFT);
                                        script_player_take_state();
                                        object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_TAKE);
                                    break;
                                    case 2:
                                        script_remove_inv_object(id_jeans);
                                        set_game_flag(JEANS_COSTUME_FLAG);
                                    break;
                                    case 3:
                                        script_say_actor("Oh yeah! This will do us good for the costume", &r08_dialogActor);
                                    break;
                                    case 4:
                                        start_script(R08_COSTUME_COMPLETE_SCRIPT);
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                            case id_shirt:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (!is_game_flag(NERD_HELP_FLAG))
                                        {
                                            script_say_actor("Don't bother me", &r08_dialogActor);
                                            end_script();
                                        }
                                        else
                                            script_say_actor("Hmm. Looks a little like your t-shirt but not enough", &r08_dialogActor);
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                            default:
                                begin_script();
                                switch (rand() % 4)
                                {
                                    case 0:
                                        script_say_actor("Don't interrupt me. I'm playing", &r08_dialogActor);
                                    break;
                                    case 1:
                                        script_say_actor("I don't want that ", &r08_dialogActor);
                                    break;
                                    case 2:
                                        script_say_actor("You are deconcentrating me", &r08_dialogActor);
                                    break;
                                    case 3:
                                        script_say_actor("Don't give me your junk", &r08_dialogActor);
                                    break;
                                    case 4:
                                        script_say_actor("Leave me alone. I'm focused on the game", &r08_dialogActor);
                                    break;
                                }
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r08_computer2:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Wow! If there is also a 386!");
                                break;
                            case 1:
                                script_say("Long live public education!");
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
                                script_say("Mmmm... no. ");
                                break;
                            case 1:
                                script_say("After having a Pentium at home, a 386 feels like a turtle");
                            break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r08_chair:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Hopefully in the future make computer chairs more fashionable and that they serve for long gaming sessions");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;
            case R08_COSTUME_COMPLETE_SCRIPT:
                switch (roomScript.step)
                {
                    case 0:
                        if (is_game_flag(BRAIN_COSTUME_FLAG) &&
                            is_game_flag(SHIRT_COSTUME_FLAG) &&
                            is_game_flag(JEANS_COSTUME_FLAG)
                            )
                        {
                            set_game_flag(NERD_SIDE_FLAG);
                            script_say_actor("I already have everything I need.", &r08_dialogActor);
                        }
                        else
                            end_script();
                    break;
                    case 1:
                        script_say_actor("I'm going to prepare the costume and take your exam", &r08_dialogActor);
                    break;
                    case 2:
                        game_fade_out(FADE_SLOW_SPEED);
                        clear_game_flag(NERD_SIDE_FLAG);
                        set_player_position(216, 104);
                        roomScript.step++;
                    break;
                    case 3:
                        script_wait(20);
                        set_game_flag(NERD_COSTUME_FLAG);
                        play_player_animation(ANIM_PLY_SURPRISE);
                    break;
                    case 4:
                        game_fade_in();
                        script_wait(10);
                    break;
                    case 5:
                        script_say_actor("Piece of cake!", &r08_dialogActor);
                    break;
                    case 6:
                        script_wait(6);
                    break;
                    case 7:
                        script_say_actor("Disguised like you, no one has noticed", &r08_dialogActor);
                    break;
                    case 8:
                        script_say("Who would say");
                    break;
                    case 9:
                        script_play_sound(sd_approved);
                    break;
                    case 10:
                        script_say_actor("You have approved the subject!", &r08_dialogActor);
                        set_game_flag(HISTORY_APPROVED_FLAG);
                    break;
                    case 11:
                        stop_player_animation();
                        script_say("Umm... ");
                    break;
                    case 12:
                        script_say("Thank you");
                    break;
                    case 13:
                        if (is_game_flag(MATH_APPROVED_FLAG) && is_game_flag(HISTORY_APPROVED_FLAG) && is_game_flag(PE_APPROVED_FLAG))
                            play_sound(sd_completed);
                        roomScript.step++;
                    break;
                    case 14:
                        if (is_game_flag(MATH_APPROVED_FLAG) && is_game_flag(HISTORY_APPROVED_FLAG) && is_game_flag(PE_APPROVED_FLAG))
                            script_say("Great! I've already passed everything!");
                        else
                            roomScript.step++;
                    break;
                    case 15:
                        change_player_dir(DIR_RIGHT);
                        script_say("I'm almost out of here before this gets weird!");
                    break;
                    case 16:
                        script_move_player(320, 104);
                    break;
                    case 17:
                        clear_game_flag(NERD_COSTUME_FLAG);
                        set_game_flag(NERD_COSTUME_PLAYING_FLAG);
                        change_room_pos(SCHOOL_ROOM_NUM, 272, 84);
                        roomScript.step++;
                    break;
                    default:
                        end_script();
                    break;
                }
            break;
            case R08_EPILOGUE_SCRIPT:
                switch (roomScript.step)
                {
                    case 0:
                        begin_script();
                        script_say_actor("Come on!", &r08_dialogActor);
                    break;
                    case 1:
                        script_wait(10);
                    break;
                    case 2:
                        begin_script();
                        script_say_actor("Die damned!", &r08_dialogActor);
                    break;
                    case 3:
                        script_wait(10);
                    break;
                    case 4:
                        begin_script();
                        script_say_actor("I hate all my enemies", &r08_dialogActor);
                    break;
                    case 5:
                        script_wait(10);
                    break;
                    case 6:
                        begin_script();
                        script_say_actor("I hate you as much as I hate my classmates", &r08_dialogActor);
                    break;
                    case 7:
                        script_wait(5);
                    break;
                    case 8:
                        begin_script();
                        script_say_actor("And I hate teachers...", &r08_dialogActor);
                    break;
                    case 9:
                        script_wait(5);
                    break;
                    case 10:
                        begin_script();
                        script_say_actor("And I hate that girl who called me weird", &r08_dialogActor);
                    break;
                    case 11:
                        script_wait(5);
                    break;
                    case 12:
                        begin_script();
                        script_say_actor("One day I'm going to take a rifle to school and I'm going to...", &r08_dialogActor);
                    break;
                    case 13:
                        set_game_flag(NERD_ERROR_FLAG);
                        script_play_sound(sd_w95Error);
                    break;
                    case 14:
                        script_wait(10);
                    break;
                    case 15:
                        set_game_flag(NERD_ERROR_2_FLAG);
                        script_wait(5);
                    break;
                    case 16:
                        script_say_actor("But most of all I hate Windows", &r08_dialogActor);
                    break;
                    case 17:
                        script_wait(20);
                    break;
                    default:
                        set_game_flag(END_FINISH_FLAG);
                        end_script();
                    break;
                }
            break;
            case R08_DOOR_CLOSE_SCRIPT:
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
                        clear_game_flag(COMPUTER_DOOR_OPEN_FLAG);
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