#include <stdint.h>
#include <stdbool.h>
#include "anim.h"
//#include "game.h" //TESTING gameTick on anim.h as external

//function to play animation. Recives pointer to struct actor animation
//Returns true when animation finished (ONCE mode) or repeats (LOOP mode)
bool play_animation(tAnimation *animation, int startFrame, int endFrame, int speed, uint8_t mode)
{
    bool animFinished = false;

    //reset animation state
    if (animation->frame > endFrame || animation->frame < startFrame)
    {
        animation->frame = startFrame;
        animation->lastFrame = startFrame;
        animation->frameTime = 0;
        animation->reverse = false;
    }
                
    //reset frame time on frame change
    if (animation->lastFrame != animation->frame)
    {
        animation->frameTime = 0;
        animation->lastFrame = animation->frame;
    }

    //increment frame time
    if (gameTick)
        animation->frameTime += 1;
    
    //if frame time reached
    if (animation->frameTime >= speed)
        //if not last frame
        if (animation->frame < endFrame)
            //next frame
            if (!animation->reverse)
                animation->frame += 1;
            else
                animation->frame -= 1;
        else if (animation->frame == startFrame && mode == ANIM_PING_PONG)
            animation->reverse = false;
        else if (mode == ANIM_LOOP)
        {
            //repeat animation
            animation->frame = startFrame;
            animFinished = true;
        }
        else if (mode == ANIM_PING_PONG)
        {
            //reverse animation
            animation->reverse = true;
            animation->frame -=1;
            animFinished = true;
        }
        else
           animFinished = true;
           
    return animFinished;
}
