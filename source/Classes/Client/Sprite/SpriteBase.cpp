#include "SpriteBase.h"
#include "CConnectionData.h"
#include "Map/MapDataCenter.h"
#include "../SpriteBehavior/RoleState/BaseAttackState.h"
#include "GraphicShape/Painter.h"

#define DRAW_EDITOR_RECT

SpriteBase::SpriteBase(int type):
			m_anim(NULL),
			nameLabel(NULL), 
			isNeedCalAttachBox(true),
			isAnimFlip(false)
{
	m_anim = new BoneAnimSprite(type);
	if (m_anim)
	{
		m_anim->addArmatureNodeToParentNode(this,1);
	}


}

SpriteBase::~SpriteBase()
{
	if(m_anim)
	{
		CC_SAFE_DELETE(m_anim);
	}
	this->unscheduleAllSelectors();	

	if (nameLabel)
	{
		nameLabel->removeFromParent();
		nameLabel = NULL;
	}
}

CCRect SpriteBase::getRect()
{
	if(m_anim != NULL)
	{
		cocos2d::CCRect rect = m_anim->GetCurViewRect().ToRect();
		return rect;
	}
	return CCRectMake(0, 0, 0, 0);	
}

bool SpriteBase::canDealWithTouch(cocos2d::CCTouch* touch)
{
	return containsTouchLocation(touch);
}

bool SpriteBase::containsTouchLocation(cocos2d::CCTouch* touch)
{
	return false;
}

bool SpriteBase::isTouchSelf(cocos2d::CCPoint pt)
{
	return false;	
}

void SpriteBase::PlayOneAnimation(int animId, int nloop, bool isLoop /* = true */)
{
	if (m_anim)
	{
		RoleActorBase * curRoleActor = m_anim->getCurRoleActorBase();
		if (NULL != curRoleActor)
		{
			curRoleActor->SetAnimationEventListener(NULL);
		}

		if (false == this->isVisible())
		{
			this->setVisible(true);
		}
		m_anim->SetAnim(animId, nloop, isLoop);
		m_anim->SetAnimFlipX(false);

		curRoleActor = m_anim->getCurRoleActorBase();
		if (NULL != curRoleActor)
		{
			curRoleActor->SetAnimationEventListener(this);
		}
	}
}

void SpriteBase::PauseAnimation()
{
	if (m_anim)
	{
		m_anim->PauseAllArmatureAnim();
	}
}

void SpriteBase::SetIsNeedCalAttachBox(bool _isNeedCalAttachBox)
{
	this->isNeedCalAttachBox = _isNeedCalAttachBox;
}

unsigned int SpriteBase::GetCurAnimFrame()
{
	if (m_anim)
	{
		return m_anim->GetCurAnimFrame();
	}
	return 0;
}

CCRect SpriteBase::GetCurColliderRect(bool bRelativeSelf /* = false */)
{
	CCAreaData areaData;
	if (m_anim)
	{
		//if (isNeedCalAttachBox)
		{
			areaData = m_anim->GetCurColliderRect();
			unsigned int width = MapDataCenter::Get()->GetOnePhysicalCellWidth();
			unsigned int height = MapDataCenter::Get()->GetOnePhysicalCellHeight();
			CCPoint pos = CCPointZero;
			if (false == bRelativeSelf)
			{
				pos = this->getPosition();
			}			
			areaData.upLeftX = pos.x + areaData.upLeftX * width;
			areaData.downRightX = pos.x + areaData.downRightX * width;
			areaData.upLeftY = pos.y + areaData.upLeftY * height;
			areaData.downRightY = pos.y + areaData.downRightY * height;
		}
	}
	return areaData.ToRect();
}

CCRect SpriteBase::GetCurAttackBox(bool bRelativeSelf /* = false */)
{
	CCAreaData areaData;
	if (m_anim)
	{
		if (isNeedCalAttachBox)
		{
			CCPoint pos = CCPointZero;
			if (false == bRelativeSelf)
			{
				pos = this->getPosition();
			}		
			unsigned int width = MapDataCenter::Get()->GetOnePhysicalCellWidth();
			unsigned int height = MapDataCenter::Get()->GetOnePhysicalCellHeight();
			areaData = m_anim->GetCurAttackBox();
			areaData.upLeftX = pos.x + areaData.upLeftX * width;
			areaData.downRightX = pos.x + areaData.downRightX * width;
			areaData.upLeftY = pos.y + areaData.upLeftY * height;
			areaData.downRightY = pos.y + areaData.downRightY * height;

		}
	}
	return areaData.ToRect();
}

CCRect SpriteBase::GetCurViewRect(bool bRelativeSelf /* = false */)
{
	CCAreaData areaData;
	if (m_anim)
	{
		CCPoint pos = CCPointZero;
		if (false == bRelativeSelf)
		{
			pos = this->getPosition();
		}		
		unsigned int width = MapDataCenter::Get()->GetOnePhysicalCellWidth();
		unsigned int height = MapDataCenter::Get()->GetOnePhysicalCellHeight();
		areaData = m_anim->GetCurViewRect();
		areaData.upLeftX = pos.x + areaData.upLeftX * width;
		areaData.downRightX = pos.x + areaData.downRightX * width;
		areaData.upLeftY = pos.y + areaData.upLeftY * height;
		areaData.downRightY = pos.y + areaData.downRightY * height;
	}
	return areaData.ToRect();
}

void SpriteBase::SetAnimFlipX(bool bFlipsX /* = false */ )
{
	if (m_anim)
	{
		m_anim->SetAnimFlipX(bFlipsX);
	}	
}

bool SpriteBase::IsAnimFlipX()
{
	if (m_anim)
	{
		return m_anim->IsCurAnimFlipX();
	}
	
	return false;
}

unsigned int SpriteBase::GetCurAnimId()
{
	if (m_anim)
	{
		return m_anim->GetCurAnimId();
	}
	return 0;
}

void SpriteBase::animationHandler(const char* _aniType, const char* _aniID, const char* _frameID)
{
}

void SpriteBase::MoveToTargetPos(const CCPoint &pt,bool bPixelPos /* = true */)
{

}

void SpriteBase::InitName(CCNode* pParentNode,std::string name,int zOrder)
{
	if (pParentNode)
	{
		if (nameLabel == NULL)
		{
			nameLabel = CCLabelTTF::create(name.c_str(),"Marker Felt",30);
			nameLabel->setColor(ccc3(255,0,0));
			pParentNode->addChild(nameLabel,zOrder);
		}
		else
		{
			nameLabel->setString(name.c_str());
		}
	}
}

void SpriteBase::update(float dt)
{
	// Note: 更新名字Label的位置
	if (nameLabel)
	{
		nameLabel->setPosition(ccp(this->getPosition().x,this->getPosition().y + 100));
	}
}

void SpriteBase::ReSchedualArmature()
{
	if (m_anim)
	{
		m_anim->ReSchedualArmature();
	}
}

void SpriteBase::drawEditorRect()
{
#ifdef DRAW_EDITOR_RECT
	CCRect attachRect = GetCurAttackBox(true);
	Painter::drawRect(attachRect,0, 0, 255, 255);
	CCRect colliderRect = GetCurColliderRect(true);
	Painter::drawRect(colliderRect,255, 0, 255, 255);
	CCRect viewRect = GetCurViewRect(true);
	Painter::drawRect(viewRect,255, 255, 0, 255);
#endif
}

void SpriteBase::draw()
{
	drawEditorRect();
	CCNode::draw();
}