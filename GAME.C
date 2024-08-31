//#define DEBUGMODE     //on compiler flags

#include <stdio.h>
#include <string.h>
#include "allegro.h"
#include "engine.h"
#include "game.h"
#include "inventor.h"
#include "player.h"
#include "utils.h"
//game data resources
#include "data.h"
#include "ego.h"
#include "objects.h"
#include "gui.h"
//includes all rooms
#include "room01.h"
#include "room02.h"

int main()
{
    //initialization
    main_init();
    game_init();
    game_fade_out();
    
    //main game loop
    while (!game.exit)
    {
        //stateless update
        main_update();

        //check actual game state
        switch (game.state)
        {
            case TITLE_STATE:
                game_fade_in();
                cursor.enabled = true;

                game_update();
                cursor_update();

                //placeholder test (and game title)
                game_write("ADVENTURE\nGAME", SAY_X, SAY_Y, GAME_TEXT_COLOR);
                cursor_draw();
                
                break;
            case PLAYING_STATE:
                //update calls
                game_update();
                msg_update();
                room[game.actualRoom].room_update();
                inventory_update();
                room_action_update();
                cursor_update();
                player_update();
                
                //draw calls
                room_draw();
                player_draw();
                room_front_draw();
                hud_draw();
                inventory_draw();
                status_bar_draw();
                cursor_draw();
                msg_draw();

                break;
            case PAUSE_STATE:
                //update calls
                game_update();

                //draw calls
                room_draw();
                player_draw();
                room_front_draw();
                game_write("PAUSA", SAY_X, SAY_Y, GAME_TEXT_COLOR);

                break;
            case MENU_STATE:
                //update calls
                game_update();
                gui_update();
                cursor_update();
                
                //draw calls
                room_draw();
                player_draw();
                room_front_draw();
                gui_draw();
                cursor_draw();
                
                break;
            case EXIT_STATE:
                game.exit = true;
        }

        //stateless draw
        main_draw();
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
    game.state = TITLE_STATE;

    //init game tick
    tick_init();
}

//general update
void main_update()
{
    clear(buffer);
    tick_update();

    //debug vars
    show_debug("X",mouse_x);
    show_debug("Y",mouse_y);
    show_debug("step", roomScript.step);
    //show_debug("gotCas",game.flags[GOT_CASSETTE]);
    //show_debug("invObj", cursor.invObject);
}

//general draw
void main_draw()
{
    //debug draw info
    debug_draw();

    //blits to screen
    blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);

    //do pending fade in
    game_do_fade_in();
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
    //loads player data file
    playerDataFile = load_datafile("ego.dat");
    if (!playerDataFile)
        abort_on_error("Archivo ego.dat invalido o inexistente");
    //loads objects data file
    objectsDataFile = load_datafile("objects.dat");
    if (!objectsDataFile)
        abort_on_error("Archivo objects.dat invalido o inexistente");
    //loads inventory data file
    inventoryDataFile = load_datafile("inv.dat");
    if (!inventoryDataFile)
        abort_on_error("Archivo inv.dat invalido o inexistente");
    //loads gui data file
    guiDataFile = load_datafile("gui.dat");
    if (!guiDataFile)
        abort_on_error("Archivo gui.dat invalido o inexistente");
        
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

    gui.image               = (BITMAP *)guiDataFile[dGui_Main].dat;
    //FIX: update datafile with guih.bmp
    gui.hsImageMain         = load_bmp("res/gui/guih.bmp", NULL); //(BITMAP *)guiDataFile[dGui_MainHs].dat;
    gui.hsImage             = gui.hsImageMain;
    //FIX:
    gui.hsImageExit         = load_bmp("res/gui/guiExHs.bmp", NULL); //(BITMAP *)guiDataFile[dGui_MainHs].dat;
    
    cursor.image            = (BITMAP *)dataFile[dCursor].dat;

    //loads room resources
    room[0].image      = (BITMAP *)dataFile[dRoom01].dat;
    room[0].hsImage    = (BITMAP *)dataFile[dRoom01hs].dat;
    room[0].wImage     = (BITMAP *)dataFile[dRoom01w].dat;
    room[0].fImage     = (BITMAP *)dataFile[dRoom01f].dat;
    room[0].song       = (MIDI *)dataFile[dSong01].dat;
    room[1].image      = (BITMAP *)dataFile[dRoom02].dat;
    room[1].hsImage    = (BITMAP *)dataFile[dRoom02hs].dat;
    room[1].song       = (MIDI *)dataFile[dSong01].dat;
    room[1].wImage     = (BITMAP *)dataFile[dRoom02w].dat;
    room[1].fImage     = NULL; //(BITMAP *)dataFile[dRoom01f].dat;

    //room start positions
    room[0].start_pos_x = 170;
    room[0].start_pos_y = 100;
    room[1].start_pos_x = 179;
    room[1].start_pos_y = 117;
    
    //assign room function pointers
    room[0].room_get_hotspot_name = &r01_get_hotspot_name;
    room[0].room_get_default_hotspot_verb = &r01_get_default_hotspot_verb;
    //room[0].room_get_num_objects = &r01_get_num_room_objects;
    room[0].room_num_objects = R01_ROOM_NUM_OBJS;
    room[0].room_get_object_info = &r01_get_object_info;
    room[0].room_init = &r01_room_init;
    room[0].room_update = &r01_room_update;

    room[1].room_get_hotspot_name = &r02_get_hotspot_name;
    room[1].room_get_default_hotspot_verb = &r02_get_default_hotspot_verb;
    //room[1].room_get_num_objects = &r02_get_num_room_objects;
    room[1].room_num_objects = R02_ROOM_NUM_OBJS;
    room[1].room_get_object_info = &r02_get_object_info;
    room[1].room_init = &r02_room_init;
    room[1].room_update = &r02_room_update;

    //test player
    player.image[0]     = (BITMAP *)playerDataFile[dEgo01].dat;
    player.image[1]     = (BITMAP *)playerDataFile[dEgo02].dat;
    player.image[2]     = (BITMAP *)playerDataFile[dEgo03].dat;
    player.image[3]     = (BITMAP *)playerDataFile[dEgo04].dat;
    player.image[4]     = (BITMAP *)playerDataFile[dEgo05].dat;
    player.image[5]     = (BITMAP *)playerDataFile[dEgo06].dat;
    player.image[6]     = (BITMAP *)playerDataFile[dEgo07].dat;
    player.image[7]     = (BITMAP *)playerDataFile[dEgo08].dat;
    player.image[8]     = (BITMAP *)playerDataFile[dEgo09].dat;
    player.image[9]     = (BITMAP *)playerDataFile[dEgo10].dat;
    player.image[10]    = (BITMAP *)playerDataFile[dEgo11].dat;
    player.tempImage    = create_bitmap(player.image[0]->w, player.image[0]->h);
    clear(player.tempImage);

}

