#ifndef H_GAME_FLAGS
#define H_GAME_FLAGS

//definition of global game flags index
/*#define GOT_CASSETTE        0
#define GOT_GUITAR          1
#define USED_COMPUTER       2
#define USED_CASSETTE       3
#define STEREO_ON           4

#define BATH_CLOSET_OPEN    5
#define BATH_DOOR_OPEN      6
#define GOT_GEL             7
#define BATH_MIRROR_MSG     8
#define BATH_LIGHT_OFF      9

#define CORRIDOR_MIRROR_MSG 10

#define PRINTED_SCHOOL_SCHEDULE 11
#define PRINTED_PHOTOCOPY       12

#define GOT_CLOCK               13
#define FLAG_GOT_SPATULA        14
#define FLAG_GOT_OAT            15
*/
enum gameFlags{
    GOT_CASSETTE_FLAG,
    GOT_GUITAR_FLAG,
    USED_COMPUTER_FLAG,
    USED_CASSETTE_FLAG,
    STEREO_ON_FLAG,
    GOT_EMPTY_CARTRIDGE_FLAG,
    GOT_BOOK,
    GOT_COIN,
    
    BATH_CLOSET_OPEN_FLAG,
    BATH_DOOR_OPEN_FLAG,
    GOT_GEL_FLAG,
    BATH_MIRROR_MSG_FLAG,
    BATH_LIGHT_OFF_FLAG,
    
    CORRIDOR_MIRROR_MSG_FLAG,
    
    GOT_CLOCK_FLAG,
    GOT_SPATULA_FLAG,
    GOT_OAT_FLAG,
    
    GOT_ANSWERS_FLAG,
    
    GOT_BRAIN_FLAG,
    GOT_KNIFE_FLAG,
    
    GOT_PHOTOCOPY_FLAG,
    GOT_SCHOOL_SCHEDULE_FLAG,
    GOT_FOLDER_FLAG,
    GOT_FULL_CARTRIDGE_FLAG,
    
    GOT_PAINT_BUCKET_FLAG,
    
    GOT_SHIRT,
    GOT_JEANS,
    
};



//definition of global game numeric vars
#define VAR_BULLETIN_BOARD      0

enum gameVars{
    BULLETIN_BOARD_VAR,
};

#endif //H_GAME_FLAGS
