#include "WithHeroProtectProp.h"
#include "SkeletonAnimRcsManager.h"
#include "Particle/ParticleManager.h"
#include "Layers/Game/LayerCommonEnum.h"

WithHeroProtectProp::WithHeroProtectProp(PropsType propType,SpriteBase* pUserSprite,CCNode* pParentNode,bool isHero):
	PropBase(propType,pUserSprite,pParentNode,isHero),
	mParticle(NULL),
	mLastTimer(0.0),
	mRunningTimer(0.0)
{

}

WithHeroProtectProp::~WithHeroProtectProp()
{

}

void WithHeroProtectProp::PreloadAnimRcs()
{

}

void WithHeroProtectProp::UseProp(CCPoint pt,bool bPlaySound /* = true */)
{
	if (mParentNode)
	{
		BoneParticle* pParticle = ParticleManager::Get()->CreateOneBoneParticle(mAnimRcsId,0,true);
		if (pParticle)
		{
			mParentNode->addChild(pParticle,(int)Z_ORDER_BATTLE_LOW_PARTICLE);
			pParticle->setPosition(pt);
			pParticle->SetUserProp(this);
			mParticle = pParticle;

			PropBase::UseProp(pt,bPlaySound);
		}
	}
}

void WithHeroProtectProp::animationHandler(CCNode* pNode,const char* _aniType, const char* _aniID, const char* _frameID)
{

}

void WithHeroProtectProp::Update(float dt)
{	
	if (mUserSprite && mParticle)
	{
		mRunningTimer += dt;
		if (mRunningTimer >= mLastTimer)
		{
			mParticle->removeFromParent();
			this->release();
		}
		else
		{
			CCPoint pt = mUserSprite->getPosition();
			mParticle->setPosition(pt);
		}
	}
}