//function to init game
void game_init()
{
    gameConfig.textSpeed    = 10; //8 chars per second? This going to be on config
    gameConfig.playerSpeed  = ftofix(0.3);
    
    //init game vars
    game.actualRoom     = 0;
    game.lastRoom       = -1;     //to force first room_init
    game.room_pos_x     = 0;
    game.room_pos_y     = 0;
    for (int i = 0; i < MAX_GAME_FLAGS; i++)
        game.flags[i] = 0;

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
    cursor_init();
    init_room_script();
    msg_init();
    player_init();
    inventory_init();
    gui_init();
}

//game update function
void game_update()
{
    //call to game keys handler
    game_keys_handler();

    //update current game state
    switch (game.state)
    {
        case TITLE_STATE:
            if (gameKeys.exitPressed)
            {
                game.state = EXIT_STATE;
            }
            else if (cursor.click)
            {
                game_fade_out();

                //test game load
                //game_load();

                game_init();
                game.state = PLAYING_STATE;
            }
            break;
        case PLAYING_STATE:
            if (gameKeys.pausePressed)
            {
                game.state = PAUSE_STATE;
            }
            else if (gameKeys.exitPressed)
            {
                game.state = MENU_STATE;
                gui_init();
            }
            else
            {
                //check room transition
                check_room_changed();
            }
            break;
        case PAUSE_STATE:
            if (gameKeys.pausePressed)
            {
                game.state = PLAYING_STATE;
            }
            break;
        case MENU_STATE:
            if (gameKeys.exitPressed)
            {
                game.state = PLAYING_STATE;
            }
            break;

    }

    //force game exit
    #ifdef DEBUGMODE
        if (key[KEY_X] && (key_shifts & KB_CTRL_FLAG))
            game.state = EXIT_STATE;
    #endif
}

