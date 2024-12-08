/*
=========================================================
 Room Number:   04
 Room Name:     04_kitchen
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room04.h"

//Funtion to return the name of hotspot by color code
void r04_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r04_corridor:
                strcpy(s, "Pasillo");
            break;
        case r04_fridge:
                strcpy(s, "Nevera");
            break;
        case r04_father:
                strcpy(s, "Pap ");
            break;
        case r04_trash:
                strcpy(s, "Papelera");
            break;
        case r04_paper:
                strcpy(s, "Papel de cocina");
            break;
        case r04_oven:
                strcpy(s, "Horno");
            break;
        case r04_spatula:
                strcpy(s, "Esp tula");
            break;
        case r04_clock:
                if (!is_game_flag(GOT_CLOCK_FLAG))
                    strcpy(s, "Reloj de cocina");
                else
                    strcpy(s, "");
            break;    
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r04_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r04_corridor:
            return GO;
            break;
        case r04_fridge:
            return LOOK;
            break;
        case r04_father:
            return TALK;
            break;
        case r04_trash:
            return LOOK;
            break;
        case r04_paper:
            return LOOK;
            break;
        case r04_oven:
            return LOOK;
            break;
        case r04_spatula:
            return LOOK;
            break;
        case r04_cheesse:
            return LOOK;
            break;
        case r04_clock:
            return LOOK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r04_get_object_info(uint8_t numObject)
{
    if (numObject < R04_ROOM_NUM_OBJS)
        return &r04_object[numObject];
    else
        return NULL;
}

//function to init room
void r04_room_init()
{
    game_fade_in();
}

//global funcion to update room
void r04_room_update()
{
    //update room objects
    r04_update_room_objects();

    //update dialog line selection
    r04_update_dialog_selection();
    
    //update room script
    r04_update_room_script();
}

//update room objects
void r04_update_room_objects()
{
    r04_object[R04_SPATULA_OBJ_ID].active = !is_game_flag(GOT_SPATULA_FLAG);
    r04_object[R04_STARCLOCK_OBJ_ID].active = !is_game_flag(GOT_CLOCK_FLAG);

    //father actor
    if (r04_dialogActor.talking)
        object_play_animation(&r04_object[R04_FATHER_OBJ_ID], r04d_objFatherIdle, r04_animations, R04_ANIM_FATHER_TALK);
    else if (dialog.active)
        r04_object[R04_FATHER_OBJ_ID].objId = r04d_objFatherIdle;
    else
        r04_object[R04_FATHER_OBJ_ID].objId = r04d_objFatherRead;
}

//update dialog selection
void r04_update_dialog_selection()
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
                        dialog_add("Hola papá", 2);
                        dialog_add("¿Buenas noticias?", 3);
                        dialog_add("Lo siento. Me voy...", 0);
                    break;
                    case 2:
                        dialog_add("Tampoco hace falta que seas tan borde", 1);
                        dialog_add("Vale, vale. Ya me callo", 0);
                    break;
                    case 3:
                        dialog_add("Pues adios", 0);
                    break;
                }
            break;
        }
    }
}

//update room script
void r04_update_room_script()
{
    //if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r04_corridor:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Por esa puerta se va al pasillo");
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
                                change_room_pos(CORRIDOR_ROOM_NUM, 221, 118);
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r04_fridge:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("La nevera de la cocina rellena de rica comida");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case OPEN:
                    case USE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("No tengo hambre");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r04_father:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Creo que tengo mas recuerdos de mi padre leyendo el peri¢dico que jugando conmigo");
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
                                script_say("Ejem... ¨Pap ?");
                                break;
                            default:
                                script_start_dialog(1);                                
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r04_trash:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("La papelera donde tiramos la basura de la cocina");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case TAKE:
                    case OPEN:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Est  vac¡a");
                                break;
                            default:
                                script_say("Acabo de tirar la basura hace poco");
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r04_paper:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Un rollo de papel de cocina");
                                break;
                            default:
                                script_say("Que raro que est‚ en la cocina");
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r04_oven:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A£n huele a pizza");
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
                                script_say("Si tuviera hambre, me har¡a una pizza");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r04_spatula:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Una esp tula para reposter¡a");
                                break;
                            default:
                                script_say("Sirve para extender el chocolate en las tartas, por ejemplo");
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
                                    script_take_object(&r04_object[R04_SPATULA_OBJ_ID].active, GOT_SPATULA_FLAG, id_spatula);
                                default:
                                    end_script();
                                    break;
                            }
                    break;
                }
                break;
            case r04_clock:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Un est£pido reloj de cocina en forma de estrella que compraron mis padres de viaje");
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
                                    script_take_object(&r04_object[R04_STARCLOCK_OBJ_ID].active, GOT_CLOCK_FLAG, id_starClock);
                                default:
                                    end_script();
                                    break;
                            }
                    break;
                }
                break;

        }
    }

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
            //1 digit for dialog id, 2 digit for dialog node and 1 digit for selLinef
            switch (((dialog.dialogId - 1) * 1000) + ((dialog.node - 1) * 100) + dialog.selLine)
            {

                case 1:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_wait(2);
                        break;
                        case 2:
                            script_say_actor("A ti que te importa", &r04_dialogActor);
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
                            script_wait(2);
                        break;
                        case 2:
                            script_say_actor("Ya he jugado bastante", &r04_dialogActor);
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
}
