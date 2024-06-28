#define DEBUGMODE

#include <stdio.h>
#include <string.h>
#include "allegro.h"
#include "engine.h"
#include "game.h"
//game data resources
#include "data.h"
//includes all rooms
#include "room01.h"
#include "room02.h"

int main()
{
    //initialization
    main_init();
    cursor_init();
    tick_init();

    //play_midi(room[actualRoom].song, -1);

    //main game loop
    while (!key[KEY_ESC])
    {
        //general update
        clear(buffer);
        tick_update();

        //check actual game state
        switch (gameState)
        {
            case TITLE_STATE:
                //placeholder test
                textprintf_centre_ex(buffer, font, SAY_X, SAY_Y, makecol(255,255,255), -1, "ADVENTURE GAME");
                cursor.enabled = true;
                cursor_update();
                cursor_draw();
                if (cursor.click)
                {
                    game_fade_out();
                    game_init();
                    cursor_init();
                    gameState = PLAYING_STATE;
                }
                break;
            case PLAYING_STATE:
                check_room_changed();

                //update
                msg_update();
                room[actualRoom].room_update();
                room_action_update();
                cursor_update();
                //game_update();

                //draw
                room_draw();
                hud_draw();
                status_bar_draw();
                cursor_draw();
                msg_draw();

                break;
        }
        //general draw
        debug_draw();

        //blits to screen
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
        //do pending fade in
        game_do_fade_in();
    }

    //quits the game
    game_exit();
    return EXIT_SUCCESS;
}

//general initialization
void main_init()
{
    //initialize and install modules
    allegro_init();
    if (install_timer() != 0)
        abort_on_error("Error iniciando el modulo timer");
    if (install_mouse() < 0)
        abort_on_error("Error iniciando el mouse");
    if (install_keyboard() != 0)
        abort_on_error("Error iniciando el teclado");
    if (install_sound(0, MIDI_AUTODETECT, 0) != 0)
        abort_on_error("Error iniciando el sonido");

    //set video mode
    set_color_depth(8);
    if (set_gfx_mode(GFX_AUTODETECT, RES_X, RES_Y, 0, 0) != 0)
        abort_on_error("Error seteando modo grafico");

     //screen buffer creation
    buffer = create_bitmap(RES_X, RES_Y);

    //load resources
    load_resources();

    //set game initial state
    gameState = TITLE_STATE;

    //clear flags
    fadein = 0;
}

//timer function callback
void incTick(void)
{
    //increment on 100ms
    tick++;;
}
END_OF_FUNCTION(incTick);

//function to load resources from dat file
void load_resources()
{
    //loads data file
    dataFile = load_datafile("data.dat");
    if (!dataFile)
        abort_on_error("Archivo data.dat invalido o inexistente");

    //sets and get the palette
    set_palette((RGB*)dataFile[dGamePal].dat);
    get_palette(gamePalette);
    
    //loads game resources
    hud.image               = (BITMAP *)dataFile[dHud].dat;
    hud.hsImage             = (BITMAP *)dataFile[dHudhs].dat;
    hud.verbSelImage[GO]    = (BITMAP *)dataFile[dHudGoSel].dat;
    hud.verbSelImage[TAKE]  = (BITMAP *)dataFile[dHudTakeSel].dat;
    hud.verbSelImage[MOVE]  = (BITMAP *)dataFile[dHudMoveSel].dat;
    hud.verbSelImage[LOOK]  = (BITMAP *)dataFile[dHudLookSel].dat;
    hud.verbSelImage[USE]   = (BITMAP *)dataFile[dHudUseSel].dat;
    hud.verbSelImage[GIVE]  = (BITMAP *)dataFile[dHudGiveSel].dat;
    hud.verbSelImage[OPEN]  = (BITMAP *)dataFile[dHudOpenSel].dat;
    hud.verbSelImage[CLOSE] = (BITMAP *)dataFile[dHudCloseSel].dat;
    hud.verbSelImage[TALK]  = (BITMAP *)dataFile[dHudTalkSel].dat;

    cursor.image       = (BITMAP *)dataFile[dCursor].dat;
    //loads room resources
    room[0].image      = (BITMAP *)dataFile[dRoom01].dat;
    room[0].hsImage    = (BITMAP *)dataFile[dRoom01hs].dat;
    room[0].song       = (MIDI *)dataFile[dSong01].dat;
    room[1].image      = (BITMAP *)dataFile[dRoom02].dat;
    room[1].hsImage    = (BITMAP *)dataFile[dRoom02hs].dat;
    room[1].song       = (MIDI *)dataFile[dSong01].dat;

    //assign room function pointers
    room[0].room_get_object = &r01_get_object;
    room[0].room_init = &r01_room_init;
    room[0].room_update = &r01_room_update;
    room[1].room_get_object = &r02_get_object;
    room[1].room_update = &r02_room_update;
    room[1].room_init = &r02_room_init;
}