//function to handle game keys
void game_keys_handler()
{
    //pause key handler
    gameKeys.pausePressed = false;
    if (key[G_KEY_PAUSE])
    {
        if (!gameKeys.memPause)
        {
            gameKeys.pausePressed = true;
            gameKeys.memPause = true;
        }
    }
    else
    {
        gameKeys.memPause = false;
    }

    //exit key handler
    gameKeys.exitPressed = false;
    if (key[G_KEY_EXIT])
    {
        if (!gameKeys.memExit)
        {
            gameKeys.exitPressed = true;
            gameKeys.memExit = true;
        }
    }
    else
    {
        gameKeys.memExit = false;
    }
}

//function to write text on screen
void game_write(char *text, int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    int posY;
    char s[MAX_SENTENCE_LENGTH];
    char *ch;

    //make a copy of the string for tokenizer
    strcpy(s, text);
    //first token
    ch = strtok(s, "\n");
    //sets the initial Y text position
    posY = y;

    //while ch != NULL (tokens left)
    while (ch)
    {
        //print text with outline
        textprintf_centre_ex(buffer, font, x-1, posY-1, makecol(1,1,1), -1, "%s", ch);
        textprintf_centre_ex(buffer, font, x+1, posY+1, makecol(1,1,1), -1, "%s", ch);
        textprintf_centre_ex(buffer, font, x, posY, makecol(r,g,b), -1, "%s", ch);
        //increment position
        posY += 10;
        //get next token
        ch = strtok(NULL, "-");
    }
}

//function to save game
void game_save()
{
    FILE* saveFile;

    saveFile = fopen("savegame.001", "wb");
    if (saveFile == NULL)
        abort_on_error("No se puede crear el archivo de guardado");
        
    if (!fwrite(&game, sizeof(struct game), 1, saveFile))
        abort_on_error("Error escribiendo el archivo de guardado");

    fclose(saveFile);
}

//function to load game
void game_load()
{
    FILE* loadFile;

    loadFile = fopen("savegame.001", "r");
    if (loadFile == NULL)
        abort_on_error("No se puede abrir el archivo de guardado");

    if (!fread(&game, sizeof(struct game), 1, loadFile))
        abort_on_error("Error leyendo el archivo de guardado");

    fclose(loadFile);
}

//function to do pending fade in
void game_do_fade_in()
{
    if (game.fadeIn)
    {
        fade_in(gamePalette, FADE_DEFAULT_SPEED);
        game.fadeIn     = false;
        game.fadeOut    = false;
    }
}

//function to check if actual room as changed
void check_room_changed()
{
    if (game.actualRoom != game.lastRoom)
    {
        game.lastRoom = game.actualRoom;
        //call new room init
        room[game.actualRoom].room_init();

        //play room song
        //play_midi(room[game.actualRoom].song, -1);

        //set player position on enter room (default or assigned)
        if (game.room_pos_x != 0 && game.room_pos_y != 0)
        {
            player.x = itofix(game.room_pos_x);
            player.y = itofix(game.room_pos_y);
        }
        else
        {
            player.x = itofix(room[game.actualRoom].start_pos_x);
            player.y = itofix(room[game.actualRoom].start_pos_y);
        }
    }
}

