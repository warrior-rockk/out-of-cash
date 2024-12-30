/*
=========================================================
 Room Number:   08
 Room Name:     08_computerRoom
=========================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room08.h"

//Funtion to return the name of hotspot by color code
void r08_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r08_door:
                strcpy(s, "Puerta");
            break;
        case r08_window:
                strcpy(s, "Ventana");
            break;
        case r08_computer3:
                strcpy(s, "Ordenador");
            break;
        case r08_manual:
                strcpy(s, "Manual");
            break;
        case r08_computer1:
                strcpy(s, "Ordenador");
            break;
        case r08_nerd:
                strcpy(s, "Friki");
            break;
        case r08_computer2:
                strcpy(s, "Ordenador");
            break;
        case r08_chair:
                strcpy(s, "Silla");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r08_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r08_door:
            return GO;
            break;
        case r08_window:
            return LOOK;
            break;
        case r08_computer3:
            return LOOK;
            break;
        case r08_manual:
            return LOOK;
            break;
        case r08_computer1:
            return LOOK;
            break;
        case r08_nerd:
            return TALK;
            break;
        case r08_computer2:
            return LOOK;
            break;
        case r08_chair:
            return LOOK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r08_get_object_info(uint8_t numObject)
{
    if (numObject < R08_ROOM_NUM_OBJS)
        return &r08_object[numObject];
    else
        return NULL;
}

//function to init room
void r08_room_init()
{
    game_fade_in();
}

//global funcion to update room
void r08_room_update()
{
    //update room objects
    r08_update_room_objects();

    //update dialog line selection
    r08_update_dialog_selection();
    
    //update room script
    r08_update_room_script();
}

//update room objects
void r08_update_room_objects()
{
    //nerd object
    if (r08_dialogActor.talking)
        object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_TALK);
    //else if (dialog.active)
    //    object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_IDLE);
    else
        object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objPlay1, r08_animations, R08_ANIM_PLAYING);
}

//update dialog selection
void r08_update_dialog_selection()
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
                        dialog_add("¨A qu‚ est s jugando?",2);
                        dialog_add("¨Por qu‚ la educaci¢n f¡sica tiene que contar en las calificaciones?",1);
                        dialog_add("No te molesto", 0);
                    break;
                    case 2:
                        dialog_add("Pero es que odio nadar",2);
                        dialog_add("¨10 largos? ¨Pero quien cree que soy, Aquaman?",2);
                        dialog_add("Ah pero, ¨tenemos piscina en este instituto?", 2);
                        if (!is_game_flag(INFO_SPORT_WORK_FLAG))
                            dialog_add("Y no hay otra cosa que pueda hacer para aprobar", 2);
                        else
                            dialog_add("¨Que dec¡a de una enfermedad en la piel?", 2);
                        dialog_add("Bah... el agua para los patos", 1);
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
void r08_update_room_script()
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
                            script_say_actor("­Estoy jugando al Age of Empires!", &r08_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Todos los alumnos tienen que pasar la £ltima prueba del curso para aprobar", &r08_dialogActor);
                        break;
                        case 3:
                            script_say_actor("La prueba consiste en realizar 10 largos de piscina sin detenerse", &r08_dialogActor);
                        break;
                        case 4:
                            script_say_actor("Y usted hasta el momento no la ha realizado", &r08_dialogActor);
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
                            script_say_actor("El trabajo duro y la fortaleza f¡sica que ense¤a la educaci¢n f¡sica", &r08_dialogActor);
                        break;
                        case 2:
                            script_say_actor("son de los valores mas importantes y necesarios que os encontrar‚is en la vida", &r08_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Adem s, se est  poniendo fond¢n", &r08_dialogActor);
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
            case r08_door:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es la puerta que da al pasillo");
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
                                change_room_pos(SCHOOL_ROOM_NUM, 272, 84);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r08_window:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Esta ventana al exterior impide que la gente haga uso fraudulentos con los ordenadores");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r08_computer3:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Ordenador");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r08_manual:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Un manual de Q-Basic para MS-DOS");
                                break;
                            case 1:
                                script_say("Aprenda a programar desde el juego Gorillas al Snake");
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r08_computer1:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Ordenador");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r08_nerd:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Friki");
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
                                script_start_dialog(1);
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r08_computer2:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Ordenador");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r08_chair:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("àjala en el futuro hagan sillas de ordenador m s c¢modas y que sirvan para largas sesiones de juego");
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