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
            if (!r05_object[R05_PHOTOCOPY_OBJ_ID].active)
                strcpy(s, "");
            else
                strcpy(s, "Fotocopias");
            break;
        case r05_paper:
            if (r05_object[R05_SHEETS_OBJ_ID].active || r05_object[R05_SHEETSPHOTO_OBJ_ID].active)
                strcpy(s, "Papel");
            else
                strcpy(s, "");
            break;
        case r05_printer:
                strcpy(s, "Impresora");
            break;    
        case r05_cartridge:
            if (is_game_flag(FULL_CARTRIDGE_NOT_ON_PRINTER_FLAG) && !is_game_flag(EMPTY_CARTRIDGE_ON_PRINTER_FLAG))
                strcpy(s, "");
            else
                strcpy(s, "Cartucho ");
            break;
        case r05_printedPaper:
            if (is_game_flag(PRINTED_SCHOOL_SCHEDULE_FLAG) ||
                is_game_flag(PRINTED_SCHOOL_SCHEDULE_PHOTO_FLAG) ||
                is_game_flag(PRINTED_PHOTOCOPY_FLAG) ||
                is_game_flag(PRINTED_SHEET_FLAG))
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
                        dialog_add("Bonita papeler¡a...",1);
                        dialog_add("¨Puedo llevarme una carpeta?",1);
                        dialog_add("¨Qu‚ son estas fotocopias que ten‚is?",3);
                        if (!is_game_flag(SCHEDULE_INFO_FLAG))
                            dialog_add("¨Para qu‚ es la impresora?",1);
                        else
                            dialog_add("¨Me puedes imprimir un horario?",0);
                        dialog_add("No necesito nada, gracias",0);
                    break;
                    case 3:
                        dialog_add("Me gustar¡a llevarme una fotocopia de Dragon Ball",4);
                    break;
                    case 4:
                        dialog_add("No tengo dinero...",1);
                        dialog_add("No me interesa, gracias", 0);
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
                            script_say_actor("Gracias", &r05_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Es un negocio familiar de hace muchos a¤os y le ponemos mucho cari¤o", &r05_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Queremos que nuestros clientes est‚n siempre satisfechos", &r05_dialogActor);
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
                            script_say_actor("Por supuesto", &r05_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Tenemos tanta confianza en nuestras carpetas que puedes llevarte una para probarla", &r05_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Tambi‚n imprimimos los horarios del instituto gratis", &r05_dialogActor);
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
                            script_say_actor("Son fotocopias de la serie anime del momento: Dragon Ball", &r05_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Son muy codiciadas por su valor coleccionista", &r05_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Adem s a la gente les gusta calcarlas y pintarlas por ellos mismos", &r05_dialogActor);
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
                                script_say_actor("Tenemos un convenio con el instituto e imprimimos los horarios a quien lo necesite", &r05_dialogActor);
                            break;
                            case 2:
                                script_say_actor("Lo hacemos sin coste alguno para los alumnos", &r05_dialogActor);
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
                               script_say_actor("Por supuesto", &r05_dialogActor);
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
                               script_say_actor("Te lo imprimo ahora mismo", &r05_dialogActor);
                               set_game_flag(EMPLOYEE_AT_COMPUTER_FLAG);
                               set_game_flag(EMPLOYEE_USING_COMPUTER_FLAG);
                           break;
                           case 4:
                                script_wait(20);
                           break;
                           case 5:
                               if (is_game_flag(PRINTED_SCHOOL_SCHEDULE_FLAG) || is_game_flag(PRINTED_SCHOOL_SCHEDULE_PHOTO_FLAG) || is_game_flag(PRINTED_PHOTOCOPY_FLAG))
                                   script_say_actor("­Oh vaya! Creo que ya hay un horario impreso de antes", &r05_dialogActor);
                               else if (is_game_flag(SHEETS_NOT_ON_PRINTER_FLAG) && !is_game_flag(PHOTOCOPY_ON_PRINTER_FLAG))
                                   script_say_actor("Ummm... Lo siento, me he quedado sin hojas en la impresora", &r05_dialogActor);
                               else if (is_game_flag(FULL_CARTRIDGE_NOT_ON_PRINTER_FLAG) && !is_game_flag(EMPTY_CARTRIDGE_ON_PRINTER_FLAG))
                                   script_say_actor("Ummm... Lo siento, la impresora me dice error de cartucho", &r05_dialogActor);
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
                               script_say_actor("Ya lo tienes", &r05_dialogActor);
                               r05_object[R05_PRINTER_OBJ_ID].active = false;
                               r05_animations[r05_object[R05_PRINTER_OBJ_ID].animationId - 1].frame = 0;
                           break;
                           case 10:
                               script_say("­Espera!... mejor no, gracias");
                           break;
                           case 11:
                               script_say("(Si imprimo el horario sobre la fotocopia de Dragon Ball la voy a estropear)");
                           break;
                           default:
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
                            script_say_actor("Cada fotocopia vale 25 pesetas", &r05_dialogActor);
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
                            script_say_actor("Lo siento. No te puedo regalar una fotocopia", &r05_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Es un art¡culo muy preciado", &r05_dialogActor);
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
                            case 1:
                                if ((is_game_flag(GOT_PHOTOCOPY_STOLEN_FLAG) || is_game_flag(GOT_PHOTOCOPY_FLAG)) && !is_game_flag(EMPLOYEER_STOLEN_ADVICE_FLAG))
                                    script_say_actor("­Oye! ¨Que llevas ah¡?", &r05_dialogActor);
                                else
                                {
                                    change_room_pos(STREET_ROOM_NUM, 258, 138);
                                    end_script();
                                }
                            break;
                            case 2:
                                change_player_dir(DIR_RIGHT);
                                if (is_game_flag(GOT_PHOTOCOPY_STOLEN_FLAG))
                                    script_say_actor("Disculpa pero no puedes llevarte las fotocopias de Dragon Ball sin pagar", &r05_dialogActor);
                                else
                                    script_say("Nada. Llevo la hoja del horario del instituto que me has impreso");
                            break;
                            case 3:
                                if (is_game_flag(GOT_PHOTOCOPY_STOLEN_FLAG))
                                {
                                    script_say_actor("Si no tienes dinero te agradecer¡a que me las devolvieras", &r05_dialogActor);
                                    end_script();
                                }
                                else
                                    script_say_actor("Ah si perdona. No me acordaba", &r05_dialogActor);
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
                                    {
                                        script_say("El dependiente ha dicho que solo me puedo llevar una gratis");
                                        end_script();
                                    }
                                    else
                                        script_move_player_to_target();
                                    break;
                                case 1:
                                    script_take_object(NULL, GOT_FOLDER_FLAG, id_folder);
                                    break;
                                case 2:
                                    script_say_actor("Tenemos tanta confianza en nuestras carpetas que puedes llevarte una gratis para probarla", &r05_dialogActor);
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
                                if (is_game_flag(PHOTOCOPY_ON_PRINTER_FLAG))
                                {
                                    script_say("He sustituido las hojas de la impresora por una fotocopia de Dragon Ball");
                                    end_script();
                                }
                                else
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
                                script_say("Es el cartucho de tinta de la impresora");
                                break;
                            default:
                                if (!is_game_flag(FULL_CARTRIDGE_NOT_ON_PRINTER_FLAG))
                                    script_say("Parece lleno");
                                else if (is_game_flag(EMPTY_CARTRIDGE_ON_PRINTER_FLAG))
                                    script_say("Parece vac¡o");
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
                                        script_take_object(&r05_object[R05_CARTRIDGEEMPTY_OBJ_ID].active, GOT_EMPTY_CARTRIDGE_FLAG, id_emptyCartridge);
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
                                script_say("Es la impresora de la papeler¡a");
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
                                            script_say("Mejor me la guardo");
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
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (!is_game_flag(FULL_CARTRIDGE_NOT_ON_PRINTER_FLAG))
                                        {
                                            script_say("Ya hay un cartucho en la impresora");
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
                                        script_remove_inv_object(id_emptyCartridge);
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
                                            script_say("Ya hay un cartucho en la impresora");
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
                                    script_say("La impresora ha impreso el horario del instituto por las 2 caras");
                                else if (is_game_flag(PRINTED_SCHOOL_SCHEDULE_PHOTO_FLAG))
                                    script_say("La impresora ha impreso el horario del instituto encima de la fotocopia de Dragon Ball");
                                else if (is_game_flag(PRINTED_PHOTOCOPY_FLAG))
                                    script_say("Como el cartucho no tenia tinta, la impresora ha sacado la fotocopia de Dragon Ball sin ning£n da¤o");
                                else if (is_game_flag(PRINTED_SHEET_FLAG))
                                    script_say("Como el cartucho no tenia tinta, la impresora ha sacado el folio sin imprimir nada");
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
                                script_move_player(137, 88);
                            break;
                            case 1:
                                change_player_dir(DIR_RIGHT);
                                script_say_actor("­Hola! ¨En que te puedo ayudar?", &r05_dialogActor);
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
                                        script_say_actor("Graaaacias", &r05_dialogActor);
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
                            default:
                                begin_script();
                                script_say_actor("Oh...Gracias, pero no sabr¡a que hacer con esto", &r05_dialogActor);
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
                            script_say_actor("­Hola! Bienvenido a nuestra papeler¡a", &r05_dialogActor);
                        else
                        {
                            script_say_actor("­Hola! Bienvenido de nuevo", &r05_dialogActor);
                            end_script();
                        }
                        break;
                    case 1:
                        script_say_actor("Mira todo lo que necesites y pregunta lo que quieras", &r05_dialogActor);
                        break;
                    case 2:
                        script_say_actor("Estamos aqu¡ para ayudar", &r05_dialogActor);
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
