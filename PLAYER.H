#ifndef H_PLAYER
#define H_PLAYER

#include <stdbool.h>
#include "anim.h"

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

//player states
enum playerStates{
    player_st_idle,
    player_st_moving,
    player_st_talking,
    player_st_taking
};

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
    enum playerStates state;
    bool moveFast;
    bool flip;
    uint8_t lookDir;
    tAnimation animation;
} player;

//function declarations
void player_init();
void player_update();
void player_update_pos();
void player_update_animation();
void player_update_scale();
void player_draw();

#endif
