/*
=========================================================
 Room Number:   06
 Room Name:     06_school
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room06.h"

//Funtion to return the name of hotspot by color code
void r06_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r06_door:
                strcpy(s, "Puerta");
            break;
        case r06_maintLockerDoor:
                strcpy(s, "Puerta");
            break;
        case r06_paint:
                strcpy(s, "Cuadro");
            break;
        case r06_computerRoomDoor:
                strcpy(s, "Puerta");
            break;
        case r06_window:
                strcpy(s, "Ventana");
            break;
        case r06_scienceRoomDoor:
                strcpy(s, "Puerta");
            break;
        case r06_board:
                strcpy(s, "Tabl¢n");
            break;
        case r06_schoolBathDoor:
                strcpy(s, "Puerta");
            break;
        case r06_lockerDoor:
                strcpy(s, "Puerta");
            break;
        case r06_orla:
                strcpy(s, "Orla");
            break;
        case r06_bench:
                strcpy(s, "Banco");
            break;
        case r06_PEOfficeRoom:
                strcpy(s, "Puerta");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r06_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r06_door:
            return GO;
            break;
        case r06_maintLockerDoor:
            return GO;
            break;
        case r06_paint:
            return LOOK;
            break;
        case r06_computerRoomDoor:
            return GO;
            break;
        case r06_window:
            return LOOK;
            break;
        case r06_scienceRoomDoor:
            return GO;
            break;
        case r06_board:
            return LOOK;
            break;
        case r06_schoolBathDoor:
            return GO;
            break;
        case r06_lockerDoor:
            return GO;
            break;
        case r06_orla:
            return LOOK;
            break;
        case r06_bench:
            return LOOK;
            break;
        case r06_PEOfficeRoom:
            return GO;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r06_get_object_info(uint8_t numObject)
{
    if (numObject < R06_ROOM_NUM_OBJS)
        return &r06_object[numObject];
    else
        return NULL;
}

//function to init room
void r06_room_init()
{
    change_player_dir(DIR_RIGHT);
    
    game_fade_in();
}

//global funcion to update room
void r06_room_update()
{
    //update room objects
    r06_update_room_objects();

    //update dialog line selection
    r06_update_dialog_selection();
    
    //update room script
    r06_update_room_script();
}

//update room objects
void r06_update_room_objects()
{

}

//update dialog selection
void r06_update_dialog_selection()
{

}

//update room script
void r06_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r06_door:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("La puerta del instituto");
                                break;
                            default:
                                script_say("La tristeza que me da verla por las ma¤anas y la alegr¡a de verla cuando me voy");
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
                                change_room_pos(STREET_ROOM_NUM, 59, 115);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r06_maintLockerDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es la puerta del armario de mantenimiento");
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
                                change_room(MAINT_LOCKER_ROOM_NUM);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r06_paint:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Un cuadro de una fotograf¡a del instituto rodeada de arboles y jardines");
                                break;
                            default:
                                script_say("Ahora todo es cemento");
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r06_computerRoomDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es la puerta del aula de inform tica");
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
                                change_room(COMPUTER_ROOM_NUM);
                                end_script();
                                break;
                        }
                    break;

                }
                break;            
            case r06_window:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es la ventana del aula de inform tica");
                                break;
                            default:
                                script_say("As¡ puedes ver si hay alg£n ordenador disponible");
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r06_scienceRoomDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es la puerta al aula de ciencia");
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
                                change_room(SCIENCE_ROOM_NUM);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r06_board:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                switch (get_game_var(VAR_BULLETIN_BOARD))
                                {
                                    case 0:
                                        script_say("El tabl¢n de anuncios del instituto");
                                        break;
                                    case 1:
                                        script_say("Se dan clases de matem ticas particulares. Contacto 555-5555");
                                        break;
                                    case 2:
                                        script_say("Grupo de m£sica rock busca guitarrista solista con equipo propio");
                                        break;
                                    case 3:
                                        script_say("Vota a Carlos para delegado de clase. Cuando solo hay un candidato, solo hay una elecci¢n");
                                        break;
                                }
                                break;
                            default:
                                if (get_game_var(VAR_BULLETIN_BOARD) < 3)
                                    inc_game_var(VAR_BULLETIN_BOARD);
                                else
                                    set_game_var(VAR_BULLETIN_BOARD, 0);
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r06_schoolBathDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es la puerta que da a los ba¤os");
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
                                change_room(SCHOOL_BATH_ROOM_NUM);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r06_lockerDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es la puerta que va a los vestuarios");
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
                                change_room(LOCKER_ROOM_NUM);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r06_orla:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es la orla de la generaci¢n de profesores del 57");
                                break;
                            default:
                                script_say("Una manada de dinosaurios es lo que son...");
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r06_bench:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Creo que nunca me he sentado en este banco");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r06_PEOfficeRoom:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es la puerta que da al despacho del profesor de educaci¢n f¡sica");
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
                                change_room(PE_OFFICE_ROOM_NUM);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
        }
    }
}
