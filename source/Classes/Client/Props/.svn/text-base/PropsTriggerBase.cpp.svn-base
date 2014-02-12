#include "PropsTriggerBase.h"
#include "PropsTriggerManager.h"
#include "Map/MapPhysicalLayer.h"
#include "Sprite/SpriteHero.h"

//////////////////////////////////////////////////////////////////////////
// Note: Trigger

TriggerEventListener::TriggerEventListener()
{
	//if (MapPhysicalLayer::GetInstance())
	//{
	//	MapPhysicalLayer::GetInstance()->AddOneTriggerListerner(this);
	//}	
}
TriggerEventListener::~TriggerEventListener()
{
	//if (MapPhysicalLayer::GetInstance())
	//{
	//	MapPhysicalLayer::GetInstance()->RemoveOneTriggerListerner(this);
	//}	
}

//////////////////////////////////////////////////////////////////////////

PropTriggerBase::PropTriggerBase(CCNode* pParentNode,std::string frameFileName,PropsType propType,PropTriggerData _triggerData):
	runningTime(0),
	displaySprite(NULL),
	animationType(kType_Prop_UnKnow),
	isDeleteSelf(false),
	triggerData(_triggerData),
	m_isPreload(false)
{
	this->propType = propType;

	CCSprite *_display = CCSprite::createWithSpriteFrameName(frameFileName.c_str());
	displaySprite = _display;
	if (_display)
	{
		pParentNode->addChild(_display);
	}

	//StartAnimation(kType_Prop_Born);
}

PropTriggerBase::~PropTriggerBase()
{
	if (this->displaySprite)
	{
		//this->displaySprite->stopAllActions();
		//this->displaySprite->unscheduleAllSelectors();		
		displaySprite->getParent()->removeChild(displaySprite,true);
		displaySprite = NULL;
	}
	//this->stopAllActions();
	//this->unscheduleAllSelectors();
	//PropsTriggerManager::Get()->RemoveOnePropFromStorage(this);
}

void PropTriggerBase::setPosition(const CCPoint &position)
{
	if (displaySprite)
	{
		return displaySprite->setPosition(position);
	}
	return this->setPosition(position);
}

const CCPoint& PropTriggerBase::getPosition()
{
	if (displaySprite)
	{
		return displaySprite->getPosition();
	}
	return this->getPosition();
}

void PropTriggerBase::setScale(float fScale)
{
	if (displaySprite)
	{
		displaySprite->setScale(fScale);
	}
}

void PropTriggerBase::setVisible(bool visible)
{
	if (displaySprite)
	{
		displaySprite->setVisible(visible);
	}
	CCNode::setVisible(visible);
}

CCAreaData PropTriggerBase::GetColliderArea()
{
	if (displaySprite)
	{
		CCSize size = displaySprite->getContentSize();
		CCAreaData areaData;
		CCPoint pos = this->getPosition();
		areaData.upLeftX = pos.x - size.width / 2;
		areaData.downRightX = pos.x + size.width / 2;
		areaData.upLeftY = pos.y + size.height / 2;
		areaData.downRightY = pos.y - size.height / 2;
		return areaData;
	}
	else
	{
		return CCAreaData();
	}	
}

void PropTriggerBase::destroy()
{
	//if (this->displaySprite)
	//{
	//	//this->displaySprite->stopAllActions();
	//	//this->displaySprite->unscheduleAllSelectors();		
	//}

	//this->stopAllActions();
	//this->unscheduleAllSelectors();
	//this->removeFromParentAndCleanup(true);

	if (m_isPreload)
	{
		this->setVisible(false);
	}
	else
	{
		this->autorelease();
	}	
}

void PropTriggerBase::Update(float dt,bool &bDeleteSelf)
{	
	//bDeleteSelf = false;
	//if (isDeleteSelf)
	//{
	//	bDeleteSelf = true;
	//	destroy();
	//}
	//else
	//{
	//	runningTime += dt;
	//	if (runningTime > 40)
	//	{
	//		bDeleteSelf = true;
	//		destroy();		
	//	}
	//}	
}

void PropTriggerBase::StartAnimation(PropAnimationType animationType)
{
	this->animationType = animationType;

	switch(animationType)
	{
	case kType_Prop_Born:
		{
			StartBornAnimation();
		}
		break;
	case kType_Prop_Move:
		{
			StartMoveAnimation();
		}
		break;
	default:
		CCLOG("Error PropTriggerSprite::StartAnimation error animation type %d",(int)animationType);
		break;
	}
}

void PropTriggerBase::StartBornAnimation()
{
	if (displaySprite)
	{
		displaySprite->setScale(0.0);
		CCScaleTo* scale_1 = CCScaleTo::create(0.7f,1.4f);
		CCScaleTo* scale_2 = CCScaleTo::create(0.2f,1.0f);
		CCCallFunc *rc = CCCallFunc::create(this,callfunc_selector(PropTriggerSprite::ScaleAnimationOver));
		CCSequence* seq = CCSequence::create(scale_1,scale_2,rc,NULL);
		displaySprite->runAction(seq);
	}
}

void PropTriggerBase::ScaleAnimationOver()
{
	StartAnimation(kType_Prop_Move);
}

void PropTriggerBase::StartMoveAnimation()
{
	if (displaySprite)
	{
		CCRotateBy *rotateAction = CCRotateBy::create(0.5,10);
		displaySprite->runAction(CCRepeatForever::create(rotateAction)); 
	}	
}