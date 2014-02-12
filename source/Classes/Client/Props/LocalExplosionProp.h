#ifndef _LOCAL_EXPLOSION_PROP_H_
#define _LOCAL_EXPLOSION_PROP_H_

#include "PropBase.h"
#include "Particle/BoneAniParticle/BoneParticle.h"

class LocalExplosionProp : public PropBase
{
public:
	LocalExplosionProp(PropsType propType,SpriteBase* pUserSprite,CCNode* pParentNode,bool isHero);
	virtual ~LocalExplosionProp();
	virtual void UseProp(CCPoint pt,bool bPlaySound = true);
	virtual void Update(float dt);
	virtual void PreloadAnimRcs();
protected:
	virtual void animationHandler(CCNode* pNode,const char* _aniType, const char* _aniID, const char* _frameID);
private:
	BoneParticle* mParticle;
};

#endif	//_LOCAL_EXPLOSION_PROP_H_