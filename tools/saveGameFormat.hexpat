#pragma little endian

struct game
{
    s32 state;
    
    s16 actualRoom;
    s16 nextRoom;
    //enter room position assigned by change_room_pos()
    s16 room_pos_x;
    s16 room_pos_y;
    s32 roomMusicPos;
    bool fadeIn;
    bool fadeOut;
    bool exit;
    u8 flags[32];  //32 bytes = 255 bit flags
    padding[1];
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
    padding[3];
};

struct inventory
{
    u8 numObjects;
    u8 objIndex[32];
    u8 page;
    bool refresh;
    padding[2];
};

struct cursor
{
    //name of the pointed object (change for hotspot)
    char objectName[25];
    char invObjName[25];
    padding[1];
    //selected action/verb
    s32 selectedVerb;
    //selected use with object inventory
    s16 invObject;
    //counters
    s16 dblClickTimer;
    //flags
    bool enabled;
    bool click;
    bool dblClick;
    bool rightClick;
    bool memClick;
    bool memRightClick;
    bool memDblClick;
    bool evalueDblClick;
    bool clicking;
    bool rightClicking;
    padding[2];
};

//global room script structure
struct roomScript
{
    s16 object;
    s16 invObject;
    s16 verb;
    s16 step;
    s16 lastStep;
    s16 stepTime;
    s16 hsX;
    s16 hsY;
    u8 type;
    bool active;
    bool scriptAssigned;
    padding[1];
};

//message structure
struct msg
{
    char msg[50];
    padding[2];
    s16 msgTime;
    bool msgFinished;
    bool msgActive;
    u16 actorTalk;
    padding[2];
};

//animation structure
struct tAnimation
{
    s16 frame;
    s16 lastFrame;
    s16 frameTime;
};

//talk structure for actors
struct tActorTalk
{
    s16 msgX;
    s16 msgY;
    u8 textColor;
    bool talking;
};

//player struct
struct player{
    s32 x;
    s32 y;
    s32 vX;
    s32 vY;
    s32 scale;
    s16 destX;
    s16 destY;
    s32 state;
    s32 prevState;
    tAnimation animation;
    tActorTalk talk;
    u8 lookDir;
    bool moveFast;
    bool flip;
};

struct savegame
{
    u8 version;
    char saveDate[20];
    gameConfig gameConfigData;
    game gameData;
    inventory invData;
    cursor cursorData;
    roomScript roomScriptData;
    msg msgData;
    player playerData;
};

savegame savegame @ 0x00;