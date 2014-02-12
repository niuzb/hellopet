#include "AwayExplosionProp.h"
#include "SkeletonAnimRcsManager.h"
#include "Particle/ParticleManager.h"
#include "Layers/Game/LayerCommonEnum.h"
#include "Map/MapDataCenter.h"

AwayExplosionProp::AwayExplosionProp(PropsType propType,SpriteBase* pUserSprite,CCNode* pParentNode,bool isHero):
	PropBase(propType,pUserSprite,pParentNode,isHero),
	mParticle(NULL)
{

}

AwayExplosionProp::~AwayExplosionProp()
{

}

CCPoint AwayExplosionProp::GetAwayPoint(const CCPoint &pt)
{
	CCPoint _pt = pt;
	if (mUserSprite)
	{
		//// Note: 判断最近的其他人员		
		//CCPoint moveDirection = mUserSprite->GetDirection();
		//float radius = 5;
		//_pt.x += radius * moveDirection.x;
		//_pt.y += radius * moveDirection.y;
		//MapDataCenter::Get()->ConvetPtToMapRange(_pt);
	}
	return _pt;
}

void AwayExplosionProp::PreloadAnimRcs()
{

}

void AwayExplosionProp::UseProp(CCPoint pt,bool bPlaySound /* = true */)
{
	if (mParentNode)
	{
		BoneParticle* pParticle = ParticleManager::Get()->CreateOneBoneParticle(mAnimRcsId,0,false);
		if (pParticle)
		{
			mParentNode->addChild(pParticle,(int)Z_ORDER_BATTLE_PARTICLE);
			CCPoint bornPt = GetAwayPoint(pt);	
			pParticle->setPosition(bornPt);
			pParticle->SetUserProp(this);
			mParticle = pParticle;

			PropBase::UseProp(pt,bPlaySound);
		}
	}
}

void AwayExplosionProp::animationHandler(CCNode* pNode,const char* _aniType, const char* _aniID, const char* _frameID)
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
					pParticle->removeFromParent();
					this->release();
				}
			}
		}
	}
}

void AwayExplosionProp::Update(float dt)
{
}