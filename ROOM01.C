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
            if (!is_game_flag(GOT_CASSETTE_FLAG))
                strcpy(s, "Casete");
            else
                strcpy(s, "");    
            break;
        case r01_spider:
                strcpy(s, "Ara¤a");
            break;
        case r01_drums:
                strcpy(s, "Tambor");
            break;
        case r01_thing:
            if (!is_game_flag(GOT_COIN_FLAG))
                strcpy(s, "Cosa");
            else
                strcpy(s, "");
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
        case r01_cartridge:
            if (is_game_flag(r01_object[R01_CARTRIDGE_OBJ_ID].active))
            {
                strcpy(s, "Cartucho vac¡o");
                break;
            }
        case r01_printer:
                strcpy(s, "Impresora");
            break;
        case r01_book1:
                strcpy(s, "Libro 1");
            break;
        case r01_book2:
            if (!is_game_flag(GOT_BOOK_FLAG))
                strcpy(s, "Libro 3");
            else
                strcpy(s, "");
            break;
        case r01_book3:
                strcpy(s, "Revista");
            break;
        case r01_book4:
                strcpy(s, "Libro 2");
            break;
        case r01_window:
                strcpy(s, "Ventana");
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
        case r01_cartridge:
            if (is_game_flag(r01_object[R01_CARTRIDGE_OBJ_ID].active))
            {
                return LOOK;
                break;
            }
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
    //rewind computer animation
    r01_animations[R01_COMPUTER_OBJ_ID].frameTime = 0;
    r01_animations[R01_COMPUTER_OBJ_ID].frame = r01d_objCompBoot1;
    
    if (!is_game_flag(GAME_START_FLAG))
        start_script(R01_GAME_START_SCRIPT);
        
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
    r01_object[R01_STEREO01_OBJ_ID].active  = is_game_flag(STEREO_ON_FLAG);
    object_play_animation(&r01_object[R01_STEREO01_OBJ_ID], r01d_objStereo01, r01_animations, R01_ANIM_PLAY_STEREO);

    r01_object[R01_COMPUTER_OBJ_ID].active  = is_game_flag(USED_COMPUTER_FLAG);
    r01_object[R01_COIN_OBJ_ID].active      = !is_game_flag(GOT_COIN_FLAG);
    r01_object[R01_CASSETTE_OBJ_ID].active  = !is_game_flag(GOT_CASSETTE_FLAG);
    r01_object[R01_BOOK_OBJ_ID].active      = !is_game_flag(GOT_BOOK_FLAG);
    //r01_object[R01_GUITAR_OBJ_ID].active  = !is_game_flag(GOT_GUITAR_FLAG);

    r01_object[R01_OPENPRINTER_OBJ_ID].active   = is_game_flag(OPEN_PRINTER_FLAG);
    r01_object[R01_CARTRIDGE_OBJ_ID].active     = is_game_flag(OPEN_PRINTER_FLAG) && !is_game_flag(GOT_EMPTY_CARTRIDGE_FLAG);
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
                            case 1:
                                script_say("Mi intento frustado de ser una estrella del rock");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE:
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es mejor que se quede en la funda");
                                break;
                            case 1:
                                script_say("Por mi bien, y por el bien de la m£sica");
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
                                if (!is_game_flag(STEREO_ON_FLAG))
                                    script_say("Es mi minicadena Hifi £ltimo modelo");
                                else
                                {
                                    script_say("La minicadena est  en marcha");
                                    end_script();
                                }
                                break;
                            case 1:
                                script_say("Con doble pletina, sintonizador de radio y equalizador gr fico");
                                break;
                            case 2:
                                if (!is_game_flag(USED_CASSETTE_FLAG))
                                    script_say("­Alucina!");
                                else
                                    script_say("Ahora tiene una cinta dentro");
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
                                else if (is_game_flag(CASSETTE_BROKEN_FLAG))
                                {
                                    script_say("La cinta se ha enganchado");
                                    end_script();
                                }
                                else
                                    script_move_player_to_target();
                                break;
                            case 1:
                                script_play_sound(sd_cassettePlay);
                            break;
                            case 2:
                                script_player_take_state();
                                break;
                            case 3:
                                toggle_game_flag(STEREO_ON_FLAG);
                                r01_object[R01_STEREO01_OBJ_ID].active = is_game_flag(STEREO_ON_FLAG);
                                roomScript.step++;
                            break;
                            case 4:
                                script_play_sound(sd_cassetteSong);
                            break;
                            case 5:
                                script_wait(110);
                            break;
                            case 6:
                                play_player_animation(ANIM_PLY_SURPRISE);
                                script_wait(20);
                            break;
                            case 7:
                                clear_game_flag(STEREO_ON_FLAG);
                                set_game_flag(CASSETTE_BROKEN_FLAG);
                                script_say("Ya se ha enganchado la cinta");
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
                                        script_play_sound(sd_cassettePut);
                                    break;
                                    case 2:
                                        script_player_take_state();
                                        break;
                                    case 3:
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
                    case USE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_move_player(roomScript.hsX,154);
                            break;
                            case 1:
                                script_move_player_no_clip(roomScript.hsX, 240);
                            break;
                            case 2:
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
                                script_say("Es un casete de lo £ltimo que ha sacado \"Reincidientes\"");
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
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("No creo que una ara¤a de juguete sea de mucha utilidad");
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
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Ya dej‚ el tambor hace mucho tiempo");
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
                                        script_play_sound(sd_unglue);
                                    break;
                                    case 2:
                                        set_game_flag(GOT_COIN_FLAG);
                                        r01_object[R01_COIN_OBJ_ID].active = false;
                                        script_add_inv_object(id_coin);
                                        break;
                                    case 3:
                                        script_say("­Eureka! Con la esp tula lo he podido despegar");
                                        break;
                                    case 4:
                                        script_say("­Es una moneda de 100 pesetas!");
                                        end_script();
                                        break;
                                }
                                break;
                            case id_knife:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_say("Tiene muy poca superficie para hacer palanca");
                                    break;
                                    case 1:
                                        script_say("Necesito algo mas ancho");
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
                    case USE:
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("No creo que las necesite");
                                break;
                            case 1:
                                begin_script();
                                script_say("Con esta resolucion VGA de 320x240 los p¡xeles son como pu¤os");
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
                                script_say("Un amigo trajo al instituto esto que llaman compact disc");
                                break;
                            case 1:
                                script_say("Se supone que va a ser el formato musical del futuro");
                                break;
                            case 2:
                                script_say("Como de momento no tengo nada para poder reproducirlo lo tengo ah¡ colgado porque brilla");
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
                                script_say("Ah¡ est  bien");
                                break;
                            case 1:
                                script_say("Su brillo ahuyenta a los mosquitos");
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
                                script_say("Mi otro grupo favorito: Los de Marras");
                            break;
                            case 1:
                                script_say("Tengo el presentimiento que a este grupo le va a ir muy bien en el futuro");
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
                                script_say("Est  mejor enganchado a la pared");
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
                    case USE:
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
                    case USE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("No tengo tiempo para descansar");
                                break;
                            case 1:
                                script_say("He de averiguar como conseguir dinero para la entrada del concierto");
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
                                script_say("Le he instalado hace poco Windows 95");
                                break;
                            case 2:
                                script_say("Pero sigo prefiriendo mi viejo MS-DOS");
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
                                script_move_player(235, 142);
                            break;
                            case 1:
                                player_take_state();
                                set_game_flag(USED_COMPUTER_FLAG);
                                script_play_sound(sd_computerBoot);
                            break;
                            case 2:
                                script_object_play_animation(&r01_object[R01_COMPUTER_OBJ_ID], r01d_objCompBoot1, r01_animations, R01_ANIM_ON_COMPUTER);
                            break;
                            case 3:
                                object_play_animation(&r01_object[R01_COMPUTER_OBJ_ID], r01d_objCompBoot6, r01_animations, R01_ANIM_BIOS_COMPUTER);
                                script_play_sound_wait(sd_computerBoot);
                            break;
                            case 4:
                                play_player_animation(ANIM_PLY_HAPPY_IDLE);
                                script_play_sound_wait(sd_win95Startup);
                                object_play_animation(&r01_object[R01_COMPUTER_OBJ_ID], r01d_objCompBoot6, r01_animations, R01_ANIM_W95_COMPUTER);
                            break;
                            case 5:
                                play_player_animation(ANIM_PLY_SURPRISE);
                                script_play_sound_wait(sd_w95Error);
                                object_play_animation(&r01_object[R01_COMPUTER_OBJ_ID], r01d_objCompBoot6, r01_animations, R01_ANIM_ERROR_COMPUTER);
                            break;
                            case 6:
                                script_say("Odio windows...");
                            break;
                            case 7:
                                script_player_take_state();
                            break;
                            default:
                                clear_game_flag(USED_COMPUTER_FLAG);
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
            case r01_cartridge:
                if (r01_object[R01_CARTRIDGE_OBJ_ID].active)
                {
                    switch(roomScript.verb)
                    {
                        case LOOK:
                            switch (roomScript.step)
                            {
                                case 0:
                                    begin_script();
                                    script_say("Es el cartucho de tinta de la impresora");
                                break;
                                case 1:
                                    script_say("Pero est  vac¡o");
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
                                    script_take_object(NULL, GOT_EMPTY_CARTRIDGE_FLAG, id_emptyCartridge);
                                    break;
                                case 2:
                                    script_wait(5);
                                    break;
                                default:
                                    end_script();
                                    break;
                            }
                        break;
                    }
                break;
                }
                else
                    roomScript.object = r01_printer;
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
                                if (!is_game_flag(OPEN_PRINTER_FLAG))
                                    script_say("Solo tiene cartucho de tinta negra");
                                else
                                    script_say("Con la tapa abierta veo el cartucho de tinta");
                                break;
                            case 2:
                                script_say("Pero no le queda tinta");
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
                                script_say("No le queda tinta");
                                break;
                            case 1:
                                script_say("Adem s tengo unos problemas con los controladores de Windows 95 y no me funciona");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch (roomScript.invObject)
                        {
                            case id_fullCartridge:
                                begin_script();
                                script_say("Aunque le ponga tinta a esa impresora no funciona bien");
                                end_script();
                            break;
                        }
                    break;
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("¨Que quieres que me lleve la impresora entera?");
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
                                if (!is_game_flag(OPEN_PRINTER_FLAG))
                                    script_move_player_to_target();
                                else
                                {
                                    script_say("Ya est  abierta");
                                    end_script();
                                }
                            break;
                            case 1:
                                script_play_sound(sd_lidOpen);
                            break;
                            case 2:
                                script_play_player_animation(ANIM_PLY_TAKE);
                                set_game_flag(OPEN_PRINTER_FLAG);
                            break;
                            default:
                                end_script();
                            break;
                        }
                    break;
                    case CLOSE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (is_game_flag(OPEN_PRINTER_FLAG))
                                    script_move_player_to_target();
                                else
                                {
                                    script_say("Ya est  cerrada");
                                    end_script();
                                }
                            break;
                            case 1:
                                script_play_sound(sd_lidClose);
                            break;
                            case 2:
                                script_play_player_animation(ANIM_PLY_TAKE);
                                clear_game_flag(OPEN_PRINTER_FLAG);
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
                                script_say("de Torcuato Luca de Tena");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE:
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Ya tuve bastante con leerlo en el colegio");
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
                                script_say("por Dan Gookin");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE:
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("No lo necesito");
                                break;
                            case 1:
                                script_say("Yo no soy dummy de MS-DOS");
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
                                script_take_object(&r01_object[R01_BOOK_OBJ_ID].active, GOT_BOOK_FLAG, id_book);
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
                                script_say("Es un cat logo musical de la tienda Tipo");
                                break;
                            case 1:
                                script_say("Pero ya no tengo dinero para comprarme ning£n disco");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE:
                    case TAKE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Sin dinero para comprar, no tiene mucho inter‚s");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
            break;
            case r01_window:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("La ventana que da a mi callej¢n");
                            break;
                            case 1:
                                script_play_sound_wait(sd_dogBarf);
                                play_player_animation(ANIM_PLY_SURPRISE);
                            break;
                            case 2:
                                stop_player_animation();
                                script_say("Otra vez los perros del callej¢n haciendo ruido");
                            break;
                            case 3:
                                script_say("Menos mal que no me dedico a grabar podcasts");
                            break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE:
                    case OPEN:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Mejor la dejo cerrada");
                                break;
                            case 1:
                                script_say("Aunque no grabe podcasts aprecio el silencio");
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case R01_GAME_START_SCRIPT:
                switch(roomScript.step)
                {
                    case 0:
                        begin_script();
                        script_say("¨Y como consigo el dinero para el concierto?");
                    break;
                    case 1:
                        script_say("Tengo que averiguarlo...");
                    break;
                    case 2:
                        set_game_flag(GAME_START_FLAG);
                        end_script();
                    break;
                }
            break;
        }
    }
}
