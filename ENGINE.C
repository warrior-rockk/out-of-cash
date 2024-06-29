#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "engine.h"
#include "game.h"

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

//function to change the actual room
void change_room(int roomNum)
{
    fade_out(FADE_DEFAULT_SPEED);
    game.actualRoom = roomNum;
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
            switch (rndNumber)
            {
                case 0:
                    say("No puedo ir ahi");
                    break;
                case 1:
                    say("No se como llegar");
                    break;
                case 2:
                    say("No me apetece andar");
                    break;
            }
            break;
        case LOOK:
            say("Nada destacable");
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
}

//global debug vars function
void show_debug(char *varName, int var)
{
    strcpy(debugVars.varName[debugVars.numVars], varName);
    debugVars.var[debugVars.numVars] = var;
    debugVars.numVars++;
}
