#ifndef H_ANIMS
#define H_ANIMS

//include resources headers for simbolic use
#include "PDATA.H"

//player animations
#define ANIM_PLY_IDLE       pd_idle,        pd_idle,        1, ANIM_ONCE
#define ANIM_PLY_WALK       pd_plyWalk01,   pd_plyWalk02,   1, ANIM_LOOP
#define ANIM_PLY_TALK       pd_talk01,      pd_talk11,      1, ANIM_PING_PONG
#define ANIM_PLY_TAKE       pd_plyTake,     pd_plyTake,     5, ANIM_ONCE

#endif  //H_ANIMS
