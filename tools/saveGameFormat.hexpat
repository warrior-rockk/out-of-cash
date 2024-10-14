struct game
{
    s16 state;
    s16 actualRoom;
    s16 nextRoom;
    //enter room position assigned by change_room_pos()
    s16 room_pos_x;
    s16 room_pos_y;
    s32 roomMusicPos;
    bool fadeIn;
    bool fadeOut;
    bool exit;
    u8 flags[255];  //32 bytes = 255 bit flags
};

struct gameConfig
{
    #define CONFIG_TEXT_SPEED_MIN   1
    #define CONFIG_TEXT_SPEED_MAX   255
    u8 textSpeed;
    #define CONFIG_PLY_SPEED_MIN    1
    #define CONFIG_PLY_SPEED_MAX    100
    u8 playerSpeed;
    u8 musicVolume;
    u8 soundVolume;
};

struct inventory
{
    //BITMAP *image;
    u8 numObjects;
    u8 objIndex[32];
    u8 page;
    bool refresh;
};

struct savegame
{
    u8 version;
    char saveDate[20];
    gameConfig gameConfigData;
    game gameData;
    inventory invData;
    /*struct cursor cursorData;
    struct roomScript roomScriptData;
    struct msg msgData;
    struct player playerData;*/
};

savegame savegame @ 0x00;