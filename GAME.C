//#define DEBUGMODE     //on compiler flags

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "allegro.h"
#include "engine.h"
#include "game.h"
#include "rooms.h"
#include "inventor.h"
#include "player.h"
#include "utils.h"
//game data resources
#include "GDATA.H"
#include "IDATA.H"
#include "SDATA.H"

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
                game_write("ADVENTURE\nGAME", SAY_X, SAY_Y, makecol(GAME_TEXT_COLOR));
                cursor_draw();
                
                break;
            case PLAYING_STATE:
                 //update calls
                game_update();
                msg_update();
                roomData[game.actualRoom].room_update();
                inventory_update();
                room_action_update();
                cursor_update();
                player_update();
                
                //draw calls
                room_draw();
                player_draw();
                room_front_layer_draw();
                hud_draw();
                inventory_draw();
                status_bar_draw();
                cursor_draw();
                msg_draw();

                break;
            case DIALOG_STATE:
                //update calls
                game_update();
                msg_update();
                roomData[game.actualRoom].room_update();
                //inventory_update();
                room_action_update();
                cursor_update();
                player_update();
                
                //draw calls
                room_draw();
                player_draw();
                room_front_layer_draw();
                //hud_draw();
                //inventory_draw();
                //status_bar_draw();
                dialog_draw();
                cursor_draw();
                msg_draw();
                
                break;
            case PAUSE_STATE:
                //update calls
                game_update();

                //draw calls
                room_draw();
                player_draw();
                room_front_layer_draw();
                game_write("PAUSA", SAY_X, SAY_Y, makecol(GAME_TEXT_COLOR));

                break;
            case MENU_STATE:
                //update calls
                game_update();
                gui_update();
                cursor_update();
                
                //draw calls
                room_draw();
                player_draw();
                room_front_layer_draw();
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
    //set unicode format
    set_uformat(U_ASCII);
    
    //initialize and install modules
    allegro_init();
    if (install_timer() != 0)
        abort_on_error("Error iniciando el modulo timer");
    if (install_mouse() < 0)
        abort_on_error("Error iniciando el mouse");
    if (install_keyboard() != 0)
        abort_on_error("Error iniciando el teclado");
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0) != 0)
        abort_on_error("Error iniciando el sonido");

    //set video mode
    set_color_depth(8);
    if (set_gfx_mode(GFX_AUTODETECT, RES_X, RES_Y, 0, 0) != 0)
        abort_on_error("Error seteando modo grafico");

     //screen buffer creation
    buffer = create_bitmap(RES_X, RES_Y);

    //load game resources
    game_load_resources();

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

//function to load game resources
void game_load_resources()
{
    //loads game main data file
    gameDataFile = load_datafile("GDATA.DAT");
    if (!gameDataFile)
        abort_on_error("Archivo GDATA.DAT invalido o inexistente");

    //loads player data file
    playerDataFile = load_datafile("PDATA.DAT");
    if (!playerDataFile)
        abort_on_error("Archivo PDATA.DAT invalido o inexistente");

    //loads inventory data file
    inventoryDataFile = load_datafile("IDATA.DAT");
    if (!inventoryDataFile)
        abort_on_error("Archivo IDATA.DAT invalido o inexistente");
        
    //creates music dat file index to load individual music objects
    actualRoom.musicDataFileIndex = create_datafile_index("MDATA.DAT");
    if (!actualRoom.musicDataFileIndex)
        abort_on_error("Archivo MDATA.DAT invalido o inexistente");

    //loads sound fata file
    soundDataFile = load_datafile("SDATA.DAT");
    if (!soundDataFile)
        abort_on_error("Archivo SDATA.DAT invalido o inexistente");
        
    //sets and get the game palette
    set_palette((RGB*)gameDataFile[gd_gamePal].dat);
    get_palette(gamePalette);
}

