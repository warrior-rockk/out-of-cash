/*
=========================================================
 Room Number:   04
 Room Name:     04_kitchen
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room04.h"

//Funtion to return the name of hotspot by color code
void r04_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r04_corridor:
                strcpy(s, "Corridor");
            break;
        case r04_fridge:
                strcpy(s, "Fridge");
            break;
        case r04_father:
                strcpy(s, "Dad");
            break;
        case r04_trash:
                strcpy(s, "Trash");
            break;
        case r04_paper:
                strcpy(s, "Kitchen paper");
            break;
        case r04_oven:
                strcpy(s, "Oven");
            break;
        case r04_spatula:
                strcpy(s, "Spatula");
            break;
        case r04_clock:
                if (!is_game_flag(GOT_CLOCK_FLAG))
                    strcpy(s, "Kitchen clock");
                else
                    strcpy(s, "");
            break;
        case r04_oat:
                if (is_game_flag(KITCHEN_CLOSET_OPEN_FLAG) && !is_game_flag(GOT_OAT_FLAG))
                {
                    strcpy(s, "Oat box");
                    break;
                }
                else
                    strcpy(s, "");
        case r04_closet:
            strcpy(s, "Closet");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r04_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r04_corridor:
            return GO;
            break;
        case r04_fridge:
            return LOOK;
            break;
        case r04_father:
            return TALK;
            break;
        case r04_trash:
            return LOOK;
            break;
        case r04_paper:
            return LOOK;
            break;
        case r04_oven:
            return LOOK;
            break;
        case r04_spatula:
            return LOOK;
            break;
        case r04_cheesse:
            return LOOK;
            break;
        case r04_clock:
            return LOOK;
            break;
        case r04_oat:
            if (is_game_flag(KITCHEN_CLOSET_OPEN_FLAG) && !is_game_flag(GOT_OAT_FLAG))
            {
                return LOOK;
                break;
            }
        case r04_closet:
            if (!is_game_flag(KITCHEN_CLOSET_OPEN_FLAG))
                return OPEN;
            else
                return CLOSE;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r04_get_object_info(uint8_t numObject)
{
    if (numObject < R04_ROOM_NUM_OBJS)
        return &r04_object[numObject];
    else
        return NULL;
}

//function to init room
void r04_room_init()
{
    r04_dialogActor.talking = false;
    game_fade_in();
}

//global funcion to update room
void r04_room_update()
{
    //update room objects
    r04_update_room_objects();

    //update dialog line selection
    r04_update_dialog_selection();
    
    //update room script
    r04_update_room_script();
}

//update room objects
void r04_update_room_objects()
{
    r04_object[R04_SPATULA_OBJ_ID].active = !is_game_flag(GOT_SPATULA_FLAG);
    r04_object[R04_STARCLOCK_OBJ_ID].active = !is_game_flag(GOT_CLOCK_FLAG);

    r04_object[R04_CLOSETOPEN_OBJ_ID].active = is_game_flag(KITCHEN_CLOSET_OPEN_FLAG);
    r04_object[R04_OAT_OBJ_ID].active = is_game_flag(KITCHEN_CLOSET_OPEN_FLAG) && !is_game_flag(GOT_OAT_FLAG);

    //father actor
    if (r04_dialogActor.talking)
        object_play_animation(&r04_object[R04_FATHER_OBJ_ID], r04d_objIdle, r04_animations, R04_ANIM_FATHER_TALK);
    else if (dialog.active || is_game_flag(FATHER_TALKING_FLAG))
        r04_object[R04_FATHER_OBJ_ID].objId = r04d_objTalk7;
    else
        r04_object[R04_FATHER_OBJ_ID].objId = r04d_objIdle;
}

//update dialog selection
void r04_update_dialog_selection()
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
                        dialog_add("Why are you always reading the newspaper?", 1);
                        dialog_add("Why is there a room we never open?", 1);
                        if (!is_game_flag(FATHER_SAY_MONEY_FLAG))
                            dialog_add("I have to ask you something...", 2);
                        else if (!is_game_flag(MATH_APPROVED_FLAG) || !is_game_flag(HISTORY_APPROVED_FLAG) || !is_game_flag(PE_APPROVED_FLAG))
                            dialog_add("What did I have to do to give me the money?", 4);
                        else
                            dialog_add("I HAVE ALREADY APPROVED EVERYTHING!", 0);
                        dialog_add("Whatever...", 0);
                    break;
                    case 2:
                        dialog_add("There's a concert I want to go to...", 3);
                        dialog_add("Can I have some dough, man?", 2);
                        dialog_add("Forget about it...", 1);
                    break;
                    case 3:
                        dialog_add("Pleeaseee... I'm very excited", 4);
                        dialog_add("You really don't want to be the best father?", 4);
                        dialog_add("Come on!! I will do anything!", 4);
                    break;
                    case 4:
                        dialog_add("But it's just that mathematics is very difficult!", 4);
                        dialog_add("But history sucks!", 4);
                        dialog_add("Physical Education? What it's usefulness?", 4);
                        dialog_add("Fuck...", 1);
                    break;
                }
            break;
        }
    }
}

//update room script
void r04_update_room_script()
{
    //if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r04_corridor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("You go through that door into the corridor");
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
                                change_room_pos(CORRIDOR_ROOM_NUM, 221, 118);
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r04_fridge:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("The kitchen fridge is filled with delicious food");
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
                                script_say("I'm not hungry ");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r04_father:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("I think I have more memories of my father reading the newspaper than than playing with me");
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
                                if (is_game_flag(GOT_MONEY_FLAG))
                                {
                                    script_say("I already have the money. I don't need to talk to him");
                                    end_script();
                                }
                                else
                                    script_move_player(97, 109);
                                break;
                            case 1:
                                change_player_dir(DIR_RIGHT);
                                script_say("Ejem... Dad?");
                            break;
                            default:
                                script_start_dialog(1);                                
                                end_script();
                                break;
                        }
                    break;
                    case GIVE:
                    case USE_WITH:
                        switch (roomScript.invObject)
                        {
                            case id_califications:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        set_game_flag(FATHER_TALKING_FLAG);
                                        if (is_game_flag(FATHER_SAY_MONEY_FLAG))
                                            script_say_actor("Let's see ", &r04_dialogActor);
                                        else
                                        {
                                            script_say("Ugh... I'd better talk to my dad first before showing him the notes");
                                            end_script();
                                        }
                                    break;
                                    case 1:
                                        if (!is_game_flag(MATH_APPROVED_FLAG) ||
                                            !is_game_flag(HISTORY_APPROVED_FLAG) ||
                                            !is_game_flag(PE_APPROVED_FLAG))
                                            roomScript.step++;
                                        else
                                            start_script(R04_ALL_APPROVED_SCRIPT);
                                    break;
                                    case 2:
                                        script_say_actor("You still need to pass:", &r04_dialogActor);
                                    break;
                                    case 3:
                                        if (!is_game_flag(MATH_APPROVED_FLAG))
                                            script_say_actor("Mathematics", &r04_dialogActor);
                                        else
                                            roomScript.step++;
                                    break;
                                    case 4:
                                        if (!is_game_flag(HISTORY_APPROVED_FLAG))
                                        {
                                            if (!is_game_flag(PE_APPROVED_FLAG))
                                                script_say_actor("History", &r04_dialogActor);
                                            else
                                                script_say_actor("e History", &r04_dialogActor);
                                        }
                                        else
                                            roomScript.step++;
                                    break;
                                    case 5:
                                        if (!is_game_flag(PE_APPROVED_FLAG))
                                        {
                                            if (is_game_flag(MATH_APPROVED_FLAG) && is_game_flag(HISTORY_APPROVED_FLAG))
                                                script_say_actor("Physical education", &r04_dialogActor);
                                            else
                                                script_say_actor("y Physical education", &r04_dialogActor);
                                        }
                                        else
                                            roomScript.step++;
                                    break;
                                    case 6:
                                        script_say_actor("Until you approve everything, I don't give you the money", &r04_dialogActor);
                                        end_script();
                                    break;
                                    default:
                                        clear_game_flag(FATHER_TALKING_FLAG);
                                        end_script();
                                    break;
                                }
                            break;
                            default:
                                begin_script();
                                switch (rand() % 4)
                                {
                                    case 0:
                                        script_say_actor("Son, put away your things.", &r04_dialogActor);
                                    break;
                                    case 1:
                                        script_say_actor("I'm reading. Don't interrupt me", &r04_dialogActor);
                                    break;
                                    case 2:
                                        script_say_actor("I did not want that at all.", &r04_dialogActor);
                                    break;
                                    case 3:
                                        script_say_actor("Very nice, but for you", &r04_dialogActor);
                                    break;
                                    case 4:
                                        script_say_actor("Don't bother son", &r04_dialogActor);
                                    break;
                                }
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r04_trash:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("The trash can where we throw the kitchen garbage");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case TAKE:
                    case OPEN:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It's empty");
                                break;
                            default:
                                script_say("I just threw out the trash recently");
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r04_paper:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A kitchen roll");
                                break;
                            case 1:
                                script_say("It's weird that it's in the kitchen");
                            break;
                            default:
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r04_oven:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Hmm...It's smells like pizza yet");
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
                                script_say("If I'm hungry, I would make me a pizza");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch (roomScript.invObject)
                        {
                            case id_starClock:
                                begin_script();
                                script_say("If you intend to carbonize the clock, it's not a good idea");
                                end_script();
                            break;
                            case id_brain:
                                begin_script();
                                script_say("If you're trying to carbonize the brain, it's not a good idea");
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r04_spatula:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A spatula for confectionery");
                            break;
                            case 1:
                                script_say("It is used to spread chocolate on cakes, for example");
                            break;
                            default:
                                script_say("Or anything viscous");
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
                                    script_take_object(&r04_object[R04_SPATULA_OBJ_ID].active, GOT_SPATULA_FLAG, id_spatula);
                                default:
                                    end_script();
                                    break;
                            }
                    break;
                }
                break;
            case r04_clock:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A star-shaped kitchen clock that my parents bought on a trip");
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
                                    script_take_object(&r04_object[R04_STARCLOCK_OBJ_ID].active, GOT_CLOCK_FLAG, id_starClock);
                                default:
                                    end_script();
                                    break;
                            }
                    break;
                }
                break;
            case r04_oat:
                if (is_game_flag(KITCHEN_CLOSET_OPEN_FLAG) && !is_game_flag(GOT_OAT_FLAG))
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("A box of oat flakes");
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
                                    script_take_object(&r04_object[R04_OAT_OBJ_ID].active, GOT_OAT_FLAG, id_oat);
                                    end_script();
                                break;
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                    break;
                }
            case r04_closet:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Kitchen closet");
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
                                if (is_game_flag(KITCHEN_CLOSET_OPEN_FLAG))
                                {
                                    script_say("Already open");
                                    end_script();
                                }
                                else
                                    script_move_player(131, 86);
                                break;
                            case 1:
                                change_player_dir(DIR_RIGHT);
                                script_play_sound(sd_closetOpen);
                            break;
                            case 2:
                                script_player_take_state();
                                break;
                            default:
                                set_game_flag(KITCHEN_CLOSET_OPEN_FLAG);
                                end_script();
                                break;
                        }
                    break;
                    case CLOSE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (!is_game_flag(KITCHEN_CLOSET_OPEN_FLAG))
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
                            default:
                                clear_game_flag(KITCHEN_CLOSET_OPEN_FLAG);
                                end_script();
                                break;
                        }

                }
            break;
            case R04_ALL_APPROVED_SCRIPT:
                switch (roomScript.step)
                {
                    case 0:
                        set_game_flag(FATHER_TALKING_FLAG);
                        script_say_actor("Congratulations son!", &r04_dialogActor);
                    break;
                    case 1:
                        script_say_actor("In the end, with work and effort, goals are achieved", &r04_dialogActor);
                    break;
                    case 2:
                        script_say_actor("Here's the money", &r04_dialogActor);
                    break;
                    case 3:
                        play_sound(sd_money);
                        script_combine_inv_object(id_califications, 0, id_money);
                    break;
                    case 4:
                        script_say("But, Dad, there are only 29 bucks here");
                    break;
                    case 5:
                        script_say("The concert ticket is worth 30!");
                    break;
                    case 6:
                        script_say_actor("Son, take what you're given and sigh for what's left", &r04_dialogActor);
                    break;
                    case 7:
                        script_say("You motherf...");                        
                    break;
                    case 8:
                        script_say_actor("That mouth...", &r04_dialogActor);
                        set_game_flag(GOT_MONEY_FLAG);
                    break;
                    default:
                        clear_game_flag(FATHER_TALKING_FLAG);
                        end_script();
                    break;
                }
            break;
        }
    }

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
            //1 digit for dialog id, 2 digit for dialog node and 1 digit for selLinef
            switch (((dialog.dialogId - 1) * 1000) + ((dialog.node - 1) * 100) + dialog.selLine)
            {

                case 1:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("In life, you have to be informed, boy", &r04_dialogActor);
                        break;
                        case 2:
                            script_say_actor("And newspapers is the only way to find out the truth", &r04_dialogActor);
                        break;
                        case 3:
                            script_say_actor("And not those bullshit things they say on TV", &r04_dialogActor);
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
                            script_say_actor("If I told you I'd have to kill you", &r04_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Besides, I don't know", &r04_dialogActor);
                        break;
                        case 3:
                            script_say_actor("That's your mother matters", &r04_dialogActor);
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
                            if (is_game_flag(MATH_APPROVED_FLAG) && is_game_flag(HISTORY_APPROVED_FLAG) && is_game_flag(PE_APPROVED_FLAG))
                            {
                                script_say_actor("Until I see your califications don't believe it", &r04_dialogActor);
                            }
                            else if (is_game_flag(FATHER_SAY_MONEY_FLAG))
                                script_say_actor("Pass Mathematics, History y Physical education and I will give you the money", &r04_dialogActor);
                            else
                                roomScript.step++;
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
                            script_say("It's from my favorite group");
                        break;
                        case 2:
                            script_say("They just put out a record and come to the city to present it");
                        break;
                        case 3:
                            script_say("The problem is that I have no money and the ticket is worth 30 bucks");
                        break;
                        case 4:
                            script_say("You will be the best father in the world if you give me the money");
                        break;
                        case 5:
                            script_say_actor("Neither in your dreams", &r04_dialogActor);
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
                            script_say_actor("Moderate your language, youthful boy!", &r04_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                    break;
                case 201:
                case 202:
                case 203:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Mmmm...", &r04_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Let's make a deal.", &r04_dialogActor);
                        break;
                        case 3:
                            script_say_actor("If you pass the subjects you failed, I will give you the money", &r04_dialogActor);
                        break;
                        case 4:
                            script_say_actor("You must pass Mathematics, History and Physical Education", &r04_dialogActor);
                            set_game_flag(FATHER_SAY_MONEY_FLAG);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 301:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("It is your obligation to learn mathematics", &r04_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 302:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("To face the future you have to know the past well", &r04_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 303:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Son", &r04_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Physical Education is a subject as respectable and important as the other", &r04_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Besides, you are getting fatty", &r04_dialogActor);
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
}