//function to init game
void game_init()
{
    gameConfig.textSpeed = 10; //8 chars per second? This going to be on config

    //init game vars
    actualRoom = 0;
    lastRoom = -1;     //to force first room_init
    
    roomAction.active = 0;
    roomAction.object = 0;
    roomAction.verb = 0;
    roomAction.step = 0;
    roomAction.lastStep = 0;
    roomAction.stepTime = 0;

    //initialize x and y position of highlight verb images
    hud.posXVerbSelImage[GO]    = VERB_SEL_ROW_1_X;
    hud.posYVerbSelImage[GO]    = VERB_SEL_COL_1_Y;
    hud.posXVerbSelImage[TAKE]  = VERB_SEL_ROW_1_X;
    hud.posYVerbSelImage[TAKE]  = VERB_SEL_COL_2_Y;
    hud.posXVerbSelImage[MOVE]  = VERB_SEL_ROW_1_X;
    hud.posYVerbSelImage[MOVE]  = VERB_SEL_COL_3_Y;
    hud.posXVerbSelImage[LOOK]  = VERB_SEL_ROW_2_X;
    hud.posYVerbSelImage[LOOK]  = VERB_SEL_COL_1_Y;
    hud.posXVerbSelImage[USE]   = VERB_SEL_ROW_2_X;
    hud.posYVerbSelImage[USE]   = VERB_SEL_COL_2_Y;
    hud.posXVerbSelImage[GIVE]  = VERB_SEL_ROW_2_X;
    hud.posYVerbSelImage[GIVE]  = VERB_SEL_COL_3_Y;
    hud.posXVerbSelImage[OPEN]  = VERB_SEL_ROW_3_X;
    hud.posYVerbSelImage[OPEN]  = VERB_SEL_COL_1_Y;
    hud.posXVerbSelImage[CLOSE] = VERB_SEL_ROW_3_X;
    hud.posYVerbSelImage[CLOSE] = VERB_SEL_COL_2_Y;
    hud.posXVerbSelImage[TALK]  = VERB_SEL_ROW_3_X;
    hud.posYVerbSelImage[TALK]  = VERB_SEL_COL_3_Y;
    
    //call init game modules
    msg_init();
}

//function to do pending fade in
void game_do_fade_in()
{
    if (fadein)
    {
        fade_in(gamePalette, FADE_DEFAULT_SPEED);
        fadein = 0;
    }
}

//function to check if actual room as changed
void check_room_changed()
{
    if (actualRoom != lastRoom)
    {
        lastRoom = actualRoom;
        //call new room init
        room[actualRoom].room_init();
    }
}

//function that handles game exit
void game_exit()
{
    //free resources
    unload_datafile(dataFile);
    //quit allegro modules
    allegro_exit();
}

//function to initialize cursor
void cursor_init()
{
    //clear cursor flags
    cursor.enabled = false;
    cursor.click = false;
    cursor.leftClick = false;
    cursor.memClick = false;
    cursor.memLeftClick = false;
    //clear verb flags
    strcpy(cursor.objectName,"");
    cursor.selectedVerb = GO;
    //move cursor to screen center
    position_mouse(RES_X>>1, RES_Y>>1);
}

//funcion to init the debug vars
void debug_init()
{
    debugVars.numVars = 0;
}

//draws the pointer cursor
void cursor_draw()
{
    if (cursor.enabled)
        draw_sprite(buffer, cursor.image, mouse_x - (cursor.image->w>>1), mouse_y - (cursor.image->h>>1));
}

//updates the cursor
void cursor_update()
{
    //handles rigth button click
    cursor.click = false;
    if ((mouse_b & 1) && !cursor.memClick)
    {
        cursor.click = true;
        cursor.memClick = true;
    }
    if (!(mouse_b & 1))
        cursor.memClick = false;

    //handles left button click
    cursor.leftClick = 0;
    if ((mouse_b & 2) && !cursor.memLeftClick)
    {
        cursor.leftClick = true;
        cursor.memLeftClick = true;
    }
    if (!(mouse_b & 2))
        cursor.memLeftClick = false;

    int hsColor;

    //check cursor behaviour
    if (cursor.enabled)
    {
        switch (gameState)
        {
            case PLAYING_STATE:
                //if cursor on room position, check color of room hotspot
                if (mouse_y < STATUS_BAR_Y)
                {
                    //obtains the hotspot room color
                    hsColor = getpixel(room[actualRoom].hsImage, mouse_x, mouse_y);
                    //gets the object name
                    room[actualRoom].room_get_object(hsColor, cursor.objectName);

                    //if cursor click on valid object
                    if (cursor.click && cursor.objectName[0] != '\0')
                    {
                        //if no previous action/object selected
                        if (!roomAction.active)
                        {
                            //saves the room vars to start script sequence
                            roomAction.active = 1;
                            roomAction.object = hsColor;
                            roomAction.verb = cursor.selectedVerb;
                        }
                    }
                }
                //if cursor on HUD position, check color of HUD
                else
                {
                    //obtains the hotspot HUD color
                    hsColor = getpixel(hud.hsImage, mouse_x, mouse_y - HUD_Y);

                    //if mouse click and action is valid
                    if (hsColor > 0 && hsColor <= NUM_VERBS && mouse_b & 1)
                    {
                        cursor.selectedVerb = hsColor - 1;
                    }

                    //if mouse left on hud: default verb
                    if (cursor.leftClick)
                    {
                        cursor.selectedVerb = GO;
                    }
                }
                //debug
                show_debug("Color", hsColor);
                break;
        }
    }
}

