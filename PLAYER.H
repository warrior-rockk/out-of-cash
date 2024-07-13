#ifndef H_PLAYER
#define H_PLAYER

#include <stdbool.h>

#define PLAYER_FAST_SPEED   1

//scale values of scale map
#define SCALE_1_COLOR   32
#define SCALE_2_COLOR   33
#define SCALE_3_COLOR   34
#define SCALE_4_COLOR   35

#define SCALE_1_VALUE   0.5
#define SCALE_2_VALUE   0.7
#define SCALE_3_VALUE   1.0
#define SCALE_4_VALUE   1.5

//player struct
struct player{
    BITMAP *image[11];
    BITMAP *tempImage;
    fixed x;
    fixed y;
    fixed vX;
    fixed vY;
    int destX;
    int destY;
    fixed scale;
    bool moving;
    bool moveFast;
    bool talking;
    bool flip;
    uint8_t lookDir;
    int frame;
} player;

//function declarations
void player_init();
void player_update();
void player_draw();

#endif
