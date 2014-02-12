#include "FlySingleBombProp.h"
#include "SkeletonAnimRcsManager.h"
#include "Particle/ParticleManager.h"
#include "Layers/Game/LayerCommonEnum.h"
#include "Map/MapDataCenter.h"

FlySingleBombProp::FlySingleBombProp(PropsType propType,SpriteBase* pUserSprite,CCNode* pParentNode,bool isHero):
	PropBase(propType,pUserSprite,pParentNode,isHero),
	mParticle(NULL),
	mRunningTimer(0.0),
	mTotoalFlyTimer(0.0),
	mMoveSpeed(0.0)
{

}

FlySingleBombProp::~FlySingleBombProp()
{

}

void FlySingleBombProp::PreloadAnimRcs()
{

}

void FlySingleBombProp::UseProp(CCPoint pt,bool bPlaySound /* = true */)
{
	//if (mParentNode)
	//{
	//	BoneParticle* pParticle = ParticleManager::Get()->CreateOneBoneParticle(mAnimRcsId,0,true);
	//	if (pParticle)
	//	{
	//		mParentNode->addChild(pParticle,(int)Z_ORDER_BATTLE_PARTICLE);
	//		pParticle->setPosition(pt);
	//		pParticle->SetUserProp(this);
	//		mParticle = pParticle;

	//		// Note: 调整特效的方向
	//		if (mUserSprite)
	//		{
	//			CCPoint moveDirection = mUserSprite->GetDirection();
	//			mDirection = moveDirection;
	//			float angle = moveDirection.getAngle();
	//			mParticle->setRotation(-CC_RADIANS_TO_DEGREES(angle-90));
	//		}

	//		PropBase::UseProp(pt,bPlaySound);
	//	}
	//}
}

void FlySingleBombProp::animationHandler(CCNode* pNode,const char* _aniType, const char* _aniID, const char* _frameID)
{
	//if (pNode)
	//{
	//	BoneParticle* pParticle = dynamic_cast<BoneParticle*>(pNode);
	//	if (pParticle)
	//	{
	//	}
	//}
}

void FlySingleBombProp::Update(float dt)
{
	if (mParticle)
	{
		mRunningTimer += dt;
		if (mRunningTimer >= mTotoalFlyTimer)
		{
			mParticle->removeFromParent();
			this->release();
		}
		else
		{
			CCPoint pixelPos = mParticle->getPosition();
			CCPoint newDstPt = CCPointZero;
			newDstPt.x = pixelPos.x + (mDirection.x * dt * mMoveSpeed * MapDataCenter::Get()->GetOneCellWidth());
			newDstPt.y = pixelPos.y + (mDirection.y * dt * mMoveSpeed * MapDataCenter::Get()->GetOneCellHeight());
			mParticle->setPosition(newDstPt);
		}
	}
}