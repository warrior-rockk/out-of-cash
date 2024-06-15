#define DEBUGMODE
#define MAIN_FILE

#include <stdio.h>
#include <string.h>
#include <allegro.h>
#include "game.h"
//include game data
#include "data.h"
//includes all rooms
#include "room01.h"
#include "room02.h"

//room structure
typedef struct tRoom
{
    //room image
    BITMAP  *image;
    //room hotspot image
    BITMAP  *hsImage;
    //room song
    MIDI    *song;
    //function pointer to get object
    void (*room_get_object)(int, char *s);
    //function pointer to do object action
    void (*room_do_object_action)(enum verbs, int);
    //function pointer to update room
    void (*room_update)(void);
} tRoom;

//hud structure
typedef struct tHUD
{
    //HUD image
    BITMAP *image;
    //HUD hotspot image
    BITMAP *hsImage;
} tHUD;

//cursor structure
typedef struct tCursor
{
    //cursor image
    BITMAP *image;
    //name of the pointed object
    char objectName[OBJECT_NAME_MAX_CHARS];
    //selected action/verb
    //int action;
    enum verbs selectedVerb;
} tCursor;

//message structure
//typedef struct tMsg
//{
//    char *msg;
//    int msgId;
//    int tickStamp;
//} tMsg;

//global structures
tRoom room[2];
tHUD hud;
tCursor cursor;
//tMsg msg;
char msg[MAX_SENTENCE_LENGTH];

//global vars
PALETTE gamePalette;
BITMAP *buffer;
DATAFILE *dataFile;
int actualRoom = 0;

//interrupt timer variable
static volatile int tick = 0;
int gameTick = 0;

//function declarations
void abort_on_error();
void load_resources();

void cursor_init();
void tick_init();
void cursor_update();
void room_draw();
void hud_draw();
void status_bar_draw();
void cursor_draw();
void debug_draw();
void msg_update();
void msg_draw();

//timer function callback
void incTick(void)
{
    tick = 1;
}
END_OF_FUNCTION(incTick);

int main()
{
    //initialize and install modules
    allegro_init();
    install_timer();
    install_mouse();
    install_keyboard();
    install_sound(0, MIDI_AUTODETECT, 0);

    //set video mode
    set_color_depth(8);
    set_gfx_mode(GFX_AUTODETECT, 320, 240, 0, 0);

     //screen buffer creation
    buffer = create_bitmap(RES_X, RES_Y);

    //load resources
    load_resources();
    
    //play_midi(room[actualRoom].song, -1);

    cursor_init();
    tick_init();

    //main game loop
    while (!key[KEY_ESC])
    {
        clear(buffer);

        //check 1seg tick
        if (tick == 1)
        {
            //sets global game tick var
            gameTick = 1;
            //reset 1sec interrupt var
            tick = 0;
        }

        //update
        msg_update();
        cursor_update();
        room[actualRoom].room_update();
        //game_update();

        //draw
        room_draw();
        hud_draw();
        status_bar_draw();
        cursor_draw();
        msg_draw();
        debug_draw();

        //blits to screen
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);

        //reset global timer tick
        gameTick = 0;
    }

    //free resources
    destroy_bitmap(room[0].image);
    destroy_bitmap(room[0].hsImage);
    destroy_midi(room[0].song);
    destroy_bitmap(room[1].image);
    destroy_bitmap(room[1].hsImage);
    destroy_midi(room[1].song);
    destroy_bitmap(hud.image);
    destroy_bitmap(cursor.image);

    unload_datafile(dataFile);

    allegro_exit();
    
    return 0;
}
//function to load resources from dat file
void load_resources()
{
    dataFile = load_datafile("data.dat");
    if (!dataFile)
        abort_on_error();

    //gamePalette     = (PALETTE *)dataFile[0].dat;
    set_palette((RGB*)dataFile[dGamePal].dat);
    
    room[0].image      = (BITMAP *)dataFile[dRoom01].dat;
    room[0].hsImage    = (BITMAP *)dataFile[dRoom01hs].dat;
    hud.image          = (BITMAP *)dataFile[dHud].dat;
    hud.hsImage        = (BITMAP *)dataFile[dHudhs].dat;
    cursor.image       = (BITMAP *)dataFile[dCursor].dat;
    room[0].song       = (MIDI *)dataFile[dSong01].dat;
    room[1].image      = (BITMAP *)dataFile[dRoom02].dat;
    room[1].hsImage    = (BITMAP *)dataFile[dRoom02hs].dat;
    room[1].song       = (MIDI *)dataFile[dSong01].dat;

    room[0].room_get_object = &r01_get_object;
    room[0].room_do_object_action = &r01_do_object_action;
    room[0].room_update = &r01_room_update;
    room[1].room_get_object = &r02_get_object;
    room[1].room_do_object_action = &r02_do_object_action;
    room[1].room_update = &r02_room_update;
}

