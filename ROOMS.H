#ifndef H_ROOMS
#define H_ROOMS

#include <stdbool.h>
//include all rooms
#include "room01.h"
#include "room02.h"

//room data structure array
typedef struct tRoomData
{
    //default start player position on room
    int start_pos_x;
    int start_pos_y;
    //room num objects
    uint8_t room_num_objects;
    
    //function pointer to init room
    void (*room_init)(void);
    //function pointer to update room
    void (*room_update)(void);
    //function pointer to get hotspot name
    void (*room_get_hotspot_name)(uint8_t, char *s);
    //function pointer to get default hotspot verb
    enum verbs (*room_get_default_hotspot_verb)(uint8_t);
    //function pointer to get object info
    tObject* (*room_get_object_info)(uint8_t numObject);
} tRoomData;


/*
//initialize of room data
tRoomData roomData[2] = {
    [0].start_pos_x = 170,
    [0].start_pos_y = 100,
    [0].room_num_objects = R01_ROOM_NUM_OBJS,
    [0].room_init = &r01_room_init;
    [0].room_update = &r01_room_update;
    [0].room_get_hotspot_name = &r01_get_hotspot_name;
    [0].room_get_default_hotspot_verb = &r01_get_default_hotspot_verb;
    [0].room_get_object_info = &r01_get_object_info;

    [1].start_pos_x = 179,
    [1].start_pos_y = 117,
    [1].room_num_objects = R02_ROOM_NUM_OBJS,
    [1].room_init = &r02_room_init;
    [1].room_update = &r02_room_update;
    [1].room_get_hotspot_name = &r02_get_hotspot_name;
    [1].room_get_default_hotspot_verb = &r02_get_default_hotspot_verb;
    [1].room_get_object_info = &r02_get_object_info;
};
*/

//other initialize of room data
tRoomData roomData[NUM_GAME_ROOMS] = {
    {R01_DATA},
    {179, 117, R02_ROOM_NUM_OBJS, &r02_room_init, &r02_room_update, &r02_get_hotspot_name, &r02_get_default_hotspot_verb, &r02_get_object_info}
};

#endif  //H_ROOMS
