# TO-DO

- [X] Fix msg duration consistency
- [X] Highlight default verbs
- [X] Iterate verb selection
- [X] Game state / game loop (second iteration)
- [X] Room enter / room init events
- [X] On-screen debug system
- [ ] Iterate On-screen debug system (multiple vars)
- [X] Fix on exit error
- [X] Handle game errors
- [X] Use fades for transitions
- [X] Use byte-bools and stdbool.h
- [X] Use uint8_t when value < 256
- [X] Bit mask macros for flags
- [X] Game struct
- [ ] Game update
- [X] Player?
- [ ] Control song playing / room transition / song continues
- [ ] Game GUI
- [X] Save / Load (first iteration)
- [ ] Game Config
- [X] Fix ints for movement
- [ ] Headers reestructuration (prevent circular includes) and improve engine structure
- [ ] Animation system
- [ ] Talk system
- [X] Player scale map (first iteration)
- [X] Temporaly? collision map (fix blockings)
- [ ] Real A* Pathfinding?
- [X] Init room position and dynamic position based on previous room (room has default start
position but can be overwritten by change_room start position
- [X] Room draw layers (sustitute bitmap to objects to save memory?
- [X] Double click for quick walk
- [X] Default right click action
- [X] Room objects
- [ ] Inventory

    -draw inv images on grid
    -pagination of inv grid
    -verb on inv object
    -combination of object on hotspot
    -combinaton of inv object on inv object

    8 inv objects x page = 4 columns on 2 rows (16 items max on first iteration)

    hotspot -> enum Name (local on room)
               int colorCode (local on room)

    object  -> definition name (local on room)
               definition of number of bitmap .h (global)

    inventory[0] -> image? description? scriptff?

- [ ] Refactor code
- [X] Flip on walk and look objects
- [X] Rethink object room array index for better identification (maybe defines for object
array indexes and change get_object_name using this defines...)
- [ ] Room definition/script tool
- [X] Game flags system
- [X] Move_player_to_target()
- [X] Get Object function generic
- [X] Talk wait


    
