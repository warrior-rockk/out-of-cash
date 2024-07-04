#include <allegro.h>
#include "player.h"
#include "game.h"
#include "engine.h"
#include "utils.h"

//function to update the player
void player_update()
{
    bool in_range_x;
    bool in_range_y;
    
    if (player.moving)
    {
        //check destination in range
        in_range_x = in_range(fixtoi(player.x), player.destX, 2);
        in_range_y = in_range(fixtoi(player.y), player.destY, 2);

        //decompose movement
        if (!in_range_x)
        {
            player.vX = fixtoi(player.x) < player.destX ? gameConfig.playerSpeed : -gameConfig.playerSpeed;
        }
        else
            player.vX = itofix(0);
            
        if (!in_range_y)
        {
            //if (in_range_x)
                player.vY = fixtoi(player.y) < player.destY ? gameConfig.playerSpeed : -gameConfig.playerSpeed;
        }
        else
            player.vY = itofix(0);

        //player on destination
        if (in_range_x && in_range_y)
        {
            player.moving = false;
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

//function to draw the player
void player_draw()
{
    if (player.moving)
    {
        if (gameTick)
        {
            player.frame = player.frame == 4 ? 3 : 4;
        }
    }
    else
        player.frame = 1;
        
    draw_sprite(buffer, player.image[player.frame], fixtoi(player.x)-(player.image[player.frame]->w>>1), fixtoi(player.y)-(player.image[player.frame]->h>>1));
}
