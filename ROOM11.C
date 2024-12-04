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
                strcpy(s, "Puerta");
            break;
        case r11_earthGlobe:
                strcpy(s, "Bola del mundo");
            break;
        case r11_things:
                strcpy(s, "Cosas");
            break;
        case r11_cup:
                strcpy(s, "Taza");
            break;
        case r11_teacher:
                strcpy(s, "Profesor");
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

}

//update dialog selection
void r11_update_dialog_selection()
{

}

//update room script
void r11_update_room_script()
{
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
                                script_say("Es la puerta que da al pasillo del instituto");
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
                                change_room_pos(SCHOOL_ROOM_NUM, 901, 82);
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
                                script_say("Nuestro peque¤o y p lido punto azul condensado en un objeto de escritorio");
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
                                script_say("Cosas varias que pertenecen al profesor de educaci¢n f¡sica");
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
                                script_say("No pienso tocar las cosas del profesor");
                                break;
                            default:
                                script_say("Solo me faltar¡a enfadarlo...");
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
                                script_say("Esperaba que fuera la cl sica taza de: Al mejor profesor de gimnasia");
                                break;
                            default:
                                script_say("Pero solo es una taza sin inscripci¢n");
                                end_script();
                                break;
                        }
                    break;
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Parece un buen objeto de inventario, pero no me hace falta");
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
                                script_say("Este profesor parece mas bien un terrorista de algun pa¡s del este...");
                                break;
                            default:
                                script_say("Con todo el respeto a todos los habitantes de pa¡ses del este que esten ahora jug ndonos");
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            

        }
    }
}