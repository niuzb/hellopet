#ifndef _SPRITE_OTH_CASTLE_H_
#define _SPRITE_OTH_CASTLE_H_

#include "SpriteBase.h"
#include "SpriteCastleBase.h"
#include "Sprite/UserData.h"
#include "NetWork/BaseMsgHandler.h"

class SpriteOthCastle : public SpriteCastleBase
{
public:
	SpriteOthCastle(int type);
	virtual ~SpriteOthCastle();

	virtual void update(float dt);
	virtual void Die();
protected:
	virtual void animationHandler(const char* _aniType, const char* _aniID, const char* _frameID);
	virtual void HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg);
};

#endif	// _SPRITE_OTH_CASTLE_H_