#ifndef H_ANIM
#define H_ANIM

#include "globals.h"
//include game animations
#include "anims.h"

//animation modes
#define ANIM_LOOP       0
#define ANIM_ONCE       1

typedef struct tAnimation
{
    int16_t frame;
    int16_t lastFrame;
    int16_t frameTime;
} tAnimation;

//declare functions
bool play_animation(tAnimation *animation, int startFrame, int endFrame, int speed, uint8_t mode);
#endif  //H_ANIM
