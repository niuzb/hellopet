#ifndef _AWAY_EXPLOSION_PROP_H_
#define _AWAY_EXPLOSION_PROP_H_

#include "PropBase.h"
#include "Particle/BoneAniParticle/BoneParticle.h"

class AwayExplosionProp : public PropBase
{
public:
	AwayExplosionProp(PropsType propType,SpriteBase* pUserSprite,CCNode* pParentNode,bool isHero);
	virtual ~AwayExplosionProp();
	virtual void UseProp(CCPoint pt,bool bPlaySound = true);
	virtual void Update(float dt);
	virtual void PreloadAnimRcs();
protected:
	CCPoint GetAwayPoint(const CCPoint &pt);
	virtual void animationHandler(CCNode* pNode,const char* _aniType, const char* _aniID, const char* _frameID);
private:
	BoneParticle* mParticle;
};

#endif	//_AWAY_EXPLOSION_PROP_H_