//function to init game
void game_init()
{
    //default game config (each savegame file stores custom config
    gameConfig.textSpeed    = 10;   //chars per second
    gameConfig.playerSpeed  = 30;
    gameConfig.musicVolume  = 0; //200
    gameConfig.soundVolume  = 200;

    //sets audio config
    set_volume(gameConfig.soundVolume, gameConfig.musicVolume);
    
    //init game vars
    game.actualRoom     = -1;    //to force first room_init
    game.nextRoom       = 0;
    //game.roomLoaded     = false;
    game.room_pos_x     = 0;
    game.room_pos_y     = 0;
    //clear game flags
    for (int i = 0; i < MAX_GAME_FLAGS; i++)
        game.flags[i] = 0;

    //init room music
    actualRoom.musicId  = -1;
    
    //call init game modules
    cursor_init();
    init_room_script();
    msg_init();
    player_init();
    inventory_init();
    gui_init();
    hud_init();
    dialog_init();
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
            if (gameKeys[G_KEY_PAUSE].pressed)
            {
                game.state = EXIT_STATE;
            }
            else if (cursor.click)
            {
                game_fade_out();
                game_init();
                game.state = PLAYING_STATE;
            }
            break;
        case PLAYING_STATE:
            if (gameKeys[G_KEY_PAUSE].pressed)
            {
                game.state = PAUSE_STATE;
                midi_pause();
            }
            else if (gameKeys[G_KEY_EXIT].pressed)
            {
                game.state = MENU_STATE;
                //midi_pause();
            }
            else
            {
                check_room_changed();
            }
            break;
        case PAUSE_STATE:
            if (gameKeys[G_KEY_PAUSE].pressed)
            {
                game.state = PLAYING_STATE;
                midi_resume();
            }
            break;
        case MENU_STATE:
            if (gameKeys[G_KEY_EXIT].pressed)
            {
                game.state = PLAYING_STATE;
                //midi_resume();
            }
            break;

    }

    #ifdef DEBUGMODE
        //force game exit
        if (key[KEY_X] && (key_shifts & KB_CTRL_FLAG))
            game.state = EXIT_STATE;

        //toogle show room walk image
        if (gameKeys[G_KEY_W].pressed && game.state == PLAYING_STATE)
            debug.showWalkImage = !debug.showWalkImage;
            
        //toogle show room hotspot image
        if (gameKeys[G_KEY_H].pressed && game.state == PLAYING_STATE)
            debug.showHotspotImage = !debug.showHotspotImage;

        //toogle cursor room objects
        if (gameKeys[G_KEY_O].pressed && game.state == PLAYING_STATE)
        {
            if (!debug.cursorRoomObjects)
            {
                debug.cursorRoomObjects = true;
                debug.numCursorRoomObject = 0;
            }
            else
                debug.cursorRoomObjects = false;
        }

        //cycle up cursor room objects
        if (gameKeys[G_KEY_PLUS].pressed && game.state == PLAYING_STATE)
        {
            if (debug.cursorRoomObjects && debug.numCursorRoomObject < roomData[game.actualRoom].room_num_objects)
                debug.numCursorRoomObject++;
        }

        //cycle down cursor room objects
        if (gameKeys[G_KEY_MINUS].pressed && game.state == PLAYING_STATE)
        {
            if (debug.cursorRoomObjects && debug.numCursorRoomObject > 0)
                debug.numCursorRoomObject--;
        }

    #endif
}

//function to handle game keys
void game_keys_handler()
{
    for (int i = 0; i < GAME_KEYS_NUM; i++)
    {
        gameKeys[i].pressed = false;
        if (key[gameKeys[i].keyId])
        {
            if (!gameKeys[i].memPressed)
            {
                gameKeys[i].pressed = true;
                gameKeys[i].memPressed = true;
            }
        }
        else
        {
            gameKeys[i].memPressed = false;
        }
    }
}

//function to write text on screen
void game_write(char *text, int x, int y, uint8_t color)
{
    int posY;
    char s[MAX_MSG_LENGTH];
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
        textprintf_centre_ex(buffer, font, x, posY, color, -1, "%s", ch);
        //increment position
        posY += 10;
        //get next token
        ch = strtok(NULL, "-");
    }
}

//function to check if savegame file slot exists and copies the saved data file
bool game_save_exists(uint8_t slot, char *s)
{
    FILE* saveFile;
    struct savegame savegame;
    char filename[13];

    //compose filenae
    sprintf(filename, "savegame.00%i", (slot + 1));
    //open/create the savegame file
    saveFile = fopen(filename, "r");
    if (!saveFile)
    {
        #ifdef DEBUGMODE
            strcpy(s, "\0");
        #else
            strcpy(s, "\0");
        #endif
        return false;
    }
    else
    {
        //rewind the file
        fseek(saveFile, 0, SEEK_SET);

        //read contents of savegame file
        if (!fread(&savegame, sizeof(struct savegame), 1, saveFile))
        {
            //closes file
            fclose(saveFile);
            #ifdef DEBUGMODE
                strcpy(s, "no read");
            #else
                strcpy(s, "\0");
            #endif
            return false;
        }
        
        //check version
        if (savegame.version != SAVEGAME_FILE_VERSION)
        {
            //closes file
            fclose(saveFile);
            #ifdef DEBUGMODE
                strcpy(s, "error version");
            #else
                strcpy(s, "\0");
            #endif
            return false;
        }
        
        //copies saved data of the file
        strcpy(s, savegame.saveDate);
        fclose(saveFile);
        return true;
    }
}

//function to save game
void game_save(uint8_t slot)
{
    FILE* saveFile;
    struct savegame savegame;
    char filename[13];

    //compose filenae
    sprintf(filename, "savegame.00%i", (slot + 1));
    //open/create the savegame file
    saveFile = fopen(filename, "wb");
    if (!saveFile)
    {
        char txtError[100];
        strcpy(txtError, strerror(errno));
        abort_on_error(txtError);
        //abort_on_error("No se puede crear el archivo de guardado");
    }
    
    //sets the contents of savegame file
    savegame.version        = SAVEGAME_FILE_VERSION;
    get_actual_date(savegame.saveDate);
    savegame.gameConfigData = gameConfig;
    game.roomMusicPos       = midi_pos;
    savegame.gameData       = game;
    savegame.invData        = inventory;
    savegame.cursorData     = cursor;
    savegame.roomScriptData = roomScript;
    savegame.msgData        = msg;
    savegame.playerData     = player;

    //write the savegame file
    if (!fwrite(&savegame, sizeof(struct savegame), 1, saveFile))
        abort_on_error("Error escribiendo el archivo de guardado");
    
    //close and clear savegame
    fclose(saveFile);
}

