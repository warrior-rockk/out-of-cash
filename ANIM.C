#include <stdint.h>
#include <stdbool.h>
#include "anim.h"
#include "game.h"

//function to play animation. Recives pointer to struct actor animation
//Returns true when animation finished (ONCE mode) or repeats (LOOP mode)
bool play_animation(tAnimation *animation, int startFrame, int endFrame, int speed, uint8_t mode)
{
    bool animFinished = false;

    //set start frame
    //if (animation->frame > endFrame || animation->frame < startFrame)
    if (!animation->animating)
    {
        animation->animating = true;
        animation->frame = startFrame;
        animation->frameTime = 0;
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
            animation->frame += 1;
        else if (mode == ANIM_LOOP)
        {
            //repeat animation
            animation->frame = startFrame;
            animFinished = true;
        }
        else
           animFinished = true;
           
    return animFinished;
}
