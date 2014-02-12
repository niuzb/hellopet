

#pragma once

#ifndef STATE_EVENT_TYPE_H
#define STATE_EVENT_TYPE_H

//  state event type
enum EventType
{
    ET_None = -1,

    ToIdle	= 0,
    ToRun	= 1,
	ToDie,

	ToBaseAttack,
	ToNormalAttack,
	ToNormalMagicFireBall,
	ToMagicAnimHandler,
	ToMoveToHandler,
	ToEffectAnimHandler,
	ToAnimHandler,
	ToAttackCheckerHandler,
	ToMagicCheckHandler,

    // add more here!
};


static bool bET_Table[][3] = {
 //         | idle | run | fight|  
/*idle */   {false, false, false },
/*run  */   {false, false, false },
/*fight*/   {false, false, false }
};


#endif
