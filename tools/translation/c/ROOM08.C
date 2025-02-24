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
    r08_dialogActor.talking = false;
    clear_game_flag(START_CREDITS_FLAG);
    
    game_fade_in();

    if (is_game_flag(PLAYER_ROCKING_FLAG))
        start_script(R08_EPILOGUE_SCRIPT);
    else if (is_game_flag(COMPUTER_DOOR_OPEN_FLAG))
        start_script(R08_DOOR_CLOSE_SCRIPT);
        
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
    if (is_game_flag(NERD_ERROR_2_FLAG))
    {
        r08_object[R08_NERD_OBJ_ID].x = 115;
        r08_object[R08_NERD_OBJ_ID].y = 100;

        if (r08_dialogActor.talking)
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_ERROR_TALK);
        }
        else
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_ERROR_IDLE);
        }
    }
    else if (is_game_flag(NERD_ERROR_FLAG))
    {
        r08_object[R08_NERD_OBJ_ID].x = 115;
        r08_object[R08_NERD_OBJ_ID].y = 100;

        object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_ERROR);
    }
    else if (is_game_flag(NERD_COSTUME_FLAG))
    {
        r08_object[R08_NERD_OBJ_ID].x = 135;
        r08_object[R08_NERD_OBJ_ID].y = 106;

        if (r08_dialogActor.talking)
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_COSTUME_TALK);
        }
        else
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_COSTUME_IDLE);
        }
    }
    else if (is_game_flag(NERD_COSTUME_PLAYING_FLAG))
    {
        r08_object[R08_NERD_OBJ_ID].x = 115;
        r08_object[R08_NERD_OBJ_ID].y = 100;
        
        if (r08_dialogActor.talking)
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objPlay1, r08_animations, R08_ANIM_COSTUME_PLAY_TALK);
        else
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objPlay1, r08_animations, R08_ANIM_COSTUME_PLAYING);
    }
    else if (is_game_flag(NERD_SIDE_FLAG))
    {
        r08_object[R08_NERD_OBJ_ID].x = 115;
        r08_object[R08_NERD_OBJ_ID].y = 100;
        
        if (r08_dialogActor.talking)
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_TALK);
        }
        else
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_IDLE);
        }
    }
    else
    {
        r08_object[R08_NERD_OBJ_ID].x = 115;
        r08_object[R08_NERD_OBJ_ID].y = 100;

        if (r08_dialogActor.talking)
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objPlay1, r08_animations, R08_ANIM_TALK_PLAYING);
        }
        else
        {
            object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objPlay1, r08_animations, R08_ANIM_PLAYING);
        }
    }

    r08_object[R08_DOOR_OBJ_ID].active =  is_game_flag(COMPUTER_DOOR_OPEN_FLAG);
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
                        if (!is_game_flag(NERD_HELP_FLAG))
                            dialog_add("¨A qu‚ est s jugando?",2);
                        else
                            dialog_add("Entonces, ¨me ayudar s a aprobar el ex men de historia?",6);
                        dialog_add("¨Est s usando el aula de inform tica para jugar?",1);
                        dialog_add("No te molesto", 0);
                    break;
                    case 2:
                        dialog_add("El juego de estrategia definitivo es el Civilization",2);
                        dialog_add("Parece que se te dan muy bien los juegos de estrategia",3);
                        dialog_add("Prefiero las aventuras gr ficas", 2);
                        dialog_add("No te quiero distraer", 1);
                    break;
                    case 3:
                        dialog_add("No tienes un poco de obsesi¢n con las guerras hist¢ricas", 3);
                        dialog_add("Si se te da tan bien la historia, ¨no podr¡as ayudarme?",4);
                        dialog_add("Muy interesante", 2);
                    break;
                    case 4:
                        dialog_add("Si me ayudas, puedes decir a la gente que somos amigos",0);
                        dialog_add("Si me ayudas, ir‚ una tarde a merendar leche con galletas a tu casa",0);
                        dialog_add("Si me ayudas, te ense¤are a hacer niveles chulos para el DOOM",0);
                        dialog_add("Bueno, d‚jalo...", 0);
                    break;
                    case 6:
                        dialog_add("¨Qu‚ necesito para el disfraz?",0);
                        dialog_add("Genial, ­Gracias!",0);
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
                            if (!is_game_flag(NERD_HELP_FLAG))
                                script_say_actor("­Estoy jugando al Age of Empires!", &r08_dialogActor);
                            else
                                dialog_jump(5, 1, 6);
                        break;
                        case 2:
                            script_say_actor("El juego de estrategia definitivo", &r08_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Estoy usando todos mis conocimientos de la guerra para hacer partidas perfectas", &r08_dialogActor);
                        break;
                        case 4:
                            script_say_actor("Me encanta jugar a ser un se¤or de la guerra y aplastar a mis enemigos", &r08_dialogActor);
                        break;
                        case 5:
                            set_game_flag(NERD_SIDE_FLAG);                            
                            script_say_actor("Mi terapeuta dice que canaliza el odio que tengo dentro", &r08_dialogActor);
                        break;
                        case 6:
                            script_wait(3);
                        break;
                        case 7:
                            script_say_actor("Si quieres puedes jugar conmigo", &r08_dialogActor);
                        break;
                        case 8:
                            script_say_actor("O venir a mi casa y te ense¤o mas juegos que tengo", &r08_dialogActor);
                        break;
                        case 9:
                            script_say_actor("O podemos merendar y jugar al Dragones y Mazmorras", &r08_dialogActor);
                        break;
                        case 10:
                            script_say_actor("Tengo una campa¤a pensada que es la bomb...", &r08_dialogActor);
                        break;
                        case 11:
                            script_say("­BASTA!");
                        break;
                        case 12:
                            script_say("No me interesa, gracias");
                        break;
                        case 13:
                            script_say_actor("Como quieras", &r08_dialogActor);
                        break;
                        default:
                            clear_game_flag(NERD_SIDE_FLAG);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 2:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Y t£ le dijiste a tus padres que te compraran el ordenador para estudiar", &r08_dialogActor);
                        break;
                        case 2:
                            script_wait(2);
                        break;
                        case 3:
                            script_say("Touch‚");
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
                            set_game_flag(NERD_SIDE_FLAG);
                            script_say_actor("Me encantan los juegos de estrategia", &r08_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Todo lo que tenga que ver con la historia y las guerras", &r08_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Y destruir ej‚rcitos enemigos con mi gran poder", &r08_dialogActor);
                        break;
                        case 4:
                            script_say_actor("Y no te creas que solo juego. Me encanta leer libros de historia y leer haza¤as de grandes batallas", &r08_dialogActor);
                        break;
                        default:
                            clear_game_flag(NERD_SIDE_FLAG);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 101:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Tambi‚n me encanta", &r08_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Todo lo que tenga que ver con la historia y las guerras", &r08_dialogActor);
                        break;
                        case 3:
                            set_game_flag(NERD_SIDE_FLAG);
                            script_say_actor("Y no solo juego, eh. Me encanta leer libros de historia y leer haza¤as de grandes batallas", &r08_dialogActor);
                        break;
                        default:
                            clear_game_flag(NERD_SIDE_FLAG);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 103:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("¨Qui‚n juega a eso en estos tiempos?", &r08_dialogActor);
                        break;
                        case 2:
                            script_wait(5);
                        break;
                        case 3:
                            play_player_animation(ANIM_PLY_LOOK_FRONT);
                            script_wait(10);
                        break;
                        case 4:
                            play_player_animation(ANIM_PLY_SMILE_FRONT);
                            script_wait(10);
                        break;
                        default:
                            stop_player_animation();
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 201:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("No lo creas", &r08_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Creo que es una afici¢n muy sana", &r08_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Y tampoco es que me vaya a dar un d¡a por entrar al colegio armado con un fusil", &r08_dialogActor);
                        break;
                        case 4:
                            set_game_flag(NERD_SIDE_FLAG);
                            script_wait(20);
                        break;
                        case 5:
                            clear_game_flag(NERD_SIDE_FLAG);
                            script_say_actor("No, no... No estar¡a bien...", &r08_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 202:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say("Necesito aprobar el ex men de historia");
                        break;
                        case 2:
                            script_say_actor("­Claro amigo! Podemos quedar en mi casa y te ense¤o todo lo que tienes que saber", &r08_dialogActor);
                        break;
                        case 3:
                            script_say("Mmm... estaba pensando mejor en otra manera de ayuda");
                        break;
                        case 4:
                            set_game_flag(NERD_SIDE_FLAG);
                            script_say_actor("¨A qu‚ te refieres?", &r08_dialogActor);
                        break;
                        case 5:
                            script_say("Estaba pensando en que hicieras t£ el examen por mi");
                        break;
                        case 6:
                            script_wait(20);
                        break;
                        case 7:
                            script_say_actor("Pero...", &r08_dialogActor);
                        break;
                        case 8:
                            script_wait(10);
                        break;
                        case 9:
                            script_say_actor("¨No ser¡a meterme en un l¡o muy grande?", &r08_dialogActor);
                        break;
                        case 10:
                            script_say("­Que va! Lo tengo todo pensado. Te disfrazas de mi y te presentas al examen");
                        break;
                        case 11:
                            script_say("­Nadie lo notar !");
                        break;
                        case 12:
                            script_say_actor("No s‚... No lo veo claro...", &r08_dialogActor);
                        break;
                        default:
                            clear_game_flag(NERD_SIDE_FLAG);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 301:
                case 302:
                case 303:
                    switch (roomScript.step)
                    {
                        case 1:
                            set_game_flag(NERD_SIDE_FLAG);
                            script_say_actor("­Oh! ¨En serio?", &r08_dialogActor);
                        break;
                        case 2:
                            script_say_actor("De acuerdo, ­te ayudar‚!", &r08_dialogActor);
                        break;
                        case 3:
                            script_say_actor("Cons¡gueme algo para disfrazarme de ti y har‚ el examen", &r08_dialogActor);
                        break;
                        default:
                            clear_game_flag(NERD_SIDE_FLAG);
                            set_game_flag(NERD_HELP_FLAG);
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 401:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Si, te ayudar‚", &r08_dialogActor);
                        break;
                        case 2:
                            script_say_actor("Cons¡gueme algo para disfrazarme de ti y har‚ el examen", &r08_dialogActor);
                        break;
                        default:
                            script_next_dialog_node();
                            end_script();
                        break;
                    }
                break;
                case 501:
                    switch (roomScript.step)
                    {
                        case 1:
                            script_say_actor("Pues no s‚...", &r08_dialogActor);
                        break;
                        case 2:
                            if (!is_game_flag(BRAIN_COSTUME_FLAG))
                                script_say_actor("Consigue algo para el pelo", &r08_dialogActor);
                            else
                                roomScript.step++;
                        break;
                        case 3:
                            if (!is_game_flag(SHIRT_COSTUME_FLAG))
                            {
                                if (is_game_flag(BRAIN_COSTUME_FLAG))
                                    script_say_actor("Consigue alguna camiseta como las tuyas", &r08_dialogActor);
                                else
                                    script_say_actor("alguna camiseta como las tuyas", &r08_dialogActor);
                            }
                            else
                                roomScript.step++;
                        break;
                        case 4:
                            if (!is_game_flag(JEANS_COSTUME_FLAG))
                            {
                                if (is_game_flag(BRAIN_COSTUME_FLAG) || is_game_flag(SHIRT_COSTUME_FLAG))
                                    script_say_actor("Consigue alg£n pantal¢n parecido al tuyo", &r08_dialogActor);
                                else
                                    script_say_actor("y alg£n pantal¢n parecido al tuyo", &r08_dialogActor);
                            }
                            else
                                roomScript.step++;
                        break;
                        case 5:
                            script_say_actor("Y con eso lo tendremos listo", &r08_dialogActor);
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
                    case USE:
                    case OPEN:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player_to_target();
                            break;
                            case 1:
                                play_sound_rnd(sd_doorOpen);
                                roomScript.step++;
                            break;
                            case 2:
                                set_game_flag(COMPUTER_DOOR_OPEN_FLAG);
                                roomScript.hsY = get_player_pos_y();
                                script_player_take_state();
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
                                script_say("Los ordenadores del instituto siguen siendo unos 486");
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
                                script_say("No tengo tiempo para jugar ahora");
                            break;
                            case 1:
                                script_say("He de aprobar las asignaturas que me quedan para conseguir el dinero");
                            break;
                            case 2:
                                script_say("Ademas ese ordenador tiene el virus Barrotes");
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
                                script_say("No me hace falta");
                            break;
                            case 1:
                                script_say("Yo ya me pas‚ a programar en C");
                            break;
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
                                script_say("Parece que est  jugando a alg£n tipo de juego de estrategia");
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
                                script_say("No puedo usarlo");
                            break;
                            case 1:
                                script_say("El friki est  jugando");
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
                                if (is_game_flag(NERD_COSTUME_PLAYING_FLAG))
                                    script_say("Supuestamente est  disfrazado de mi");
                                else
                                    script_say("Este chaval es el rarito del instituto");
                                break;
                            case 1:
                                if (is_game_flag(NERD_COSTUME_PLAYING_FLAG))
                                {
                                    script_say("Creo que esto va a ser material para mis pesadillas");
                                    end_script();
                                }
                                else
                                script_say("Siempre esta metido en su mundo b‚lico y de juegos de rol");
                            break;
                            case 2:
                                script_say("No parece que tenga muchos amigos");
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
                                if (!is_game_flag(HISTORY_APPROVED_FLAG))
                                    script_move_player(214, 126);
                                else
                                {
                                    script_say("Ya me ha sido de suficiente ayuda");
                                    end_script();
                                }
                                break;
                            case 1:
                                change_player_dir(DIR_LEFT);
                                script_start_dialog(1);
                            break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                    case GIVE:
                        switch (roomScript.invObject)
                        {
                            case id_brain:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (!is_game_flag(NERD_HELP_FLAG))
                                        {
                                            script_say_actor("¨Y qu‚ hago con eso?", &r08_dialogActor);
                                            end_script();
                                        }
                                        else
                                            script_say_actor("Podr¡a servir como pelo, pero el color es muy claro", &r08_dialogActor);
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                            case id_blackBrain:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (!is_game_flag(NERD_HELP_FLAG))
                                        {
                                            script_say_actor("¨Para qu‚ me das esto?", &r08_dialogActor);
                                            end_script();
                                        }
                                        else
                                            script_move_player(186, 130);
                                    break;
                                    case 1:
                                        change_player_dir(DIR_LEFT);
                                        script_player_take_state();
                                        object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_TAKE);
                                    break;
                                    case 2:
                                        script_remove_inv_object(id_blackBrain);
                                        set_game_flag(BRAIN_COSTUME_FLAG);
                                    break;
                                    case 3:
                                        script_say_actor("­Perfecto! Usaremos esto para el disfraz", &r08_dialogActor);
                                    break;
                                    case 4:
                                        start_script(R08_COSTUME_COMPLETE_SCRIPT);
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                            case id_starShirt:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (!is_game_flag(NERD_HELP_FLAG))
                                        {
                                            script_say_actor("¨Para qu‚ me das esto?", &r08_dialogActor);
                                            end_script();
                                        }
                                        else
                                            script_move_player(186, 130);
                                    break;
                                    case 1:
                                        change_player_dir(DIR_LEFT);
                                        script_player_take_state();
                                        object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_TAKE);
                                    break;
                                    case 2:
                                        script_remove_inv_object(id_starShirt);
                                        set_game_flag(SHIRT_COSTUME_FLAG);
                                    break;
                                    case 3:
                                        script_say_actor("­Muy bien! Esto servir  para el disfraz", &r08_dialogActor);
                                    break;
                                    case 4:
                                        start_script(R08_COSTUME_COMPLETE_SCRIPT);
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                            case id_jeans:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (!is_game_flag(NERD_HELP_FLAG))
                                        {
                                            script_say_actor("¨Para qu‚ me das esto?", &r08_dialogActor);
                                            end_script();
                                        }
                                        else
                                            script_move_player(186, 130);                                            
                                    break;
                                    case 1:
                                        change_player_dir(DIR_LEFT);
                                        script_player_take_state();
                                        object_play_animation(&r08_object[R08_NERD_OBJ_ID], r08d_objIdle, r08_animations, R08_ANIM_TAKE);
                                    break;
                                    case 2:
                                        script_remove_inv_object(id_jeans);
                                        set_game_flag(JEANS_COSTUME_FLAG);
                                    break;
                                    case 3:
                                        script_say_actor("­Oh si! Esto nos vendr  bien para el disfraz", &r08_dialogActor);
                                    break;
                                    case 4:
                                        start_script(R08_COSTUME_COMPLETE_SCRIPT);
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                            case id_shirt:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        if (!is_game_flag(NERD_HELP_FLAG))
                                        {
                                            script_say_actor("Oye, no me molestes", &r08_dialogActor);
                                            end_script();
                                        }
                                        else
                                            script_say_actor("Mmm. Se parece un poco a tu camiseta pero no lo suficiente", &r08_dialogActor);
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                            default:
                                begin_script();
                                switch (rand() % 4)
                                {
                                    case 0:
                                        script_say_actor("No me interrumpas. Estoy jugando", &r08_dialogActor);
                                    break;
                                    case 1:
                                        script_say_actor("No quiero eso", &r08_dialogActor);
                                    break;
                                    case 2:
                                        script_say_actor("Me est s desconcentrando", &r08_dialogActor);
                                    break;
                                    case 3:
                                        script_say_actor("No me des tus trastos", &r08_dialogActor);
                                    break;
                                    case 4:
                                        script_say_actor("D‚jame. Estoy concentrado en el juego", &r08_dialogActor);
                                    break;
                                }
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
                                script_say("­Vaya! ­Si tambi‚n hay un 386!");
                                break;
                            case 1:
                                script_say("­Viva la educaci¢n p£blica!");
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
                                script_say("Mmmm, no");
                                break;
                            case 1:
                                script_say("Despu‚s de tener un Pentium en casa un 386 se me hace tortuga");
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
            case R08_COSTUME_COMPLETE_SCRIPT:
                switch (roomScript.step)
                {
                    case 0:
                        if (is_game_flag(BRAIN_COSTUME_FLAG) &&
                            is_game_flag(SHIRT_COSTUME_FLAG) &&
                            is_game_flag(JEANS_COSTUME_FLAG)
                            )
                        {
                            set_game_flag(NERD_SIDE_FLAG);
                            script_say_actor("Creo que ya tengo todo lo que necesito", &r08_dialogActor);
                        }
                        else
                            end_script();
                    break;
                    case 1:
                        script_say_actor("Voy a prepararme el disfraz y me presentar‚ a tu examen", &r08_dialogActor);
                    break;
                    case 2:
                        game_fade_out(FADE_SLOW_SPEED);
                        clear_game_flag(NERD_SIDE_FLAG);
                        set_player_position(216, 104);
                        roomScript.step++;
                    break;
                    case 3:
                        script_wait(20);
                        set_game_flag(NERD_COSTUME_FLAG);
                        play_player_animation(ANIM_PLY_SURPRISE);
                    break;
                    case 4:
                        game_fade_in();
                        script_wait(10);
                    break;
                    case 5:
                        script_say_actor("­Ha estado chupado!", &r08_dialogActor);
                    break;
                    case 6:
                        script_wait(6);
                    break;
                    case 7:
                        script_say_actor("Disfrazado as¡, nadie se ha dado cuenta de que no eras t£", &r08_dialogActor);
                    break;
                    case 8:
                        script_say("Salta a la vista");
                    break;
                    case 9:
                        script_play_sound(sd_approved);
                    break;
                    case 10:
                        script_say_actor("­Tienes la asignatura aprobada!", &r08_dialogActor);
                        set_game_flag(HISTORY_APPROVED_FLAG);
                    break;
                    case 11:
                        stop_player_animation();
                        script_say("Emm...");
                    break;
                    case 12:
                        script_say("Gracias");
                    break;
                    case 13:
                        if (is_game_flag(MATH_APPROVED_FLAG) && is_game_flag(HISTORY_APPROVED_FLAG) && is_game_flag(PE_APPROVED_FLAG))
                            play_sound(sd_completed);
                        roomScript.step++;
                    break;
                    case 14:
                        if (is_game_flag(MATH_APPROVED_FLAG) && is_game_flag(HISTORY_APPROVED_FLAG) && is_game_flag(PE_APPROVED_FLAG))
                            script_say("­Genial! ­Ya he aprobado todo!");
                        else
                            roomScript.step++;
                    break;
                    case 15:
                        change_player_dir(DIR_RIGHT);
                        script_say("Casi que me voy de aqu¡ antes de que esto se ponga raro");
                    break;
                    case 16:
                        script_move_player(320, 104);
                    break;
                    case 17:
                        clear_game_flag(NERD_COSTUME_FLAG);
                        set_game_flag(NERD_COSTUME_PLAYING_FLAG);
                        change_room_pos(SCHOOL_ROOM_NUM, 272, 84);
                        roomScript.step++;
                    break;
                    default:
                        end_script();
                    break;
                }
            break;
            case R08_EPILOGUE_SCRIPT:
                switch (roomScript.step)
                {
                    case 0:
                        begin_script();
                        script_say_actor("­Vamos!", &r08_dialogActor);
                    break;
                    case 1:
                        script_wait(10);
                    break;
                    case 2:
                        begin_script();
                        script_say_actor("­Morid malditos!", &r08_dialogActor);
                    break;
                    case 3:
                        script_wait(10);
                    break;
                    case 4:
                        begin_script();
                        script_say_actor("Odio a todos mis enemigos", &r08_dialogActor);
                    break;
                    case 5:
                        script_wait(10);
                    break;
                    case 6:
                        begin_script();
                        script_say_actor("Os odio tanto como a mis compa¤eros de clase", &r08_dialogActor);
                    break;
                    case 7:
                        script_wait(5);
                    break;
                    case 8:
                        begin_script();
                        script_say_actor("Y odio a los profesores...", &r08_dialogActor);
                    break;
                    case 9:
                        script_wait(5);
                    break;
                    case 10:
                        begin_script();
                        script_say_actor("Y odio a aquella chica que me llam¢ raro", &r08_dialogActor);
                    break;
                    case 11:
                        script_wait(5);
                    break;
                    case 12:
                        begin_script();
                        script_say_actor("Un dia voy a llevar un fusil al instituto y voy a...", &r08_dialogActor);
                    break;
                    case 13:
                        set_game_flag(NERD_ERROR_FLAG);
                        script_play_sound(sd_w95Error);
                    break;
                    case 14:
                        script_wait(10);
                    break;
                    case 15:
                        set_game_flag(NERD_ERROR_2_FLAG);
                        script_wait(5);
                    break;
                    case 16:
                        script_say_actor("Pero sobretodo odio Windows", &r08_dialogActor);
                    break;
                    case 17:
                        script_wait(20);
                    break;
                    default:
                        set_game_flag(END_FINISH_FLAG);
                        end_script();
                    break;
                }
            break;
            case R08_DOOR_CLOSE_SCRIPT:
                switch(roomScript.step)
                {
                    case 0:
                        change_player_dir(DIR_RIGHT);
                        script_wait(1);
                    break;
                    case 1:
                        roomScript.hsY = get_player_pos_y();
                        script_player_take_state();
                    break;
                    case 2:
                        play_sound_rnd(sd_doorClose);
                        clear_game_flag(COMPUTER_DOOR_OPEN_FLAG);
                        roomScript.step++;
                    break;
                    default:
                        change_player_dir(DIR_LEFT);
                        end_script();
                    break;
                }
            break;
        }
    }
}