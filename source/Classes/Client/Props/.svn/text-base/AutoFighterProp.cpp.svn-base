#include "AutoFighterProp.h"
#include "SkeletonAnimRcsManager.h"
#include "Particle/ParticleManager.h"
#include "Layers/Game/LayerCommonEnum.h"

AutoFighterProp::AutoFighterProp(PropsType propType,SpriteBase* pUserSprite,CCNode* pParentNode,bool isHero):
	PropBase(propType,pUserSprite,pParentNode,isHero),
	mParticle(NULL)
{

}

AutoFighterProp::~AutoFighterProp()
{

}

void AutoFighterProp::UseProp(CCPoint pt,bool bPlaySound /* = true */)
{
	if (mParentNode)
	{
		BoneParticle* pParticle = ParticleManager::Get()->CreateOneBoneParticle(mAnimRcsId,0,false);
		if (pParticle)
		{
			mParentNode->addChild(pParticle,(int)Z_ORDER_BATTLE_PARTICLE);
			pParticle->setPosition(pt);
			pParticle->SetUserProp(this);
			mParticle = pParticle;

			PropBase::UseProp(pt,bPlaySound);
		}
	}
}

void AutoFighterProp::animationHandler(CCNode* pNode,const char* _aniType, const char* _aniID, const char* _frameID)
{
}

void AutoFighterProp::Update(float dt)
{

}