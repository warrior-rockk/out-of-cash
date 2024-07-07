#ifndef H_PLAYER
#define H_PLAYER

#include <stdbool.h>

//player struct
struct player{
    BITMAP *image[11];
    fixed x;
    fixed y;
    fixed vX;
    fixed vY;
    int destX;
    int destY;
    bool moving;
    bool talking;
    int frame;
} player;

//function declarations
void player_update();
void player_draw();

#endif
