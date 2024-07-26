#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdint.h>
#include "engine.h"
#include "utils.h"
#include "game.h"
#include "inventory.h"
#include "player.h"

//function to say something. Returns 1 when finished
int say(char *message)
{
    //copy message to structure
    strcpy(msg.msg, message);

    //if not msg finished, set msg active
    if (!msg.msgFinished)
        msg.msgActive = true;

    //return finished state
    return msg.msgFinished;
}

//function to say something from script. Increments script step on finish
void script_say(char *message)
{
    if (say(message))
    {
        roomScript.step++;
    }
}

//function to wait on script. Increments script step on finish
void script_wait(int time)
{
    if (roomScript.stepTime > time)
    {
        cursor.enabled = true;
        roomScript.step++;
    }
    else
    {
        cursor.enabled = false;
    }
}

//function to move player and autoincrements script step
void script_move_player(int x, int y)
{
    static bool memMoving;

    //if player is not moving
    if (!is_player_moving())
    {
        if (!memMoving)
        {
            //mem flag and call move_player
            memMoving = true;
            move_player(x, y);
        }
        else
        {
            //increment step when finish moving
            memMoving = false;
            roomScript.step++;
        }
    }
}

//function to move player to target and autoincrements script step
void script_move_player_to_target()
{
    script_move_player(roomScript.hsX, roomScript.hsY);
}

//function to take and object (inactives the object, sets the game flag and adds object
//to inventory
void script_take_object(bool *objActive, uint8_t gameFlag, uint8_t invObjectNum)
{
    *objActive = false;
    set_game_flag(gameFlag);
    inventory_add(invObjectNum);
}

//function to set game flag
void set_game_flag(uint8_t flagNum)
{
    SET_BIT(game.flags[flagNum % 8], flagNum/8);
}

//function to clear game flag
void clear_game_flag(uint8_t flagNum)
{
    CLEAR_BIT(game.flags[flagNum % 8], flagNum/8);
}

//function to check game flag
bool is_game_flag(uint8_t flagNum)
{
    return CHECK_BIT(game.flags[flagNum % 8], flagNum/8);
}

//function to change the actual room
void change_room(int roomNum)
{
    fade_out(FADE_DEFAULT_SPEED);
    game.actualRoom = roomNum;
}

//function to change the actual room and set player position on new room
void change_room_pos(int roomNum, int x, int y)
{
    game.room_pos_x = x;
    game.room_pos_y = y;
    change_room(roomNum);
}

//function to do game fade out
void game_fade_out()
{
    game.fadeIn = false;
    fade_out(FADE_DEFAULT_SPEED);
}

//function to do game fade in
void game_fade_in()
{
    game.fadeIn = true;
}

//function to perform default verb action when nothing is scripted
void default_verb_action(enum verbs roomVerb)
{
    static int lastRndNumber;
    int rndNumber;

    //get random number distinct to last
    do
    {
        rndNumber = rand() % NUM_RAND_ANSWERS;
    }
    while (rndNumber == lastRndNumber);
    lastRndNumber = rndNumber;
    
    switch(roomVerb)
    {
        case GO:
            move_player(mouse_x, mouse_y);
            break;
        case LOOK:
            switch (rndNumber)
            {
                case 0:
                    say("Nada destacable");
                    break;
                case 1:
                    say("No veo nada");
                    break;
                case 2:
                    say("No hay nada que ver");
                    break;
            }
            break;
        case TAKE:
            say("No puedo coger eso");
            break;
        default:
            say("No tengo nada programado");
    }
}

//actions when script begins
void begin_script()
{
    roomScript.scriptAssigned = true;
}

//actions when script ends
void end_script()
{
    roomScript.object = 0;
    roomScript.verb = 0;
    roomScript.active = false;
    roomScript.scriptAssigned = false;
    roomScript.hsX = 0;
    roomScript.hsY = 0;
}

//global debug vars function
void show_debug(char *varName, int var)
{
    strcpy(debugVars.varName[debugVars.numVars], varName);
    debugVars.var[debugVars.numVars] = var;
    debugVars.numVars++;
}

//function to move the player
void move_player(int x, int y)
{
    //set the flag and positions
    player.moving = true;
    player.moveFast = cursor.dblClick;
    player.destX = x;
    player.destY = y;
}

//function to move the player to pointer target
void move_player_to_target()
{
    //move the player to the roomScript pointed
    move_player(roomScript.hsX, roomScript.hsY);
}

//function to return if player is moving
bool is_player_moving()
{
    return player.moving;
}

//function to change the direction of player
void change_player_dir(uint8_t dir)
{
    player.lookDir = dir;
}
