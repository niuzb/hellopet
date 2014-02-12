#include "RoundFlyBombProp.h"
#include "SkeletonAnimRcsManager.h"
#include "Particle/ParticleManager.h"
#include "Layers/Game/LayerCommonEnum.h"
#include "Map/MapDataCenter.h"

RoundFlyBombProp::RoundFlyBombProp(PropsType propType,SpriteBase* pUserSprite,CCNode* pParentNode,bool isHero):
	PropBase(propType,pUserSprite,pParentNode,isHero),
	mRunningTimer(0.0),
	mTotoalFlyTimer(0.0),
	mMoveSpeed(0.0),
	mParticleNums(4)
{

}

RoundFlyBombProp::~RoundFlyBombProp()
{

}

void RoundFlyBombProp::UseProp(CCPoint pt,bool bPlaySound /* = true */)
{
	if (mParentNode)
	{
		float angle = 0;
		float deltaAngle = 360.0 / mParticleNums;
		for (int index = 0;index < mParticleNums;index++)
		{
			BoneParticle* pParticle = ParticleManager::Get()->CreateOneBoneParticle(mAnimRcsId,0,true);
			if (pParticle)
			{
				mParentNode->addChild(pParticle,(int)Z_ORDER_BATTLE_PARTICLE);
				pParticle->setPosition(pt);
				pParticle->SetUserProp(this);
				mVecParticles.push_back(pParticle);
				
				CCPoint direction = CCPoint::forAngle(angle);
				mVecParticleDirections.push_back(direction);
				pParticle->setRotation(-CC_RADIANS_TO_DEGREES(angle-90));
				angle += deltaAngle;	
			}
		}
		PropBase::UseProp(pt,bPlaySound);
	}
}

void RoundFlyBombProp::animationHandler(CCNode* pNode,const char* _aniType, const char* _aniID, const char* _frameID)
{
	//if (pNode)
	//{
	//	BoneParticle* pParticle = dynamic_cast<BoneParticle*>(pNode);
	//	if (pParticle)
	//	{
	//	}
	//}
}

void RoundFlyBombProp::PreloadAnimRcs()
{

}

void RoundFlyBombProp::Update(float dt)
{
	mRunningTimer += dt;
	size_t count = mVecParticles.size();
	for (size_t index = 0;index < count;index++)
	{
		BoneParticle* pParticle = mVecParticles[index];
		if (pParticle)
		{
			CCPoint direction = mVecParticleDirections[index];

			CCPoint pixelPos = pParticle->getPosition();
			CCPoint newDstPt = CCPointZero;
			newDstPt.x = pixelPos.x + (direction.x * dt * mMoveSpeed * MapDataCenter::Get()->GetOneCellWidth());
			newDstPt.y = pixelPos.y + (direction.y * dt * mMoveSpeed * MapDataCenter::Get()->GetOneCellHeight());
			pParticle->setPosition(newDstPt);
		}
	}

	if (mRunningTimer >= mTotoalFlyTimer)
	{
		for (size_t index = 0;index < count;index++)
		{
			BoneParticle* pParticle = mVecParticles[index];
			pParticle->removeFromParent();
		}
		this->release();
	}
}