//function to load game
void game_load(uint8_t slot)
{
    FILE* loadFile;
    struct savegame savegame;
    char filename[13];

    //compose filenae
    sprintf(filename, "savegame.00%i", slot + 1);
    //open savegame file
    loadFile = fopen(filename, "r");
    if (!loadFile)
    {
        char txtError[100];
        strcpy(txtError, strerror(errno));
        abort_on_error(txtError);
        //abort_on_error("No se puede abrir el archivo de guardado");
    }

    //rewind the file
    fseek(loadFile, 0, SEEK_SET);
        
    //read contents of savegame file
    if (!fread(&savegame, sizeof(struct savegame), 1, loadFile))
        abort_on_error("Error leyendo el archivo de guardado");

    //check version
    if (savegame.version != SAVEGAME_FILE_VERSION)
        abort_on_error("Version de archivo de guardado incompatible");

    //writes savegame data to game
    gameConfig  = savegame.gameConfigData;
    game        = savegame.gameData;
    inventory   = savegame.invData;
    cursor      = savegame.cursorData;
    roomScript  = savegame.roomScriptData;
    msg         = savegame.msgData;
    player      = savegame.playerData;

    //sets audio config
    set_volume(gameConfig.soundVolume, gameConfig.musicVolume);
    //loads saved room resources
    room_load(game.actualRoom);
    //seeks room music to saved position
    midi_seek(game.roomMusicPos);
    //forces refresh room_init
    roomData[game.actualRoom].room_init();
    //forces refresh inventory
    inventory.refresh = true;
    
    //close savegame file
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
    if (game.actualRoom != game.nextRoom)
    {
        //fade room transition if actual or new room has fadeRoom property
        if (roomData[game.actualRoom].fadeRoom || roomData[game.nextRoom].fadeRoom)
            game_fade_out(FADE_DEFAULT_SPEED);
        else
            game_fade_out(FADE_FAST_SPEED);

        TRACE("Change from room %i to room %i\n", game.actualRoom, game.nextRoom);
        game.actualRoom = game.nextRoom;

        //load room resources
        room_load(game.actualRoom);

        //call new room init
        roomData[game.actualRoom].room_init();

        //set player position on enter room (default or assigned)
        if (game.room_pos_x != 0 && game.room_pos_y != 0)
        {
            player.x = itofix(game.room_pos_x);
            player.y = itofix(game.room_pos_y);
        }
        else
        {
            player.x = itofix(roomData[game.actualRoom].start_pos_x);
            player.y = itofix(roomData[game.actualRoom].start_pos_y);
        }

        //reset game room position
        game.room_pos_x = 0;
        game.room_pos_y = 0;
    }
}

//function that handles game exit
void game_exit()
{
    //free resources
    unload_datafile(gameDataFile);
    unload_datafile(playerDataFile);
    unload_datafile(inventoryDataFile);

    //quit allegro modules
    allegro_exit();
}

//function to initialize cursor
void cursor_init()
{
    //set cursor image
    cursorImage = (BITMAP *)gameDataFile[gd_cursor].dat;
    
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
    #ifdef DEBUGMODE
    debug.numVars = 0;
    debug.showWalkImage = false;
    #endif
}

//draws the pointer cursor
void cursor_draw()
{
    if (cursor.enabled)
        draw_sprite(buffer, cursorImage, mouse_x - (cursorImage->w>>1), mouse_y - (cursorImage->h>>1));

    #ifdef DEBUGMODE
    if (debug.cursorRoomObjects)
    {
        tObject *obj;
        BITMAP *objImage;

        //get pointer to object structure
        obj = roomData[game.actualRoom].room_get_object_info(debug.numCursorRoomObject);
        //check null pointer
        if (obj != NULL)
        {
            //get pointer to bitmap object
            objImage = (BITMAP *)actualRoom.dataFile[obj->objId].dat;
            //draw the object as cursor
            draw_sprite(buffer, objImage, mouse_x - (objImage->w>>1), mouse_y - (objImage->h>>1));
        }
        else
            debug.numCursorRoomObject = 0;
    }
    #endif
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

    //handles left button click
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
    
    //handles right button click
    cursor.rightClick = 0;
    if ((mouse_b & 2) && !cursor.memRightClick)
    {
        cursor.rightClick = true;
        cursor.memRightClick = true;
    }
    if (!(mouse_b & 2))
        cursor.memRightClick = false;

    //handles cursor clicking
    cursor.clicking         = mouse_b & 1;
    cursor.rightClicking    = mouse_b & 2;
}

//updates function for cursor. Do call for click handler and check cursor actions
void cursor_update()
{
    //call buttons handler
    cursor_button_handler();

    //check cursor behaviour
    if (cursor.enabled)
    {
        switch (game.state)
        {
            case PLAYING_STATE:
                //if cursor on room position
                if (mouse_y < STATUS_BAR_Y)
                {
                    cursor_action_room();
                }
                //if cursor on HUD position, check color of HUD
                else
                {
                    cursor_action_HUD();
                }
                break;
            case MENU_STATE:
                cursor_action_menu();

                break;
            case DIALOG_STATE:
                cursor_action_dialog();

                break;
        }
    }
}

