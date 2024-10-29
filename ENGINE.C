#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdint.h>
#include "engine.h"
#include "utils.h"
#include "game.h"
#include "inventory.h"
#include "player.h"

//initialize roomScript struct
void init_room_script()
{
    roomScript.active = false;
    roomScript.scriptAssigned = false;
    roomScript.type  = ROOM_SCRIPT_TYPE;
    roomScript.object = 0;
    roomScript.invObject = 0;
    roomScript.verb = 0;
    roomScript.step = 0;
    roomScript.lastStep = 0;
    roomScript.stepTime = 0;
    roomScript.hsX = 0;
    roomScript.hsY = 0;
}

//function to actor say something. Returns 1 when finished
int say_actor(char *message, tActorTalk *actorTalk)
{        
    //check message length
    ASSERT(strlen(message) <= MAX_MSG_LENGTH);
    
    //assign actor talk pointer
    msg.actorTalk = actorTalk;

    //copy message to structure
    strcpy(msg.msg, message);

    //if not msg finished, set msg active
    if (!msg.msgFinished)
        msg.msgActive = true;

    //return finished state
    return msg.msgFinished;
}

//function to actor say something from script. Increments script step on finish
void script_say_actor(char *message, tActorTalk *actorTalk)
{
    if (say_actor(message, actorTalk))
    {
        roomScript.step++;
    }
}

//function to player say something. Returns 1 when finished
int say(char *message)
{
    return say_actor(message, &player.talk);
}

//function to player say something from script. Increments script step on finish
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
    //set player state
    player.state = player_st_taking;
    //deactivate room object
    *objActive = false;
    //set game flag
    set_game_flag(gameFlag);
    //add object to inventory
    inventory_add(invObjectNum);
    //plays take sound
    play_sound_rnd(sd_take);
}

//function to remove object inventory and increment script
void script_remove_inv_object(int numObject)
{
    inventory_remove(numObject);
    //reset "use with" verb
    if (cursor.selectedVerb == USE_WITH)
        cursor.selectedVerb = USE;
    roomScript.step++;
}

//function to play animation and increments script step when finished (DEPRECATED)
void script_play_player_animation(int startFrame, int endFrame, int speed)
{
    if (play_animation(&player.animation, startFrame, endFrame, speed, ANIM_ONCE))
    {
        roomScript.step++;
        player.state = player_st_idle;
    }
}
//function to change player state to take state
void script_player_take_state()
{
    static bool memTaking;

    if (player.state != player_st_taking)
    {
        if (!memTaking)
        {
            memTaking = true;
            player.state = player_st_taking;
        }
        else
        {
            memTaking = false;
            roomScript.step++;
        }
    }
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

//function to toggle game flag
void toogle_game_flag(uint8_t flagNum)
{
    TOOGLE_BIT(game.flags[flagNum % 8], flagNum/8);
}

//function to check game flag
bool is_game_flag(uint8_t flagNum)
{
    return CHECK_BIT(game.flags[flagNum % 8], flagNum/8);
}

//function to change the actual room
void change_room(int roomNum)
{
    //game_fade_out();
    game.nextRoom = roomNum;
    //game.roomLoaded = false;
}

//function to change the actual room and set player position on new room
void change_room_pos(int roomNum, int x, int y)
{
    game.room_pos_x = x;
    game.room_pos_y = y;
    change_room(roomNum);
}

//function to do game fade out
void game_fade_out(int fadeSpeed)
{
    game.fadeIn = false;
    fade_out(fadeSpeed);
    game.fadeOut = true;
}

//function to do game fade in
void game_fade_in()
{
    if (game.fadeOut)
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
        case USE_WITH:
            say("Esas cosas no combinan");
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
    roomScript.invObject = 0;
    roomScript.verb = 0;
    roomScript.active = false;
    roomScript.scriptAssigned = false;
    roomScript.hsX = 0;
    roomScript.hsY = 0;
    roomScript.type = ROOM_SCRIPT_TYPE;
}

//global debug vars function
void show_debug(char *varName, int var)
{
    #ifdef DEBUGMODE
    if (debug.numVars < DEBUG_MAX_VARS)
    {
        strcpy(debug.varName[debug.numVars], varName);
        debug.var[debug.numVars] = var;
        debug.numVars++;
    }
    #endif
}

//function to move the player
void move_player(int x, int y)
{
    //set the flag and positions
    player.state = player_st_moving;
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
    return player.state == player_st_moving;
}

//function to change the direction of player
void change_player_dir(uint8_t dir)
{
    player.lookDir = dir;
}

//plays room object animation if object is active
void object_play_animation(tObject *object, uint8_t idleFrame, tAnimation *animation, int startFrame, int endFrame, int speed, uint8_t mode)
{
    //if object is active
    if (object->active)
        //plays parameter animation
        play_animation(&animation[object->animationId - 1], startFrame, endFrame, speed, mode);
    else
        //sets idle frame
        animation[object->animationId - 1].frame = idleFrame;

    //sets object idImage to current animation frame
    object->objId = animation[object->animationId - 1].frame;

}

//starts a dialog and increments script step
void script_start_dialog(uint8_t dialogId)
{
    //change game state to dialog
    game.state = DIALOG_STATE;

    //initialize dialog data
    dialog_init();
    dialog.node = 1;
    dialog.active = true;
    dialog.state = DIALOG_ST_SELECT;
    dialog.dialogId = dialogId;

    //end script
    end_script();
}

//function to set the next dialog node and increments script step
void script_next_dialog_node()
{
    dialog.node = dialog.lineDestNode[dialog.selLine - 1];
    dialog.state = DIALOG_ST_SELECT;
    dialog.selLine = 0;

    //continue script
    roomScript.step++;
}

//function to add line of dialog
void dialog_add(char *textLine, uint8_t destNode)
{
    ASSERT(strlen(textLine) <= MAX_MSG_LENGTH);
    
    dialog.nodeNumLines++;

    strcpy(dialog.lineText[dialog.nodeNumLines-1], textLine);
    dialog.lineDestNode[dialog.nodeNumLines-1] = destNode;
}

//function to stop a dialog
void stop_dialog()
{
    dialog_init();
    game.state = PLAYING_STATE;    
}

//function to play game global sound
void play_sound(int16_t soundId)
{
    play_sample((SAMPLE*)soundDataFile[soundId].dat, gameConfig.soundVolume, 127, 1000, 0);
}

//function to play game global sound with random frecuency mod
void play_sound_rnd(uint16_t soundId)
{
    play_sample((SAMPLE*)soundDataFile[soundId].dat, gameConfig.soundVolume, 127, rand() % (1200 - 800 + 1) + 800, 0);
}
