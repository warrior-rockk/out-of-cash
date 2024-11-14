#ifndef H_ROOMS
#define H_ROOMS

#include <stdbool.h>
//include all rooms
#include "room00.h"
#include "room01.h"
#include "room02.h"
#include "room03.h"
#include "room04.h"
#include "room05.h"
#include "room06.h"
#include "room07.h"
#include "room08.h"

#define NUM_GAME_ROOMS          13

//room data structure array
typedef struct tRoomData
{
    //default start player position on room
    int start_pos_x;
    int start_pos_y;
    //room num objects
    uint8_t room_num_objects;
    //room music
    uint8_t roomMusicId;
    //room properties
    bool fadeRoom;
    bool lightsOff;
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

//initialize room data
static tRoomData roomData[NUM_GAME_ROOMS] = {
    {R00_DATA},
    {R01_DATA},
    {R02_DATA},
    {R03_DATA},
    {R04_DATA},
    {R05_DATA},
    {R06_DATA},
    {R07_DATA},
    {R08_DATA},
};

#endif  //H_ROOMS