//function that handles action of cursor on HUD
void cursor_action_HUD()
{
    //obtains the hotspot HUD color
    uint8_t hsColor = getpixel(hud.hsImage, mouse_x, mouse_y - HUD_Y);

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
                    roomScript.type = INVENTORY_SCRIPT_TYPE;
                    roomScript.object = get_inv_obj_id(get_inv_obj_position(hsColor) - 1);
                    roomScript.verb = cursor.selectedVerb;
                    roomScript.hsX = mouse_x;
                    roomScript.hsY = mouse_y;
                }
            }
        }
    }

    //debug
    show_debug("Color hud", hsColor);
}

//function that handles action of cursor on menu
void cursor_action_menu()
{
    //dummy variable for char pointer used on save_game_exists
    char dummy[SAVEGAME_DATE_CHARS];

    //obtains the hotspot gui color (coords relative to gui base image)
    uint8_t hsColor = getpixel(gui.hsImage, mouse_x - gui.x, mouse_y - gui.y);

    //obtain normalized x value from sliders
    fixed norm_value = norm_x((mouse_x - gui.x), GUI_SLIDER_MIN_X, GUI_SLIDER_MAX_X);

    //reset gui slot selection
    gui.slotSel = 0;
    
    //check hotspot color
    switch (hsColor)
    {
        case GUI_SLIDER_1_COLOR:
            if (cursor.clicking)
                gameConfig.textSpeed = scale_x(norm_value, CONFIG_TEXT_SPEED_MIN, CONFIG_TEXT_SPEED_MAX);
            break;
        case GUI_SLIDER_2_COLOR:
            if (cursor.clicking)
                gameConfig.playerSpeed = scale_x(norm_value, CONFIG_PLY_SPEED_MIN, CONFIG_PLY_SPEED_MAX);
            break;
        case GUI_SLIDER_3_COLOR:
            if (cursor.clicking)
            {
                gameConfig.musicVolume = scale_x(norm_value, 0, 255);
                set_volume(gameConfig.soundVolume, gameConfig.musicVolume);
            }
            break;
        case GUI_SLIDER_4_COLOR:
            if (cursor.clicking)
            {
                gameConfig.soundVolume = scale_x(norm_value, 0, 255);
                set_volume(gameConfig.soundVolume, gameConfig.musicVolume);
            }
            //feedback random global sound
            if (cursor.click)
                play_sound_rnd(rand() % sd_COUNT);
            break;    
        case GUI_LOAD_SLOT_1_COLOR ... GUI_LOAD_SLOT_5_COLOR:
            //get slot selected
            gui.slotSel = (hsColor - GUI_LOAD_SLOT_1_COLOR) + 1;

            if (cursor.click && game_save_exists(gui.slotSel - 1, dummy))
            {
                //load game slot
                gui.state = GUI_MAIN_STATE;
                game_load(hsColor - GUI_LOAD_SLOT_1_COLOR);
            }
            break;
        case GUI_SAVE_SLOT_1_COLOR ... GUI_SAVE_SLOT_5_COLOR:
            //get slot selected
            gui.slotSel = (hsColor - GUI_SAVE_SLOT_1_COLOR) + 1;
            
            if (cursor.click)
            {
                //save game slot
                game.state = PLAYING_STATE;
                gui_init();
                game_save(hsColor - GUI_SAVE_SLOT_1_COLOR);
            }
            break;
        default:
            if (cursor.click)
            {
                //if color is valid for main gui buttons
                if (hsColor >= GUI_COLOR_OFFSET && hsColor <= (GUI_COLOR_OFFSET + GUI_NUM_OPTIONS))
                    //change gui state
                    gui.state = (hsColor - GUI_COLOR_OFFSET);
            }
            break;
    }

    //debug
    show_debug("Color menu", hsColor);
}

