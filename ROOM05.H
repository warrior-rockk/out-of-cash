/*
=========================================================
 Room Number:   05
 Room Name:     05_stationery
=========================================================
*/

#ifndef H_ROOM05
#define H_ROOM05

#include <allegro.h>
#include "anim.h"
//include room datafile header data
#include "R05DATA.H"

//define room properties
#define R05_START_POS_X         132
#define R05_START_POS_Y         64
#define R05_ROOM_NUM_OBJS       10
#define R05_MUSIC_ID            0
#define R05_FADE                false
#define R05_LIGHTS_OFF          false

//define room data (compose room properties and function pointers)
#define R05_DATA R05_START_POS_X, R05_START_POS_Y, R05_ROOM_NUM_OBJS, R05_MUSIC_ID, R05_FADE , R05_LIGHTS_OFF , &r05_room_init, &r05_room_update, &r05_get_hotspot_name, &r05_get_default_hotspot_verb, &r05_get_object_info

//define object array alias
#define R05_EMPLOYEER_OBJ_ID        0
#define R05_PRINTEDSCHPHOTO_OBJ_ID  1
#define R05_SHEETS_OBJ_ID           2
#define R05_PRINTEDSCH_OBJ_ID       3
#define R05_PRINTEDPHOTO_OBJ_ID     4
#define R05_PHOTOCOPY_OBJ_ID        5
#define R05_SHEETSPHOTO_OBJ_ID      6
#define R05_CARTRIDGEFULL_OBJ_ID    7
#define R05_CARTRIDGEEMPTY_OBJ_ID   8
#define R05_PRINTER_OBJ_ID          9

//define object data (objId, x, y, animId, active, layer)
#define R05_OBJ_0           r05d_objAnimIdle,   261, 71,  1, true, 0
#define R05_OBJ_1           r05d_objPrintedSchPhoto,   244, 103,  0, false, 0
#define R05_OBJ_2           r05d_objSheets,   254, 85,  0, true, 0
#define R05_OBJ_3           r05d_objPrintedSch,   244, 103,  0, false, 0
#define R05_OBJ_4           r05d_objPrintedPhoto,   244, 103,  0, false, 0
#define R05_OBJ_5           r05d_objPhotocopy,   192, 78,  0, true, 0
#define R05_OBJ_6           r05d_objSheetsPhoto,   254, 85,  0, false, 0
#define R05_OBJ_7           r05d_objCartridgeFull,   251, 91,  0, true, 0
#define R05_OBJ_8           r05d_objCartridgeEmpty,   251, 91,  0, false, 0
#define R05_OBJ_9           r05d_objPrintSchd1,       251, 94,  2, false, 0

//define room animations
#define R05_NUM_ANIMATIONS  2

//define animations with id 1
#define R05_ANIM_TALK           r05d_objTalk1, r05d_objTalk9, 1, ANIM_PING_PONG
#define R05_ANIM_PRINTING       r05d_objPrinting1, r05d_objPrinting6, 3, ANIM_PING_PONG
#define R05_ANIM_COMPUTER_TALK  r05d_objComputerTalk1, r05d_objComputerTalk6, 1, ANIM_PING_PONG
#define R05_ANIM_WALK           r05d_objWalk1, r05d_objWalk4, 1, ANIM_ONCE
#define R05_ANIM_WALK_REVERSE   r05d_objWalkReverse1, r05d_objWalkReverse4, 1, ANIM_ONCE

//define animations with id 2
#define R05_ANIM_PRINT_SCHD     r05d_objPrintSchd1, r05d_objPrintSchd22, 1, ANIM_ONCE

//define room scripts
#define R05_WELLCOME_SCRIPT 256

//hotspot code room enumeration
enum r05_hotspotCode{
    r05_door    = 32,
    r05_folders    = 39,
    r05_stationeryMaterial    = 41,
    r05_photocopies    = 33,
    r05_paper    = 36,
    r05_cartridge    = 35,
    r05_printer    = 42,
    r05_printedPaper    = 34,
    r05_mouse    = 37,
    r05_monitor    = 38,
    r05_employee    = 44,
};

//declare and define room objects array
static tObject r05_object[R05_ROOM_NUM_OBJS] =
{
    {R05_OBJ_0},
    {R05_OBJ_1},
    {R05_OBJ_2},
    {R05_OBJ_3},
    {R05_OBJ_4},
    {R05_OBJ_5},
    {R05_OBJ_6},
    {R05_OBJ_7},
    {R05_OBJ_8},
    {R05_OBJ_9},
};

//declare room objects animations array
static tAnimation r05_animations[R05_NUM_ANIMATIONS];

//declare room dialog actor
static tActorTalk r05_dialogActor = {244, 50, 70, false};

//declare room functions called from game
void r05_get_hotspot_name(uint8_t colorCode, char *s);
enum verbs r05_get_default_hotspot_verb(uint8_t colorCode);
tObject* r05_get_object_info(uint8_t numObject);
void r05_room_init();
void r05_room_update();

//declare internal functions
void r05_update_room_objects();
void r05_update_room_script();
void r05_update_dialog_selection();
#endif
