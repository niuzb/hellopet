#include "LocalExplosionProp.h"
#include "SkeletonAnimRcsManager.h"
#include "Particle/ParticleManager.h"
#include "Layers/Game/LayerCommonEnum.h"

LocalExplosionProp::LocalExplosionProp(PropsType propType,SpriteBase* pUserSprite,CCNode* pParentNode,bool isHero):
	PropBase(propType,pUserSprite,pParentNode,isHero),
	mParticle(NULL)
{
	
}

LocalExplosionProp::~LocalExplosionProp()
{
	if (mParticle)
	{
		mParticle->removeFromParent();
	}
}

void LocalExplosionProp::PreloadAnimRcs()
{
	if (mParentNode)
	{
		BoneParticle* pParticle = ParticleManager::Get()->CreateOneBoneParticle(mAnimRcsId,0,false);
		if (pParticle)
		{
			mParentNode->addChild(pParticle,(int)Z_ORDER_BATTLE_PARTICLE);
			pParticle->SetUserProp(this);
			mParticle = pParticle;
			pParticle->PauseAnimation();
		}
	}
}

void LocalExplosionProp::UseProp(CCPoint pt,bool bPlaySound /* = true */)
{
	if (mParentNode)
	{
		if(NULL == mParticle)
		{
			PreloadAnimRcs();
		}
		if (mParticle)
		{
			mParticle->setPosition(pt);
			mParticle->setVisible(true);
			mParticle->PlayOneAnimation(kType_ANI_Action_Play,0,false);
			PropBase::UseProp(pt,bPlaySound);
		}
	}
}

void LocalExplosionProp::animationHandler(CCNode* pNode,const char* _aniType, const char* _aniID, const char* _frameID)
{
	if (pNode)
	{
		BoneParticle* pParticle = dynamic_cast<BoneParticle*>(pNode);
		if (pParticle)
		{
			if (false == pParticle->GetIsParticleLoop())
			{
				if (0 == strcmp(_aniType,"loopComplete") ||
					0 == strcmp(_aniType,"complete")) 
				{
					if (m_isDestorySelfWhenEnd)
					{
						pParticle->removeFromParent();
						this->release();
						mParticle = NULL;
					}
					else
					{
						mParticle->PauseAnimation();
						mParticle->setVisible(false);
					}
				}
			}
		}
	}
}

void LocalExplosionProp::Update(float dt)
{
}