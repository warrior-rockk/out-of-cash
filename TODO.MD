# TO-DO

- [ ] Gameplay:
    * ABOUT menu?
    * sound of cassette playing?

    * more look descriptions on stationery?
    * more dialog lines on actors
    * open oven and fridge kitchen?
    * front player?
    * front player when nerd says nobody plays point and click games?

- [ ] Funtion to move player to specific velocity?
- [ ] No twice replace_unicode (game_write and say_actor)
- [ ] Custom fade in/out with get_color / set_color?
    RGB color;
       
       if (gameTick)
       {
       for (int i = 1; i < 256; i++)
        {
            get_color(i, &color);
            
            color.r = color.r >= 1 ? color.r - 1 : 0;
            color.g = color.g >= 1 ? color.g - 1 :  0;
            color.b = color.b >= 1 ? color.b - 1 : 0;

            set_color(i, &color);
        }
        }
- [ ] Text font size configurable?
    gameFont[0] = font; <- system font. Not to bad for text but it's DOS generic
    char *fontName2[1] = {"verdana8", NULL}; <-very thick. Delete
    ->char *fontName3[2] = {"verdana8Bold", NULL}; <-good normal font for say
    char *fontName4[3] = {"verdana9", NULL}; <-very tick. Delete
    char *fontName5[4] = {"verdana9Bold", NULL}; <- good big font for say (configurable?)
    char *fontName1[5] = {"gameFont", NULL}; <-smallest font. Is the font of verbs buttons
- [ ] Time base below 100ms?
- [ ] Different player walk speed based on configured speed
- [ ] Remove lightsOff of rooms data structure
- [ ] Bug: continue actual sentence say when load savegame (I'm not sure because the new talk system)
- [ ] Music smooth transition (music fades and screen fades?)
- [ ] Real A* Pathfinding?
- [ ] Separate renderer
- [ ] Hud structure doesn't need BITMAP array of selected verbs images. Could use the
internal grabber number def (same for gui)
- [ ] BUG: player walks slow on game start?

- [X] Bug on load game when actor talking
- [X] no click bypass text near to end time
- [X] On exit: destroy bitmaps and game modules exit (deallocate voices, etc..)
- [X] Free fonts
- [X] Delay on text dialog selection scroll?
- [X] End game
- [X] Don't use ints (32 bits). Use uint16_t or int16_t instead
- [X] Room definition/script tool
- [X] Sound effects
- [X] Add take 2 random
- [X] Block cursor while script running?
- [X] New object focused on inventory (blink?. No, go to last inventory page)
- [X] Bug on first game script_move_player_to() after intro
- [X] fade in/out speed parameter all functions (bug on engine.h on function game_fade_off)
- [X] Bug: say text errors on unique frame? (I think is debug text info)
- [X] Bug: incorrect frames on animations
- [X] Scroll long dialog line
- [X] Bug selecting inexistent dialog lines
- [X] Bug on lights off when reset game
- [X] Debug when load game with room scroll
- [X] Spanish characters on system font
- [X] Custom fonts
- [X] debug mode for jump to room
- [X] Bug: show_debug overwrite lines
- [X] Reset roomScript vars on room change to prevent gameplay blocking because missing end_script()
- [X] Remove borders for small rooms and draw on center of screen
- [X] Draw borders on front layer for hide player?
- [X] default verb for inventory (LOOK or USE WITH)
- [X] Debug: use arrows to move room object
- [X] Auto-separate say lines?
- [X] BUG: actors text off-positions
- [X] Debug keys mem (key handler scalable?)
- [X] Avoid pointers on savegame structure
- [X] Save and resume music on game save/load
- [X] Change lastRoom by actualRoom, nextRoom
- [X] Talk system
- [X] Bug: player visible off-screen on PAUSE and DIALOG state
- [X] global.h for fast compiling
- [X] Separate game.h data to engine.h to avoid recompile all the objects that not are related (like gui defines)
- [X] Audio volume
- [X] Datafile for songs and the rooms uses song id
- [X] Control song playing / room transition / song continues
- [X] Bug: exception on exit
- [X] Bug: save don't work
- [X] Fixed player stuck
- [X] Dialog system
- [X] Pass front layer to objects
- [X] BUG: inventory object spotted on status bar
- [X] Structure game resources
- [X] Separate grabber file data.h. The name was temporaly.
- [X] Fix msg duration consistency
- [X] Highlight default verbs
- [X] Iterate verb selection
- [X] Game state / game loop (second iteration)
- [X] Room enter / room init events
- [X] On-screen debug system
- [X] Fix on exit error
- [X] Handle game errors
- [X] Use fades for transitions
- [X] Use byte-bools and stdbool.h
- [X] Use uint8_t when value < 256
- [X] Bit mask macros for flags
- [X] Game struct
- [X] Game update (first iteration)
- [X] Player?
- [X] Game GUI
- [X] Save / Load (first iteration)
- [X] Game Config
- [X] Fix ints for movement
- [X] Animation system
- [X] Place text talk on character
- [X] Multi-line text (char 10 = \n)
- [X] Player scale map (first iteration)
- [X] Temporaly? collision map (fix blockings)
- [X] Init room position and dynamic position based on previous room (room has default start
position but can be overwritten by change_room start position
- [X] Room draw layers (sustitute bitmap to objects to save memory?
- [X] Double click for quick walk
- [X] Default right click action
- [X] Room objects
- [X] Inventory
- [X] Refactor code (separate cursor update function)
- [X] Flip on walk and look objects
- [X] Rethink object room array index for better identification (maybe defines for object
array indexes and change get_object_name using this defines...)
- [X] Game flags system
- [X] Move_player_to_target()
- [X] Get Object function generic
- [X] Talk wait
- [X] Define DEBUGMODE on 1 file. Passed on compiler options -DDEBUGMODE
- [X] Bug: right click on default verb don't work on first
- [X] Bug: verb on inventary: incorrect index
- [X] Bug: don't use object inventory on inventory
- [X] Bug: reset use with verb when finished with item
- [X] Player: change state bools with general state var
- [X] Bug: player talks on pause
- [X] Player: improve state-animation system and external state change
