#include <allegro.h>
#include "player.h"
#include "game.h"
#include "engine.h"
#include "utils.h"

//function to init player
void player_init()
{
    player.state            = player_st_idle;
    player.prevState        = player_st_idle;
    player.animation.frame  = 1;

    player.x = 0;
    player.y = 0;
    player.vX = 0;
    player.vY = 0;
    player.destX = 0;
    player.destY = 0;
    player.scale = 0;

    player.moveFast = false;
    player.flip = false;
    player.lookDir = 0;

}

//function to update the player
void player_update()
{
    //updates prevState
    player.prevState = player.state;

    //calls player update functions
    player_update_pos();
    player_update_animation();
    player_update_scale();
}

//function to update player position
void player_update_pos()
{
    bool in_range_x;
    bool in_range_y;
    fixed actualSpeed;
    
    if (player.state == player_st_moving)
    {
        //check destination in range
        in_range_x = in_range(fixtoi(player.x), player.destX, 2);
        in_range_y = in_range(fixtoi(player.y), player.destY, 2);
    
        //assign actual speed
        actualSpeed = fixdiv(itofix(gameConfig.playerSpeed), itofix(100));
        if (player.moveFast)
            actualSpeed = fixmul(actualSpeed,itofix(2));

        //decompose movement
        if (!in_range_x)
        {
            player.vX = fixtoi(player.x) < player.destX ? actualSpeed : -actualSpeed;
        }
        else
            player.vX = itofix(0);
            
        if (!in_range_y)
        {
            player.vY = fixtoi(player.y) < player.destY ? actualSpeed : -actualSpeed;
        }
        else
            player.vY = itofix(0);
    
        //check walk map
        if (getpixel(room[game.actualRoom].wImage, fixtoi(player.x + player.vX), fixtoi(player.y)) == 0)
        {
            player.vX = itofix(0);
        }
    
        if (getpixel(room[game.actualRoom].wImage, fixtoi(player.x) , fixtoi(player.y + player.vY)) == 0)
        {
            player.vY = itofix(0);
        }
    
        //player blocked
        if (player.vX == itofix(0) && player.vY == itofix(0))
        {
            player.state = player_st_idle;
        }
    
        //player on destination
        if (in_range_x && in_range_y)
        {
            player.state = player_st_idle;;
            player.vX = itofix(0);
            player.vY = itofix(0);
            player.x = itofix(player.destX);
            player.y = itofix(player.destY);
        }

    }
    
    //update position
    player.x += player.vX;
    player.y += player.vY;
}

//function to update player animation
void player_update_animation()
{
    //animation state
    switch (player.state)
    {
        case player_st_idle:
            //idle animation
            play_animation(&player.animation, ANIM_PLY_IDLE);
            break;
        case player_st_moving:
            //walk animation
            play_animation(&player.animation, ANIM_PLY_WALK);
            break;
        case player_st_talking:
            //talk animation
            play_animation(&player.animation, ANIM_PLY_TALK);
            break;
        case player_st_taking:
            if (play_animation(&player.animation, ANIM_PLY_TAKE))
            {
                player.state = player_st_idle;
            }
            break;
     }
}

//function to update player scale
void player_update_scale()
{
    //get scale map value
    switch (getpixel(room[game.actualRoom].wImage, fixtoi(player.x) , fixtoi(player.y + player.vY)))
    {
        case SCALE_1_COLOR:
            player.scale = ftofix(SCALE_1_VALUE);
            break;
        case SCALE_2_COLOR:
            player.scale = ftofix(SCALE_2_VALUE);
            break;
        case SCALE_3_COLOR:
            player.scale = ftofix(SCALE_3_VALUE);
            break;
        case SCALE_4_COLOR:
            player.scale = ftofix(SCALE_4_VALUE);
            break;
        default:
            player.scale = ftofix(1.0);
            break;
    }

}

//function to draw the player
void player_draw()
{

    //check player flip
    if (player.vX < fixtoi(0) || player.lookDir == DIR_LEFT)
    {
        player.flip = true;
    }
    else if (player.vX > fixtoi(0) || player.lookDir == DIR_RIGHT)
    {
        player.flip = false;
    }

    //draw player (flipped, escaled, original)
    if (player.flip && player.scale == itofix(1))
    {
        //flipped
        draw_sprite_h_flip(buffer, player.image[player.animation.frame], fixtoi(player.x)-(player.image[player.animation.frame]->w>>1), fixtoi(player.y)-(player.image[player.animation.frame]->h>>1));
    }
    else if (!player.flip && player.scale != itofix(1))
    {
        //scaled

        //calculate scale weight and height
        fixed scaleW = fixmul(itofix(player.image[player.animation.frame]->w),player.scale);
        fixed scaleH = fixmul(itofix(player.image[player.animation.frame]->h),player.scale);
        //draw streched and reposition
        stretch_sprite(buffer, player.image[player.animation.frame], fixtoi(player.x)-(fixtoi(scaleW)>>1), fixtoi(player.y)-(fixtoi(scaleH)>>1),fixtoi(scaleW),fixtoi(scaleH));
    }
    else if (player.flip && player.scale != itofix(1))
    {
        //flipped and scaled
        clear(player.tempImage);
        draw_sprite_h_flip(player.tempImage, player.image[player.animation.frame], 0 , 0);

        //calculate scale weight and height
        fixed scaleW = fixmul(itofix(player.image[player.animation.frame]->w),player.scale);
        fixed scaleH = fixmul(itofix(player.image[player.animation.frame]->h),player.scale);
        //draw streched and reposition
        stretch_sprite(buffer, player.tempImage, fixtoi(player.x)-(fixtoi(scaleW)>>1), fixtoi(player.y)-(fixtoi(scaleH)>>1),fixtoi(scaleW),fixtoi(scaleH));
    }
    else
    {
        //original
        draw_sprite(buffer, player.image[player.animation.frame], fixtoi(player.x)-(player.image[player.animation.frame]->w>>1), fixtoi(player.y)-(player.image[player.animation.frame]->h>>1));
    }
}
