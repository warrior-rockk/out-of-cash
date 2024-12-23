/*
=========================================================
 Room Number:   12
 Room Name:     12_schoolBath
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room12.h"

//Funtion to return the name of hotspot by color code
void r12_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r12_door:
                strcpy(s, "Puerta");
            break;
        case r12_mirror:
                strcpy(s, "Espejo");
            break;
        case r12_towelDispenser:
                strcpy(s, "Dispensador papel");
            break;
        case r12_washbowl:
                strcpy(s, "Lavabo");
            break;
        case r12_closedDoor:
                strcpy(s, "Puerta");
            break;
        case r12_hole:
                strcpy(s, "Agujero");
            break;
        case r12_holeDoor:
                strcpy(s, "Puerta");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r12_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r12_door:
            return GO;
            break;
        case r12_mirror:
            return LOOK;
            break;
        case r12_towelDispenser:
            return LOOK;
            break;
        case r12_washbowl:
            return LOOK;
            break;
        case r12_closedDoor:
            return OPEN;
            break;
        case r12_hole:
            return LOOK;
            break;
        case r12_holeDoor:
            return OPEN;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r12_get_object_info(uint8_t numObject)
{
    if (numObject < R12_ROOM_NUM_OBJS)
        return &r12_object[numObject];
    else
        return NULL;
}

//function to init room
void r12_room_init()
{
    game_fade_in();
}

//global funcion to update room
void r12_room_update()
{
    //update room objects
    r12_update_room_objects();

    //update dialog line selection
    r12_update_dialog_selection();
    
    //update room script
    r12_update_room_script();
}

//update room objects
void r12_update_room_objects()
{

}

//update dialog selection
void r12_update_dialog_selection()
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
                        dialog_add("¨A que te refieres con curso y asignatura?",1);
                        dialog_add("¨Que haces ah¡ dentro?",1);
                        dialog_add("¨Est  ocupado?",3);
                        dialog_add("Hasta luego",0);
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
void r12_update_room_script()
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
                            script_say_actor("Dime curso y asignatura y te consigo respuestas a los ex menes", &r12_dialogActor);
                        break;
                        case 2:
                            script_say_actor("100% garantizado o devolvemos el dinero", &r05_dialogActor);
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
                            script_say_actor("Me dedico a conseguir a la gente las respuestas a los ex menes", &r12_dialogActor);
                        break;
                        case 2:
                            script_say_actor("A cambio de una peque¤a compensaci¢n ec¢nomica", &r05_dialogActor);
                        break;
                        case 3:
                            script_say_actor("De algo hay que vivir, tio", &r05_dialogActor);
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
                            script_say_actor("Este v ter esta reservado para tareas empresariales", &r12_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
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
            case r12_door:
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
                                change_room_pos(SCHOOL_ROOM_NUM, 607, 79);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r12_mirror:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (!is_game_flag(SCHOOLBATH_MIRROR_MSG_FLAG))
                                {
                                    set_game_flag(SCHOOLBATH_MIRROR_MSG_FLAG);
                                    inc_game_var(MIRROR_MSG_COUNT_VAR);
                                }
                                switch (get_game_var(MIRROR_MSG_COUNT_VAR))
                                {
                                    case 1:
                                        script_say("El programador del juego ha sido tan vago como para no programar los reflejos...");
                                        break;
                                    case 2:
                                        script_say("Otro espejo con reflejo sin programar...");
                                        break;
                                    case 3:
                                        script_say("Con lo poco que cuesta programar los reflejos...");
                                        break;
                                }
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r12_towelDispenser:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Un dispensador de papel");
                                break;
                            default:
                                script_say("Tan in£til como su capacidad para secar");
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r12_washbowl:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("¨Se lavar  alguien las manos en este instituto?");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r12_closedDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Este WC parece que no est  en servicio");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r12_hole:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Parece que hay alguien dentro de este WC...");
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
                                script_say("¨Hola?");
                                break;
                            case 1:
                                script_say_actor("¨Curso y asignatura?", &r12_dialogActor);
                                break;
                            default:
                                script_start_dialog(1);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r12_holeDoor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Parece que est  ocupado...");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            

        }
    }
}