#ifndef _ROUND_FLY_BOMB_PROP_H_
#define _ROUND_FLY_BOMB_PROP_H_

#include "PropBase.h"
#include "Particle/BoneAniParticle/BoneParticle.h"
#include "vector"

class RoundFlyBombProp : public PropBase
{
public:
	RoundFlyBombProp(PropsType propType,SpriteBase* pUserSprite,CCNode* pParentNode,bool isHero);
	virtual ~RoundFlyBombProp();
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
	std::vector<BoneParticle*> mVecParticles;
	std::vector<CCPoint> mVecParticleDirections;
	float mRunningTimer;
	float mTotoalFlyTimer;
	float mMoveSpeed;
	int   mParticleNums;
};

#endif	//_ROUND_FLY_BOMB_PROP_H_