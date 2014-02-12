#include "HeroRunState.h"
#include "Sprite/SpriteHero.h"
#include "Map/MapDataCenter.h"
#include "CommonUtils.h"

HeroRunState::HeroRunState(SpriteBase* pHero):
	moveDirection(CCPointZero),
	destPt(CCPointZero),
	destCellPt(CCPointZero)
{
	heroInstance = pHero;
	isRunOver = true;
}

HeroRunState::~HeroRunState()
{

}

void HeroRunState::update(float dt)
{
	//if (heroInstance)
	//{
	//	if (isRunOver == false)
	//	{
	//		CCPoint pixelPos = heroInstance->getPositionPixel();
	//		CCPoint newDstPt = CCPointZero;
	//		newDstPt.x = pixelPos.x + (moveDirection.x * dt * heroInstance->GetMoveSpeed() * MapDataCenter::Get()->GetOneCellWidth());
	//		newDstPt.y = pixelPos.y + (moveDirection.y * dt * heroInstance->GetMoveSpeed() * MapDataCenter::Get()->GetOneCellHeight());

	//		float deltaX1 = destPt.x - pixelPos.x;
	//		float deltaY1 = destPt.y - pixelPos.y;
	//		float deltaX2 = - newDstPt.x + destPt.x;
	//		float deltaY2 = - newDstPt.y + destPt.y;
	//		if (deltaX1*deltaX2 <= 0 && deltaY1*deltaY2 <= 0)
	//		{
	//			heroInstance->setPosition(destPt,true);
	//			isRunOver = true;
	//		}
	//		else
	//		{
	//			heroInstance->setPosition(newDstPt,true);
	//		}
	//	}
	//}
}

bool HeroRunState::CheckMoveOverOrNot()
{
	//if (heroInstance)
	//{
	//	CCPoint pixelPos = heroInstance->getPositionPixel();
	//	CCPoint distancePt = ccpSub(destPt,pixelPos);
	//	if ()
	//	{
	//	}
	//}	
	return true;
}

void HeroRunState::ReCalMoveSteps(const CCPoint& oldPt,const CCPoint& dstPt)
{	
	//if (CommonUtils::IsPointEqual(oldPt,dstPt))
	//{
	//	isRunOver = true;
	//	moveDirection = CCPointZero;
	//	return ;
	//}

	//moveDirection = ccpNormalize(ccpSub(dstPt,oldPt));
	//float angle = moveDirection.getAngle();
	//if (heroInstance)
	//{
	//	heroInstance->SetDirection(moveDirection);
	//	heroInstance->setRotation(-CC_RADIANS_TO_DEGREES(angle));
	//}
}

bool HeroRunState::UpdateMoveSteps(const CCPoint& dstPt,CCPoint &cellDestPt,bool bPixelPos /* = true */)
{
	bool bRet = false;

	//CCPoint newCellPt = CCPointZero;
	//if (bPixelPos)
	//{
	//	MapDataCenter::Get()->ConvertPtToCellPos(dstPt,newCellPt);
	//}	
	//else
	//{
	//	newCellPt = dstPt;
	//}
	//if (false == CommonUtils::IsPointEqual(newCellPt,destCellPt))
	//{
	//	isRunOver = false;
	//	if (bPixelPos)
	//	{
	//		this->destPt = dstPt;
	//	}
	//	else
	//	{
	//		MapDataCenter::Get()->ConvertCellPosToWordPos(dstPt.x,dstPt.y,this->destPt);
	//	}
	//	this->destCellPt = newCellPt;
	//	ReCalMoveSteps(heroInstance->getPositionPixel(),this->destPt);
	//	cellDestPt = newCellPt;
	//	bRet = true;
	//}

	return bRet;
}
