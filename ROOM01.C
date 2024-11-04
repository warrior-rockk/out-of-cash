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
                strcpy(s, "Araña");
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
                strcpy(s, "SofÃ¡");
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
                strcpy(s, "Libro 1");
            break;
        case r01_book2:
                strcpy(s, "Libro 2");
            break;
        case r01_book3:
                strcpy(s, "Libro 3");
            break;
        case r01_book4:
                strcpy(s, "Libro 4");
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
                                script_say("Guitarra");
                                break;
                            default:
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
                                script_say("Minicadena");
                                break;
                            default:
                                end_script();
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
                                script_say("Puerta");
                                break;
                            default:
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
                                script_say("Casete");
                                break;
                            default:
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
                                script_say("AraÃƒÂ±a");
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
                                script_say("Tambor");
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
                                script_say("Cosa");
                                break;
                            default:
                                end_script();
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
                                script_say("Gafas");
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
                                script_say("Cajones");
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
                                script_say("SofÃƒÂ¡");
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
                                script_say("Ordenador");
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
                                script_say("Figuras");
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
                                script_say("Impresora");
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
                                script_say("Libro 1");
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
                                script_say("Libro 2");
                                break;
                            default:
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
                                script_say("Libro 3");
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
