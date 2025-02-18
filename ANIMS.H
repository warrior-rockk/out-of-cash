#ifndef H_ANIMS
#define H_ANIMS

//include resources headers for simbolic use
#include "PDATA.H"

//player animations
#define ANIM_PLY_IDLE               pd_idle,        pd_idle,        1, ANIM_ONCE
#define ANIM_PLY_BACK               pd_backTalk01,  pd_backTalk01,  1, ANIM_ONCE
#define ANIM_PLY_FRONT_IDLE         pd_frontTalk03, pd_frontTalk03, 1, ANIM_LOOP
#define ANIM_PLY_WALK               pd_walk01,      pd_walk06,      1, ANIM_LOOP
#define ANIM_PLY_WALK_BACK          pd_walkBack01,  pd_walkBack06,  1, ANIM_LOOP
#define ANIM_PLY_WALK_FRONT         pd_walkFront01, pd_walkFront06, 1, ANIM_LOOP
#define ANIM_PLY_TALK               pd_talk01,      pd_talk11,      1, ANIM_PING_PONG
#define ANIM_PLY_FRONT_TALK         pd_frontTalk01, pd_frontTalk11, 1, ANIM_PING_PONG
#define ANIM_PLY_TAKE               pd_take,        pd_take,        5, ANIM_ONCE
#define ANIM_PLY_TAKE_UP            pd_takeUp,      pd_takeUp,      5, ANIM_ONCE
#define ANIM_PLY_TAKE_LOW           pd_takeLow,     pd_takeLow,     5, ANIM_ONCE
#define ANIM_PLY_BACK_TALK          pd_backTalk01,  pd_backTalk04,  1, ANIM_PING_PONG
#define ANIM_PLY_APPLY_OAT_1        pd_applyOat1,   pd_applyOat3,   3, ANIM_ONCE
#define ANIM_PLY_APPLY_OAT_STILL    pd_applyOat4,   pd_applyOat4,   1, ANIM_LOOP
#define ANIM_PLY_APPLY_OAT_2        pd_applyOat5,   pd_applyOat6,   3, ANIM_ONCE
#define ANIM_PLY_APPLY_OAT_STILL_2  pd_applyOat6,   pd_applyOat6,   3, ANIM_ONCE
#define ANIM_PLY_END_OAT            pd_endOat1,     pd_endOat3,     3, ANIM_ONCE
#define ANIM_PLY_SURPRISE           pd_surprise,    pd_surprise,    1, ANIM_LOOP
#define ANIM_PLY_HAPPY_IDLE         pd_talk01,      pd_talk01,      1, ANIM_LOOP
#define ANIM_PLY_HAPPY              pd_happy,       pd_happy,       1, ANIM_LOOP
#define ANIM_PLY_WASH_HANDS         pd_washHands01, pd_washHands03, 3, ANIM_PING_PONG
#define ANIM_PLY_ROCKING            pd_rocking01,   pd_rocking02,   4, ANIM_LOOP
#define ANIM_PLY_LOOK_FRONT         pd_lookFront,   pd_lookFront,   1, ANIM_LOOP
#define ANIM_PLY_SMILE_FRONT        pd_smileFront,  pd_smileFront,  1, ANIM_LOOP

#endif  //H_ANIMS
