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
                        if (!is_game_flag(DIALOG_KNOW_ANSWERS))
                            dialog_add("¨A que te refieres con curso y asignatura?",2);
                        else
                            dialog_add("De verdad que necesito las respuestas de M tematicas de 1§ de BUP", 3);
                        if (!is_game_flag(DIALOG_KNOW_ANSWERS) || is_game_flag(HISTORY_APPROVED_FLAG))
                            dialog_add("¨Que haces ah¡ dentro?",2);
                        else if (is_game_flag(ASKED_BY_HISTORY_ANSWERS))
                            dialog_add("¨Ya tienes las respuestas de Historia de 1§ de BUP?", 1);
                        else
                            dialog_add("Necesito las respuestas de Historia de 1§ de BUP", 2);
                        if (!is_game_flag(ASK_BY_WC_FLAG))
                            dialog_add("¨Est  este v ter ocupado?",1);
                        else
                            dialog_add("¨Sigue este v ter ocupado?",1);
                        dialog_add("Hasta luego",0);
                    break;
                    case 2:
                        dialog_add("Pero esto no es muy legal ¨no?",2);
                        dialog_add("¨Como s‚ que eres de fiar y son correctas las respuestas?",2);
                        dialog_add("­Genial! Necesito las respuestas de M tematicas de 1§ de BUP", 3);
                        if (!is_game_flag(HISTORY_APPROVED_FLAG))
                            dialog_add("­Perfecto! Necesito las respuestas de Historia de 1§ de BUP", 2);
                        dialog_add("Gracias, pero no, gracias", 1);
                    break;
                    case 3:
                        dialog_add("Pero es que no tengo dinero, colega",1);
                        if (is_game_flag(ASKED_BY_MATH_ANSWERS))
                        {
                            dialog_add("¨Hay algo que puedas aceptar a cambio de las respuestas?", 1);
                            dialog_add("Muy caro...Me esperar‚ a rebajas", 0);
                        }
                        else
                            dialog_add("Muy caro...Me esperar‚ a rebajas", 0);
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
                    if (!is_game_flag(DIALOG_KNOW_ANSWERS))
                    {
                       switch (roomScript.step)
                       {
                           case 1:
                               script_say_actor("Dime curso y asignatura y te consigo respuestas a los ex menes", &r12_dialogActor);
                           break;
                           case 2:
                               script_say_actor("100% garantizado o devolvemos el dinero, tronco", &r12_dialogActor);
                           break;
                           default:
                               set_game_flag(DIALOG_KNOW_ANSWERS);
                               script_next_dialog_node();
                               end_script();
                           break;
                       }
                    }
                    else
                        dialog_jump(2, 3, 3);
                break;
                case 2:
                    if (!is_game_flag(DIALOG_KNOW_ANSWERS) || is_game_flag(HISTORY_APPROVED_FLAG))
                    {
                        switch (roomScript.step)
                        {
                            case 1:
                                script_say_actor("Colega, me dedico a hacer a la gente feliz", &r12_dialogActor);
                            break;
                            case 2:
                                script_say_actor("Consigo las respuestas para los ex menes del instituto", &r12_dialogActor);
                                break;
                            case 3:
                                script_say_actor("A cambio de una peque¤a compensaci¢n ec¢nomica, por supuesto", &r12_dialogActor);
                            break;
                            case 4:
                                script_say_actor("De algo hay que vivir, t¡o", &r12_dialogActor);
                            break;
                            default:
                                set_game_flag(DIALOG_KNOW_ANSWERS);
                                script_next_dialog_node();
                                end_script();
                            break;
                        }
                    }
                    else
                        dialog_jump(2, 4, 1);
                break;
                case 3:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Este v ter esta reservado para tareas empresariales", &r12_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Busc te otro para tus asuntos, colega", &r12_dialogActor);
                        break;
                        default:
                            set_game_flag(ASK_BY_WC_FLAG);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 101:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("T¡o, la legalidad es un concepto muy subjetivo y difuminado en la sociedad actual de consumo", &r12_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Adem s, estas respuestas no son lo peor que te pueden vender en un ba¤o de instituto, colega", &r12_dialogActor);
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
                            script_say_actor("Tio, si est s en un v ter buscando respuestas a ex menes es que est s desesperado", &r12_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Ahora mismo soy tu mejor opci¢n", &r12_dialogActor);
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
                            script_say_actor("Dabuten, son 1000 pesetas", &r12_dialogActor);
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
                            script_say_actor("Lo siento colega, se me han acabado las respuestas de Historia de 1§ de BUP", &r12_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Parece que es una asignatura de las dif¡ciles y ya me han comprado todas las que ten¡a", &r12_dialogActor);
                        break;
                        default:
                            set_game_flag(ASKED_BY_HISTORY_ANSWERS);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 201:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Mala suerte chaval", &r12_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Si no hay dinero, no hay respuestas", &r12_dialogActor);
                        break;
                        default:
                            set_game_flag(ASKED_BY_MATH_ANSWERS);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 202:
                    if (is_game_flag(ASKED_BY_MATH_ANSWERS))
                    {
                        switch (roomScript.step)
                        {
                            case 1:
                                script_say_actor("Mmmm....", &r12_dialogActor);
                            break;
                            case 2:
                                script_say_actor("No s‚, mi principal motivaci¢n es el dinero", &r12_dialogActor);
                            break;
                            case 3:
                                script_say_actor("Pero no te creas que soy tan superficial", &r12_dialogActor);
                            break;
                            case 4:
                                script_say_actor("Tambi‚n tengo gustos muy exquisitos", &r12_dialogActor);
                            break;
                            case 5:
                                script_say_actor("Me gusta el buen cine", &r12_dialogActor);
                            break;
                            case 6:
                                script_say_actor("Los c¢mics", &r12_dialogActor);
                            break;
                            case 7:
                                script_say_actor("Y sobretodo el manga y el anime", &r12_dialogActor);
                            break;
                            case 8:
                                script_say_actor("Si pudieras conseguirme algo de eso, quiz s podemos llegar a un acuerdo", &r12_dialogActor);
                            break;
                            default:
                                set_game_flag(INFO_ANIME_FLAG);
                                script_next_dialog_node();
                                end_script();
                            break;
                        }
                    }
                    else
                    {
                        script_next_dialog_node();
                        end_script();
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
                                if (is_game_flag(MATH_APPROVED_FLAG))
                                {
                                    script_say("Ya no necesito nada de este tipo");
                                    end_script();
                                }
                                else
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
                    case GIVE:
                        switch (roomScript.invObject)
                        {
                            case id_photocopy:
                                if (!is_game_flag(INFO_ANIME_FLAG))
                                {
                                    script_say("¨Porqu‚ deber¡a darle esta fotocopia de Dragon Ball?");
                                    end_script();
                                }
                                else
                                {
                                    switch (roomScript.step)
                                    {
                                        case 0:
                                            begin_script();
                                            script_say("Perdona...");
                                        break;
                                        case 1:
                                            script_say_actor("¨Qu‚ quieres, t¡o?", &r12_dialogActor);
                                        break;
                                        case 2:
                                            script_say("Dec¡as que te gustaba el manga, ¨no?");
                                        break;
                                        case 3:
                                            script_say("Pues tengo esta fotocopia exclusiva de Dragon Ball para ti");
                                        break;
                                        case 4:
                                            script_say_actor("¨UNA FOTOCOPIA DE DRAGON BALL?", &r12_dialogActor);
                                        break;
                                        case 5:
                                            script_say_actor("Colega, eres un crack. ­Me encanta Dragon Ball!", &r12_dialogActor);
                                        break;
                                        case 6:
                                            script_say_actor("D mela y te dar‚ las respuestas del examen de Matem ticas", &r12_dialogActor);
                                            r12_object[R12_HAND_OBJ_ID].active = true;
                                        break;
                                        case 7:
                                            script_move_player(207, 114);
                                        break;
                                        case 8:
                                            script_player_take_state();
                                        break;
                                        case 9:
                                            r12_object[R12_HAND_OBJ_ID].active = false;
                                            script_remove_inv_object(id_photocopy);
                                        break;
                                        case 10:
                                            script_say_actor("­Wow gracias! ­Encima es de Goku!", &r12_dialogActor);
                                        break;
                                        case 11:
                                            script_say_actor("Aqu¡ tienes las respuestas", &r12_dialogActor);
                                            r12_object[R12_HANDEXAM_OBJ_ID].active = true;
                                        break;
                                        case 12:
                                            script_take_object(&r12_object[R12_HANDEXAM_OBJ_ID].active, MATH_APPROVED_FLAG, id_answers);
                                            r12_object[R12_HAND_OBJ_ID].active = true;
                                        break;
                                        case 13:
                                            script_say("­Gracias!");
                                        break;
                                        case 14:
                                            if (is_game_flag(MATH_APPROVED_FLAG) && is_game_flag(HISTORY_APPROVED_FLAG) && is_game_flag(PE_APPROVED_FLAG))
                                                play_sound(sd_completed);
                                            else
                                                play_sound(sd_approved);
                                            roomScript.step++;
                                        break;
                                        case 15:
                                            r12_object[R12_HAND_OBJ_ID].active = false;
                                            if (is_game_flag(MATH_APPROVED_FLAG) && is_game_flag(HISTORY_APPROVED_FLAG) && is_game_flag(PE_APPROVED_FLAG))
                                            {
                                                script_say("­Genial! ­Ya he aprobado todo!");
                                            }
                                            else
                                            {
                                                script_say("Con estas respuestas ya tengo aprobado el examen de matem ticas");
                                            }
                                        break;
                                        default:
                                            end_script();
                                            break;
                                    }
                                }
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