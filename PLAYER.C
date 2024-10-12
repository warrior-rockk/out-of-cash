#include <allegro.h>
#include "player.h"
#include "game.h"
#include "engine.h"
#include "utils.h"

//function to init player
void player_init()
{
    //sets player images frames
    for (int i = 0; i < pd_COUNT; i++)
    {
        playerData.image[i]  = (BITMAP *)playerDataFile[i].dat;
    }

    //creates temporal image
    if (!playerData.tempImage)
        playerData.tempImage    = create_bitmap(playerData.image[0]->w, playerData.image[0]->h);
    //clear temporal image
    clear(playerData.tempImage);

    //clear player vars and state
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

    player.talk.textColor = PLAYER_TEXT_COLOR;
    player.talk.talking = false;

}

//function to update the player
void player_update()
{
    //updates prevState
    player.prevState = player.state;

    //check player talking
    if (player.talk.talking)
        player.state = player_st_talking;
    else if (player.state == player_st_talking)
        player.state = player_st_idle;
        
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
        //calculate player relative position (on feet)
        fixed relX = fixadd(player.x, itofix(PLAYER_POS_X_OFFSET));
        fixed relY = fixadd(player.y, itofix(PLAYER_POS_Y_OFFSET));
        
        //check destination in range
        in_range_x = in_range(fixtoi(relX), player.destX, 2);
        in_range_y = in_range(fixtoi(relY), player.destY, 2);
    
        //assign actual speed
        actualSpeed = fixdiv(itofix(gameConfig.playerSpeed), itofix(100));
        if (player.moveFast)
            //double speed
            actualSpeed = fixmul(actualSpeed,itofix(2));

        //decompose movement
        if (!in_range_x)
        {
            player.vX = fixtoi(relX) < player.destX ? actualSpeed : -actualSpeed;
        }
        else
            player.vX = itofix(0);

        if (!in_range_y)
        {
            player.vY = fixtoi(relY) < player.destY ? actualSpeed : -actualSpeed;
        }
        else
            player.vY = itofix(0);

        //check walk map
        if (getpixel(actualRoom.wImage, fixtoi(relX + player.vX), fixtoi(relY)) == 0)
        {
            player.vX = itofix(0);
        }
    
        if (getpixel(actualRoom.wImage, fixtoi(relX) , fixtoi(relY + player.vY)) == 0)
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
            player.state = player_st_idle;
            player.vX = itofix(0);
            player.vY = itofix(0);
        }

    }
    
    //update position
    player.x += player.vX;
    player.y += player.vY;

    //update talk position
    player.talk.msgX = player.x;
    player.talk.msgY = fixtoi(player.y) - fixtoi((fixmul((itofix(playerData.image[player.animation.frame]->h>>1)), player.scale)));

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
    switch (getpixel(actualRoom.wImage, fixtoi(fixadd(player.x, itofix(PLAYER_POS_X_OFFSET))) , fixtoi(fixadd(player.y, itofix(PLAYER_POS_Y_OFFSET)) + player.vY)))
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
        draw_sprite_h_flip(buffer, playerData.image[player.animation.frame], fixtoi(player.x)-(playerData.image[player.animation.frame]->w>>1), fixtoi(player.y)-(playerData.image[player.animation.frame]->h>>1));
    }
    else if (!player.flip && player.scale != itofix(1))
    {
        //scaled

        //calculate scale weight and height
        fixed scaleW = fixmul(itofix(playerData.image[player.animation.frame]->w),player.scale);
        fixed scaleH = fixmul(itofix(playerData.image[player.animation.frame]->h),player.scale);
        //draw streched and reposition
        stretch_sprite(buffer, playerData.image[player.animation.frame], fixtoi(player.x)-(fixtoi(scaleW)>>1), fixtoi(player.y)-(fixtoi(scaleH)>>1),fixtoi(scaleW),fixtoi(scaleH));
    }
    else if (player.flip && player.scale != itofix(1))
    {
        //flipped and scaled
        clear(playerData.tempImage);
        draw_sprite_h_flip(playerData.tempImage, playerData.image[player.animation.frame], 0 , 0);

        //calculate scale weight and height
        fixed scaleW = fixmul(itofix(playerData.image[player.animation.frame]->w),player.scale);
        fixed scaleH = fixmul(itofix(playerData.image[player.animation.frame]->h),player.scale);
        //draw streched and reposition
        stretch_sprite(buffer, playerData.tempImage, fixtoi(player.x)-(fixtoi(scaleW)>>1), fixtoi(player.y)-(fixtoi(scaleH)>>1),fixtoi(scaleW),fixtoi(scaleH));
    }
    else
    {
        //original
        draw_sprite(buffer, playerData.image[player.animation.frame], fixtoi(player.x)-(playerData.image[player.animation.frame]->w>>1), fixtoi(player.y)-(playerData.image[player.animation.frame]->h>>1));
    }
}
