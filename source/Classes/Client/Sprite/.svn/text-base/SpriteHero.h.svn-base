#ifndef _SPRITE_HERO_H_
#define _SPRITE_HERO_H_

#include "SpriteBase.h"
#include "SpriteHeroBase.h"
#include "Sprite/UserData.h"
#include "Props/PropsDefiner.h"
#include "NetWork/BaseMsgHandler.h"

class SpriteHero : public SpriteHeroBase
{
public:
	SpriteHero(int type);
	virtual ~SpriteHero();

	virtual void update(float dt);
	virtual void Die();
protected:
	virtual void animationHandler(const char* _aniType, const char* _aniID, const char* _frameID);
	virtual void HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg);
};

#endif	// _SPRITE_HERO_H_