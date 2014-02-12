#ifndef _SPRITE_OTH_HERO_H_
#define _SPRITE_OTH_HERO_H_

#include "SpriteHeroBase.h"
#include "SpriteBase.h"
#include "Sprite/UserData.h"

class SpriteOthHero : public SpriteHeroBase
{
public:
	SpriteOthHero(int type);
	virtual ~SpriteOthHero();

	virtual void update(float dt);
	virtual void Die();
protected:
	virtual void animationHandler(const char* _aniType, const char* _aniID, const char* _frameID);
	virtual void HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg);
};

#endif	// _SPRITE_OTH_HERO_H_