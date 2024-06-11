#include <stdio.h>
#include <allegro.h>
#include "game.h"
#include "datos.h"
#include "room01.h"

//struct definition
typedef struct tActor
{
    float x;
    float y;
    int width;
    int height;
    float vX;
    float vY;
    int graph;
    BITMAP *image[6];
} tActor;

typedef struct tRoom
{
    BITMAP  *image;
    BITMAP  *hsImage;
    MIDI    *song;
} tRoom;

typedef struct tHUD
{
    BITMAP *image;
    BITMAP *hsImage;
} tHUD;

typedef struct tCursor
{
    char objectName[OBJECT_NAME_MAX_CHARS];
    tCursorActions action;
    BITMAP *image;
} tCursor;

//global object
tActor player;
tRoom room;
tHUD hud;
tCursor cursor;

//global vars
PALETTE gamePalette;
BITMAP *buffer;
DATAFILE *dataFile;

//function declarations
void abort_on_error();
void load_resources();
void init_cursor();
void load_dat_resources();
void draw_cursor(BITMAP *buffer);
void draw_debug(BITMAP *buffer);
void draw_status_bar(BITMAP *buffer);

int main()
{
    //initialize and install modules
    allegro_init();
    install_mouse();
    install_keyboard();
    install_sound(0, MIDI_AUTODETECT, 0);
    
    set_color_depth(8);
    set_gfx_mode(GFX_AUTODETECT, 320, 240, 0, 0);

     //screen buffer creation
    buffer = create_bitmap(RES_X, RES_Y);

    //load resources
    load_dat_resources();
    
    play_midi(room.song, -1);

    init_cursor();
    
    //game loop
    while (!key[KEY_ESC])
    {
        clear(buffer);
        blit(room.image, buffer, 0, 0, 0, 0, room.image->w, room.image->h);
        blit(hud.image, buffer, 0, 0, 0, HUD_Y, hud.image->w, hud.image->h);

        draw_debug(buffer);
        draw_status_bar(buffer);
        draw_cursor(buffer);
        //blits to screen
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    }

    //free resources
    destroy_bitmap(room.image);
    destroy_bitmap(room.hsImage);
    destroy_bitmap(hud.image);
    destroy_bitmap(cursor.image);
    destroy_midi(room.song);
//    unload_datafile(dataFile);
    
    return 0;
}

//function to load resources
void load_resources()
{
    //load bitmaps
    room.image = load_bitmap("res/rooms/room01.bmp", gamePalette);
    //set global palette
    set_palette(gamePalette);

    room.hsImage = load_bitmap("res/rooms/room01hs.bmp", 0);
    hud.image = load_bitmap("res/hud.bmp", 0);
    cursor.image = load_bitmap("res/cursor.bmp", 0);

    //load song
    room.song = load_midi("music/song02.mid");
}

//function to load resources from dat file
void load_dat_resources()
{
    dataFile = load_datafile("datos.dat");
    if (!dataFile)
        abort_on_error();

    //gamePalette     = (PALETTE *)dataFile[0].dat;
    set_palette((RGB*)dataFile[dGamePal].dat);
    
    room.image      = (BITMAP *)dataFile[dRoom01].dat;
    room.hsImage    = (BITMAP *)dataFile[dRoom01hs].dat;
    hud.image       = (BITMAP *)dataFile[dHud].dat;
    hud.hsImage     = (BITMAP *)dataFile[dHudhs].dat;
    cursor.image    = (BITMAP *)dataFile[dCursor].dat;
    room.song       = (MIDI *)dataFile[dSong01].dat;
}

//function to initialize cursor
void init_cursor()
{
    strcpy(cursor.objectName,"");
    cursor.action = IR;
    position_mouse(RES_X>>1, RES_Y>>1);
}

//function to draw the pointer cursor
void draw_cursor(BITMAP *buffer)
{
    draw_sprite(buffer, cursor.image, mouse_x - (cursor.image->w>>1), mouse_y - (cursor.image->h>>1));
}

//function to draw debug info
void draw_debug(BITMAP *buffer)
{
    textprintf_ex(buffer, font, 0, 10, makecol(255,255,255), -1, "Mouse x: %i @ Mouse y: %i", mouse_x, mouse_y);
    textprintf_ex(buffer, font, 0, 26, makecol(255,255,255), -1, "Mouse: %i", mouse_b);
}

//function to status bar
void draw_status_bar(BITMAP *buffer)
{
    int hsColor;
    char objectName[OBJECT_NAME_MAX_CHARS];

    //check color of room
    if (mouse_y < STATUS_BAR_Y)
    {
        //obtains the hotspot room color
        hsColor = getpixel(room.hsImage, mouse_x, mouse_y);
        //gets the object name
        get_object(hsColor, objectName);

    }
    //check color of HUD
    else
    {
        //obtains the hotspot HUD color
        hsColor = getpixel(hud.hsImage, mouse_x, mouse_y - HUD_Y);

    }

    textprintf_ex(buffer, font, 0, 18, makecol(255,255,255), -1, "Color: %i", hsColor);
    cursor.action = IR;
    
    //prints status
    textprintf_centre_ex(buffer, font, STATUS_BAR_X, STATUS_BAR_Y, makecol(255,255,255), -1, "%s %s", verbs[cursor.action], objectName);

    //test actions
    if (mouse_b & 1)
    {
        do_object_action(cursor.action, hsColor);
    }
    
}

void abort_on_error()
{
    allegro_exit();
    printf("No se encuentra el archivo");
    exit(-1);
}

END_OF_MAIN()
