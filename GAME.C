//on compiler flags
//#define DEBUGMODE

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "allegro.h"
#include "engine.h"
#include "game.h"
#include "rooms.h"
#include "inv.h"
#include "player.h"
#include "utils.h"
//game data resources
#include "GDATA.H"
#include "IDATA.H"
#include "SDATA.H"
#include "MDATA.H"

int main()
{
    //initialization
    main_init();
    game_init();
    game_fade_out(FADE_SLOW_SPEED);


    #ifdef DEBUGMODE
        change_room_pos(BEDROOM_ROOM_NUM, 170, 100);
        game.state = PLAYING_STATE;
    #endif

    play_music(md_warcomLogo, 0);

    //main game loop
    while (!game.exit)
    {
        //stateless update
        main_update();

        //check actual game state
        switch (game.state)
        {
            case LOGO_STATE:
                game_fade_in();
                cursor.enabled = false;

                game_update();

                //draw warcom logo
                draw_sprite(buffer, (BITMAP *)gameDataFile[gd_warcomLogo].dat, (GAME_WARCOM_LOGO_POS_X) - (((BITMAP *)gameDataFile[gd_warcomLogo].dat)->w>>1), (GAME_WARCOM_LOGO_POS_Y) - (((BITMAP *)gameDataFile[gd_warcomLogo].dat)->h>>1));
                //write text
                game_write("WARCOM SOFT 2025", C_X, GAME_WARCOM_TEXT_POS_Y, 114, 4);
            break;
            case DOS_LOGO_STATE:
                game_fade_in();
                cursor.enabled = false;

                game_update();

                //draw ms-dos club logo
                draw_sprite(buffer, (BITMAP *)gameDataFile[gd_msdosLogo].dat, (RES_X>>1) - (((BITMAP *)gameDataFile[gd_msdosLogo].dat)->w>>1), (RES_Y>>1) - (((BITMAP *)gameDataFile[gd_msdosLogo].dat)->h>>1));
            break;
            case PROLOGUE_STATE:
                game_fade_in();
                cursor.enabled = false;

                cursor_update();
                game_update();

                switch (seq.step)
                {
                    case 0:
                        game_write("Corr¡a el a¤o 1995 en una ciudad cualquiera", C_X, C_Y, makecol(GAME_TEXT_COLOR), 2);
                    break;
                    case 1:
                        game_write("Nuestro protagonista pasea despreocupado\npor la calle como cualquier otro d¡a", C_X, C_Y, makecol(GAME_TEXT_COLOR), 2);
                    break;
                    case 2:
                        game_write("Nada parece importarle en la vida hasta\nque una noticia llama poderosamente su atenci¢n", C_X, C_Y, makecol(GAME_TEXT_COLOR), 2);
                    break;
                }
            break;
            case INTRO_STATE:
                 //update calls
                game_update();
                msg_update();
                roomData[game.actualRoom].room_update();
                room_action_update();
                cursor_update();
                player_update();
                
                //draw calls
                room_draw();
                player_draw();
                room_front_layer_draw();
                msg_draw();

            break;
            case TITLE_STATE:
                game_fade_in();
                cursor.enabled = true;

                cursor_update();
                game_update();

                //draw game title
                draw_sprite(buffer, (BITMAP *)gameDataFile[gd_title].dat, (C_X) - (((BITMAP *)gameDataFile[gd_title].dat)->w>>1), (GAME_TITLE_POS_Y) - (((BITMAP *)gameDataFile[gd_title].dat)->h>>1));
                game_write("(SIN BLANCA)", C_X, GAME_TITLE_ESP_POS_Y, makecol(255,255,255), 2);
                game_write("Haz click para comenzar", C_X, GAME_TITLE_FOOTER_POS_Y, makecol(255,233,12), 2);
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
                playTime_update();
                
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
                game_write("PAUSA", C_X, C_Y, makecol(GAME_TEXT_COLOR), 4);

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
            case RESTART_STATE:
                game_update();
            break;
            case END_STATE:
                 //update calls
                game_update();
                msg_update();
                roomData[game.actualRoom].room_update();
                room_action_update();
                cursor_update();
                player_update();
                
                //draw calls
                room_draw();
                player_draw();
                room_objects_draw(FRONT_LAYER);
                if (is_game_flag(START_CREDITS_FLAG))
                    credits_draw();
                msg_draw();
                cursor_draw();
            break;
            case EXIT_STATE:
                game.exit = true;
            break;
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
    //set env var trace log file
    setenv("ALLEGRO_TRACE", "GAME.LOG", 1);

    TRACE("Outcash (Sin blanca) version %i.%i\n", MAJOR_VERSION, MINOR_VERSION);
    TRACE("Initializing systems and modules\n");
    
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

    TRACE("All system and modules initialized\n");
    
    //load game resources
    game_load_resources();

    //set game initial state
    game.state = LOGO_STATE;

    //init game tick
    tick_init();

    //init debug
    #ifdef DEBUGMODE
        //debug.showDebugInfo = true;
    #endif
}

//general update
void main_update()
{
    clear(buffer);
    tick_update();
    sfx_update();
    
    //debug vars
    show_debug("X",mouse_x);
    show_debug("Y",mouse_y);
    show_debug("Player x", fixtoi(player.x));
    show_debug("Player y", fixtoi(player.y));
    show_debug("Script.step", roomScript.step);

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
    TRACE("Loading game resources\n");
    
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

    //loads game font
    //PALETTE pal;
    gameFont[0] = font;
    char *fontName2[] = {"verdana8", NULL};
    gameFont[1] = load_dat_font("GDATA.DAT", NULL, fontName2);
    char *fontName3[] = {"verdana8Bold", NULL};
    gameFont[2] = load_dat_font("GDATA.DAT", NULL, fontName3);
    char *fontName4[] = {"verdana9", NULL};
    gameFont[3] = load_dat_font("GDATA.DAT", NULL, fontName4);
    char *fontName5[] = {"verdana9Bold", NULL};
    gameFont[4] = load_dat_font("GDATA.DAT", NULL, fontName5);
    char *fontName1[] = {"gameFont", NULL};
    gameFont[5] = load_dat_font("GDATA.DAT", NULL, fontName1);;
    
    /*gameFont = load_dat_font("GDATA.DAT", NULL, fontName[0]);
    if (!gameFont)
        abort_on_error("Error cargando fuente de texto");
    */
    TRACE("Game resources loaded\n");
}

//function to free game resources
void game_free_resources()
{
    TRACE("Freeing game resources\n");

    TRACE("Destroying data file index\n");
    destroy_datafile_index(actualRoom.musicDataFileIndex);
    
    TRACE("Unloading data files\n");
    unload_datafile(gameDataFile);
    unload_datafile(playerDataFile);
    unload_datafile(inventoryDataFile);
    unload_datafile(soundDataFile);

    TRACE("Unloading fonts\n");
    for (int i = 1; i <= 5; i++)
        destroy_font(gameFont[i]);

    //free music resources
    if (actualRoom.musicDataFile)
    {
        TRACE("Unload music data file object\n");
        unload_datafile_object(actualRoom.musicDataFile);
    }
    
    TRACE("Game resources free completed\n");
}

//function to init game
void game_init()
{
    //default game config (each savegame file stores custom config)
    gameConfig.textSpeed    = 10;   //chars per second
    gameConfig.playerSpeed  = 20;
    gameConfig.musicVolume  = 180;
    gameConfig.soundVolume  = 200;

    //sets audio config
    set_hardware_volume(gameConfig.soundVolume, gameConfig.musicVolume);
    set_volume(gameConfig.soundVolume, gameConfig.musicVolume);
    
    //init game vars
    game.actualRoom             = -1;    //to force first room_init
    game.nextRoom               = STREET_ROOM_NUM;
    game.room_pos_x             = 30;
    game.room_pos_y             = 120;
    game.fadeSpeed              = FADE_DEFAULT_SPEED;
    
    //clear game flags
    for (int i = 0; i < MAX_GAME_FLAGS; i++)
        game.flags[i] = 0;
    //clear game vars
    for (int i = 0; i < MAX_GAME_VARS; i++)
        game.vars[i] = 0;
        
    //init scroll
    roomScroll.x = 0;
    roomScroll.y = 0;
    
    //init room music
    actualRoom.musicId  = -1;

    //game font
    actualFont = 2;
    
    //call init game modules
    cursor_init();
    init_room_script();
    msg_init();
    player_init();
    inventory_init();
    gui_init();
    hud_init();
    dialog_init();
    sfx_init();
    playTime_init();
    
    //initial game inventory object
    inventory_add(id_califications);
    
    TRACE("Game initialized\n");
}

//game update function
void game_update()
{
    //call to game keys handler
    game_keys_handler();

    //update current game state
    switch (game.state)
    {
        case LOGO_STATE:
            if (midi_pos < 0 || gameKeys[G_KEY_EXIT].pressed)
            {
                seq.timeCounter = 0;
                seq.step = 0;
                game_fade_out(FADE_SLOW_SPEED);
                game.state = DOS_LOGO_STATE;
                sfx_play(sd_msDosJingle, SFX_GAME_VOICE , false);
                stop_music();
            }
        break;
        case DOS_LOGO_STATE:
            if (gameTick)
                seq.timeCounter++;
            if (seq.timeCounter >= 60 || gameKeys[G_KEY_EXIT].pressed)
            {
                seq.timeCounter = 0;
                seq.step = 0;
                game_fade_out(FADE_SLOW_SPEED);
                game.state = PROLOGUE_STATE;
                sfx[SFX_GAME_VOICE].stop = true;
                play_music(md_intro, -1);
                actualRoom.musicId = md_intro;
            }
        break;
        case PROLOGUE_STATE:
            if (gameTick)
                seq.timeCounter++;
            if (seq.timeCounter >= 40 || cursor.click)
            {
                game_fade_out(FADE_SLOW_SPEED);
                seq.step++;
                seq.timeCounter = 0;
            }
            if (seq.step > 2)
            {
                seq.timeCounter = 0;
                seq.step = 0;
                game_fade_out(FADE_SLOW_SPEED);
                set_game_flag(INTRO_FLAG);
                game.state = INTRO_STATE;
            }
            else if(gameKeys[G_KEY_EXIT].pressed)
            {
                game_fade_out(FADE_SLOW_SPEED);
                stop_midi();
                change_room(BEDROOM_ROOM_NUM);
                game.state = TITLE_STATE;
                play_music(md_title, -1);
            }
        break;
        case INTRO_STATE:
            if (!is_game_flag(INTRO_FLAG) || gameKeys[G_KEY_EXIT].pressed)
            {
                game_fade_out(FADE_SLOW_SPEED);
                change_room(BEDROOM_ROOM_NUM);
                game.state = TITLE_STATE;
                play_music(md_title, -1);
            }
            else
                check_room_changed();
        break;
        case TITLE_STATE:
            if (cursor.click)
            {
                game_fade_out(FADE_SLOW_SPEED);
                stop_music();
                game_init();
                change_room_pos(BEDROOM_ROOM_NUM, 170, 100);
                game.state = PLAYING_STATE;
            }
        break;
        case PLAYING_STATE:
            //restore sound based on prev state
            if (game.prevState == MENU_STATE)
            {
                resume_sound();
                //midi_resume();
            }
                
            if (gameKeys[G_KEY_PAUSE].pressed)
            {
                game.state = PAUSE_STATE;
                midi_pause();
                pause_sound();
            }
            else if (gameKeys[G_KEY_EXIT].pressed)
            {
                game.state = MENU_STATE;
                //midi_pause();
                pause_sound();
            }
            else if (is_game_flag(GAME_END_FLAG))
            {
                game_fade_out(FADE_SLOW_SPEED);
                credits_init();
                change_room(ENDING_ROOM_NUM);
                game.state = END_STATE;
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
                resume_sound();
                midi_resume();
            }
        break;
        case MENU_STATE:
            cursor.enabled = true;
            if (gameKeys[G_KEY_EXIT].pressed)
            {
                game.state = PLAYING_STATE;
                resume_sound();
                sfx[SFX_GAME_VOICE].stop = true;
                //midi_resume();
            }
        break;
        case END_STATE:
            if (gameKeys[G_KEY_EXIT].pressed || is_game_flag(END_FINISH_FLAG))
            {
                game.state = RESTART_STATE;
            }
            else
            {
                switch (seq.step)
                {
                    case 1:
                        seq.timeCounter += gameTick;
                        if (seq.timeCounter >= 60)
                        {
                            seq.timeCounter = 0;
                            seq.step++;
                        }
                    break;
                    case 2:
                        set_game_flag(END_CREDITS_FLAG);
                    break;
                }
                check_room_changed();
            }
        break;
        case RESTART_STATE:
            game_fade_out(FADE_SLOW_SPEED);
            game_init();
            game.state = LOGO_STATE;
            play_music(md_warcomLogo, 0);
        break;        
    }

    if (game.state != game.prevState)
    {
        TRACE("Change game state from %i to %i\n", game.prevState, game.state);
        game.prevState = game.state;
    }
    
    #ifdef DEBUGMODE
        //force game exit
        if (key[KEY_X] && (key_shifts & KB_CTRL_FLAG))
            game.state = EXIT_STATE;

        //toogle show room walk image
        if (gameKeys[G_KEY_W].pressed)
            debug.showWalkImage = !debug.showWalkImage;
            
        //toogle show room hotspot image
        if (gameKeys[G_KEY_H].pressed)
            debug.showHotspotImage = !debug.showHotspotImage;

        //toogle show debug info
        if (gameKeys[G_KEY_D].pressed)
            debug.showDebugInfo = !debug.showDebugInfo;

        //toogle cursor room objects
        if (gameKeys[G_KEY_O].pressed && (game.state == PLAYING_STATE || game.state == END_STATE))
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
        if (gameKeys[G_KEY_UP].pressed && (key_shifts & KB_SHIFT_FLAG) && (game.state == PLAYING_STATE || game.state == END_STATE))
        {
            if (debug.cursorRoomObjects && debug.numCursorRoomObject < roomData[game.actualRoom].room_num_objects)
                debug.numCursorRoomObject++;
            else
                actualFont = actualFont < 5 ? ++actualFont : 0;
        }

        //cycle down cursor room objects
        if (gameKeys[G_KEY_DOWN].pressed && (key_shifts & KB_SHIFT_FLAG) && (game.state == PLAYING_STATE || game.state == END_STATE))
        {
            if (debug.cursorRoomObjects && debug.numCursorRoomObject > 0)
                debug.numCursorRoomObject--;
            else
                actualFont = actualFont > 0 ? --actualFont : 5;
        }

        //log object placement position
        if ((game.state == PLAYING_STATE || game.state == END_STATE) && debug.cursorRoomObjects && cursor.click)
            TRACE("Object %i Position x: %i Position y: %i\n", debug.numCursorRoomObject, cursor.x, cursor.y);

        //move cursor with arrows
        if (gameKeys[G_KEY_LEFT].pressed && !(key_shifts & KB_SHIFT_FLAG))
            mouse_x--;
        if (gameKeys[G_KEY_RIGHT].pressed && !(key_shifts & KB_SHIFT_FLAG))
            mouse_x++;
        if (gameKeys[G_KEY_UP].pressed && !(key_shifts & KB_SHIFT_FLAG))
            mouse_y--;
        if (gameKeys[G_KEY_DOWN].pressed && !(key_shifts & KB_SHIFT_FLAG))
            mouse_y++;

        //get all inventory items
        if (gameKeys[G_KEY_I].pressed)
            get_all_inv_objects();

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
void game_write(char *text, int x, int y, uint8_t color, uint8_t fontIndex)
{
    int posY;
    char s[MAX_MSG_LENGTH];
    char *ch;

    //replace unicode Latin-1 chars
    replace_unicode_str(text);
    
    //make a copy of the string for tokenizer
    strcpy(s, text);
    //first token
    ch = strtok(s, "\n");
    //sets the initial Y text position
    posY = y;

    //while ch != NULL (tokens left)
    while (ch)
    {
        //print black outline text
        textprintf_centre_ex(buffer, gameFont[fontIndex], x+1, posY, BLACK_COLOR, -1, "%s", ch);
        textprintf_centre_ex(buffer, gameFont[fontIndex], x-1, posY, BLACK_COLOR, -1, "%s", ch);
        textprintf_centre_ex(buffer, gameFont[fontIndex], x, posY+1, BLACK_COLOR, -1, "%s", ch);
        textprintf_centre_ex(buffer, gameFont[fontIndex], x, posY-1, BLACK_COLOR, -1, "%s", ch);

        //print text
        textprintf_centre_ex(buffer, gameFont[fontIndex], x, posY, color, -1, "%s", ch);
        
        //increment line position
        posY += text_height(gameFont[fontIndex]);
        
        //get next token
        ch = strtok(NULL, "\n");
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
    saveFile = fopen(filename, "rb");
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
    savegame.playTime       = playTime;
    savegame.gameConfigData = gameConfig;
    game.roomMusicPos       = midi_pos;
    savegame.gameData       = game;
    savegame.invData        = inventory;
    savegame.cursorData     = cursor;
    savegame.roomScriptData = roomScript;
    savegame.msgData        = msg;
    savegame.playerData     = player;
    savegame.sfx            = sfx[SFX_ROOM_VOICE];

    //write the savegame file
    if (!fwrite(&savegame, sizeof(struct savegame), 1, saveFile))
        abort_on_error("Error escribiendo el archivo de guardado");
    else
        TRACE("Saved game on slot %i with date: %s\n", (slot + 1), savegame.saveDate);

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
    loadFile = fopen(filename, "rb");
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
    playTime    = savegame.playTime;
    gameConfig  = savegame.gameConfigData;
    game        = savegame.gameData;
    inventory   = savegame.invData;
    cursor      = savegame.cursorData;
    roomScript  = savegame.roomScriptData;
    msg         = savegame.msgData;
    player      = savegame.playerData;
    sfx[SFX_ROOM_VOICE]  = savegame.sfx;

    //sets audio config
    set_hardware_volume(gameConfig.soundVolume, gameConfig.musicVolume);
    set_volume(gameConfig.soundVolume, gameConfig.musicVolume);

    //loads saved room resources
    room_load(game.actualRoom);

    //calculate room image borders
    calculate_image_borders(actualRoom.image, &actualRoom.roomBorders);
    //calculate hotspot/walk image borders
    calculate_image_borders(actualRoom.hsImage, &actualRoom.hsWalkBorders);

    //seeks room music to saved position
    midi_seek(game.roomMusicPos);
    //allocates and seeks sound to saved position
    reallocate_voice(SFX_ROOM_VOICE, (SAMPLE*)soundDataFile[sfx[SFX_ROOM_VOICE].sampleId].dat);
    voice_set_position(SFX_ROOM_VOICE, sfx[SFX_ROOM_VOICE].position);

    //forces refresh room_init
    roomData[game.actualRoom].room_init();
    //forces refresh inventory
    inventory.refresh = true;
    
    //close savegame file
    fclose(loadFile);

    TRACE("Loaded game from slot %i with date: %s\n", (slot + 1), savegame.saveDate);
    TRACE("Game saved play time: %02dh %02dm\n", savegame.playTime.hours, savegame.playTime.minutes);
}

//function to do pending fade in
void game_do_fade_in()
{
    if (game.fadeIn)
    {
        fade_in(gamePalette, game.fadeSpeed);
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
        //if (roomData[game.actualRoom].fadeRoom || roomData[game.nextRoom].fadeRoom)
        //    game_fade_out(FADE_DEFAULT_SPEED);
        //else
        //    game_fade_out(FADE_FAST_SPEED);
        game_fade_out(FADE_DEFAULT_SPEED);
        
        TRACE("Change from room %i to room %i\n", game.actualRoom, game.nextRoom);
        game.lastRoom = game.actualRoom;
        game.actualRoom = game.nextRoom;
        game.actualRoomLightOff = false;
        
        //load room resources
        room_load(game.actualRoom);

        //calculate room image borders
        calculate_image_borders(actualRoom.image, &actualRoom.roomBorders);
        //calculate hotspot/walk image borders
        calculate_image_borders(actualRoom.hsImage, &actualRoom.hsWalkBorders);
        
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

//function to calculate image borders
void calculate_image_borders(BITMAP *image, tBorders *border)
{
    //if image width is smaller than room screen area
    if (image->w < RES_X)
    {
        border->left   = (RES_X - image->w)>>1;
        border->right  = RES_X -  border->left;
    }
    else
    {
        border->left = 0;
        border->right = RES_X;
    }

    //if image height is smaller than room screen area
    if (image->h < HUD_Y)
    {
        border->up    = (HUD_Y - image->h)>>1;
        border->down  = HUD_Y -  border->up;
    }
    else
    {
        border->up = 0;
        border->down = RES_Y;
    }
}

//function that handles game exit
void game_exit()
{
    TRACE("Exiting game\n");
    
    //free game resources
    game_free_resources();

    //destroy game modules
    player_destroy();
    inventory_destroy();
    gui_destroy();
    sfx_destroy();
    
    TRACE("Quit allegro modules\n");
    TRACE("Game played for: %02dh %02dm\n", playTime.hours, playTime.minutes);
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
    if (cursor.enabled && ((!msg.msgActive && !roomScript.active) || game.state == MENU_STATE))
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
    //update cursor position
    cursor.x = mouse_x + roomScroll.x;
    cursor.y = mouse_y + roomScroll.y;
    
    //call buttons handler
    cursor_button_handler();

    //check cursor behaviour
    if (cursor.enabled && ((!msg.msgActive && !roomScript.active) || game.state == MENU_STATE))
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
            //clear cursor inventory vars
            cursor.invObject = 0;
            strcpy(cursor.invObjName,"");
        }

        //if mouse left on hud: default verb
        if (cursor.rightClick)
        {
            cursor.selectedVerb = GO;
            //clear cursor inventory vars
            cursor.invObject = 0;
            strcpy(cursor.invObjName,"");
        }
    }
    else if (mouse_x < HUD_INVENTORY_X)
    {
        //SCROLL INVENTORY BUTTONS REGION

        if (cursor.click)
        {
            uint8_t invLastPage =  inventory.numObjects <= INV_OBJECTS_PER_PAGE ? 0 : ((inventory.numObjects - 1) / INV_OBJECTS_PER_ROW) - 1;

            //scroll down inventory page
            if (hsColor == INV_SCROLL_DOWN_CODE && inventory.page < invLastPage)
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
                uint8_t invLastPage =  inventory.numObjects <= INV_OBJECTS_PER_PAGE ? 0 : ((inventory.numObjects - 1) / INV_OBJECTS_PER_ROW) - 1;
                inventory.page = invLastPage;
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

        //on use with verb, don't allow use object on same object
        if (cursor.selectedVerb == USE_WITH && get_inv_obj_id(get_inv_obj_position(hsColor) - 1) == cursor.invObject)
            strcpy(cursor.objectName, "");
        //on give verb, don't allow give inv object to inv object
        else if (cursor.selectedVerb == GIVE && cursor.invObjName[0] != '\0')
            strcpy(cursor.objectName, "");
        else
            //gets the object name
            get_inv_obj_name(get_inv_obj_position(hsColor), cursor.objectName);

        //replace latin 1 unicode chars
        replace_unicode_str(cursor.objectName);
    
        //check right click action on inventory object (evaluated before the left click)
        if (cursor.rightClick)
        {
            //if valid inv object, set default inv object verb
            if (cursor.objectName[0] != '\0')
                cursor.selectedVerb = LOOK;
        }
        
        //if cursor click on valid inv object or rightClick (default verb assigned) and selected ver isn't GO
        if ((cursor.click || cursor.rightClick) && cursor.objectName[0] != '\0' && cursor.selectedVerb != GO)
        {
            if (cursor.selectedVerb == GIVE)
            {
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
                    roomScript.hsX = cursor.x; //mouse_x;
                    roomScript.hsY = cursor.y; //mouse_y;

                    roomScript.invObject = cursor.invObject;
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
                set_hardware_volume(gameConfig.soundVolume, gameConfig.musicVolume);
                set_volume(gameConfig.soundVolume, gameConfig.musicVolume);
            }
            break;
        case GUI_SLIDER_4_COLOR:
            if (cursor.clicking)
            {
                gameConfig.soundVolume = scale_x(norm_value, 0, 255);
                set_hardware_volume(gameConfig.soundVolume, gameConfig.musicVolume);
                set_volume(gameConfig.soundVolume, gameConfig.musicVolume);
            }
            //feedback random global sound
            if (cursor.click)
                sfx_play((rand() % sd_COUNT), SFX_GAME_VOICE , true);
                //sfx_play(sd_take, SFX_GAME_VOICE , true);
            break;
        case GUI_LOAD_SLOT_1_COLOR ... GUI_LOAD_SLOT_5_COLOR:
            //get slot selected
            gui.slotSel = (hsColor - GUI_LOAD_SLOT_1_COLOR) + 1;

            if (cursor.click && game_save_exists(gui.slotSel - 1, dummy))
            {
                //load game slot
                gui.state = GUI_MAIN_STATE;
                game.state = PLAYING_STATE;
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
        case GUI_DEBUG_ROOM_INI_COLOR ... GUI_DEBUG_ROOM_END_COLOR:
            if (cursor.click)
            {
                game.state = PLAYING_STATE;
                gui_init();
                change_room(hsColor - GUI_DEBUG_ROOM_INI_COLOR);
                
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
    uint8_t hsColor = getpixel(actualRoom.hsImage, cursor.x - actualRoom.hsWalkBorders.left, cursor.y - actualRoom.hsWalkBorders.up);

    //if selected verb is GIVE and not assigned the inventory object, no name allowed
    if (cursor.selectedVerb == GIVE && cursor.invObjName[0] == '\0')
        strcpy(cursor.objectName, "");
    else
        //gets the room object name
        roomData[game.actualRoom].room_get_hotspot_name(hsColor, cursor.objectName);

    //replace latin 1 unicode chars
    replace_unicode_str(cursor.objectName);
    
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
            roomScript.hsX = cursor.x;
            roomScript.hsY = cursor.y;

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
    if (hsColor > 0 && hsColor <= dialog.nodeNumLines)
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
    if (!roomScript.active && !msg.msgActive)
    {
        //check if the verb is USE_WITH to print object inventory or not
        if (cursor.selectedVerb == USE_WITH)
            textprintf_centre_ex(buffer, font, STATUS_BAR_X, STATUS_BAR_TEXT_Y, makecol(255,255,255), -1, "%s %s con %s", verbName[cursor.selectedVerb], cursor.invObjName, cursor.objectName);
        else if (cursor.selectedVerb == GIVE && cursor.invObjName[0] != '\0')
            textprintf_centre_ex(buffer, font, STATUS_BAR_X, STATUS_BAR_TEXT_Y, makecol(255,255,255), -1, "%s %s a %s", verbName[cursor.selectedVerb], cursor.invObjName, cursor.objectName);
        else
            textprintf_centre_ex(buffer, font, STATUS_BAR_X, STATUS_BAR_TEXT_Y, makecol(255,255,255), -1, "%s %s", verbName[cursor.selectedVerb], cursor.objectName);
    }
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
        //cursor.enabled = false;
        
        int msgLength = strlen(msg.msg);

        if (msgLength > 0)
        {
            int msgDuration = (msgLength / gameConfig.textSpeed);
            //1 second duration minimum
            if (msgDuration == 0)
                msgDuration = 1;

            //convert to 100ms base
            msgDuration *= 10;

            if (msg.msgTime >= msgDuration || (cursor.click && msg.msgTime > TEXT_MIN_TIME_BYPASS))
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
        //cursor.enabled = true;
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
        int msgLines;
        int msgWidth = get_msg_length(msg.msg, &msgLines);

        //check msg X limits for avoid text outscreen
        if (msg.actorTalk->msgX < (msgWidth>>1))
            msgX = (msgWidth>>1);
        else if (msg.actorTalk->msgX > (RES_X - (msgWidth>>1)))
            msgX = RES_X - (msgWidth>>1);
        else
            msgX = msg.actorTalk->msgX;

        //get msg Y
        msgY = msg.actorTalk->msgY - TEXT_ACTOR_MARGIN - ((msgLines - 1) * MSG_LINE_SPACING);
        //check msg Y for avoid text outscreen
        if (msgY < MSG_LINE_SPACING)
            msgY = MSG_LINE_SPACING;
            
        //call to write text
        game_write(msg.msg, msgX, msgY, msg.actorTalk->textColor, actualFont);
    }
}

//function to get msg length (in pixels). Returns the length of largest line
//and pointer to num of lines on msg
int get_msg_length(char *text, int *lines)
{
    char s[MAX_MSG_LENGTH];
    char *ch;
    int msgLength = 0;
    int lineCount;
    
    //make a copy of the string for tokenizer
    strcpy(s, text);

    //first token
    ch = strtok(s, "\n");
    lineCount = 0;
    
    //run for tokens
    while(ch)
    {
        //check largest line
        if (text_length(font, ch) > msgLength)
            msgLength = text_length(font, ch);
        //next token
        ch = strtok(NULL, "\n");
        lineCount++;
    }

    //pointer to num of lines
    *lines = lineCount;
    
    return msgLength;
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
    sprintf(filename, "R%02dDATA.DAT", roomNumber);
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
        //disable cursor
        cursor.enabled = false;
        
        //sequence timer
        if (gameTick)
        {
          roomScript.stepTime++;
        }
        //reset step timer on step change
        if (roomScript.step != roomScript.lastStep)
        {
            TRACE("    Script step from %i to %i\n", roomScript.lastStep, roomScript.step);
            roomScript.stepTime = 0;
            roomScript.lastStep = roomScript.step;
        }

        if (!roomScript.scriptAssigned)
        {
            //is selectedVerb USE on inventory and not script assigned, change verb to USE_WITH
            if (cursor.selectedVerb == USE && roomScript.type == INVENTORY_SCRIPT_TYPE)
            {
                //sets USE_WITH verb
                cursor.selectedVerb = USE_WITH;
                //sets inventory object name verb
                strcpy(cursor.invObjName, cursor.objectName);
                //sets inventory id
                cursor.invObject =roomScript.object;
            }
            else
            {
                default_verb_action(roomScript.verb);
            }
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
        ASSERT(roomData[game.actualRoom].roomMusicId < md_COUNT);
        
        //assign actual room music id
        actualRoom.musicId = roomData[game.actualRoom].roomMusicId;

        //play room music
        play_music(actualRoom.musicId, -1);
    }
}

//draws the actual room and room objects
void room_draw()
{
    //test: move to new function room_update
    room_update_scroll();
    
    if (!game.actualRoomLightOff)
        //draw room image centered on room screen zone
        blit(actualRoom.image, buffer, roomScroll.x, roomScroll.y, actualRoom.roomBorders.left, actualRoom.roomBorders.up, actualRoom.image->w, actualRoom.image->h);

    #ifdef DEBUGMODE
        //draw hotspot image on debug mode
        if (debug.showHotspotImage)
                blit(actualRoom.hsImage, buffer, roomScroll.x, roomScroll.y, actualRoom.hsWalkBorders.left, actualRoom.hsWalkBorders.up, actualRoom.hsImage->w, actualRoom.hsImage->h);
        //draw walk image on debug mode
        if (debug.showWalkImage)
                blit(actualRoom.wImage, buffer, roomScroll.x, roomScroll.y, actualRoom.hsWalkBorders.left, actualRoom.hsWalkBorders.up, actualRoom.wImage->w, actualRoom.wImage->h);
    #endif

    //draw room objects back layer
    room_objects_draw(BACK_LAYER);
}

//draws the room front layer objects
void room_front_layer_draw()
{
    //draw room objects front layer
    room_objects_draw(FRONT_LAYER);

    //draw black background on hud position
    rectfill(buffer, 0, HUD_Y, RES_X, RES_Y, BLACK_COLOR);

    //draw black borders around room
    if (actualRoom.roomBorders.left > 0)
    {
        rectfill(buffer, 0, 0, actualRoom.roomBorders.left, HUD_Y, BORDER_COLOR);
        rectfill(buffer, actualRoom.roomBorders.right, 0, RES_X, HUD_Y, BORDER_COLOR);
    }
    if (actualRoom.roomBorders.up > 0)
    {
        rectfill(buffer, actualRoom.roomBorders.left, 0, actualRoom.roomBorders.right, actualRoom.roomBorders.up, BORDER_COLOR);
        rectfill(buffer, actualRoom.roomBorders.left, actualRoom.roomBorders.down, actualRoom.roomBorders.right, HUD_Y, BORDER_COLOR);
    }
}

//draws room objects filtered by layer parameter
void room_objects_draw(uint8_t layer)
{
    tObject *obj;
    BITMAP *objImage;

    //on debug room objects don't draw the room objects
    #ifdef DEBUGMODE
        if (debug.cursorRoomObjects && (key_shifts & KB_SHIFT_FLAG))
            return;
    #endif

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
            draw_sprite(buffer, objImage, obj->x-(objImage->w>>1) - roomScroll.x, obj->y - (objImage->h>>1) - roomScroll.y);
        }
    }
}

//function to update room scroll
void room_update_scroll()
{
    //if room image needs scroll on x
    if (actualRoom.image->w > RES_X)
    {
        //start move scroll with player on center of screen
        if (fixtoi(player.x) > RES_X>>1)
            roomScroll.x = fixtoi(player.x) - (RES_X>>1);
        else
            roomScroll.x = 0;
            
        //scroll x limits
        roomScroll.x = clamp(roomScroll.x, 0, actualRoom.image->w - RES_X);
    }
    else
    {
        roomScroll.x = 0;
    }

    //scroll on Y not implemented on this version of engine
    roomScroll.y = 0;
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
    gui.hsImageExit         = (BITMAP *)gameDataFile[gd_guiExitHs].dat;
    gui.hsImageOptions      = (BITMAP *)gameDataFile[gd_guiOptionsHs].dat;
    gui.hsImageSave         = (BITMAP *)gameDataFile[gd_guiSaveHs].dat;
    gui.hsImageLoad         = (BITMAP *)gameDataFile[gd_guiLoadHs].dat;
    gui.imageSlotSel        = (BITMAP *)gameDataFile[gd_guiSlotSel].dat;

    gui.hsImage             = create_bitmap(gui.image->w, gui.image->h);
    
    //set gui position (center of screen)
    gui.x = (RES_X>>1) - (gui.image->w>>1);
    gui.y = (RES_Y>>1) - (gui.image->h>>1);

    //gui state
    gui.state = GUI_MAIN_STATE;
}

//function to destroy gui (free resources)
void gui_destroy()
{
    TRACE("Destroy GUI system\n");

    destroy_bitmap(gui.hsImage);

    TRACE("Destroy GUI system\n");
}

//function to update the gui
void gui_update()
{
    //cursor.enabled = true;
    
    //reset gui hotspot image
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
        case GUI_ABOUT_STATE:
            break;
        case GUI_EXIT_STATE:
            //draw hotspot state zone
            draw_sprite(gui.hsImage, gui.hsImageExit , GUI_CONTENT_X, GUI_CONTENT_Y);
            break;
        case GUI_EXIT_TITLE_STATE:
            game.state = RESTART_STATE;
            stop_music();
            stop_sound();
            sfx[SFX_GAME_VOICE].stop = true;
            game_fade_out(FADE_DEFAULT_SPEED);
            break;
        case GUI_EXIT_DOS_STATE:
            game.state = EXIT_STATE;
            game_fade_out(FADE_DEFAULT_SPEED);
            break;
        case GUI_MAIN_STATE:
            #ifdef DEBUGMODE
                //draw hotspot debug zone
                draw_sprite(gui.hsImage, (BITMAP *)gameDataFile[gd_guiDebugHs].dat , GUI_CONTENT_X, GUI_CONTENT_Y);
            #endif
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
                    textprintf_ex(buffer, gameFont[2], gui.x + GUI_CONTENT_X + GUI_SLOTS_X, gui.y + GUI_CONTENT_Y + GUI_SLOTS_Y + (GUI_SLOTS_Y_SPACING * i), GUI_SEL_SLOT_TEXT_COLOR, -1, "%i.%s", i + 1, saveDate);
                }
                else
                    //draw savegame text (bright)
                    textprintf_ex(buffer, gameFont[2], gui.x + GUI_CONTENT_X + GUI_SLOTS_X, gui.y + GUI_CONTENT_Y + GUI_SLOTS_Y + (GUI_SLOTS_Y_SPACING * i), makecol(255,255,255), -1, "%i.%s", i + 1, saveDate);
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
                    textprintf_ex(buffer, gameFont[2], gui.x + GUI_CONTENT_X + GUI_SLOTS_X, gui.y + GUI_CONTENT_Y + GUI_SLOTS_Y + (GUI_SLOTS_Y_SPACING * i), GUI_SEL_SLOT_TEXT_COLOR, -1, "%i.%s", i + 1, saveDate);
                }
                else
                    //draw savegame text (bright)
                    textprintf_ex(buffer, gameFont[2], gui.x + GUI_CONTENT_X + GUI_SLOTS_X, gui.y + GUI_CONTENT_Y + GUI_SLOTS_Y + (GUI_SLOTS_Y_SPACING * i), makecol(255,255,255), -1, "%i.%s", i + 1, saveDate);
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
            game_write("Out Of Cash\n(Sin Blanca)\n \nProgramado por Warrior\n \nWarcom Soft.2025", gui.x + GUI_CONTENT_X + (GUI_CONTENT_W>>1), gui.y + GUI_CONTENT_Y, 74, 2);
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
        case GUI_MAIN_STATE:
            #ifdef DEBUGMODE
            //draw gui contents
            draw_sprite(buffer, (BITMAP *)gameDataFile[gd_guiDebug].dat, gui.x + GUI_CONTENT_X, gui.y + GUI_CONTENT_Y);
            #endif
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
    static int iniPos = 0;
    static int lastLine = 0;
    static int scrollDelay = 0;
    
    char strScroll[MAX_DIALOG_LINE_SCROLL + 1];
    
    if (dialog.state == DIALOG_ST_SELECT)
    {
        //run all the lines of the select dialog node
        for (int i = 0; i < dialog.nodeNumLines; i++)
        {        
            //if actual draw line is the hightlighted line
            if ((dialog.highlightLine - 1) == i)
            {
                //increment scroll string pos on game tick
                if (gameTick)
                {
                    if (scrollDelay >= DIALOG_TEXT_SCROLL_DELAY)
                    {
                        if ((iniPos + MAX_DIALOG_LINE_SCROLL) <= strlen(dialog.lineText[i]))
                            iniPos++;
                    }
                    else
                        scrollDelay++;
                }

                //compone string scroll substring
                strncpy(strScroll, dialog.lineText[i] + iniPos, MAX_DIALOG_LINE_SCROLL);
                strScroll[MAX_DIALOG_LINE_SCROLL] = '\0';

                //draw scroll dialog line on highlight color
                textprintf_ex(buffer, gameFont[actualFont], 0, HUD_Y + DEBUG_FONT_HEIGHT + (DEBUG_FONT_HEIGHT*i), makecol(255,255,255), -1, "%s", strScroll);

                //reset iniPos string scroll on line change
                if (lastLine != dialog.highlightLine)
                {
                    iniPos = 0;
                    scrollDelay = 0;
                }
                lastLine = dialog.highlightLine;
            }
            else
            {
                //compose string scroll substring
                strncpy(strScroll, dialog.lineText[i], MAX_DIALOG_LINE_SCROLL);
                strScroll[MAX_DIALOG_LINE_SCROLL] = '\0';
            
                //draw dialog line on regular color
                textprintf_ex(buffer, gameFont[actualFont], 0, HUD_Y + DEBUG_FONT_HEIGHT + (DEBUG_FONT_HEIGHT*i), makecol(200,200,200), -1, "%s", strScroll);
            }
        }
   
        //reset dialog choices
        dialog.nodeNumLines = 0;
    }
    else
    {
        lastLine = 0;
        iniPos = 0;
        scrollDelay = 0;
    }
}

//function to init sfx sound system
void sfx_init()
{
    //init all sfx voices
    for (int i = 0; i < SFX_NUM_VOICES; i++)
    {
        //get soundcard voice (reallocate if exists)
        if (!voice_check(i))
        {
            int voice = allocate_voice((SAMPLE*)soundDataFile[sd_take].dat);
            TRACE("SFX voice %i allocated to soundcard voice %i\n", i, voice);
        }
        else
            reallocate_voice(i, (SAMPLE*)soundDataFile[sd_take].dat);

        sfx[i].sampleId = sd_take;

        //init channel flags
        sfx[i].playing     = false;
        sfx[i].paused      = false;
        sfx[i].pause       = false;
        sfx[i].stop        = false;
        sfx[i].finished    = false;
        sfx[i].position    = -1;
    }

    TRACE("SFX system initialized\n");
}

//function to destroy sfx system (free resources)
void sfx_destroy()
{
    TRACE("Destroy SFX system\n");
    
    //free all sfx voices
    for (int i = 0; i < SFX_NUM_VOICES; i++)
    {
        //get soundcard voice (reallocate if exists)
        if (!voice_check(i))
            deallocate_voice(i);
    }

    TRACE("SFX system destroyed\n");
}

//function to update sfx sound system
void sfx_update()
{
    for (int i = 0; i < SFX_NUM_VOICES; i++)
    {
        //handles sound pause
        if (sfx[i].pause)
        {
            if (sfx[i].playing)
            {
                //do the stop/pause
                voice_stop(i);
                //set flag
                sfx[i].paused = true;
            }
            else
                //clear flag
                sfx[i].pause = false;
        }
    
        //handles sound resume
        if (!sfx[i].pause && sfx[i].paused)
        {
            //resume sound if was started
            if (sfx[i].position >= 0)
                voice_start(i);
            //clear flag
            sfx[i].paused = false;
        }
    
        //handles sound stop
        if (sfx[i].stop)
        {
            if (sfx[i].playing)
                //do sound stop
                voice_stop(i);
            //clear flag
            sfx[i].stop = false;
            //set flag
            sfx[i].finished = true;
        }
    
        //handles clear sound playing flag
        if (sfx[i].playing && !sfx[i].paused)
        {
            //stores sound position
            sfx[i].position = voice_get_position(i);
            //clear flag when sound finished
            if (sfx[i].position == -1)
            {
                sfx[i].playing = false;
                sfx[i].finished = true;
            }
        }
    }
}

//function to play a sound
void sfx_play(uint16_t soundId, uint8_t voice, bool rndFreq)
{
    ASSERT(voice < SFX_NUM_VOICES);
    ASSERT(soundId < sd_COUNT);

    //reallocate the sample on select voice of selected channel
    reallocate_voice(voice, (SAMPLE*)soundDataFile[soundId].dat);
    sfx[voice].sampleId = soundId;

    //randomize frequency
    if (rndFreq)
    {
        //get a random percent variation from twice of SFX_FREQ_RND_PERCENT (half for negative, half for positive)
        int freqVariation = (rand() % (SFX_FREQ_RND_PERCENT * 2));

        //get sample original frequency
        int sampleFreq = voice_get_frequency(voice);
        TRACE("Original freq: %iHz | ", sampleFreq);

        //calculate new frequency
        float newFreq;
        //if variation is below half
        if (freqVariation < SFX_FREQ_RND_PERCENT)
        {
            //sub the percentage variation to original freq
            newFreq = (float)sampleFreq - ((float)sampleFreq * ((float)freqVariation / 100.0));
            TRACE("Variation: -%i%% | ", freqVariation);
        }
        else
        {
            //add the percentage variation to original freq
            newFreq = ((float)sampleFreq * ((float)(freqVariation - SFX_FREQ_RND_PERCENT) / 100.0)) + (float)sampleFreq;
            TRACE("Variation: +%i%% | ", (freqVariation - SFX_FREQ_RND_PERCENT));
        }

        //set the new frequency
        voice_set_frequency(voice, (int)newFreq);
        TRACE("New freq: %iHz\n", (int)newFreq);
        
    }
    
    //start sample allocated on voice channel
    voice_start(voice);

    //set flag
    sfx[voice].playing = true;
    sfx[voice].finished = false;
}

//function to play midi music
void play_music(uint16_t musicId, int loop)
{
    //stop actual music
    stop_music();

    //load index music index
    TRACE("Load music data file object\n");
    actualRoom.musicDataFile  = load_datafile_object_indexed(actualRoom.musicDataFileIndex, musicId);
    
    //play midi
    TRACE("Play midi music\n");
    play_midi((MIDI *)actualRoom.musicDataFile[0].dat, loop);
}

//function to stop midi music
void stop_music()
{
    //stop actual music
    TRACE("Stopping midi\n");
    stop_midi();
}

//function to init credits
void credits_init()
{
    strcpy(credits.line[0], "Un juego de:");
    strcpy(credits.line[1], "Warrior");
    strcpy(credits.line[2], "Programaci¢n");
    strcpy(credits.line[3], "Warrior");
    strcpy(credits.line[4], "Gr ficos");
    strcpy(credits.line[5], "Warrior");
    strcpy(credits.line[6], "M£sica");
    strcpy(credits.line[7], "Warrior");
    strcpy(credits.line[8], "Sonido");
    strcpy(credits.line[9], "Warrior");
    strcpy(credits.line[10], "Productor ejecutivo");
    strcpy(credits.line[11], "Emm... Warrior");
    strcpy(credits.line[12], "Productor asociado");
    strcpy(credits.line[13], "Umm ¨Warrior?");
    strcpy(credits.line[14], "Marketing");
    strcpy(credits.line[15], "­Ah si! Warrior");
    strcpy(credits.line[16], "Contabilidad");
    strcpy(credits.line[17], "Casio");    
    strcpy(credits.line[18], "Control de calidad");
    strcpy(credits.line[19], "Cali..¨qu‚?");

    strcpy(credits.line[20], "GRACIAS POR JUGAR");

    //init credits position and color
    for (int i = 0; i < CREDITS_NUM - 1; i+=2)
    {
        if (i == 0)
        {
            credits.pos_y[i] = RES_Y + 10;
        }
        else
            credits.pos_y[i] = credits.pos_y[i - 1] + CREDITS_GROUP_SPACING;
    
        credits.pos_y[i + 1] = credits.pos_y[i] + CREDITS_LINE_SPACING;
        
        credits.color[i]    = PURPLE_COLOR;
        credits.color[i+1]  = WHITE_COLOR;    
    }

    //init final message credits pos and color
    credits.pos_y[20] = credits.pos_y[20 - 1] + ((CREDITS_GROUP_SPACING + CREDITS_LINE_SPACING) * 4);
    credits.color[20] = WHITE_COLOR;
}

//function to draw credits
void credits_draw()
{
    for (int i = 0; i < CREDITS_NUM; i++)
    {
        if (credits.pos_y[i] > - 12)
        {
            if (seq.step == 0)
                credits.pos_y[i] -= gameTick;
            if (credits.pos_y[i] <= 248)
                game_write(credits.line[i], C_X, credits.pos_y[i], credits.color[i], 4);
        }
    }

    //if final credit on center screen
    if (credits.pos_y[20] <= (RES_Y>>1) && seq.step == 0)
    {
        //next end sequence
        seq.step = 1;
    }

    //if (credits.pos_y[CREDITS_NUM - 1] <= -12)
    //    set_game_flag(END_CREDITS_FLAG);
}

//function to init playTime
void playTime_init()
{
    playTime.centSeconds    = 0;
    playTime.minutes        = 0;
    playTime.hours          = 0;
}

//function to update playTime
void playTime_update()
{
    if (gameTick)
    {
        if (playTime.centSeconds >= 600)
        {
            if (playTime.minutes >= 59)
            {
                playTime.hours++;
                playTime.minutes = 0;
            }
            else
                playTime.minutes++;

            playTime.centSeconds = 0;
        }
        else
            playTime.centSeconds++;
    }
}
END_OF_MAIN()
