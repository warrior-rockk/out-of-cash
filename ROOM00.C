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
                strcpy(s, "Puerta");
            break;
        case r00_sign:
                strcpy(s, "Cartel");
            break;
        case r00_stationery:
                strcpy(s, "Papeler¡a");
            break;
        case r00_school:
                strcpy(s, "Colegio");
            break;
        case r00_shop:
                strcpy(s, "Tienda");
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
                                script_say("Es la puerta de entrada a mi casa");
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
                                script_say("Zurraspa Producciones presenta:");
                                break;
                            case 1:
                                script_say("Reincidentes en concierto");
                                break;
                            case 2:
                                script_say("Presentando su £ltimo disco en directo");
                                break;
                            case 3:
                                script_say("Precio de la entrada: 5000 pesetas");
                                break;    
                            case 4:
                                script_say("Tengo que conseguir el dinero como sea");
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
                                script_say("Por all¡ se va a la papeler¡a");
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
                                script_say("Por ah¡ se va hacia mi instituto");
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
                                script_say("Mi tienda de ordenadores de confianza");
                                break;
                            case 1:
                                script_say("Aqui me compr‚ mi Pentium 100 por un buen precio");
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
                                script_say("Nah, ya me gast‚ todo mi dinero en el Pentium");
                                break;
                            case 1:
                                script_say("Adem s todo el que consiga lo necesito para ir al concierto");
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
                        script_move_player(160, 120);
                    break;
                    case 1:
                        script_say("Um...");
                    break;
                    case 2:
                        script_move_player(80, 120);
                    break;
                    case 3:
                        change_player_dir(DIR_BACK);
                        script_wait(20);
                    break;
                    case 4:
                        script_say("­Concierto de Reincidentes!");
                    break;
                    case 5:
                        script_say("5000 pelas la entrada");
                    break;
                    case 6:
                        change_player_dir(DIR_RIGHT);
                        script_say("Tengo que conseguir el dinero como sea");
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
