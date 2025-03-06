/*
=========================================================
 Room Number:   05
 Room Name:     05_stationery
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room05.h"

//Funtion to return the name of hotspot by color code
void r05_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r05_door:
                strcpy(s, "Door");
            break;
        case r05_folders:
                strcpy(s, "Folders");
            break;
        case r05_stationeryMaterial:
                strcpy(s, "Stationery material");
            break;
        case r05_photocopies:
            if (!r05_object[R05_PHOTOCOPY_OBJ_ID].active)
                strcpy(s, "");
            else
                strcpy(s, "Photocopies");
            break;
        case r05_paper:
            if (r05_object[R05_SHEETS_OBJ_ID].active || r05_object[R05_SHEETSPHOTO_OBJ_ID].active)
                strcpy(s, "Paper");
            else
                strcpy(s, "");
            break;
        case r05_printer:
                strcpy(s, "Printer");
            break;    
        case r05_cartridge:
            if (is_game_flag(FULL_CARTRIDGE_NOT_ON_PRINTER_FLAG) && !is_game_flag(EMPTY_CARTRIDGE_ON_PRINTER_FLAG))
                strcpy(s, "");
            else
                strcpy(s, "Cartridge");
            break;
        case r05_printedPaper:
            if (is_game_flag(PRINTED_SCHOOL_SCHEDULE_FLAG) ||
                is_game_flag(PRINTED_SCHOOL_SCHEDULE_PHOTO_FLAG) ||
                is_game_flag(PRINTED_PHOTOCOPY_FLAG) ||
                is_game_flag(PRINTED_SHEET_FLAG))
                strcpy(s, "Paper impreso");
            else
                strcpy(s, "");
            break;
        case r05_mouse:
                strcpy(s, "Mouse");
            break;
        case r05_monitor:
                strcpy(s, "Monitor");
            break;
        case r05_employee:
            strcpy(s, "Dependent");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r05_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r05_door:
            return GO;
            break;
        case r05_folders:
            return LOOK;
            break;
        case r05_stationeryMaterial:
            return LOOK;
            break;
        case r05_photocopies:
            return LOOK;
            break;
        case r05_paper:
            return LOOK;
            break;
        case r05_cartridge:
            return LOOK;
            break;
        case r05_printer:
            return LOOK;
            break;
        case r05_printedPaper:
            return LOOK;
            break;
        case r05_mouse:
            return LOOK;
            break;
        case r05_monitor:
            return LOOK;
            break;
        case r05_employee:
            return TALK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r05_get_object_info(uint8_t numObject)
{
    if (numObject < R05_ROOM_NUM_OBJS)
        return &r05_object[numObject];
    else
        return NULL;
}

//function to init room
void r05_room_init()
{
    r05_dialogActor.talking = false;
    start_script(R05_WELLCOME_SCRIPT);
    game_fade_in();
}

//global funcion to update room
void r05_room_update()
{
    //update room objects
    r05_update_room_objects();

    //update dialog line selection
    r05_update_dialog_selection();
    
    //update room script
    r05_update_room_script();
}

//update room objects
void r05_update_room_objects()
{
    r05_object[R05_PHOTOCOPY_OBJ_ID].active = !is_game_flag(GOT_PHOTOCOPY_STOLEN_FLAG) && !is_game_flag(PHOTOCOPY_ON_PRINTER_FLAG) && !is_game_flag(USED_PHOTOCOPY_FLAG);
    r05_object[R05_SHEETS_OBJ_ID].active = !is_game_flag(SHEETS_NOT_ON_PRINTER_FLAG);
    r05_object[R05_SHEETSPHOTO_OBJ_ID].active = is_game_flag(PHOTOCOPY_ON_PRINTER_FLAG) && !is_game_flag(USED_PHOTOCOPY_FLAG);
    r05_object[R05_CARTRIDGEFULL_OBJ_ID].active = !is_game_flag(FULL_CARTRIDGE_NOT_ON_PRINTER_FLAG);
    r05_object[R05_CARTRIDGEEMPTY_OBJ_ID].active = is_game_flag(EMPTY_CARTRIDGE_ON_PRINTER_FLAG);
    
    r05_object[R05_PRINTEDSCH_OBJ_ID].active = is_game_flag(PRINTED_SCHOOL_SCHEDULE_FLAG);
    r05_object[R05_PRINTEDSCHPHOTO_OBJ_ID].active = is_game_flag(PRINTED_SCHOOL_SCHEDULE_PHOTO_FLAG);
    r05_object[R05_PRINTEDPHOTO_OBJ_ID].active = is_game_flag(PRINTED_PHOTOCOPY_FLAG);
    r05_object[R05_PRINTEDSHEET_OBJ_ID].active = is_game_flag(PRINTED_SHEET_FLAG) && !is_game_flag(GOT_SHEETS_FLAG);
    
    //employeer actor
    if (r05_dialogActor.talking)
        if (!is_game_flag(EMPLOYEE_AT_COMPUTER_FLAG))
            object_play_animation(&r05_object[R05_EMPLOYEER_OBJ_ID], r05d_objAnimIdle, r05_animations, R05_ANIM_TALK);
        else
            object_play_animation(&r05_object[R05_EMPLOYEER_OBJ_ID], r05d_objAnimIdle, r05_animations, R05_ANIM_COMPUTER_TALK);
    else if (is_game_flag(EMPLOYEE_USING_COMPUTER_FLAG))
        object_play_animation(&r05_object[R05_EMPLOYEER_OBJ_ID], r05d_objAnimIdle, r05_animations, R05_ANIM_PRINTING);
    else if (is_game_flag(EMPLOYEE_AT_COMPUTER_FLAG))
        r05_object[R05_EMPLOYEER_OBJ_ID].objId = r05d_objPrinting1;
    else if (is_game_flag(EMPLOYEE_RETURN_FLAG))
    {
        if (object_play_animation(&r05_object[R05_EMPLOYEER_OBJ_ID], r05d_objAnimIdle, r05_animations, R05_ANIM_WALK_REVERSE))
            clear_game_flag(EMPLOYEE_RETURN_FLAG);
    }
    else
        r05_object[R05_EMPLOYEER_OBJ_ID].objId = r05d_objAnimIdle;
}

//update dialog selection
void r05_update_dialog_selection()
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
                        dialog_add("Nice stationery...",1);
                        dialog_add("Can I take a folder?",1);
                        dialog_add("What are these photocopies you have?",3);
                        if (!is_game_flag(SCHEDULE_INFO_FLAG))
                            dialog_add("What is the printer for?",1);
                        else
                            dialog_add("Can you print me a schedule?",0);
                        dialog_add("I don’t need anything, thanks.",0);
                    break;
                    case 3:
                        dialog_add("I like to take a Dragon Ball photocopy",4);
                    break;
                    case 4:
                        dialog_add("I have no money",1);
                        dialog_add("No interest in that, thanks", 0);
                    break;
                    
                }
            break;
        }
    }
}

//update room script
void r05_update_room_script()
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
                            script_say_actor("Thank you", &r05_dialogActor);
                        break;
                        case 2:
                            script_say_actor("It is a family business of many years ago and we put a lot of love into it", &r05_dialogActor);
                        break;
                        case 3:
                            script_say_actor("We want our customers to always be satisfied", &r05_dialogActor);
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
                            script_say_actor("Of course", &r05_dialogActor);
                        break;
                        case 2:
                            script_say_actor("We're so confident in our folders that you can take one with you to try out", &r05_dialogActor);
                        break;
                        case 3:
                            script_say_actor("We also print school schedules for free", &r05_dialogActor);
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
                            script_say_actor("They are photocopies of the anime series of the moment: Dragon Ball", &r05_dialogActor);
                        break;
                        case 2:
                            script_say_actor("They are highly coveted for their collector value", &r05_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Besides, people like to trace and paint them themselves", &r05_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 4:
                    if (!is_game_flag(SCHEDULE_INFO_FLAG))
                    {
                        switch (roomScript.step)
                        {
                            case 1:
                                script_say_actor("We have an agreement with the collegue and we print the schedules to those who need it", &r05_dialogActor);
                            break;
                            case 2:
                                script_say_actor("We do it at no cost to students", &r05_dialogActor);
                            break;
                            default:
                                script_next_dialog_node();
                                set_game_flag(SCHEDULE_INFO_FLAG);
                                end_script();
                            break;
                        }
                    }
                    else
                    {
                       switch (roomScript.step)
                       {
                           case 1:
                               script_say_actor("Of course", &r05_dialogActor);
                           break;
                           case 2:
                               if (is_game_flag(PHOTOCOPY_ON_PRINTER_FLAG) && !is_game_flag(FULL_CARTRIDGE_NOT_ON_PRINTER_FLAG))
                               {
                                   roomScript.step = 10;
                               }
                               else
                               {
                                   if (object_play_animation(&r05_object[R05_EMPLOYEER_OBJ_ID], r05d_objAnimIdle, r05_animations, R05_ANIM_WALK))
                                       roomScript.step++;
                               }
                           break;
                           case 3:
                               script_say_actor("I'll print it out for you right now", &r05_dialogActor);
                               set_game_flag(EMPLOYEE_AT_COMPUTER_FLAG);
                               set_game_flag(EMPLOYEE_USING_COMPUTER_FLAG);
                           break;
                           case 4:
                                script_wait(20);
                           break;
                           case 5:
                               if (is_game_flag(PRINTED_SCHOOL_SCHEDULE_FLAG) || is_game_flag(PRINTED_SCHOOL_SCHEDULE_PHOTO_FLAG) || is_game_flag(PRINTED_PHOTOCOPY_FLAG))
                                   script_say_actor("­Oh wow! I think there's already a printed schedule from before", &r05_dialogActor);
                               else if (is_game_flag(SHEETS_NOT_ON_PRINTER_FLAG) && !is_game_flag(PHOTOCOPY_ON_PRINTER_FLAG))
                                   script_say_actor("Ummm... sorry, I ran out of sheets in the printer", &r05_dialogActor);
                               else if (is_game_flag(FULL_CARTRIDGE_NOT_ON_PRINTER_FLAG) && !is_game_flag(EMPTY_CARTRIDGE_ON_PRINTER_FLAG))
                                   script_say_actor("Ummm... sorry, the printer tells me cartridge error", &r05_dialogActor);
                               else
                               {
                                   roomScript.step = 20;
                                   play_sound(sd_printer);
                               }
                           break;
                           case 20:
                               clear_game_flag(EMPLOYEE_USING_COMPUTER_FLAG);
                               r05_object[R05_PRINTER_OBJ_ID].active = true;

                               
                               if (is_game_flag(PHOTOCOPY_ON_PRINTER_FLAG))
                               {
                                   set_game_flag(USED_PHOTOCOPY_FLAG);
                                   if (object_play_animation(&r05_object[R05_PRINTER_OBJ_ID], r05d_objPrintPhoto1, r05_animations, R05_ANIM_PRINT_PHOTO))
                                   {
                                       roomScript.step++;
                                       set_game_flag(PRINTED_PHOTOCOPY_FLAG);
                                       clear_game_flag(PHOTOCOPY_ON_PRINTER_FLAG);
                                       //r05_object[R05_PRINTEDPHOTO_OBJ_ID].active = true;
                                   }
                               }
                               else
                               {
                                   set_game_flag(USED_SHEETS_FLAG);
                                   set_game_flag(SHEETS_NOT_ON_PRINTER_FLAG);
                                   
                                   if (is_game_flag(EMPTY_CARTRIDGE_ON_PRINTER_FLAG))
                                   {
                                       if (object_play_animation(&r05_object[R05_PRINTER_OBJ_ID], r05d_objPrintSchdEmpty1, r05_animations, R05_ANIM_PRINT_SCHD_EMPTY))
                                       {
                                           roomScript.step++;
                                           set_game_flag(PRINTED_SHEET_FLAG);
                                           clear_game_flag(USED_SHEETS_FLAG);
                                       }
                                   }
                                   else
                                   {
                                       if (object_play_animation(&r05_object[R05_PRINTER_OBJ_ID], r05d_objPrintSchd1, r05_animations, R05_ANIM_PRINT_SCHD))
                                       {
                                           roomScript.step++;
                                           set_game_flag(PRINTED_SCHOOL_SCHEDULE_FLAG);
                                           //r05_object[R05_PRINTEDSCH_OBJ_ID].active = true;
                                       }
                                   }
                               }
                           break;
                           case 21:
                               script_say_actor("You got it ", &r05_dialogActor);
                               r05_object[R05_PRINTER_OBJ_ID].active = false;
                               r05_animations[r05_object[R05_PRINTER_OBJ_ID].animationId - 1].frame = 0;
                           break;
                           case 10:
                               script_say("Wait!... better than not, thank you");
                           break;
                           case 11:
                               change_player_dir(DIR_FRONT);
                               script_say("If I print the schedule on the photocopy of Dragon Ball I will damaged it");
                           break;
                           default:
                               change_player_dir(DIR_RIGHT);
                               r05_object[R05_PRINTER_OBJ_ID].active = false;
                               clear_game_flag(EMPLOYEE_USING_COMPUTER_FLAG);
                               if (is_game_flag(EMPLOYEE_AT_COMPUTER_FLAG))
                               {
                                  set_game_flag(EMPLOYEE_RETURN_FLAG);
                                  clear_game_flag(EMPLOYEE_AT_COMPUTER_FLAG);
                               }
                               script_next_dialog_node();
                               end_script();
                           break;
                       }
                    }
                break;
                case 201:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Each photocopy is worth one dime", &r05_dialogActor);
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
                            script_say_actor("Sorry. I can't give you a photocopy", &r05_dialogActor);
                        break;
                        case 2:
                            script_say_actor("It is a very precious item", &r05_dialogActor);
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
            case r05_door:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Door");
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
                                if ((is_game_flag(GOT_PHOTOCOPY_STOLEN_FLAG) || is_game_flag(GOT_PHOTOCOPY_FLAG)) && !is_game_flag(EMPLOYEER_STOLEN_ADVICE_FLAG))
                                    script_say_actor("Hey! What do you have there?", &r05_dialogActor);
                                else
                                {
                                    change_room_pos(STREET_ROOM_NUM, 258, 138);
                                    end_script();
                                }
                            break;
                            case 2:
                                change_player_dir(DIR_RIGHT);
                                if (is_game_flag(GOT_PHOTOCOPY_STOLEN_FLAG))
                                    script_say_actor("Excuse me but you can't take Dragon Ball photocopies without paying", &r05_dialogActor);
                                else
                                    script_say("Nothing. I have the school schechule sheet that you have printed for me");
                            break;
                            case 3:
                                if (is_game_flag(GOT_PHOTOCOPY_STOLEN_FLAG))
                                {
                                    script_say_actor("If you don't have any money, I prefer for returning it to me!", &r05_dialogActor);
                                    end_script();
                                }
                                else
                                    script_say_actor("Oh, excuse me. I didn't remember", &r05_dialogActor);
                                break;
                            case 4:
                                set_game_flag(EMPLOYEER_STOLEN_ADVICE_FLAG);
                                change_room_pos(STREET_ROOM_NUM, 258, 138);
                                end_script();
                            break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r05_folders:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Nice folders to put sheets in");
                                break;
                            case 1:
                                script_say("And very high quality and finishes");
                                break;
                            case 2:
                                script_say_actor("You can get one for free to try it out and make sure it's quality", &r05_dialogActor);
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
                                    if (is_game_flag(GOT_FOLDER_FLAG))
                                    {
                                        script_say("The clerk said I can only take one for free");
                                        end_script();
                                    }
                                    else
                                        script_move_player_to_target();
                                    break;
                                case 1:
                                    script_take_object(NULL, GOT_FOLDER_FLAG, id_folder);
                                    break;
                                case 2:
                                    script_say_actor("We're so confident in our folders that you can take one for free to try it out", &r05_dialogActor);
                                    break;
                                default:
                                    end_script();
                                    break;
                            }
                    break;
                }
                break;            
            case r05_stationeryMaterial:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("I've always loved stationery and the things they sell on it");
                                break;
                            case 1:
                                script_say("But I'm not interested in anything you have here!");
                                break;
                            case 2:
                                script_say_actor("All our material is top notch and at incredible prices", &r05_dialogActor);
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r05_photocopies:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("These are photocopies with drawings from the Dragon Ball series");
                                break;
                            case 1:
                                script_say_actor("Every kid in high school knows that the cool thing is to have these photocopies", &r05_dialogActor);
                                break;
                            case 2:
                                script_say_actor("For one dime, you can take the one you like the most", &r05_dialogActor);
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
                                    script_take_object(&r05_object[R05_PHOTOCOPY_OBJ_ID].active, GOT_PHOTOCOPY_STOLEN_FLAG, id_photocopy);
                                default:
                                    end_script();
                                    break;
                            }
                    break;
                }
                break;            
            case r05_paper:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (is_game_flag(PHOTOCOPY_ON_PRINTER_FLAG))
                                {
                                    script_say("I replaced the printer sheet with a photocopy of Dragon Ball");
                                    end_script();
                                }
                                else
                                    script_say("It's the paper that is loaded in the printer");
                                break;
                            default:
                                script_say("A regular A4...");
                                end_script();
                                break;
                        }
                    break;
                    case TAKE:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_move_player(R05_PRINTER_X, R05_PRINTER_Y);
                                    break;
                                case 1:
                                    change_player_dir(DIR_RIGHT);
                                    if (is_game_flag(PHOTOCOPY_ON_PRINTER_FLAG))
                                    {
                                        script_take_object(&r05_object[R05_SHEETSPHOTO_OBJ_ID].active, GOT_PHOTOCOPY_STOLEN_FLAG, id_photocopy);
                                        clear_game_flag(PHOTOCOPY_ON_PRINTER_FLAG);
                                    }
                                    else
                                    {
                                        script_take_object(&r05_object[R05_SHEETS_OBJ_ID].active, GOT_SHEETS_FLAG, id_sheet);
                                        set_game_flag(SHEETS_NOT_ON_PRINTER_FLAG);
                                    }
                                    break;
                                default:
                                    end_script();
                                    break;
                            }
                    break;
                }
                break;            
            case r05_cartridge:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It is the ink cartridge of the printer");
                                break;
                            default:
                                if (!is_game_flag(FULL_CARTRIDGE_NOT_ON_PRINTER_FLAG))
                                    script_say("Looks full");
                                else if (is_game_flag(EMPTY_CARTRIDGE_ON_PRINTER_FLAG))
                                    script_say("Looks empty");
                                end_script();
                                break;
                        }
                    break;
                    case TAKE:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_move_player(R05_PRINTER_X, R05_PRINTER_Y);
                                    break;
                                case 1:
                                    change_player_dir(DIR_RIGHT);
                                    if (!is_game_flag(FULL_CARTRIDGE_NOT_ON_PRINTER_FLAG))
                                    {
                                        set_game_flag(FULL_CARTRIDGE_NOT_ON_PRINTER_FLAG);
                                        script_take_object(&r05_object[R05_CARTRIDGEFULL_OBJ_ID].active, GOT_FULL_CARTRIDGE_FLAG, id_fullCartridge);
                                    }
                                    else if (is_game_flag(EMPTY_CARTRIDGE_ON_PRINTER_FLAG))
                                    {
                                        clear_game_flag(EMPTY_CARTRIDGE_ON_PRINTER_FLAG);
                                        if (!is_game_flag(OPENED_EMPTY_CARTRIDGE_FLAG))
                                            script_take_object(&r05_object[R05_CARTRIDGEEMPTY_OBJ_ID].active, GOT_EMPTY_CARTRIDGE_FLAG, id_emptyCartridge);
                                        else
                                            script_take_object(&r05_object[R05_CARTRIDGEEMPTY_OBJ_ID].active, GOT_EMPTY_CARTRIDGE_FLAG, id_openedEmptyCartridge);
                                    }
                                    break;
                                default:
                                    end_script();
                                    break;
                            }
                    break;
                }
                break;            
            case r05_printer:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It's the stationery's printer");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch (roomScript.invObject)
                        {
                            case id_sheet:
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
                                        clear_game_flag(SHEETS_NOT_ON_PRINTER_FLAG);
                                        clear_game_flag(GOT_SHEETS_FLAG);
                                        script_remove_inv_object(id_sheet);
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
                                        if (is_game_flag(GOT_PHOTOCOPY_STOLEN_FLAG))
                                            script_move_player_to_target();
                                        else
                                        {
                                            script_say("I better keep it");
                                            end_script();
                                        }
                                    break;
                                    case 1:
                                        script_player_take_state();
                                    break;
                                    case 2:
                                        r05_object[R05_SHEETSPHOTO_OBJ_ID].active = true;
                                        set_game_flag(PHOTOCOPY_ON_PRINTER_FLAG);
                                        clear_game_flag(GOT_PHOTOCOPY_STOLEN_FLAG);
                                        script_remove_inv_object(id_photocopy);
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                            case id_emptyCartridge:
                            case id_openedEmptyCartridge:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (!is_game_flag(FULL_CARTRIDGE_NOT_ON_PRINTER_FLAG))
                                        {
                                            script_say("There is already a cartridge in the printer");
                                            end_script();
                                        }
                                        else
                                            script_move_player(R05_PRINTER_X, R05_PRINTER_Y);
                                    break;
                                    case 1:
                                        script_player_take_state();
                                    break;
                                    case 2:
                                        r05_object[R05_CARTRIDGEEMPTY_OBJ_ID].active = true;
                                        set_game_flag(EMPTY_CARTRIDGE_ON_PRINTER_FLAG);
                                        clear_game_flag(GOT_EMPTY_CARTRIDGE_FLAG);
                                        script_remove_inv_object(roomScript.invObject);
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                            case id_fullCartridge:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (is_game_flag(EMPTY_CARTRIDGE_ON_PRINTER_FLAG))
                                        {
                                            script_say("There is already a cartridge in the printer");
                                            end_script();
                                        }
                                        else
                                            script_move_player(R05_PRINTER_X, R05_PRINTER_Y);
                                    break;
                                    case 1:
                                        script_player_take_state();
                                    break;
                                    case 2:
                                        r05_object[R05_CARTRIDGEFULL_OBJ_ID].active = true;
                                        clear_game_flag(FULL_CARTRIDGE_NOT_ON_PRINTER_FLAG);
                                        clear_game_flag(GOT_FULL_CARTRIDGE_FLAG);
                                        script_remove_inv_object(id_fullCartridge);
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
            case r05_printedPaper:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (is_game_flag(PRINTED_SCHOOL_SCHEDULE_FLAG))
                                    script_say("The printer has printed the high school schedule on both sides");
                                else if (is_game_flag(PRINTED_SCHOOL_SCHEDULE_PHOTO_FLAG))
                                    script_say("The printer has printed the high school schedule on top of the Dragon Ball photocopy");
                                else if (is_game_flag(PRINTED_PHOTOCOPY_FLAG))
                                    script_say("As the cartridge had no ink, the printer took out the photocopy of Dragon Ball without any damage");
                                else if (is_game_flag(PRINTED_SHEET_FLAG))
                                    script_say("As the cartridge had no ink, the printer took out the sheet without printing anything");
                                else
                                    end_script();
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
                                    script_move_player(R05_PRINTER_X, R05_PRINTER_Y);
                                    break;
                                case 1:
                                    change_player_dir(DIR_RIGHT);
                                    if (is_game_flag(PRINTED_SCHOOL_SCHEDULE_FLAG))
                                    {
                                        clear_game_flag(PRINTED_SCHOOL_SCHEDULE_FLAG);
                                        script_take_object(&r05_object[R05_PRINTEDSCH_OBJ_ID].active, GOT_PRINTED_SCH_FLAG, id_schedule);
                                    }
                                    else if (is_game_flag(PRINTED_SCHOOL_SCHEDULE_PHOTO_FLAG))
                                    {
                                        clear_game_flag(PRINTED_SCHOOL_SCHEDULE_PHOTO_FLAG);
                                        script_take_object(&r05_object[R05_PRINTEDSCHPHOTO_OBJ_ID].active, GOT_PRINTED_SCH_PHOTO_FLAG, id_photocopySchedule);
                                    }
                                    else if (is_game_flag(PRINTED_PHOTOCOPY_FLAG))
                                    {
                                        clear_game_flag(PRINTED_PHOTOCOPY_FLAG);
                                        script_take_object(&r05_object[R05_PRINTEDPHOTO_OBJ_ID].active, GOT_PHOTOCOPY_FLAG, id_photocopy);
                                    }
                                    else if (is_game_flag(PRINTED_SHEET_FLAG))
                                    {
                                        clear_game_flag(PRINTED_SHEET_FLAG);
                                        script_take_object(&r05_object[R05_PRINTEDSHEET_OBJ_ID].active, GOT_SHEETS_FLAG, id_sheet);
                                    }
                                    break;
                                default:
                                    end_script();
                                    break;
                            }
                    break;
                }
                break;            
            case r05_mouse:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It's the mouse of the stationery computer");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r05_monitor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It's the monitor of the stationery computer");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;
            case r05_employee:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It's the helpful stationery dependent");
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
                                script_move_player(137, 88);
                            break;
                            case 1:
                                change_player_dir(DIR_RIGHT);
                                script_say_actor("Hi! How can I help you?", &r05_dialogActor);
                            break;
                            case 2:
                                script_start_dialog(1);
                                end_script();
                            break;
                        }
                    break;
                    case GIVE:
                        switch (roomScript.invObject)
                        {
                            case id_photocopy:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_say_actor("Thaaaaank youuuuu", &r05_dialogActor);
                                    break;
                                    case 1:
                                        clear_game_flag(GOT_PHOTOCOPY_STOLEN_FLAG);
                                        r05_object[R05_PHOTOCOPY_OBJ_ID].active = true;
                                        script_remove_inv_object(id_photocopy);
                                    break;
                                    default:
                                        end_script();
                                    break;
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
                                        script_say_actor("Oh...Thank you, pero no sabr¡a que hacer con esto", &r05_dialogActor);
                                    break;
                                    case 1:
                                        script_say_actor("Very kind, but I don't need it", &r05_dialogActor);
                                    break;
                                    case 2:
                                        script_say_actor("No thanks, we don't use those kinds of items", &r05_dialogActor);
                                    break;
                                    case 3:
                                        script_say_actor("Ummm, I am not interested", &r05_dialogActor);
                                    break;
                                    case 4:
                                        script_say_actor("You may need it more than me", &r05_dialogActor);
                                    break;
                                }
                                end_script();
                            break;
                        }
                    break;
                }
                break;
            case R05_WELLCOME_SCRIPT:
                switch (roomScript.step)
                {
                    case 0:
                        begin_script();
                        if (!is_game_flag(WELLCOME_FLAG))
                            script_say_actor("Hi! Welcome to our stationery", &r05_dialogActor);
                        else
                        {
                            script_say_actor("Hi! Welcome back", &r05_dialogActor);
                            end_script();
                        }
                        break;
                    case 1:
                        script_say_actor("See what you need and ask what you want", &r05_dialogActor);
                        break;
                    case 2:
                        script_say_actor("I'm Here to help", &r05_dialogActor);
                        set_game_flag(WELLCOME_FLAG);
                        break;
                    default:
                        end_script();
                        break;
                }
                break;
        }
    }
}
