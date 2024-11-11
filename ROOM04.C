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
        case r04_cheesse:
                strcpy(s, "Queso");
            break;
        case r04_clock:
                if (!is_game_flag(GOT_CLOCK))
                    strcpy(s, "Reloj");
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

}

//update dialog selection
void r04_update_dialog_selection()
{

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
                                script_player_take_state();
                                break;
                            //case 2:
                            //    script_take_object();
                            //    break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r04_cheesse:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Me encanta el queso");
                                break;
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
                }
                break;

        }
    }
}
