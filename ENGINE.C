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
    if (msg.msgFinished == 0)
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
            switch (rndNumber)
            {
                case 0:
                    say("Nada destacable");
                    break;
                case 1:
                    say("No veo nada en especial");
                    break;
                case 2:
                    say("Aqui no hay nada que ver");
                    break;
            }
            break;
        case TAKE:
            switch (rndNumber)
            {
                case 0:
                    say("No puedo coger eso");
                    break;
                case 1:
                    say("No lo necesito");
                    break;
                case 2:
                    say("Ya llevo demasiadas cosas");
                    break;
            }
            break;
        default:
            say("No tengo nada programado");
    }
}