//funcion that handles action of cursor on room
void cursor_action_room()
{
    //obtains the hotspot room color
    uint8_t hsColor = getpixel(actualRoom.hsImage, mouse_x, mouse_y);

    //gets the object name
    roomData[game.actualRoom].room_get_hotspot_name(hsColor, cursor.objectName);

    //check right click action on room (evaluated before the left click)
    if (cursor.rightClick)
    {
        //if valid object, get default object verb
        if (cursor.objectName[0] != '\0')
            cursor.selectedVerb = roomData[game.actualRoom].room_get_default_hotspot_verb(hsColor);
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
            roomScript.type = ROOM_SCRIPT_TYPE;
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

    //debug
    show_debug("Color room", hsColor);
}

//function that handles action of cursor on dialog
void cursor_action_dialog()
{
    //obtains the hotspot dialog color (coords relative to gui base image)
    uint8_t hsColor = getpixel(hud.dialogHsImage, mouse_x, mouse_y - HUD_Y);

    //if cursor on valid dialog line
    if (hsColor >= 0 && hsColor <= dialog.nodeNumLines)
    {
        //sets line highlighted
        dialog.highlightLine = hsColor;

        //if click on dialog line
        if (cursor.click)
        {
            //sets the selection on dialog structure
            dialog.selLine   = hsColor;
            //sets script state for dialog
            dialog.state = DIALOG_ST_SCRIPT;

            //sets the room script for dialog
            roomScript.active = true;
            roomScript.type = DIALOG_SCRIPT_TYPE;
        }
    }
    else
        dialog.highlightLine = 0;

    //debug
    show_debug("Color dialog", hsColor);
}

//draws debug info
void debug_draw()
{
    #ifdef DEBUGMODE
    //writes all the debug vars
    for (int i = 0; i < debug.numVars; i++)
    {
        textprintf_ex(buffer, font, 0, DEBUG_Y + (DEBUG_FONT_HEIGHT*i), makecol(255,255,255), -1, "%s: %i", debug.varName[i], debug.var[i]);
    }

    //reset debug vars
    debug.numVars = 0;
    
    #endif //DEBUGMODE
}

//draws the status bar
void status_bar_draw()
{
    //check if the verb is USE_WITH to print object inventory or not
    if (cursor.selectedVerb != USE_WITH)
        textprintf_centre_ex(buffer, font, STATUS_BAR_X, STATUS_BAR_TEXT_Y, makecol(255,255,255), -1, "%s %s", verbName[cursor.selectedVerb], cursor.objectName);
    else
        textprintf_centre_ex(buffer, font, STATUS_BAR_X, STATUS_BAR_TEXT_Y, makecol(255,255,255), -1, "%s %s con %s", verbName[cursor.selectedVerb], cursor.invObjName, cursor.objectName);
}

//function to init msg structure
void msg_init()
{
    //clear msg and vars
    strcpy(msg.msg, "");
    msg.msgTime = 0;
    msg.msgFinished = false;
    msg.msgActive = false;
    msg.actorTalk = NULL;
}


//function to update message
void msg_update()
{
    //if msg finished, reset the flags
    if (msg.msgFinished)
    {
        msg.msgActive = false;
        msg.msgFinished = false;
        //player.state = player_st_idle;
        msg.actorTalk->talking = false;
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

            if (msg.msgTime >= msgDuration || cursor.click)
            {
                msg.msgFinished = true;
                msg.actorTalk->talking = false;
            }
            else
            {
                msg.msgTime += gameTick > 0;
                //set talking flag
                //player.state = player_st_talking;
                msg.actorTalk->talking = true;
            }
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
    if (!game.fadeIn && msg.msgActive)
    {
        int msgX;
        int msgY;

        //get msg length in pixels
        int msgWidth = get_msg_length(msg.msg); //text_length(font, msg.msg);

        //check msg X limits for avoid text outscreen
        if (msg.actorTalk->msgX < (msgWidth>>1))
            msgX = (msgWidth>>1);
        else if (msg.actorTalk->msgX > (RES_X - (msgWidth>>1)))
            msgX = RES_X - (msgWidth>>1);
        else
            msgX = msg.actorTalk->msgX;

        //get msg Y
        msgY = msg.actorTalk->msgY - TEXT_ACTOR_MARGIN;
        
        //call to write text
        game_write(msg.msg, msgX, msgY, msg.actorTalk->textColor);
    }
}

//function to get msg length (in pixels). On multiline, returns the lenght of first line
int get_msg_length(char *text)
{
    char s[MAX_MSG_LENGTH];
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
void abort_on_error(const char *format, ...)
{
    char buf[1024];

    //get the arguments of formatted string
    va_list arglist;
    va_start(arglist, format);
    vsprintf(buf, format, arglist);
    va_end(arglist);

    #ifndef DEBUGMODE
    allegro_message(buf);
    #else
    allegro_message(buf);
    allegro_message(allegro_error);
    #endif
    exit(EXIT_FAILURE);
}

//load a room datafile
DATAFILE* room_load_datafile(uint8_t roomNumber)
{
    DATAFILE *df;
    char filename[8];
    
    //compone room datafile name
    sprintf(filename, "R%02dDATA.DAT", roomNumber + 1);
    TRACE("Load room datafile: %s\n", filename);
    //loads datafile
    df = load_datafile(filename);

    //check datafile
    if (!df)
        abort_on_error("Archivo %s invalido o inexistente", filename);
    else
        return df;
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

//load the room data
void room_load(uint8_t roomNumber)
{
    TRACE("Free actual room datafile resources\n");
    
    //unload previous datafile
    if (actualRoom.dataFile)
        unload_datafile(actualRoom.dataFile);

    //free the room pointers
    actualRoom.image   = NULL;
    actualRoom.hsImage = NULL;
    actualRoom.wImage  = NULL;

    //loads actual room datafile
    actualRoom.dataFile = room_load_datafile(roomNumber);
    //sets the resources pointers
    actualRoom.image   = (BITMAP *)actualRoom.dataFile[0].dat;
    actualRoom.hsImage = (BITMAP *)actualRoom.dataFile[1].dat;
    actualRoom.wImage  = (BITMAP *)actualRoom.dataFile[2].dat;

    if (!actualRoom.hsImage)
        TRACE("Error loading hotspot room image\n");
        
    //check if room music has to need changed
    if (actualRoom.musicId != roomData[game.actualRoom].roomMusicId)
    {
        //stop actual music
        stop_midi();
        //free music resources
        unload_datafile_object(actualRoom.musicDataFile);
        actualRoom.music            = NULL;

        //load room music
        actualRoom.musicDataFile    = load_datafile_object_indexed(actualRoom.musicDataFileIndex, roomData[game.actualRoom].roomMusicId);
        actualRoom.music            = (MIDI *)actualRoom.musicDataFile[0].dat;

        //assign actual room music id
        actualRoom.musicId = roomData[game.actualRoom].roomMusicId;

        //play room music
        play_midi(actualRoom.music, -1);
    }
}

//draws the actual room and room objects
void room_draw()
{
    //if (game.roomLoaded)
    //{
        //draw room image
        blit(actualRoom.image, buffer, 0, 0, 0, 0, actualRoom.image->w, actualRoom.image->h);

        #ifdef DEBUGMODE
            //draw hotspot image on debug mode
            if (debug.showHotspotImage)
                    blit(actualRoom.hsImage, buffer, 0, 0, 0, 0, actualRoom.hsImage->w, actualRoom.hsImage->h);
            //draw walk image on debug mode
            if (debug.showWalkImage)
                    blit(actualRoom.wImage, buffer, 0, 0, 0, 0, actualRoom.wImage->w, actualRoom.wImage->h);
        #endif
        
        //draw room objects back layer
        room_objects_draw(BACK_LAYER);
    //}
}

//draws the room front layer objects
void room_front_layer_draw()
{
    //if (game.roomLoaded)
    //{
        //draw room objects front layer
        room_objects_draw(FRONT_LAYER);
        //draw black background on hud position
        rectfill(buffer, 0, HUD_Y, RES_X, RES_Y, BLACK_COLOR);
    //}
}

//draws room objects filtered by layer parameter
void room_objects_draw(uint8_t layer)
{
    tObject *obj;
    BITMAP *objImage;
    //runs for room objects
    for (int i = 0; i < roomData[game.actualRoom].room_num_objects; i++)
    {
        //get pointer to object structure
        obj = roomData[game.actualRoom].room_get_object_info(i);
        //check null pointer
        if (obj == NULL)
            abort_on_error("Error accediendo a indice de objecto no existente");
        //check object active and layer
        else if (obj->active && obj->layer == layer)
        {
            //get pointer to bitmap object
            objImage = (BITMAP *)actualRoom.dataFile[obj->objId].dat;
            //draw the object
            draw_sprite(buffer, objImage, obj->x-(objImage->w>>1), obj->y - (objImage->h>>1));
        }
    }
}

//inits the hud
void hud_init()
{
    //sets hud images
    hud.image               = (BITMAP *)gameDataFile[gd_hud].dat;
    hud.hsImage             = (BITMAP *)gameDataFile[gd_hudhs].dat;
    hud.verbSelImage[GO]    = (BITMAP *)gameDataFile[gd_hudGoSel].dat;
    hud.verbSelImage[TAKE]  = (BITMAP *)gameDataFile[gd_hudTakeSel].dat;
    hud.verbSelImage[MOVE]  = (BITMAP *)gameDataFile[gd_hudMoveSel].dat;
    hud.verbSelImage[LOOK]  = (BITMAP *)gameDataFile[gd_hudLookSel].dat;
    hud.verbSelImage[USE]   = (BITMAP *)gameDataFile[gd_hudUseSel].dat;
    hud.verbSelImage[GIVE]  = (BITMAP *)gameDataFile[gd_hudGiveSel].dat;
    hud.verbSelImage[OPEN]  = (BITMAP *)gameDataFile[gd_hudOpenSel].dat;
    hud.verbSelImage[CLOSE] = (BITMAP *)gameDataFile[gd_hudCloseSel].dat;
    hud.verbSelImage[TALK]  = (BITMAP *)gameDataFile[gd_hudTalkSel].dat;

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
        draw_sprite(buffer, (BITMAP *)gameDataFile[gd_hudUpSel].dat, SEL_UP_DOWN_X, SEL_UP_Y + HUD_Y);
    if (hud.selDownButton)
        draw_sprite(buffer, (BITMAP *)gameDataFile[gd_hudDownSel].dat, SEL_UP_DOWN_X, SEL_DOWN_Y + HUD_Y);

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
    //sets gui images
    gui.image               = (BITMAP *)gameDataFile[gd_guiMain].dat;
    gui.hsImageMain         = (BITMAP *)gameDataFile[gd_guiMainHs].dat;
    gui.hsImage             = gui.hsImageMain;
    gui.hsImageExit         = (BITMAP *)gameDataFile[gd_guiExitHs].dat;
    gui.hsImageOptions      = (BITMAP *)gameDataFile[gd_guiOptionsHs].dat;
    gui.hsImageSave         = (BITMAP *)gameDataFile[gd_guiSaveHs].dat;
    gui.hsImageLoad         = (BITMAP *)gameDataFile[gd_guiLoadHs].dat;
    gui.imageSlotSel        = (BITMAP *)gameDataFile[gd_guiSlotSel].dat;

    //set gui position (center of screen)
    gui.x = (RES_X>>1) - (gui.image->w>>1);
    gui.y = (RES_Y>>1) - (gui.image->h>>1);

    //gui state
    gui.state = GUI_MAIN_STATE;
}

//function to update the gui
void gui_update()
{
    cursor.enabled = true;
    
    //compose gui hotspot image: main gui hotspot
    draw_sprite(gui.hsImage, gui.hsImageMain, 0, 0);

    //check gui state
    switch (gui.state)
    {
        case GUI_LOAD_STATE:
            //draw hotspot state zone
            draw_sprite(gui.hsImage, gui.hsImageLoad, GUI_CONTENT_X, GUI_CONTENT_Y);
            break;
        case GUI_SAVE_STATE:
            //draw hotspot state zone
            draw_sprite(gui.hsImage, gui.hsImageSave, GUI_CONTENT_X, GUI_CONTENT_Y);
            break;
        case GUI_OPTIONS_STATE:
            //draw hotspot state zone
            draw_sprite(gui.hsImage, gui.hsImageOptions, GUI_CONTENT_X, GUI_CONTENT_Y);
            break;
        case GUI_EXIT_STATE:
            //draw hotspot state zone
            draw_sprite(gui.hsImage, gui.hsImageExit , GUI_CONTENT_X, GUI_CONTENT_Y);
            break;
        case GUI_EXIT_TITLE_STATE:
            game.state = TITLE_STATE;
            stop_midi();
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
    char saveDate[SAVEGAME_DATE_CHARS];
    
    //draw main gui on center of screen
    draw_sprite(buffer, gui.image, gui.x, gui.y);

    switch (gui.state)
    {
        case GUI_LOAD_STATE:
            for (int i = 0; i < SAVEGAME_SLOTS; i++)
            {
                //check savegame file
                game_save_exists(i, saveDate);

                if (gui.slotSel == (i + 1))
                {
                    //draw slot selection
                    draw_sprite(buffer, gui.imageSlotSel, gui.x + GUI_CONTENT_X, gui.y + GUI_CONTENT_Y + GUI_SLOTS_SEL_Y + (GUI_SLOTS_Y_SPACING * i));
                    //draw savegame text (dark)
                    textprintf_ex(buffer, font, gui.x + GUI_CONTENT_X + GUI_SLOTS_X, gui.y + GUI_CONTENT_Y + GUI_SLOTS_Y + (GUI_SLOTS_Y_SPACING * i), GUI_SEL_SLOT_TEXT_COLOR, -1, "%i.%s", i + 1, saveDate);
                }
                else
                    //draw savegame text (bright)
                    textprintf_ex(buffer, font, gui.x + GUI_CONTENT_X + GUI_SLOTS_X, gui.y + GUI_CONTENT_Y + GUI_SLOTS_Y + (GUI_SLOTS_Y_SPACING * i), makecol(255,255,255), -1, "%i.%s", i + 1, saveDate);
            }
            //draw button highlighted
            draw_sprite(buffer, (BITMAP *)gameDataFile[gd_guiLoadSel].dat, gui.x + GUI_BUTTONS_X, gui.y + GUI_BUTTONS_Y + (GUI_BUTTONS_SPACING * gui.state));
            break;
        case GUI_SAVE_STATE:
            for (int i = 0; i < SAVEGAME_SLOTS; i++)
            {
                //check savegame file
                game_save_exists(i, saveDate);

                if (gui.slotSel == (i + 1))
                {
                    //draw slot selection
                    draw_sprite(buffer, gui.imageSlotSel, gui.x + GUI_CONTENT_X, gui.y + GUI_CONTENT_Y + GUI_SLOTS_SEL_Y + (GUI_SLOTS_Y_SPACING * i));
                    //draw savegame text (dark)
                    textprintf_ex(buffer, font, gui.x + GUI_CONTENT_X + GUI_SLOTS_X, gui.y + GUI_CONTENT_Y + GUI_SLOTS_Y + (GUI_SLOTS_Y_SPACING * i), GUI_SEL_SLOT_TEXT_COLOR, -1, "%i.%s", i + 1, saveDate);
                }
                else
                    //draw savegame text (bright)
                    textprintf_ex(buffer, font, gui.x + GUI_CONTENT_X + GUI_SLOTS_X, gui.y + GUI_CONTENT_Y + GUI_SLOTS_Y + (GUI_SLOTS_Y_SPACING * i), makecol(255,255,255), -1, "%i.%s", i + 1, saveDate);
            }
            //draw button highlighted
            draw_sprite(buffer, (BITMAP *)gameDataFile[gd_guiSaveSel].dat, gui.x + GUI_BUTTONS_X, gui.y + GUI_BUTTONS_Y + (GUI_BUTTONS_SPACING * gui.state));
            break;
        case GUI_OPTIONS_STATE:
            //draw gui contents
            draw_sprite(buffer, (BITMAP *)gameDataFile[gd_guiOptions].dat, gui.x + GUI_CONTENT_X, gui.y + GUI_CONTENT_Y);
            //draw button highlighted
            draw_sprite(buffer, (BITMAP *)gameDataFile[gd_guiOptionsSel].dat, gui.x + GUI_BUTTONS_X, gui.y + GUI_BUTTONS_Y + (GUI_BUTTONS_SPACING * gui.state));
            //draw options sliders
            fixed norm_value;
            int scaled_value;
            
            norm_value = norm_x(gameConfig.textSpeed, CONFIG_TEXT_SPEED_MIN, CONFIG_TEXT_SPEED_MAX);
            scaled_value = scale_x(norm_value, GUI_SLIDER_MIN_X, GUI_SLIDER_MAX_X);
            draw_sprite(buffer, (BITMAP *)gameDataFile[gd_guiSlider].dat, gui.x + scaled_value, gui.y + GUI_SLIDER_1_Y);

            norm_value = norm_x(gameConfig.playerSpeed, CONFIG_PLY_SPEED_MIN, CONFIG_PLY_SPEED_MAX);
            scaled_value = scale_x(norm_value, GUI_SLIDER_MIN_X, GUI_SLIDER_MAX_X);
            draw_sprite(buffer, gameDataFile[gd_guiSlider].dat, gui.x + scaled_value, gui.y + GUI_SLIDER_2_Y);

            norm_value      = norm_x(gameConfig.musicVolume, 0, 255);
            scaled_value    = scale_x(norm_value, GUI_SLIDER_MIN_X, GUI_SLIDER_MAX_X);
            draw_sprite(buffer, gameDataFile[gd_guiSlider].dat, gui.x + scaled_value, gui.y + GUI_SLIDER_3_Y);

            norm_value      = norm_x(gameConfig.soundVolume, 0, 255);
            scaled_value    = scale_x(norm_value, GUI_SLIDER_MIN_X, GUI_SLIDER_MAX_X);
            draw_sprite(buffer, gameDataFile[gd_guiSlider].dat, gui.x + scaled_value, gui.y + GUI_SLIDER_4_Y);
            break;
        case GUI_ABOUT_STATE:
            //draw gui contents
            //draw_sprite(buffer, (BITMAP *)guiDataFile[dGui_Options].dat, gui.x + GUI_CONTENT_X, gui.y + GUI_CONTENT_Y);
            //draw button highlighted
            draw_sprite(buffer, (BITMAP *)gameDataFile[gd_guiAboutSel].dat, gui.x + GUI_BUTTONS_X, gui.y + GUI_BUTTONS_Y + (GUI_BUTTONS_SPACING * gui.state));
            break;
        case GUI_EXIT_STATE:
            //draw gui contents
            draw_sprite(buffer, (BITMAP *)gameDataFile[gd_guiExit].dat, gui.x + GUI_CONTENT_X, gui.y + GUI_CONTENT_Y);
            //draw button highlighted
            draw_sprite(buffer, (BITMAP *)gameDataFile[gd_guiExitSel].dat, gui.x + GUI_BUTTONS_X, gui.y + GUI_BUTTONS_Y + (GUI_BUTTONS_SPACING * gui.state));
            break;
        case GUI_EXIT_TITLE_STATE:
            //draw gui contents
            draw_sprite(buffer, (BITMAP *)gameDataFile[gd_guiExit].dat, gui.x + GUI_CONTENT_X, gui.y + GUI_CONTENT_Y);
            //draw button highlighted
            draw_sprite(buffer, (BITMAP *)gameDataFile[gd_guiExitTitleSel].dat, gui.x + GUI_BUTTONS_EXIT, gui.y + GUI_BUTTON_EXIT_TITLE_Y);
            break;
        case GUI_EXIT_DOS_STATE:
            //draw gui contents
            draw_sprite(buffer, (BITMAP *)gameDataFile[gd_guiExit].dat, gui.x + GUI_CONTENT_X, gui.y + GUI_CONTENT_Y);
            //draw button highlighted
            draw_sprite(buffer, (BITMAP *)gameDataFile[gd_guiExitDosSel].dat, gui.x + GUI_BUTTONS_EXIT, gui.y + GUI_BUTTON_EXIT_DOS_Y);
            break;
    }
}

//function to init dialog system
void dialog_init()
{
    dialog.active = false;
    dialog.state = DIALOG_ST_SELECT;
    dialog.dialogId = 0;
    dialog.selLine = 0;
    dialog.node = 0;
    dialog.nodeNumLines = 0;
    dialog.highlightLine = 0;

    hud.dialogHsImage = (BITMAP *)gameDataFile[gd_hudDialogHs].dat;
}

//function to draw the dialog
void dialog_draw()
{
    if (dialog.state == DIALOG_ST_SELECT)
    {
       for (int i = 0; i < dialog.nodeNumLines; i++)
       {
           if ((dialog.highlightLine - 1) == i)
               textprintf_ex(buffer, font, 0, HUD_Y + DEBUG_FONT_HEIGHT + (DEBUG_FONT_HEIGHT*i), makecol(255,255,255), -1, "%s", dialog.lineText[i]);
           else
               textprintf_ex(buffer, font, 0, HUD_Y + DEBUG_FONT_HEIGHT + (DEBUG_FONT_HEIGHT*i), makecol(200,200,200), -1, "%s", dialog.lineText[i]);
       }
   
       //reset dialog choices
       dialog.nodeNumLines = 0;
    }
}

END_OF_MAIN()
