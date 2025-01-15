#ifndef H_PLAYER
#define H_PLAYER

#include <stdbool.h>
#include "PDATA.H"
#include "engine.h"
#include "anim.h"

#define PLAYER_TEXT_COLOR   30
#define PLAYER_FAST_SPEED   1
#define PLAYER_POS_X_OFFSET 0
#define PLAYER_POS_Y_OFFSET 20

//scale values
#define SCALE_INI_COLOR     32
#define NO_SCALE_COLOR      247
#define SCALE_COLOR_SCALE   0.2
#define PLAYER_MIN_SCALE    SCALE_COLOR_SCALE
#define PLAYER_MAX_SCALE    3.0

//player states
enum playerStates{
    player_st_idle,
    player_st_moving,
    player_st_talking,
    player_st_taking,
    player_st_animating,
};

//player struct
struct player{
    //BITMAP *image[pd_COUNT];
    //BITMAP *tempImage;
    fixed x;
    fixed y;
    fixed vX;
    fixed vY;
    fixed scale;
    int16_t destX;
    int16_t destY;
    enum playerStates state;
    enum playerStates prevState;
    tAnimation animation;
    tActorTalk talk;
    uint8_t lookDir;
    bool moveFast;
    bool flip;
} player;

struct playerData{
    BITMAP *image[pd_COUNT];
    BITMAP *tempImage;
} playerData;

//function declarations
void player_init();
void player_destroy();
void player_update();
void player_update_pos();
void player_update_animation();
void player_update_scale();
void player_draw();

#endif