//function that handles game exit
void game_exit()
{
    //test save game
    game_save();
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
    cursor.dblClick = false;
    cursor.rightClick = false;
    cursor.memClick = false;
    cursor.memRightClick = false;
    cursor.memDblClick = false;
    cursor.evalueDblClick = false;
    cursor.invObject = 0;
    cursor.dblClickTimer = 0;

    //clear verb flags
    strcpy(cursor.objectName,"");
    strcpy(cursor.invObjName,"");
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

//function that handles rise clicks
void cursor_button_handler()
{
    //handles doble click (fast walk)
    cursor.dblClick = false;
    if (cursor.evalueDblClick)
    {
        if ( (mouse_b & 1) && !cursor.memClick)
        {
            cursor.dblClick = true;
            cursor.memDblClick = true;
        }
        //timeout double click
        if (cursor.dblClickTimer >= DBL_CLICK_MAX_TIME)
        {
            cursor.evalueDblClick = false;
            cursor.dblClickTimer = 0;
        }
        else
            cursor.dblClickTimer += gameTick;
    }

    //handles rigth button click
    cursor.click = false;
    if ((mouse_b & 1) && !cursor.memClick && !cursor.dblClick)
    {
        cursor.click = true;
        cursor.memClick = true;
        //if verb is GO, evaluate doble click for fast walk
        cursor.evalueDblClick = cursor.selectedVerb == GO;
    }
    if (!(mouse_b & 1))
    {
        cursor.memClick = false;
        cursor.memDblClick = false;
    }
    
    //handles left button click
    cursor.rightClick = 0;
    if ((mouse_b & 2) && !cursor.memRightClick)
    {
        cursor.rightClick = true;
        cursor.memRightClick = true;
    }
    if (!(mouse_b & 2))
        cursor.memRightClick = false;
}

//updates function for cursor. Do call for click handler and check cursor actions
void cursor_update()
{
    //call buttons handler
    cursor_button_handler();

    //check cursor behaviour
    uint8_t hsColor;

    if (cursor.enabled)
    {
        switch (game.state)
        {
            case MENU_STATE:
                //obtains the hotspot gui color (coords relative to gui base image)
                hsColor = getpixel(gui.hsImage, mouse_x - gui.x, mouse_y - gui.y);

                //if mouse click and colorCode is valid
                if (cursor.click && hsColor >= GUI_COLOR_OFFSET && hsColor <= (GUI_COLOR_OFFSET + GUI_NUM_OPTIONS))
                {
                    //change gui state
                    gui.state = (hsColor - GUI_COLOR_OFFSET);
                }
                break;
            case PLAYING_STATE:
                //if cursor on room position, check color of room hotspot
                if (mouse_y < STATUS_BAR_Y)
                {
                    //obtains the hotspot room color
                    hsColor = getpixel(room[game.actualRoom].hsImage, mouse_x, mouse_y);
                    //gets the object name
                    room[game.actualRoom].room_get_hotspot_name(hsColor, cursor.objectName);

                    //check right click action on room (evaluated before the left click)
                    if (cursor.rightClick)
                    {
                        //if valid object, get default object verb
                        if (cursor.objectName[0] != '\0')
                            cursor.selectedVerb = room[game.actualRoom].room_get_default_hotspot_verb(hsColor);
                        else
                            //otherwise, select go verb
                            cursor.selectedVerb = GO;
                    }

                    //if cursor click on valid object or double click with GO verb or rightClick (default verb assigned)
                    if ((cursor.click || cursor.dblClick || cursor.rightClick) && (cursor.objectName[0] != '\0' || cursor.selectedVerb == GO))
                    {
                        //if no previous action/object selected
                        if (!roomScript.active)
                        {
                            //saves the room vars to start script sequence
                            roomScript.active = true;
                            roomScript.invScript = false;
                            roomScript.object = hsColor;
                            roomScript.verb = cursor.selectedVerb;
                            roomScript.invObject = cursor.invObject;
                            roomScript.hsX = mouse_x;
                            roomScript.hsY = mouse_y;

                            //change player look dir
                            if (roomScript.hsX < fixtoi(player.x))
                                change_player_dir(DIR_LEFT);
                            else
                                change_player_dir(DIR_RIGHT);
                        }
                    }
                }
                //if cursor on HUD position, check color of HUD
                else
                {
                    //obtains the hotspot HUD color
                    hsColor = getpixel(hud.hsImage, mouse_x, mouse_y - HUD_Y);

                    //check mouse hud region
                    if (mouse_x < HUD_SCROLL_X)
                    {
                        //BUTTONS VERBS REGION
                        
                        //if mouse click and action is valid
                        if (cursor.click && hsColor > 0 && hsColor <= NUM_VERBS)
                        {
                            cursor.selectedVerb = hsColor - 1;
                        }

                        //if mouse left on hud: default verb
                        if (cursor.rightClick)
                        {
                            cursor.selectedVerb = GO;
                        }
                    }
                    else if (mouse_x < HUD_INVENTORY_X)
                    {
                        //SCROLL INVENTORY BUTTONS REGION

                        if (cursor.click)
                        {
                            //scroll down inventory page
                            if (hsColor == INV_SCROLL_DOWN_CODE && inventory.page < ((inventory.numObjects - 1) / INV_OBJECTS_PER_ROW) && inventory.page < MAX_INV_PAGE)
                            {
                                inventory.page++;
                                inventory.refresh = true;
                                //set flag for highlight button
                                hud.selDownButton = true;
                            }
                            //scroll up inventory page
                            if (hsColor == INV_SCROLL_UP_CODE && inventory.page > 0)
                            {
                                inventory.page--;
                                inventory.refresh = true;
                                //set flag for highlight button
                                hud.selUpButton = true;
                            }
                        }
                        
                        if (cursor.rightClick)
                        {
                            //go to last inventory page
                            if (hsColor == INV_SCROLL_DOWN_CODE)
                            {
                                inventory.page = inventory.numObjects <= INV_OBJECTS_PER_PAGE ? 0 : ((inventory.numObjects - 1) / INV_OBJECTS_PER_ROW) - 1;
                                inventory.refresh = true;
                                //set flag for highlight button
                                hud.selDownButton = true;
                            }
                            //go to first inventory page
                            if (hsColor == INV_SCROLL_UP_CODE)
                            {
                                inventory.page = 0;
                                inventory.refresh = true;
                                //set flag for highlight button
                                hud.selUpButton = true;
                            }
                        }
                    }
                    else
                    {
                        //INVENTORY BUTTONS REGION

                        //gets the object name
                        if (get_inv_obj_id(get_inv_obj_position(hsColor) - 1) == cursor.invObject && cursor.selectedVerb == USE_WITH)
                            //don't allow use object on same object
                            strcpy(cursor.objectName, "");
                        else
                            get_inv_obj_name(get_inv_obj_position(hsColor), cursor.objectName);
                            
                        //if cursor click on valid inv object or rightClick (default verb assigned) and selected ver isn't GO
                        if ((cursor.click || cursor.rightClick) && cursor.objectName[0] != '\0' && cursor.selectedVerb != GO)
                        {
                            //check if click USE verb on inventory object
                            if (cursor.selectedVerb == USE)
                            {
                                //sets USE_WITH verb
                                cursor.selectedVerb = USE_WITH;
                                //sets inventory object name verb
                                strcpy(cursor.invObjName, cursor.objectName);
                                //sets inventory id
                                cursor.invObject = get_inv_obj_id(get_inv_obj_position(hsColor) - 1);
                            }
                            else
                            {
                                //if no previous action/object selected
                                if (!roomScript.active)
                                {
                                    //saves the room vars to start script sequence
                                    roomScript.active = true;
                                    roomScript.invScript = true;
                                    roomScript.object = get_inv_obj_id(get_inv_obj_position(hsColor) - 1);
                                    roomScript.verb = cursor.selectedVerb;
                                    roomScript.hsX = mouse_x;
                                    roomScript.hsY = mouse_y;
                                }
                            }
                        }
                    }
                }
                break;
        }
        //debug
        show_debug("Color", hsColor);
    }
}

//draws debug info
void debug_draw()
{
    #ifdef DEBUGMODE
        //writes all the debug vars
        for (int i = 0; i < debugVars.numVars; i++)
        {
            textprintf_ex(buffer, font, 0, DEBUG_Y + (DEBUG_FONT_HEIGHT*i), makecol(255,255,255), -1, "%s: %i", debugVars.varName[i], debugVars.var[i]);
        }
    #endif //DEBUGMODE

    //reset debug vars
    debugVars.numVars = 0;
}

//draws the status bar
void status_bar_draw()
{
    //check if the verb is USE_WITH to print object inventory or not
    if (cursor.selectedVerb != USE_WITH)
        textprintf_centre_ex(buffer, font, STATUS_BAR_X, STATUS_BAR_Y, makecol(255,255,255), -1, "%s %s", verbName[cursor.selectedVerb], cursor.objectName);
    else
        textprintf_centre_ex(buffer, font, STATUS_BAR_X, STATUS_BAR_Y, makecol(255,255,255), -1, "%s %s con %s", verbName[cursor.selectedVerb], cursor.invObjName, cursor.objectName);
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
        player.state = player_st_idle;
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

            //set talking flag
            player.state = player_st_talking;
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
    //don't draw the text if fade in on progress
    if (!game.fadeIn)
    {
        int msgX;
        int msgY;
        
        //get msg length in pixels
        int msgWidth = get_msg_length(msg.msg); //text_length(font, msg.msg);

        //check msg X limits for avoid text outscreen
        if (fixtoi(player.x) < (msgWidth>>1))
            msgX = (msgWidth>>1);
        else if (fixtoi(player.x) > (RES_X - (msgWidth>>1)))
            msgX = RES_X - (msgWidth>>1);
        else
            msgX = fixtoi(player.x);

        //get msg Y
        msgY = fixtoi(player.y) - fixtoi((fixmul((itofix(player.image[player.animation.frame]->h>>1)), player.scale))) - TEXT_ACTOR_MARGIN;
        
        //call to write text
        game_write(msg.msg, msgX, msgY, PLAYER_TEXT_COLOR);
    }
}

//function to get msg length (in pixels). On multiline, returns the lenght of first line
int get_msg_length(char *text)
{
    char s[MAX_SENTENCE_LENGTH];
    char *ch;

    //make a copy of the string for tokenizer
    strcpy(s, text);

    //first token
    ch = strtok(s, "\n");

    if (ch)
        return text_length(font, ch);
    else
        return 0;
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
    if (!roomScript.active)
    {
        //reset sequence vars
        roomScript.step = 0;
        roomScript.lastStep = 0;
        roomScript.stepTime = 0;
    }
    else
    {
        //sequence timer
        if (gameTick)
        {
          roomScript.stepTime++;
        }
        //reset step timer on step change
        if (roomScript.step != roomScript.lastStep)
        {
            roomScript.stepTime = 0;
            roomScript.lastStep = roomScript.step;
        }

        if (!roomScript.scriptAssigned)
        {
            default_verb_action(roomScript.verb);
            end_script();
        }
    }
}

//draws the actual room to buffer
void room_draw()
{
    //draw room image
    blit(room[game.actualRoom].image, buffer, 0, 0, 0, 0, room[game.actualRoom].image->w, room[game.actualRoom].image->h);
    
    //draw room objects
    tObject *obj;
    BITMAP *objImage;
    for (int i = 0; i < room[game.actualRoom].room_num_objects; i++)
    {
        //get pointer to object structure
        obj = room[game.actualRoom].room_get_object_info(i);
        //check null pointer
        if (obj == NULL)
            abort_on_error("Error accediendo a indice de objecto no existente");
        //check object active
        else if (obj->active)
        {
            //get pointer to bitmap object
            objImage = (BITMAP *)objectsDataFile[obj->objId].dat;
            //draw the object
            draw_sprite(buffer, objImage, obj->x-(objImage->w>>1), obj->y - (objImage->h>>1));
        }
    }
}

//draws the actual room front layer to buffer
void room_front_draw()
{
    if (room[game.actualRoom].fImage != NULL)
        masked_blit(room[game.actualRoom].fImage, buffer, 0, 0, 0, 0, room[game.actualRoom].fImage->w, room[game.actualRoom].fImage->h);
}

//draws the hud to buffer
void hud_draw()
{
    //draws main image
    blit(hud.image, buffer, 0, 0, 0, HUD_Y, hud.image->w, hud.image->h);

    //blits highlight selected verb (using image because haven't smaller font)
    if (cursor.selectedVerb == USE_WITH)
        //USE_WITH verb uses same USE highlight image
        draw_sprite(buffer, hud.verbSelImage[USE],hud.posXVerbSelImage[USE], HUD_Y + hud.posYVerbSelImage[USE]);
    else
        draw_sprite(buffer, hud.verbSelImage[cursor.selectedVerb],hud.posXVerbSelImage[cursor.selectedVerb], HUD_Y + hud.posYVerbSelImage[cursor.selectedVerb]);

    //blits selected scroll inventory button
    if (hud.selUpButton)
        draw_sprite(buffer, (BITMAP *)dataFile[dHudUpSel].dat, SEL_UP_DOWN_X, SEL_UP_Y + HUD_Y);
    if (hud.selDownButton)
        draw_sprite(buffer, (BITMAP *)dataFile[dHudDownSel].dat, SEL_UP_DOWN_X, SEL_DOWN_Y + HUD_Y);

    //reset scroll flags on mouse release
    if (!mouse_b & 1)
    {
        hud.selUpButton = false;
        hud.selDownButton = false;
    }
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

//function to init the gui
void gui_init()
{
    //set gui position (center of screen)
    gui.x = (RES_X>>1) - (gui.image->w>>1);
    gui.y = (RES_Y>>1) - (gui.image->h>>1);
    //gui state
    gui.state = GUI_MAIN_STATE;
}

//function to update the gui
void gui_update()
{
    //compose gui hotspot image
    draw_sprite(gui.hsImage, gui.hsImageMain, 0, 0);
    
    switch (gui.state)
    {
        case GUI_EXIT_STATE:
            //draw hotspot state zone
            draw_sprite(gui.hsImage, gui.hsImageExit , GUI_CONTENT_X, GUI_CONTENT_Y);
            break;
        case GUI_EXIT_TITLE_STATE:
            game.state = TITLE_STATE;
            game_fade_out();
            break;
        case GUI_EXIT_DOS_STATE:
            game.state = EXIT_STATE;
            game_fade_out();
            break;
    }
}

//function to draw the gui
void gui_draw()
{
    //draw base gui on center of screen
    draw_sprite(buffer, gui.image, gui.x, gui.y);

    switch (gui.state)
    {
        case GUI_LOAD_STATE:
            //draw gui contents
            //draw_sprite(buffer, (BITMAP *)guiDataFile[dGui_Options].dat, gui.x + GUI_CONTENT_X, gui.y + GUI_CONTENT_Y);
            //draw button highlighted
            draw_sprite(buffer, (BITMAP *)guiDataFile[dGui_LoadSel].dat, gui.x + GUI_BUTTONS_X, gui.y + GUI_BUTTONS_Y + (GUI_BUTTONS_SPACING * gui.state));
            break;
        case GUI_SAVE_STATE:
            //draw gui contents
            //draw_sprite(buffer, (BITMAP *)guiDataFile[dGui_Options].dat, gui.x + GUI_CONTENT_X, gui.y + GUI_CONTENT_Y);
            //draw button highlighted
            draw_sprite(buffer, (BITMAP *)guiDataFile[dGui_SaveSel].dat, gui.x + GUI_BUTTONS_X, gui.y + GUI_BUTTONS_Y + (GUI_BUTTONS_SPACING * gui.state));
            break;
        case GUI_OPTIONS_STATE:
            //draw gui contents
            draw_sprite(buffer, (BITMAP *)guiDataFile[dGui_Options].dat, gui.x + GUI_CONTENT_X, gui.y + GUI_CONTENT_Y);
            //draw button highlighted
            draw_sprite(buffer, (BITMAP *)guiDataFile[dGui_OptionsSel].dat, gui.x + GUI_BUTTONS_X, gui.y + GUI_BUTTONS_Y + (GUI_BUTTONS_SPACING * gui.state));
            break;
        case GUI_ABOUT_STATE:
            //draw gui contents
            //draw_sprite(buffer, (BITMAP *)guiDataFile[dGui_Options].dat, gui.x + GUI_CONTENT_X, gui.y + GUI_CONTENT_Y);
            //draw button highlighted
            draw_sprite(buffer, (BITMAP *)guiDataFile[dGui_AboutSel].dat, gui.x + GUI_BUTTONS_X, gui.y + GUI_BUTTONS_Y + (GUI_BUTTONS_SPACING * gui.state));
            break;
        case GUI_EXIT_STATE:
            //draw gui contents
            draw_sprite(buffer, (BITMAP *)guiDataFile[dGui_Exit].dat, gui.x + GUI_CONTENT_X, gui.y + GUI_CONTENT_Y);
            //draw button highlighted
            draw_sprite(buffer, (BITMAP *)guiDataFile[dGui_ExitSel].dat, gui.x + GUI_BUTTONS_X, gui.y + GUI_BUTTONS_Y + (GUI_BUTTONS_SPACING * gui.state));
            break;
        case GUI_EXIT_TITLE_STATE:
            //draw gui contents
            draw_sprite(buffer, (BITMAP *)guiDataFile[dGui_Exit].dat, gui.x + GUI_CONTENT_X, gui.y + GUI_CONTENT_Y);
            //draw button highlighted
            draw_sprite(buffer, (BITMAP *)guiDataFile[dGui_ExitTitleSel].dat, gui.x + GUI_BUTTONS_EXIT, gui.y + GUI_BUTTON_EXIT_TITLE_Y);
            break;
        case GUI_EXIT_DOS_STATE:
            //draw gui contents
            draw_sprite(buffer, (BITMAP *)guiDataFile[dGui_Exit].dat, gui.x + GUI_CONTENT_X, gui.y + GUI_CONTENT_Y);
            //draw button highlighted
            draw_sprite(buffer, (BITMAP *)guiDataFile[dGui_ExitDosSel].dat, gui.x + GUI_BUTTONS_EXIT, gui.y + GUI_BUTTON_EXIT_DOS_Y);
            break;
    }
}

END_OF_MAIN()