//function to initialize cursor
void cursor_init()
{
    strcpy(cursor.objectName,"");
    //cursor.action = GO;
    cursor.selectedVerb = GO;
    position_mouse(RES_X>>1, RES_Y>>1);
}

//draws the pointer cursor
void cursor_draw()
{
    draw_sprite(buffer, cursor.image, mouse_x - (cursor.image->w>>1), mouse_y - (cursor.image->h>>1));
}

//updates the cursor
void cursor_update()
{
    int hsColor;

    //check color of room hotspot
    if (mouse_y < STATUS_BAR_Y)
    {
        //obtains the hotspot room color
        hsColor = getpixel(room[actualRoom].hsImage, mouse_x, mouse_y);
        //gets the object name
        room[actualRoom].room_get_object(hsColor, cursor.objectName);

        //test room actions
        if (mouse_b & 1)
        {
            room[actualRoom].room_do_object_action(cursor.selectedVerb, hsColor);
        }
    }
    //check color of HUD
    else
    {
        //obtains the hotspot HUD color
        hsColor = getpixel(hud.hsImage, mouse_x, mouse_y - HUD_Y);
        //if action is valid and mouse click
        if (hsColor > 0 && hsColor <= NUM_VERBS && mouse_b & 1)
        {
                cursor.selectedVerb = hsColor - 1;
        }

        //mouse left on hud: default verb
        if (mouse_b & 2)
        {
            cursor.selectedVerb = GO;
        }
    }

    //debug
    textprintf_ex(buffer, font, 0, 18, makecol(255,255,255), -1, "Color: %i", hsColor);

}

//draws debug info
void debug_draw()
{
    textprintf_ex(buffer, font, 0, 10, makecol(255,255,255), -1, "Mouse x: %i @ Mouse y: %i", mouse_x, mouse_y);
    textprintf_ex(buffer, font, 0, 26, makecol(255,255,255), -1, "Mouse: %i", mouse_b);
    textprintf_ex(buffer, font, 0, 34, makecol(255,255,255), -1, "Action: %i", cursor.selectedVerb);
    textprintf_ex(buffer, font, 0, 34+8, makecol(255,255,255), -1, "Tick: %i", tick);
}

//draws the status bar
void status_bar_draw()
{
    textprintf_centre_ex(buffer, font, STATUS_BAR_X, STATUS_BAR_Y, makecol(255,255,255), -1, "%s %s", verbName[cursor.selectedVerb], cursor.objectName);
}

//function to change the actual room
void change_room(int roomNum)
{
    fade_out(10);
    actualRoom = roomNum;
    fade_in(gamePalette, 10);
}

//function to say something
void say(char *message)
{
    strcpy(msg, message);
}

//function to update message
void msg_update()
{
    strcpy(msg,"");
}

//funcion to draw message
void msg_draw()
{
    textprintf_centre_ex(buffer, font, SAY_X, SAY_Y, makecol(255,255,255), -1, "%s", msg);
}

void abort_on_error()
{
    allegro_exit();
    printf("No se encuentra el archivo");
    exit(-1);
}

//draws the actual room to buffer
void room_draw()
{
    blit(room[actualRoom].image, buffer, 0, 0, 0, 0, room[actualRoom].image->w, room[actualRoom].image->h);
}

//draws the hud to buffer
void hud_draw()
{
    blit(hud.image, buffer, 0, 0, 0, HUD_Y, hud.image->w, hud.image->h);
}

//function to init the tick timer
void tick_init()
{
    tick = 0;
    LOCK_VARIABLE(tick);
    LOCK_FUNCTION(incTick);
    install_int(incTick, 1000);
}

void mytrace(char *s, ...)
{
    TRACE(s);
}
END_OF_MAIN()
