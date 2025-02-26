/*
=========================================================
 Room Number:   11
 Room Name:     11_PEOffice
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room11.h"

//Funtion to return the name of hotspot by color code
void r11_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r11_door:
                strcpy(s, "Door");
            break;
        case r11_earthGlobe:
                strcpy(s, "World Ball");
            break;
        case r11_things:
                strcpy(s, "Stuff");
            break;
        case r11_cup:
                strcpy(s, "Mug");
            break;
        case r11_teacher:
                strcpy(s, "Teacher");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r11_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r11_door:
            return GO;
            break;
        case r11_earthGlobe:
            return LOOK;
            break;
        case r11_things:
            return LOOK;
            break;
        case r11_cup:
            return LOOK;
            break;
        case r11_teacher:
            return TALK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r11_get_object_info(uint8_t numObject)
{
    if (numObject < R11_ROOM_NUM_OBJS)
        return &r11_object[numObject];
    else
        return NULL;
}

//function to init room
void r11_room_init()
{
    r11_dialogActor.talking = false;
    if (is_game_flag(PEOFFICE_DOOR_OPEN_FLAG))
        start_script(R11_DOOR_CLOSE_SCRIPT);
        
    game_fade_in();
}

//global funcion to update room
void r11_room_update()
{
    //update room objects
    r11_update_room_objects();

    //update dialog line selection
    r11_update_dialog_selection();
    
    //update room script
    r11_update_room_script();
}

//update room objects
void r11_update_room_objects()
{
    //teacher object
    if (r11_dialogActor.talking)
        object_play_animation(&r11_object[R11_TEACHER_OBJ_ID], r11d_objTalk7, r11_animations, R11_ANIM_TALK);
    else if (dialog.active)
        object_play_animation(&r11_object[R11_TEACHER_OBJ_ID], r11d_objTalk7, r11_animations, R11_ANIM_IDLE);
    else
        object_play_animation(&r11_object[R11_TEACHER_OBJ_ID], r11d_objReading1, r11_animations, R11_ANIM_READING);

    r11_object[R11_PLY_BACK_OAT_OBJ_ID].active = is_game_flag(APPLIED_OAT_FLAG);

    if (is_game_flag(SHOW_DISEASE_FLAG))
    {
        start_script(R11_SHOW_DISEASE_SCRIPT);
        clear_game_flag(SHOW_DISEASE_FLAG);
    }

    r11_object[R11_DOOR_OBJ_ID].active      = is_game_flag(PEOFFICE_DOOR_OPEN_FLAG);
}

//update dialog selection
void r11_update_dialog_selection()
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
                        dialog_add("You won't be able to approve me physical education?",2);
                        dialog_add("Why does physical education have to count in grades?",1);
                        dialog_add("Regards from McClane", 0);
                    break;
                    case 2:
                        dialog_add("But I hate swimming",2);
                        dialog_add("10 laps? Who do you think I am, Aquaman?",2);
                        dialog_add("Ah but, Do we have a pool in this school?", 2);
                        if (!is_game_flag(INFO_SPORT_WORK_FLAG))
                            dialog_add("And there's nothing else I can do to pass?”", 2);
                        else
                            dialog_add("What about the skin disease?", 2);
                        dialog_add("So, Do I have to pass an arcade swimming test?", 2);
                        dialog_add("Bah... water for the ducks", 1);
                    break;
                    case 4:
                        dialog_add("I have no money",1);
                        dialog_add("No interest in that, thanks.", 0);
                    break;
                    
                }
            break;
        }
    }
}

//update room script
void r11_update_room_script()
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
                            script_say_actor("Sir, you already know well what is necessary", &r11_dialogActor);
                        break;
                        case 2:
                            script_say_actor("All students have to pass the last test of the course to pass", &r11_dialogActor);
                        break;
                        case 3:
                            script_say_actor("The test consists of doing 10 laps on the pool without stopping", &r11_dialogActor);
                        break;
                        case 4:
                            script_say_actor("And you haven't done it so far", &r11_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 2:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("The hard work and physical strength that physical education teaches", &r11_dialogActor);
                        break;
                        case 2:
                            script_say_actor("are some of the most important and necessary values that you will find in life", &r11_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Besides, your are getting fatty", &r11_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 3:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Mac, who?", &r11_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 101:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("And I hate complaining people awithout discipline", &r11_dialogActor);
                        break;
                        case 2:
                            script_say_actor("And in case you don't understand the irony, I mean you", &r11_dialogActor);
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
                            script_say_actor("We have been practicing long all year for this test", &r11_dialogActor);
                        break;
                        case 2:
                            script_say_actor("and all students are able to do it", &r11_dialogActor);
                        break;
                        case 3:
                            script_say_actor("If you have attended class...", &r11_dialogActor);
                        break;
                        case 4:
                            script_say("Um... yeah...");
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
                            script_say_actor("The discipline and hard work done by this institute has achieved great things", &r11_dialogActor);
                        break;
                        case 2:
                            script_say_actor("From the financing of the Olympic pool that we have", &r11_dialogActor);
                        break;
                        case 3:
                            script_say_actor("to the luxurious teachers' lounge", &r11_dialogActor);
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
                            if (!is_game_flag(INFO_SPORT_WORK_FLAG))
                                script_say_actor("No, you know", &r11_dialogActor);
                            else
                                roomScript.step = 5;
                        break;
                        case 2:
                            script_say_actor("All students must pass the aquatic test to pass", &r11_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Unless...", &r11_dialogActor);
                        break;
                        case 4:
                            script_say("Unless?");
                        break;
                        case 5:
                            if (!is_game_flag(INFO_SPORT_WORK_FLAG))
                                script_say_actor("Unless for some type of infectious skin disease it prevents you from using the pool facilities", &r11_dialogActor);
                            else
                                script_say_actor("It is possible not to perform the swim test due to some type of infectious skin disease that prevents you from using the pool facilities", &r11_dialogActor);
                        break;
                        case 6:
                            script_say_actor("In that case, the student will have to do a work about sport to pass", &r11_dialogActor);
                            set_game_flag(INFO_SPORT_WORK_FLAG);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 105:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Don't say silly", &r11_dialogActor);
                        break;
                        case 2:
                            script_say_actor("In true point and click games there are no arcade mini-games", &r11_dialogActor);
                        break;
                        case 3:
                            script_say_actor("That goes against the philosophy of the adventure player", &r11_dialogActor);
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
            case r11_door:
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
                                set_game_flag(PEOFFICE_DOOR_OPEN_FLAG);
                                roomScript.hsY = get_player_pos_y();
                                script_player_take_state();
                            break;
                            default:
                                change_room_pos(SCHOOL_ROOM_NUM, 901, 84);
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r11_earthGlobe:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Our pale blue dot condensed on a desk object");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r11_things:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Stuff varias que pertenecen al profesor de educaci¢n f¡sica");
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
                                script_say("I'm not going to touch the teacher's stuff");
                                break;
                            default:
                                script_say("I don't want to piss him off...");
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r11_cup:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("I expected it to be the classic cup of: To the best gym teacher");
                                break;
                            default:
                                script_say("But it's just a regular cup");
                                end_script();
                                break;
                        }
                    break;
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Looks like a good inventory item, but I don't need it");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r11_teacher:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("This teacher looks more like a terrorist from the Die Hard film");
                                break;
                            default:
                                script_say("YIPPEE KI YAY MOTHERFUCKER!");
                                end_script();
                                break;
                        }
                    break;
                    case TALK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (is_game_flag(PE_APPROVED_FLAG))
                                {
                                    script_say("Now that I have passed I don't need any of him");
                                    end_script();
                                }
                                else
                                    script_move_player(136, 106);
                            break;
                            case 1:
                                change_player_dir(DIR_RIGHT);
                                script_say("Excuse me, professor…");
                            break;
                            case 2:
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
                            case id_bookSheets:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (!is_game_flag(SPORT_WORK_FLAG))
                                            script_say_actor("I don't know why you gives me this", &r11_dialogActor);
                                        else
                                            script_say_actor("This is not an appropriate way to present a work about sport", &r11_dialogActor);
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                            case id_fullFolder:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (!is_game_flag(SPORT_WORK_FLAG))
                                        {
                                            script_say_actor("Only people who have an illness that prevents them from testing have to do a work", &r11_dialogActor);
                                            end_script();
                                        }
                                        else
                                            script_move_player(140, 106);
                                    break;
                                    case 1:
                                        change_player_dir(DIR_RIGHT);
                                        script_say("Excuse me, professor…");
                                    break;
                                    case 2:
                                        script_say("Here 's the work about the sport");
                                    break;
                                    case 3:
                                        script_move_player(165, 106);
                                    break;
                                    case 4:
                                        object_play_animation(&r11_object[R11_TEACHER_OBJ_ID], r11d_objTalk7, r11_animations, R11_ANIM_TAKE);
                                        script_player_take_state();
                                    break;
                                    case 5:
                                        script_remove_inv_object(id_fullFolder);
                                    break;
                                    case 6:
                                        roomScript.step++;
                                    break;
                                    case 7:
                                        roomScript.step++;
                                    break;
                                    case 8:
                                        script_say_actor("All rightm, Good job", &r11_dialogActor);
                                    break;
                                    case 9:
                                        script_say_actor("You have the subject approved", &r11_dialogActor);
                                    break;
                                    case 10:
                                        script_say_actor("And hope you get better", &r11_dialogActor);
                                        set_game_flag(PE_APPROVED_FLAG);
                                    break;
                                    case 11:
                                        if (is_game_flag(MATH_APPROVED_FLAG) && is_game_flag(HISTORY_APPROVED_FLAG) && is_game_flag(PE_APPROVED_FLAG))
                                            play_sound(sd_completed);
                                        roomScript.step++;
                                    break;
                                    case 12:
                                        if (is_game_flag(MATH_APPROVED_FLAG) && is_game_flag(HISTORY_APPROVED_FLAG) && is_game_flag(PE_APPROVED_FLAG))
                                            script_say("Great! I've already passed everything!");
                                        else
                                            script_play_sound_wait(sd_approved);
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
                                        script_say_actor("Don't interrupt me. I'm correcting", &r11_dialogActor);
                                    break;
                                    case 1:
                                        script_say_actor("I don't know why you gives me that", &r11_dialogActor);
                                    break;
                                    case 2:
                                        script_say_actor("No, Thanks", &r11_dialogActor);
                                    break;
                                    case 3:
                                        script_say_actor("I didn't ask for anything", &r11_dialogActor);
                                    break;
                                    case 4:
                                        script_say_actor("That's for you", &r11_dialogActor);
                                    break;
                                }
                                end_script();
                            break;
                        }
                    break;
                }
                break;
            case R11_SHOW_DISEASE_SCRIPT:
                switch (roomScript.step)
                {
                    case 0:
                        begin_script();
                        object_pos_on_player(&r11_object[R11_PLY_BACK_OAT_OBJ_ID]);
                        change_player_dir(DIR_BACK);
                        script_say("Emm... ¨Teacher?");
                    break;
                    case 1:
                        script_say("I'm afraid I won't be able to do the swim test");
                        object_play_animation(&r11_object[R11_TEACHER_OBJ_ID], r11d_objTalk7, r11_animations, R11_ANIM_SURPRISE);
                    break;
                    case 2:
                        object_play_animation(&r11_object[R11_TEACHER_OBJ_ID], r11d_objTalk7, r11_animations, R11_ANIM_SURPRISE);
                        script_say("I got an ugly rash on my leg");
                    break;
                    case 3:
                        script_say_actor("Of course son! Don't worry", &r11_dialogActor);
                    break;
                    case 4:
                        script_say_actor("That doesn't look good and should be examined by a doctor", &r11_dialogActor);
                    break;
                    case 5:
                        script_say_actor("And don't worry about the test", &r11_dialogActor);
                    break;
                    case 6:
                        script_say_actor("Bring me a work about sport and I will approve the subject", &r11_dialogActor);
                    break;
                    case 7:
                        change_player_dir(DIR_RIGHT);
                        clear_game_flag(APPLIED_OAT_FLAG);
                        script_play_player_animation(ANIM_PLY_END_OAT);
                    break;
                    default:
                        set_game_flag(SPORT_WORK_FLAG);
                        end_script();
                    break;
                }
            break;
            case R11_DOOR_CLOSE_SCRIPT:
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