#ifndef _WITH_HERO_PROTECT_PROP_H_
#define _WITH_HERO_PROTECT_PROP_H_

#include "PropBase.h"
#include "Particle/BoneAniParticle/BoneParticle.h"

class WithHeroProtectProp : public PropBase
{
public:
	WithHeroProtectProp(PropsType propType,SpriteBase* pUserSprite,CCNode* pParentNode,bool isHero);
	virtual ~WithHeroProtectProp();
	virtual void UseProp(CCPoint pt,bool bPlaySound = true);
	virtual void Update(float dt);
	/**
	* Instruction : 设置技能的持续时间
	* @param : 
	* @result : 
	*/
	void SetLastTimer(float timer)
	{
		mLastTimer = timer;
	}
	virtual void PreloadAnimRcs();
protected:
	virtual void animationHandler(CCNode* pNode,const char* _aniType, const char* _aniID, const char* _frameID);
private:
	BoneParticle* mParticle;
	// Note: 已持续时间
	float mRunningTimer;
	// Note: 持续总作用时间
	float mLastTimer;
};

#endif	//_WITH_HERO_PROTECT_PROP_H_