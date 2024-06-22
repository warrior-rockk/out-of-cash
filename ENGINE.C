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
        msg.msgActive = 1;

    //return finished state
    return msg.msgFinished;
}

//function to change the actual room
void change_room(int roomNum)
{
    //fade_out(10);
    actualRoom = roomNum;
    //fade_in(gamePalette, 10);
}
//function to perform default verb action when nothing is scripted
void default_verb_action(enum verbs roomVerb)
{
    int rndNumber;
    rndNumber = rand() % 3;
    
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

void end_script()
{
    roomAction.object = 0;
    roomAction.verb = 0;
    roomAction.active = 0;
}
