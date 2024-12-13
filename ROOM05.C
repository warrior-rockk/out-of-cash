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
                strcpy(s, "Puerta");
            break;
        case r05_folders:
                strcpy(s, "Carpetas");
            break;
        case r05_stationeryMaterial:
                strcpy(s, "Material papeler¡a");
            break;
        case r05_photocopies:
            if (is_game_flag(GOT_PHOTOCOPY_STOLEN_FLAG))
                strcpy(s, "");
            else
                strcpy(s, "Fotocopias");
            break;
        case r05_paper:
            if (is_game_flag(GOT_SHEETS_FLAG))
                strcpy(s, "");
            else
                strcpy(s, "Papel");
            break;
        case r05_cartridge:
            if (is_game_flag(GOT_CARTRIDGE_FULL_FLAG))
                strcpy(s, "");
            else
                strcpy(s, "Cartucho ");
            break;
        case r05_printer:
                strcpy(s, "Impresora");
            break;
        case r05_printedPaper:
            if (is_game_flag(PRINTED_SCHOOL_SCHEDULE_FLAG) ||
                is_game_flag(PRINTED_SCHOOL_SCHEDULE_PHOTO_FLAG) ||
                is_game_flag(PRINTED_PHOTOCOPY_FLAG))
                strcpy(s, "Papel impreso");
            else
                strcpy(s, "");
            break;
        case r05_mouse:
                strcpy(s, "Rat¢n");
            break;
        case r05_monitor:
                strcpy(s, "Monitor");
            break;
        case r05_employee:
            strcpy(s, "Dependiente");
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
    r05_object[R05_PHOTOCOPY_OBJ_ID].active = !is_game_flag(GOT_PHOTOCOPY_STOLEN_FLAG);
    r05_object[R05_SHEETS_OBJ_ID].active = !is_game_flag(GOT_SHEETS_FLAG);
    r05_object[R05_CARTRIDGEFULL_OBJ_ID].active = !is_game_flag(GOT_CARTRIDGE_FULL_FLAG);

    r05_object[R05_PRINTEDSCH_OBJ_ID].active = is_game_flag(PRINTED_SCHOOL_SCHEDULE_FLAG);
    r05_object[R05_PRINTEDSCHPHOTO_OBJ_ID].active = is_game_flag(PRINTED_SCHOOL_SCHEDULE_PHOTO_FLAG);
    r05_object[R05_PRINTEDPHOTO_OBJ_ID].active = is_game_flag(PRINTED_PHOTOCOPY_FLAG);
}

//update dialog selection
void r05_update_dialog_selection()
{

}

