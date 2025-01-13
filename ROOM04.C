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
        case r04_oat:
                if (is_game_flag(KITCHEN_CLOSET_OPEN_FLAG) && !is_game_flag(GOT_OAT_FLAG))
                {
                    strcpy(s, "Caja avena");
                    break;
                }
                else
                    strcpy(s, "");
        case r04_closet:
            strcpy(s, "Armario");
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
        case r04_oat:
            if (is_game_flag(KITCHEN_CLOSET_OPEN_FLAG) && !is_game_flag(GOT_OAT_FLAG))
            {
                return LOOK;
                break;
            }
        case r04_closet:
            if (!is_game_flag(KITCHEN_CLOSET_OPEN_FLAG))
                return OPEN;
            else
                return CLOSE;
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

    r04_object[R04_CLOSETOPEN_OBJ_ID].active = is_game_flag(KITCHEN_CLOSET_OPEN_FLAG);
    r04_object[R04_OAT_OBJ_ID].active = is_game_flag(KITCHEN_CLOSET_OPEN_FLAG) && !is_game_flag(GOT_OAT_FLAG);

    //father actor
    if (r04_dialogActor.talking)
        object_play_animation(&r04_object[R04_FATHER_OBJ_ID], r04d_objIdle, r04_animations, R04_ANIM_FATHER_TALK);
    else if (dialog.active)
        r04_object[R04_FATHER_OBJ_ID].objId = r04d_objTalk7;
    else
        r04_object[R04_FATHER_OBJ_ID].objId = r04d_objIdle;
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
                        dialog_add("¨Por qu‚ siempre estas leyendo el peri¢dico?", 1);
                        dialog_add("¨Por qu‚ hay una habitaci¢n que nunca abrimos?", 1);
                        if (!is_game_flag(FATHER_SAY_MONEY_FLAG))
                            dialog_add("Tengo que pedirte una cosa...", 2);
                        else if (!is_game_flag(MATH_APPROVED_FLAG) || !is_game_flag(HISTORY_APPROVED_FLAG) || !is_game_flag(PE_APPROVED_FLAG))
                            dialog_add("¨Qu‚ ten¡a que hacer para que me des el dinero?", 4);
                        else
                            dialog_add("­YA HE APROBADO TODO!", 0);
                        dialog_add("Da igual...", 0);
                    break;
                    case 2:
                        dialog_add("Hay un concierto al que quiero ir...", 3);
                        dialog_add("¨Me das pasta, viejo?", 2);
                        dialog_add("En realidad no era nada...", 1);
                    break;
                    case 3:
                        dialog_add("Vaaa, porfavor... Me hace mucha ilusi¢n", 4);
                        dialog_add("¨De verdad no quieres ser el mejor padre?", 4);
                        dialog_add("­­Vengaa!! ­Har‚ lo que sea!", 4);
                    break;
                    case 4:
                        dialog_add("­Pero es que las Matem ticas son muy dif¡ciles!", 1);
                        dialog_add("­Pero es que Historia es un rollo!", 1);
                        dialog_add("¨Educaci¢n F¡sica? ¨Para qu‚ me sirve?", 1);
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
                                if (is_game_flag(GOT_MONEY_FLAG))
                                {
                                    script_say("Ya tengo el dinero. No necesito hablar nada con ‚l");
                                    end_script();
                                }
                                else
                                    script_say("Ejem... ¨Pap ?");
                                break;
                            default:
                                script_start_dialog(1);                                
                                end_script();
                                break;
                        }
                    break;
                    case GIVE:
                    case USE_WITH:
                        switch (roomScript.invObject)
                        {
                            case id_califications:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (is_game_flag(FATHER_SAY_MONEY_FLAG))
                                            script_say_actor("Veamos...", &r04_dialogActor);
                                        else
                                        {
                                            script_say("Uf... Mejor deber¡a hablar con mi padre primero antes de ense¤arle las notas");
                                            end_script();
                                        }
                                    break;
                                    case 1:
                                        if (!is_game_flag(MATH_APPROVED_FLAG) ||
                                            !is_game_flag(HISTORY_APPROVED_FLAG) ||
                                            !is_game_flag(PE_APPROVED_FLAG))
                                            roomScript.step++;
                                        else
                                            start_script(R04_ALL_APPROVED_SCRIPT);
                                    break;
                                    case 2:
                                        script_say_actor("Todav¡a tienes que aprobar:", &r04_dialogActor);
                                    break;
                                    case 3:
                                        if (!is_game_flag(MATH_APPROVED_FLAG))
                                            script_say_actor("Matem ticas", &r04_dialogActor);
                                        else
                                            roomScript.step++;
                                    break;
                                    case 4:
                                        if (!is_game_flag(HISTORY_APPROVED_FLAG))
                                        {
                                            if (!is_game_flag(PE_APPROVED_FLAG))
                                                script_say_actor("Historia", &r04_dialogActor);
                                            else
                                                script_say_actor("e Historia", &r04_dialogActor);
                                        }
                                        else
                                            roomScript.step++;
                                    break;
                                    case 5:
                                        if (!is_game_flag(PE_APPROVED_FLAG))
                                        {
                                            if (is_game_flag(MATH_APPROVED_FLAG) && is_game_flag(HISTORY_APPROVED_FLAG))
                                                script_say_actor("Educaci¢n f¡sica", &r04_dialogActor);
                                            else
                                                script_say_actor("y Educaci¢n f¡sica", &r04_dialogActor);
                                        }
                                        else
                                            roomScript.step++;
                                    break;
                                    case 6:
                                        script_say_actor("Hasta que no lo apruebes todo no te dar‚ el dinero", &r04_dialogActor);
                                        end_script();
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
                            case 1:
                                script_say("Que raro que est‚ en la cocina");
                            break;
                            default:
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
            case r04_oat:
                if (is_game_flag(KITCHEN_CLOSET_OPEN_FLAG) && !is_game_flag(GOT_OAT_FLAG))
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("Una caja de copos de avena");
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
                                    script_take_object(&r04_object[R04_OAT_OBJ_ID].active, GOT_OAT_FLAG, id_oat);
                                    end_script();
                                break;
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                    break;
                }
            case r04_closet:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Un armario de la cocina");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case OPEN:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (is_game_flag(KITCHEN_CLOSET_OPEN_FLAG))
                                {
                                    script_say("Ya est  abierto");
                                    end_script();
                                }
                                else
                                    script_move_player_to_target();
                                break;
                            case 1:
                                script_play_sound(sd_closetOpen);
                            break;
                            case 2:
                                script_player_take_state();
                                break;
                            default:
                                set_game_flag(KITCHEN_CLOSET_OPEN_FLAG);
                                end_script();
                                break;
                        }
                    break;
                    case CLOSE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (!is_game_flag(KITCHEN_CLOSET_OPEN_FLAG))
                                {
                                    script_say("Ya est  cerrado");
                                    end_script();
                                }
                                else
                                    script_move_player_to_target();
                                break;
                            case 1:
                                script_play_sound(sd_closetClose);
                            break;
                            case 2:
                                script_player_take_state();
                                break;
                            default:
                                clear_game_flag(KITCHEN_CLOSET_OPEN_FLAG);
                                end_script();
                                break;
                        }

                }
            break;
            case R04_ALL_APPROVED_SCRIPT:
                switch (roomScript.step)
                {
                    case 0:
                        script_say_actor("­Muy bien hijo!", &r04_dialogActor);
                    break;
                    case 1:
                        script_say_actor("Al final con trabajo y esfuerzo se consiguen metas", &r04_dialogActor);
                    break;
                    case 2:
                        script_say_actor("Aqu¡ tienes el dinero", &r04_dialogActor);
                    break;
                    case 3:
                        play_sound(sd_money);
                        script_remove_inv_object(id_califications);
                        script_add_inv_object(id_money);
                    break;
                    case 4:
                        script_say("Pero pap , aqui solo hay 4900 pelas");
                    break;
                    case 5:
                        script_say("­La entrada del concierto vale 5000!");
                    break;
                    case 6:
                        script_say_actor("Hijo, toma lo que te dan y suspira por lo que queda", &r04_dialogActor);
                    break;
                    case 7:
                        script_say("Ser  hijop...");                        
                    break;
                    case 8:
                        script_say_actor("Esa boca...", &r04_dialogActor);
                        set_game_flag(GOT_MONEY_FLAG);
                    break;
                    default:
                        end_script();
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
                            script_say_actor("En la vida hay que estar informado, muchacho", &r04_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Y el peri¢dico es el £nico modo de enterarme de la verdad", &r04_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Y no de esas bazofias que dicen por la tele", &r04_dialogActor);
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
                            script_say_actor("Si te lo dijera tendr¡a que matarte", &r04_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Adem s, no lo s‚", &r04_dialogActor);
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
                            if (is_game_flag(MATH_APPROVED_FLAG) && is_game_flag(HISTORY_APPROVED_FLAG) && is_game_flag(PE_APPROVED_FLAG))
                            {
                                script_say_actor("A ver, ense¤ame las notas...", &r04_dialogActor);
                            }
                            else if (is_game_flag(FATHER_SAY_MONEY_FLAG))
                                script_say_actor("Aprueba Matem ticas, Historia y Educaci¢n f¡sica y te dar‚ el dinero", &r04_dialogActor);
                            else
                                roomScript.step++;
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
                            script_say("Es de mi grupo favorito");
                        break;
                        case 2:
                            script_say("Acaban de sacar disco y vienen a la ciudad a presentarlo");
                        break;
                        case 3:
                            script_say("El problema es que no tengo dinero y la entrada vale 5000 pelas");
                        break;
                        case 4:
                            script_say("Ser¡as el mejor padre del mundo si me dejas el dinero");
                        break;
                        case 5:
                            script_say_actor("Ni lo sue¤es", &r04_dialogActor);
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
                            script_say_actor("­Modera tu lenguaje jovenzuelo!", &r04_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                    break;
                case 201:
                case 202:
                case 203:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Mmmm...", &r04_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Vamos a hacer un trato", &r04_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Si apruebas las asignaturas que has suspendido, te dar‚ el dinero", &r04_dialogActor);
                            set_game_flag(FATHER_SAY_MONEY_FLAG);
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
                            script_say_actor("Es tu obligaci¢n saber aprender las Matem ticas", &r04_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 302:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Para afrontar el futuro tienes que conocer bien el pasado", &r04_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 303:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Hijo", &r04_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Educaci¢n F¡sica es una asignatura tan respetable e importante como las dem s", &r04_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Adem s te est s poniendo fond¢n", &r04_dialogActor);
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
