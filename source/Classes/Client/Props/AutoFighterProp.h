#ifndef _AUTO_FIGHTER_PROP_H_
#define _AUTO_FIGHTER_PROP_H_

#include "PropBase.h"
#include "Particle/BoneAniParticle/BoneParticle.h"

class AutoFighterProp : public PropBase
{
public:
	AutoFighterProp(PropsType propType,SpriteBase* pUserSprite,CCNode* pParentNode,bool isHero);
	virtual ~AutoFighterProp();
	virtual void UseProp(CCPoint pt,bool bPlaySound = true);
	virtual void Update(float dt);

	/**
	* Instruction : Ìí¼Óµ½Åö×²¼ì²âÇøÓò
	* @param : 
	* @result : 
	*/
	//void AddToColliderDecter();
protected:
	virtual void animationHandler(CCNode* pNode,const char* _aniType, const char* _aniID, const char* _frameID);
private:
	BoneParticle* mParticle;
};

#endif	//_AUTO_FIGHTER_PROP_H_