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
                        dialog_add("¨No podr¡a aprobarme la educaci¢n f¡sica?",2);
                        dialog_add("¨Por qu‚ la educaci¢n f¡sica tiene que contar en las calificaciones?",1);
                        dialog_add("Saludos de McClane", 0);
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
void r11_update_room_script()
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
                            script_say_actor("Joven, ya sabe de sobra lo que es necesario", &r11_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Todos los alumnos tienen que pasar la £ltima prueba del curso para aprobar", &r11_dialogActor);
                        break;
                        case 3:
                            script_say_actor("La prueba consiste en realizar 10 largos de piscina sin detenerse", &r11_dialogActor);
                        break;
                        case 4:
                            script_say_actor("Y usted hasta el momento no la ha realizado", &r11_dialogActor);
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
                            script_say_actor("El trabajo duro y la fortaleza f¡sica que ense¤a la educaci¢n f¡sica", &r11_dialogActor);
                        break;
                        case 2:
                            script_say_actor("son de los valores mas importantes y necesarios que os encontrar‚is en la vida", &r11_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Adem s, se est  poniendo fond¢n", &r11_dialogActor);
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
                            script_say_actor("Mac, ¨qui‚n?", &r11_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 101:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Y yo odio a la gente quejica y sin disciplina", &r11_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Y por si no entiende la iron¡a me refiero a usted", &r11_dialogActor);
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
                            script_say_actor("Hemos estado practicando largos todo el curso para esta prueba", &r11_dialogActor);
                        break;
                        case 2:
                            script_say_actor("y todos los alumnos son capaces de realizarla", &r11_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Siempre claro que haya acudido a las clases...", &r11_dialogActor);
                        break;
                        case 4:
                            script_say("Emm... ya...");
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
                            script_say_actor("La disciplina y trabajo duro que realiza este instituto ha conseguido grandes cosas", &r11_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Desde la financiaci¢n de la piscina ol¡mpica de la que disponemos", &r11_dialogActor);
                        break;
                        case 3:
                            script_say_actor("hasta la lujosa sala de profesores", &r11_dialogActor);
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
                            if (!is_game_flag(INFO_SPORT_WORK_FLAG))
                                script_say_actor("No, ya lo sabe", &r11_dialogActor);
                            else
                                roomScript.step = 5;
                        break;
                        case 2:
                            script_say_actor("Todos los alumnos deben superar la prueba acu tica para aprobar", &r11_dialogActor);
                        break;
                        case 3:
                            script_say_actor("A no ser...", &r11_dialogActor);
                        break;
                        case 4:
                            script_say("¨A no ser?");
                        break;
                        case 5:
                            if (!is_game_flag(INFO_SPORT_WORK_FLAG))
                                script_say_actor("A no ser que por alg£n tipo de enfermedad cut nea infecciosa le impida usar las instalaciones de la piscina", &r11_dialogActor);
                            else
                                script_say_actor("Es posible no realizar la prueba de nataci¢n por alg£n tipo de enfermedad cut nea infecciosa que le impida usar las instalaciones de la piscina", &r11_dialogActor);
                        break;
                        case 6:
                            script_say_actor("En ese caso el alumno tendr  que realizar un trabajo sobre el deporte para aprobar", &r11_dialogActor);
                            set_game_flag(INFO_SPORT_WORK_FLAG);
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
                                script_say("Este profesor parece mas bien un terrorista de la pel¡cula Junga de Cristal");
                                break;
                            default:
                                script_say("­YIPIEE YAI EII MOTHERFUCKER!");
                                end_script();
                                break;
                        }
                    break;
                    case TALK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Disculpe profesor...");
                            break;
                            case 1:
                                script_start_dialog(1);
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