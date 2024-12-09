/*
=========================================================
 Room Number:   01
 Room Name:     01_bedRoom
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "engine.h"
#include "room01.h"

//Funtion to return the name of hotspot by color code
void r01_get_hotspot_name(uint8_t colorCode, char *s)
{
    //check the object
    switch(colorCode)
    {
        case r01_guitar:
                strcpy(s, "Guitarra");
            break;
        case r01_stereo:
                strcpy(s, "Minicadena");
            break;
        case r01_door:
                strcpy(s, "Puerta");
            break;
        case r01_cassette:
                strcpy(s, "Casete");
            break;
        case r01_spider:
                strcpy(s, "Ara¤a");
            break;
        case r01_drums:
                strcpy(s, "Tambor");
            break;
        case r01_thing:
                strcpy(s, "Cosa");
            break;
        case r01_glasses:
                strcpy(s, "Gafas");
            break;
        case r01_cd:
                strcpy(s, "Cd");
            break;
        case r01_poster:
                strcpy(s, "Poster");
            break;
        case r01_draws:
                strcpy(s, "Cajones");
            break;
        case r01_sofa:
                strcpy(s, "Sof ");
            break;
        case r01_computer:
                strcpy(s, "Ordenador");
            break;
        case r01_toys:
                strcpy(s, "Figuras");
            break;
        case r01_printer:
                strcpy(s, "Impresora");
            break;
        case r01_book1:
                strcpy(s, "Libro");
            break;
        case r01_book2:
                strcpy(s, "Libro");
            break;
        case r01_book3:
                strcpy(s, "Libro");
            break;
        case r01_book4:
                strcpy(s, "Libro");
            break;
        default:
            strcpy(s, "");
    }
}

//function to return default hotspot verb
enum verbs r01_get_default_hotspot_verb(uint8_t colorCode)
{
    //check the object
    switch(colorCode)
    {
        case r01_guitar:
            return LOOK;
            break;
        case r01_stereo:
            return LOOK;
            break;
        case r01_door:
            return OPEN;
            break;
        case r01_cassette:
            return LOOK;
            break;
        case r01_spider:
            return LOOK;
            break;
        case r01_drums:
            return LOOK;
            break;
        case r01_thing:
            return LOOK;
            break;
        case r01_glasses:
            return LOOK;
            break;
        case r01_cd:
            return LOOK;
            break;
        case r01_poster:
            return LOOK;
            break;
        case r01_draws:
            return OPEN;
            break;
        case r01_sofa:
            return LOOK;
            break;
        case r01_computer:
            return USE;
            break;
        case r01_toys:
            return LOOK;
            break;
        case r01_printer:
            return LOOK;
            break;
        case r01_book1:
            return LOOK;
            break;
        case r01_book2:
            return LOOK;
            break;
        case r01_book3:
            return LOOK;
            break;
        case r01_book4:
            return LOOK;
            break;
        default:
            return LOOK;
    }
}

//function to return room object info
tObject* r01_get_object_info(uint8_t numObject)
{
    if (numObject < R01_ROOM_NUM_OBJS)
        return &r01_object[numObject];
    else
        return NULL;
}

//function to init room
void r01_room_init()
{
    //update room objects state
    r01_object[R01_CASSETTE_OBJ_ID].active  = !is_game_flag(GOT_CASSETTE_FLAG);
    r01_object[R01_GUITAR_OBJ_ID].active    = !is_game_flag(GOT_GUITAR_FLAG);
    r01_object[R01_STEREO01_OBJ_ID].active    = is_game_flag(STEREO_ON_FLAG);
    
    game_fade_in();
}

//global funcion to update room
void r01_room_update()
{
    //update room objects
    r01_update_room_objects();

    //update dialog line selection
    r01_update_dialog_selection();
    
    //update room script
    r01_update_room_script();
}

//update room objects
void r01_update_room_objects()
{
    //Stereo
    object_play_animation(&r01_object[R01_STEREO01_OBJ_ID], r01d_objStereo01, r01_animations, R01_ANIM_PLAY_STEREO);
}

//update dialog selection
void r01_update_dialog_selection()
{

}

//update room script
void r01_update_room_script()
{
//if script active is room script type
    if (roomScript.active && roomScript.type == ROOM_SCRIPT_TYPE)
    {
        //sequence actions
        switch (roomScript.object)
        {
            case r01_guitar:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Mi guitarra marca Sonora");
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
                                script_take_object(&r01_object[R01_GUITAR_OBJ_ID].active, GOT_GUITAR_FLAG, id_guitar);
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r01_stereo:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es mi minicadena Hifi £ltimo modelo");
                                break;
                            case 1:
                                begin_script();
                                script_say("Con doble pletina, sintonizador de radio y equalizador gr fico");
                                break;
                            case 2:
                                begin_script();
                                script_say("Wow!!");
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
                                if (!is_game_flag(USED_CASSETTE_FLAG))
                                {
                                    script_say("No hay ning£n casete dentro para escuchar");
                                    end_script();
                                }
                                else
                                    script_move_player_to_target();
                                break;
                            case 1:
                                script_player_take_state();
                                break;
                            case 2:
                                toogle_game_flag(STEREO_ON_FLAG);
                                r01_object[R01_STEREO01_OBJ_ID].active = is_game_flag(STEREO_ON_FLAG);
                                end_script();
                                break;
                            default:
                                end_script();
                                break;
                        }
                        break;
                    case USE_WITH:
                        switch (roomScript.invObject)
                        {
                            case id_cassette:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_move_player_to_target();
                                        break;
                                    case 1:
                                        script_player_take_state();
                                        break;
                                    case 2:
                                        script_remove_inv_object(id_cassette);
                                        set_game_flag(USED_CASSETTE_FLAG);
                                        end_script();
                                        break;
                                }
                                break;
                        }
                        break;
                }
                break;            
            case r01_door:
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
                    case OPEN ... CLOSE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Siempre est  abierta");
                                break;
                            case 1:
                                begin_script();
                                script_say("No tengo secretos para mis padres...");
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
                                script_move_player(roomScript.hsX,200);
                                break;
                            case 1:
                                change_room_pos(CORRIDOR_ROOM_NUM,174,38);
                                end_script();
                                break;
                        }
                        break;
                }
                break;            
            case r01_cassette:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es un casete de lo £ltimo que ha sacado Reincidentes");
                                break;
                            case 1:
                                begin_script();
                                script_say("La £ltima compra que pude hacer cuando ten¡a dinero");
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
                                script_take_object(&r01_object[R01_CASSETTE_OBJ_ID].active, GOT_CASSETTE_FLAG, id_cassette);
                                end_script();
                                break;
                        }
                        break;
                }
                break;            
            case r01_spider:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es mi figura exclusiva de ara¤a de la serie He-man");
                                break;
                            case 1:
                                begin_script();
                                script_say("­POR EL PODER DE GREYSKULL!");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r01_drums:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es mi tambor de mi ‚poca de tamborilero");
                                break;
                            case 1:
                                begin_script();
                                script_say("En la ‚poca que lo tocaba todav¡a no hab¡a descubierto el rock");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r01_thing:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("No s‚ que puede ser eso...");
                                break;
                            case 1:
                                begin_script();
                                script_say("Brilla un poco y parece estar pegado al suelo...");
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
                                script_say("No consigo cogerlo");
                                break;
                            case 1:
                                begin_script();
                                script_say("Est  muy pegado al suelo");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch (roomScript.invObject)
                        {
                            case id_spatula:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_move_player_to_target();
                                        break;
                                    case 1:
                                        set_game_flag(GOT_COIN_FLAG);
                                        script_add_inv_object(id_coin);
                                        break;
                                    case 2:
                                        script_say("­Eureka! Con la esp tula lo he podido despegar");
                                        break;
                                    case 3:
                                        script_say("­Es una moneda de 100 pesetas!");
                                        end_script();
                                        break;
                                }
                                break;
                        }
                        break;
                }
                break;            
            case r01_glasses:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Son mis gafas de cerca, de lejos y para leer");
                                break;
                            case 1:
                                begin_script();
                                script_say("Tambi‚n las uso cuando llevo lentillas");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r01_cd:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Cd");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r01_poster:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Poster");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r01_draws:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Estos cajones no guardan mas que porquer¡a dentro");
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
                                script_say("No hay nada de inter‚s dentro");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r01_sofa:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("¨Cuantos chavales pueden permitirse tener un sofa en su habitaci¢n?");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r01_computer:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Mi flamante Pentium a 100Mhz");
                                break;
                            case 1:
                                begin_script();
                                script_say("M quina de alta tecnolog¡a solo para manos expertas");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r01_toys:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Son mis figuras de los Caballeros del Zod¡aco edici¢n limitada");
                                break;
                            case 1:
                                begin_script();
                                script_say("Mira como brillan esos cromados...");
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
                                script_say("Prefiero dejarlos aqu¡");
                                break;
                            case 1:
                                begin_script();
                                script_say("Van a ser mi jubilaci¢n");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case r01_printer:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Mi impresora de inyecci¢n");
                                break;
                            case 1:
                                begin_script();
                                script_say("Solo tiene cartucho de tinta negra");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r01_book1:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("\"La edad prohibida\"");
                                break;
                            case 1:
                                begin_script();
                                script_say("de Torcuato Luca de Tena");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r01_book4:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("\"MSDOS para Dummies\"");
                                break;
                            case 1:
                                begin_script();
                                script_say("por Dan Gookin");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case r01_book2:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("\"Del deporte tambi‚n se sale\"");
                                break;
                            case 1:
                                begin_script();
                                script_say("por Diego Maradona");
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
                                script_take_object(NULL, GOT_BOOK_FLAG, id_book);
                                end_script();
                                break;
                        }
                        break;
                }
                break;            
            case r01_book3:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Libro 4");
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
