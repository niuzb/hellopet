#ifndef _FLY_SINGLE_BOMB_PROP_H_
#define _FLY_SINGLE_BOMB_PROP_H_

#include "PropBase.h"
#include "Particle/BoneAniParticle/BoneParticle.h"

class FlySingleBombProp : public PropBase
{
public:
	FlySingleBombProp(PropsType propType,SpriteBase* pUserSprite,CCNode* pParentNode,bool isHero);
	virtual ~FlySingleBombProp();
	virtual void UseProp(CCPoint pt,bool bPlaySound = true);
	virtual void Update(float dt);
	void SetPropRunningTimer(float timer){
		CCAssert(timer>0,"FlySingleBombProp timer must > 0");
		mTotoalFlyTimer = timer;
	}
	void SetMoveSpeed(float moveSpeed){
		mMoveSpeed = moveSpeed;
	}
	virtual void PreloadAnimRcs();
protected:
	virtual void animationHandler(CCNode* pNode,const char* _aniType, const char* _aniID, const char* _frameID);
private:
	BoneParticle* mParticle;
	float mRunningTimer;
	float mTotoalFlyTimer;
	float mMoveSpeed;
};

#endif	//_FLY_SINGLE_BOMB_PROP_H_