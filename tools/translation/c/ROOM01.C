/*
=========================================================
 Room Number:   01
 Room Name:     01_bedRoom
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room01.h"

//Funtion to return the name of hotspot by color code
void r01_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r01_guitar:
                strcpy(s, "Guitar");
            break;
        case r01_stereo:
                strcpy(s, "Mini Chain");
            break;
        case r01_door:
                strcpy(s, "Gate");
            break;
        case r01_cassette:
            if (!is_game_flag(GOT_CASSETTE_FLAG))
                strcpy(s, "Compact Cassette");
            else
                strcpy(s, "");    
            break;
        case r01_spider:
                strcpy(s, "9 beta Arabinofuranosyladenine");
            break;
        case r01_drums:
                strcpy(s, "Drum");
            break;
        case r01_thing:
            if (!is_game_flag(GOT_COIN_FLAG))
                strcpy(s, "Thing");
            else
                strcpy(s, "");
            break;
        case r01_glasses:
                strcpy(s, "Glasses");
            break;
        case r01_cd:
                strcpy(s, "Cd");
            break;
        case r01_poster:
                strcpy(s, "Poster");
            break;
        case r01_draws:
                strcpy(s, "Drawers");
            break;
        case r01_sofa:
                strcpy(s, "Zeph.&#09;");
            break;
        case r01_computer:
                strcpy(s, "Computer");
            break;
        case r01_toys:
                strcpy(s, "Figures");
            break;
        case r01_cartridge:
            if (is_game_flag(r01_object[R01_CARTRIDGE_OBJ_ID].active))
            {
                strcpy(s, "Empty cartridge");
                break;
            }
        case r01_printer:
                strcpy(s, "Printer");
            break;
        case r01_book1:
                strcpy(s, "Book 1");
            break;
        case r01_book2:
            if (!is_game_flag(GOT_BOOK_FLAG))
                strcpy(s, "Book 3");
            else
                strcpy(s, "");
            break;
        case r01_book3:
                strcpy(s, "Revista");
            break;
        case r01_book4:
                strcpy(s, "Book 2");
            break;
        case r01_window:
                strcpy(s, "Window");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r01_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r01_guitar:
            return LOOK;
            break;
        case r01_stereo:
            return LOOK;
            break;
        case r01_door:
            return OPEN;
            break;
        case r01_cassette:
            return LOOK;
            break;
        case r01_spider:
            return LOOK;
            break;
        case r01_drums:
            return LOOK;
            break;
        case r01_thing:
            return LOOK;
            break;
        case r01_glasses:
            return LOOK;
            break;
        case r01_cd:
            return LOOK;
            break;
        case r01_poster:
            return LOOK;
            break;
        case r01_draws:
            return OPEN;
            break;
        case r01_sofa:
            return LOOK;
            break;
        case r01_computer:
            return USE;
            break;
        case r01_toys:
            return LOOK;
            break;
        case r01_cartridge:
            if (is_game_flag(r01_object[R01_CARTRIDGE_OBJ_ID].active))
            {
                return LOOK;
                break;
            }
        case r01_printer:
            return LOOK;
            break;
        case r01_book1:
            return LOOK;
            break;
        case r01_book2:
            return LOOK;
            break;
        case r01_book3:
            return LOOK;
            break;
        case r01_book4:
            return LOOK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r01_get_object_info(uint8_t numObject)
{
    if (numObject < R01_ROOM_NUM_OBJS)
        return &r01_object[numObject];
    else
        return NULL;
}

//function to init room
void r01_room_init()
{
    //rewind computer animation
    r01_animations[R01_COMPUTER_OBJ_ID].frameTime = 0;
    r01_animations[R01_COMPUTER_OBJ_ID].frame = r01d_objCompBoot1;
    
    if (!is_game_flag(GAME_START_FLAG))
        start_script(R01_GAME_START_SCRIPT);
        
    game_fade_in();
}

//global funcion to update room
void r01_room_update()
{
    //update room objects
    r01_update_room_objects();

    //update dialog line selection
    r01_update_dialog_selection();
    
    //update room script
    r01_update_room_script();
}

//update room objects
void r01_update_room_objects()
{
    //Stereo
    r01_object[R01_STEREO01_OBJ_ID].active  = is_game_flag(STEREO_ON_FLAG);
    object_play_animation(&r01_object[R01_STEREO01_OBJ_ID], r01d_objStereo01, r01_animations, R01_ANIM_PLAY_STEREO);

    r01_object[R01_COMPUTER_OBJ_ID].active  = is_game_flag(USED_COMPUTER_FLAG);
    r01_object[R01_COIN_OBJ_ID].active      = !is_game_flag(GOT_COIN_FLAG);
    r01_object[R01_CASSETTE_OBJ_ID].active  = !is_game_flag(GOT_CASSETTE_FLAG);
    r01_object[R01_BOOK_OBJ_ID].active      = !is_game_flag(GOT_BOOK_FLAG);
    //r01_object[R01_GUITAR_OBJ_ID].active  = !is_game_flag(GOT_GUITAR_FLAG);

    r01_object[R01_OPENPRINTER_OBJ_ID].active   = is_game_flag(OPEN_PRINTER_FLAG);
    r01_object[R01_CARTRIDGE_OBJ_ID].active     = is_game_flag(OPEN_PRINTER_FLAG) && !is_game_flag(GOT_EMPTY_CARTRIDGE_FLAG);
}

//update dialog selection
void r01_update_dialog_selection()
{

}

//update room script
void r01_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r01_guitar:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("My Sonora brand guitar");
                                break;
                            case 1:
                                script_say("My frustrated attempt to be a rock star");
                                break;
                            default:
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
                                script_say("It's better to stay in the case");
                                break;
                            case 1:
                                script_say(" and for the sake ofmusic, and for the sake ofmusic");
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r01_stereo:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (!is_game_flag(STEREO_ON_FLAG))
                                    script_say("Is my mini chain Hifi £last model");
                                else
                                {
                                    script_say("The mini-chain is running");
                                    end_script();
                                }
                                break;
                            case 1:
                                script_say(" radio tuner and graphic equalizer, radio tuner and graphic equalizer");
                                break;
                            case 2:
                                if (!is_game_flag(USED_CASSETTE_FLAG))
                                    script_say("-Hallucinating!");
                                else
                                    script_say("You now have a tape inside");
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
                                if (!is_game_flag(USED_CASSETTE_FLAG))
                                {
                                    script_say("There is no cassette inside to listen to");
                                    end_script();
                                }
                                else if (is_game_flag(CASSETTE_BROKEN_FLAG))
                                {
                                    script_say("Tape has snagged");
                                    end_script();
                                }
                                else
                                    script_move_player_to_target();
                                break;
                            case 1:
                                script_play_sound(sd_cassettePlay);
                            break;
                            case 2:
                                script_player_take_state();
                                break;
                            case 3:
                                toggle_game_flag(STEREO_ON_FLAG);
                                r01_object[R01_STEREO01_OBJ_ID].active = is_game_flag(STEREO_ON_FLAG);
                                roomScript.step++;
                            break;
                            case 4:
                                script_play_sound(sd_cassetteSong);
                            break;
                            case 5:
                                script_wait(110);
                            break;
                            case 6:
                                play_player_animation(ANIM_PLY_SURPRISE);
                                script_wait(20);
                            break;
                            case 7:
                                clear_game_flag(STEREO_ON_FLAG);
                                set_game_flag(CASSETTE_BROKEN_FLAG);
                                script_say("Tape has already been hooked");
                            break;
                            default:
                                end_script();
                                break;
                        }
                        break;
                    case USE_WITH:
                        switch (roomScript.invObject)
                        {
                            case id_cassette:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_move_player_to_target();
                                        break;
                                    case 1:
                                        script_play_sound(sd_cassettePut);
                                    break;
                                    case 2:
                                        script_player_take_state();
                                        break;
                                    case 3:
                                        script_remove_inv_object(id_cassette);
                                        set_game_flag(USED_CASSETTE_FLAG);
                                        end_script();
                                        break;
                                }
                                break;
                        }
                        break;
                }
                break;            
            case r01_door:
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
                    case OPEN ... CLOSE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It's always  open");
                                break;
                            case 1:
                                begin_script();
                                script_say("I have no secrets for my parents...");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case GO:
                    case USE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player(roomScript.hsX,154);
                            break;
                            case 1:
                                script_move_player_no_clip(roomScript.hsX, 240);
                            break;
                            case 2:
                                change_room_pos(CORRIDOR_ROOM_NUM,174,38);
                                end_script();
                                break;
                        }
                        break;
                }
                break;            
            case r01_cassette:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It is a cassette of the last thing that\ "Repeaters\" has taken out");
                                break;
                            case 1:
                                begin_script();
                                script_say("Thelast purchase I was able to make when I had money");
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
                                script_take_object(&r01_object[R01_CASSETTE_OBJ_ID].active, GOT_CASSETTE_FLAG, id_cassette);
                                end_script();
                                break;
                        }
                        break;
                }
                break;            
            case r01_spider:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It is my exclusive ara¤a figure from the He-man series");
                                break;
                            case 1:
                                begin_script();
                                script_say("-BY THE POWER OF GREYSKULL!");
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
                                script_say("I don't think a toy earring is very useful");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r01_drums:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It's my drum from my drummer bit");
                                break;
                            case 1:
                                begin_script();
                                script_say(" I had not yet discovered rock");
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
                                script_say("I left the drum a long time ago");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r01_thing:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("I don't know what that could be...");
                                break;
                            case 1:
                                begin_script();
                                script_say("It shines a little and seems to be stuck to the ground...");
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
                                script_say("I can't catch it");
                                break;
                            case 1:
                                begin_script();
                                script_say("It is  very close to the ground");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch (roomScript.invObject)
                        {
                            case id_spatula:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_move_player_to_target();
                                        break;
                                    case 1:
                                        script_play_sound(sd_unglue);
                                    break;
                                    case 2:
                                        set_game_flag(GOT_COIN_FLAG);
                                        r01_object[R01_COIN_OBJ_ID].active = false;
                                        script_add_inv_object(id_coin);
                                        break;
                                    case 3:
                                        script_say("­Eureka! With the sputum I was able to take it off");
                                        break;
                                    case 4:
                                        script_say("-It's a 100 pesetas coin!");
                                        end_script();
                                        break;
                                }
                                break;
                            case id_knife:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_say("It has very little surface to leverage");
                                    break;
                                    case 1:
                                        script_say("I need something wider");
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
            case r01_glasses:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say(" far and reading, far and reading");
                                break;
                            case 1:
                                begin_script();
                                script_say("I also wear them when I wear contact lenses");
                                break;
                            default:
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
                                script_say("I don't think I need them");
                                break;
                            case 1:
                                begin_script();
                                script_say("With this 320x240 VGA resolution the pixels are like pu¤os");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r01_cd:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A friend brought to school what they call compact disc");
                                break;
                            case 1:
                                script_say("It's supposed to be the music format of the future");
                                break;
                            case 2:
                                script_say(" I have it hanging there because it shines");
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
                                script_say("Ah¡it 's  okay");
                                break;
                            case 1:
                                script_say("Its brightness drives away mosquitoes");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r01_poster:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("My other favorite group: Los de Marras");
                            break;
                            case 1:
                                script_say("I have a feeling that this group is going to do very well in the future");
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
                                script_say("It is  better attached to the wall");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r01_draws:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("These drawers keep nothing but porquer¡a inside");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE:
                    case OPEN:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("There is nothing of interest inside");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r01_sofa:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("How many kids can afford to have a sofa in their room?");
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
                                script_say("I don't have time to rest");
                                break;
                            case 1:
                                script_say("I have to figure out how to get money for the concert ticket");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r01_computer:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("My brand new 100Mhz Pentium");
                                break;
                            case 1:
                                script_say("I recently installed Windows 95 for you");
                                break;
                            case 2:
                                script_say("But I still prefer my old MS-DOS");
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
                                script_move_player(235, 142);
                            break;
                            case 1:
                                player_take_state();
                                set_game_flag(USED_COMPUTER_FLAG);
                                script_play_sound(sd_computerBoot);
                            break;
                            case 2:
                                script_object_play_animation(&r01_object[R01_COMPUTER_OBJ_ID], r01d_objCompBoot1, r01_animations, R01_ANIM_ON_COMPUTER);
                            break;
                            case 3:
                                object_play_animation(&r01_object[R01_COMPUTER_OBJ_ID], r01d_objCompBoot6, r01_animations, R01_ANIM_BIOS_COMPUTER);
                                script_play_sound_wait(sd_computerBoot);
                            break;
                            case 4:
                                play_player_animation(ANIM_PLY_HAPPY_IDLE);
                                script_play_sound_wait(sd_win95Startup);
                                object_play_animation(&r01_object[R01_COMPUTER_OBJ_ID], r01d_objCompBoot6, r01_animations, R01_ANIM_W95_COMPUTER);
                            break;
                            case 5:
                                play_player_animation(ANIM_PLY_SURPRISE);
                                script_play_sound_wait(sd_w95Error);
                                object_play_animation(&r01_object[R01_COMPUTER_OBJ_ID], r01d_objCompBoot6, r01_animations, R01_ANIM_ERROR_COMPUTER);
                            break;
                            case 6:
                                script_say("I hate windows...");
                            break;
                            case 7:
                                script_player_take_state();
                            break;
                            default:
                                clear_game_flag(USED_COMPUTER_FLAG);
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r01_toys:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("They are my figures of the Knights of the Zodiac Limited Edition");
                                break;
                            case 1:
                                begin_script();
                                script_say("Look how those chromes shine...");
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
                                script_say("I'd rather leave them here!");
                                break;
                            case 1:
                                begin_script();
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 57 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r01_cartridge:
                if (is_game_flag(r01_object[R01_CARTRIDGE_OBJ_ID].active))
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 57 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                                case 1:
                                    script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 57 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
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
                                    script_take_object(NULL, GOT_EMPTY_CARTRIDGE_FLAG, id_emptyCartridge);
                                    break;
                                case 2:
                                    script_wait(5);
                                    break;
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                break;
                }
            case r01_printer:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 56 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            case 1:
                                if (!is_game_flag(OPEN_PRINTER_FLAG))
                                    script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 56 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                else
                                    script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 56 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            case 2:
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 55 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
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
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 55 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            case 1:
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 55 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch (roomScript.invObject)
                        {
                            case id_fullCartridge:
                                begin_script();
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 54 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                end_script();
                            break;
                        }
                    break;
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 54 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
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
                                if (!is_game_flag(OPEN_PRINTER_FLAG))
                                    script_move_player_to_target();
                                else
                                {
                                    script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 54 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                    end_script();
                                }
                            break;
                            case 1:
                                script_play_sound(sd_lidOpen);
                            break;
                            case 2:
                                script_player_take_state();
                                set_game_flag(OPEN_PRINTER_FLAG);
                            break;
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
                                if (is_game_flag(OPEN_PRINTER_FLAG))
                                    script_move_player_to_target();
                                else
                                {
                                    script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 53 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                    end_script();
                                }
                            break;
                            case 1:
                                script_play_sound(sd_lidClose);
                            break;
                            case 2:
                                script_player_take_state();
                                clear_game_flag(OPEN_PRINTER_FLAG);
                            break;
                            default:
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case r01_book1:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 53 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            case 1:
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 52 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            default:
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
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 52 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r01_book4:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 52 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            case 1:
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 51 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            default:
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
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 51 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            case 1:
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 51 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                            break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r01_book2:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 50 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            case 1:
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 50 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
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
                                script_take_object(&r01_object[R01_BOOK_OBJ_ID].active, GOT_BOOK_FLAG, id_book);
                                end_script();
                                break;
                        }
                        break;
                }
                break;            
            case r01_book3:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 50 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            case 1:
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 49 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            default:
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
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 49 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE,MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 49 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
            break;
            case r01_window:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 49 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                            break;
                            case 1:
                                script_play_sound_wait(sd_dogBarf);
                                play_player_animation(ANIM_PLY_SURPRISE);
                            break;
                            case 2:
                                stop_player_animation();
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 48 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                            break;
                            case 3:
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 48 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                            break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE:
                    case OPEN:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 48 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                break;
                            case 1:
                                script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 47 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case R01_GAME_START_SCRIPT:
                switch(roomScript.step)
                {
                    case 0:
                        begin_script();
                        script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 47 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                    break;
                    case 1:
                        script_say("MYMEMORY WARNING: YOU USED ALL AVAILABLE FREE TRANSLATIONS FOR TODAY. NEXT AVAILABLE IN  12 HOURS 58 MINUTES 47 SECONDS VISIT HTTPS://MYMEMORY.TRANSLATED.NET/DOC/USAGELIMITS.PHP TO TRANSLATE MORE");
                    break;
                    case 2:
                        set_game_flag(GAME_START_FLAG);
                        end_script();
                    break;
                }
            break;
        }
    }
}
