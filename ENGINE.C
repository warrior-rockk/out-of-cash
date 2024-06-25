#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "engine.h"
#include "game.h"

//local vars
static int lastRndNumber;

//function to say something. Returns 1 when finished
int say(char *message)
{
    //copy message to structure
    strcpy(msg.msg, message);

    //if not msg finished, set msg active
    if (!msg.msgFinished)
        msg.msgActive = 1;

    //return finished state
    return msg.msgFinished;
}

//function to change the actual room
void change_room(int roomNum)
{
    fade_out(6);
    actualRoom = roomNum;
    fade_in(gamePalette, 6);
}
//function to perform default verb action when nothing is scripted
void default_verb_action(enum verbs roomVerb)
{
    //get non-repeat random number
    int rndNumber;
    do
    {
        rndNumber = rand() % 3;
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

void begin_script()
{
    roomAction.scriptAssigned = 1;
}

void end_script()
{
    roomAction.object = 0;
    roomAction.verb = 0;
    roomAction.active = 0;
    roomAction.scriptAssigned = 0;
}

void show_debug(char *varName, int var)
{
    strcpy(debugVars.varName[debugVars.numVars], varName);
    debugVars.var[debugVars.numVars] = var;
    debugVars.numVars++;
}