//update room script
void r05_update_room_script()
{
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
                                script_say("Puerta");
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
                                change_room_pos(STREET_ROOM_NUM, 258, 138);
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
                                script_say("Unas bonitas carpetas para meter folios");
                                break;
                            case 1:
                                script_say("Y de muy alta calidad y acabados");
                                break;
                            case 2:
                                script_say_actor("Puedes llevarte una gratis para probarla y asegurarte de su calidad", &r05_dialogActor);
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
                                        script_say("El dependiente ha dicho que solo me puedo llevar una gratis");
                                    else
                                        script_move_player_to_target();
                                    break;
                                case 1:
                                    if (is_game_flag(GOT_FOLDER_FLAG))
                                        script_say_actor("Asi es", &r05_dialogActor);
                                    else
                                        script_take_object(NULL, GOT_FOLDER_FLAG, id_folder);
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
                                script_say("Siempre me han encantado las papeler¡as y las cosas que venden en ellas");
                                break;
                            case 1:
                                script_say("Pero no me interesa nada de lo que tienen aqu¡");
                                break;
                            case 2:
                                script_say_actor("Todo nuestro material es de primera y a unos precios incre¡bles", &r05_dialogActor);
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
                                script_say("Son unas fotocopias con dibujos de la serie Dragon Ball");
                                break;
                            case 1:
                                script_say_actor("Todo chaval del instituto sabe que lo mas mol¢n es tener estas fotocopias", &r05_dialogActor);
                                break;
                            case 2:
                                script_say_actor("Por 25 pesetas puedes llevarte la que mas te guste", &r05_dialogActor);
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
                                script_say("Es el papel que hay cargado en la impresora");
                                break;
                            default:
                                script_say("Un A4 est ndar...");
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
                                    script_take_object(&r05_object[R05_SHEETS_OBJ_ID].active, GOT_SHEETS_FLAG, id_sheet);
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
                                script_say("Es el cartucho de tinta de la impresora");
                                break;
                            default:
                                script_say("Parece lleno");
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
                                    script_take_object(&r05_object[R05_CARTRIDGEFULL_OBJ_ID].active, GOT_CARTRIDGE_FULL_FLAG, id_fullCartridge);
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
                                script_say("Es la impresora de la papeler¡a");
                                break;
                            default:
                                end_script();
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
                                    script_say("La impresora ha impreso el horario del instituto por las 2 caras");
                                else if (is_game_flag(PRINTED_SCHOOL_SCHEDULE_PHOTO_FLAG))
                                    script_say("La impresora ha impreso el horario del instituto encima de la fotocopia de Dragon Ball");
                                else if (is_game_flag(PRINTED_PHOTOCOPY_FLAG))
                                    script_say("Como el cartucho no tenia tinta, la impresora ha sacado la fotocopia de Dragon Ball sin ning£n da¤o");
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
                                    script_move_player_to_target();
                                    break;
                                case 1:
                                    if (is_game_flag(PRINTED_SCHOOL_SCHEDULE_FLAG))
                                        script_take_object(&r05_object[R05_PRINTEDSCH_OBJ_ID].active, GOT_PRINTED_SCH_FLAG, id_schedule);
                                    else if (is_game_flag(PRINTED_SCHOOL_SCHEDULE_PHOTO_FLAG))
                                        script_take_object(&r05_object[R05_PRINTEDSCHPHOTO_OBJ_ID].active, GOT_PRINTED_SCH_PHOTO_FLAG, id_photocopySchedule);
                                    else if (is_game_flag(PRINTED_PHOTOCOPY_FLAG))
                                        script_take_object(&r05_object[R05_PRINTEDPHOTO_OBJ_ID].active, GOT_PHOTOCOPY_FLAG, id_photocopy);
                                    break;
                                case 2:
                                    if (is_game_flag(PRINTED_SCHOOL_SCHEDULE_FLAG))
                                        clear_game_flag(PRINTED_SCHOOL_SCHEDULE_FLAG);
                                    else if (is_game_flag(PRINTED_SCHOOL_SCHEDULE_PHOTO_FLAG))
                                        clear_game_flag(PRINTED_SCHOOL_SCHEDULE_PHOTO_FLAG);
                                    else if (is_game_flag(PRINTED_PHOTOCOPY_FLAG))
                                        clear_game_flag(PRINTED_PHOTOCOPY_FLAG);
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
                                script_say("Es el rat¢n del ordenador de la papeler¡a");
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
                                script_say("Es el monitor del ordenador de la papeler¡a");
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
                                script_say("Es el servicial dependiente de la papeler¡a");
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
                                script_say_actor("­Hola! ¨En que te puedo ayudar?", &r05_dialogActor);
                                break;
                            case 1:
                                script_start_dialog(1);
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
                        script_say_actor("Bienvenido a nuestra papeler¡a", &r05_dialogActor);
                        break;
                    case 1:
                        script_say_actor("Mira todo lo que necesites y pregunta lo que quieras", &r05_dialogActor);
                        break;
                    case 2:
                        script_say_actor("Estamos aqu¡ para ayudar", &r05_dialogActor);
                        break;
                    default:
                        end_script();
                        break;
                }
                break;
        }
    }
}