//draws debug info
void debug_draw()
{
    //writes all the debug vars
    for (int i = 0; i < debugVars.numVars; i++)
    {
        textprintf_ex(buffer, font, 0, DEBUG_Y + (DEBUG_FONT_HEIGHT*i), makecol(255,255,255), -1, "%s: %i", debugVars.varName[i], debugVars.var[i]);
    }
    //reset debug vars
    debugVars.numVars = 0;
}

//draws the status bar
void status_bar_draw()
{
    textprintf_centre_ex(buffer, font, STATUS_BAR_X, STATUS_BAR_Y, makecol(255,255,255), -1, "%s %s", verbName[cursor.selectedVerb], cursor.objectName);
}

//function to init msg structure
void msg_init()
{
    //clear msg and vars
    strcpy(msg.msg, "");
    msg.msgTime = 0;
    msg.msgFinished = false;
    msg.msgActive = false;
}


//function to update message
void msg_update()
{
    //if msg finished, reset the flags
    if (msg.msgFinished)
    {
        msg.msgActive = false;
        msg.msgFinished = false;
    }

    //if msg active, calculate the relation of string length/characters per second
    //and manage the msg time and finished flag
    if (msg.msgActive)
    {
        //disables cursor
        cursor.enabled = false;
        
        int msgLength = strlen(msg.msg);

        if (msgLength > 0)
        {
            int msgDuration = (msgLength / gameConfig.textSpeed);
            //1 second duration minimum
            if (msgDuration == 0)
                msgDuration = 1;

            //convert to 100ms base
            msgDuration *= 10;

            //show_debug("msgLength", msgLength);
            //show_debug("msgDuration", msgDuration);

            if (msg.msgTime >= msgDuration || cursor.click)
            {
                msg.msgFinished = true;
            }
            else
                msg.msgTime += gameTick > 0;
        }
    }
    else
    {
        //if not active, reset time and clear msg string
        msg.msgTime = 0;
        strcpy(msg.msg,"");
        //enable cursor
        cursor.enabled = true;
    }
}

//funcion to draw message
void msg_draw()
{
    if (!fadein)
        textprintf_centre_ex(buffer, font, SAY_X, SAY_Y, makecol(255,255,255), -1, "%s", msg.msg);
}

//function to abort program with critical error
void abort_on_error(const char *msg)
{
    //exit to return text mode
    //allegro_exit();
    //printf(msg);
    #ifndef DEBUGMODE
    allegro_message(msg);
    #else
    allegro_message(msg);
    allegro_message(allegro_error);
    #endif
    exit(EXIT_FAILURE);
}

//updates the room action structure
void room_action_update()
{
    //if nothing selected
    if (!roomAction.active)
    {
        //reset sequence vars
        roomAction.step = 0;
        roomAction.lastStep = 0;
        roomAction.stepTime = 0;
    }
    else
    {
        //sequence timer
        if (gameTick)
        {
          roomAction.stepTime++;
        }
        //reset step timer on step change
        if (roomAction.step != roomAction.lastStep)
        {
            roomAction.stepTime = 0;
            roomAction.lastStep = roomAction.step;
        }

        if (!roomAction.scriptAssigned)
        {
            default_verb_action(roomAction.verb);
            end_script();
        }
    }
}

//draws the actual room to buffer
void room_draw()
{
    blit(room[actualRoom].image, buffer, 0, 0, 0, 0, room[actualRoom].image->w, room[actualRoom].image->h);
}

//draws the hud to buffer
void hud_draw()
{
    //draws main image
    blit(hud.image, buffer, 0, 0, 0, HUD_Y, hud.image->w, hud.image->h);
    //blits highlight selected verb (using image because haven't smaller font)
    draw_sprite(buffer, hud.verbSelImage[cursor.selectedVerb],hud.posXVerbSelImage[cursor.selectedVerb], HUD_Y + hud.posYVerbSelImage[cursor.selectedVerb]);
}

//function to init the tick timer
void tick_init()
{
    tick = 0;
    LOCK_VARIABLE(tick);
    LOCK_FUNCTION(incTick);
    install_int(incTick, 100);  //100ms
}

//check 1seg tick
void tick_update()
{
    //reset global timer tick
    gameTick = false;

    if (tick) //100ms tick
    {
        //sets global game tick var
        gameTick = true;
        //reset timer interrupt var
        tick = 0;
    }
}

void mytrace(char *s, ...)
{
    TRACE(s);
}

END_OF_MAIN()
