#ifndef H_ANIM
#define H_ANIM

//include game animations
//#include "anims.h" //for what??

//animation modes
#define ANIM_LOOP       0
#define ANIM_ONCE       1

typedef struct tAnimation
{
    int frame;
    int lastFrame;
    int frameTime;
} tAnimation;

//global vars
extern bool gameTick;

//declare functions
bool play_animation(tAnimation *animation, int startFrame, int endFrame, int speed, uint8_t mode);
#endif  //H_ANIM
