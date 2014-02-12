#ifndef _PROPS_TRIGGER_BASE_H_
#define _PROPS_TRIGGER_BASE_H_

#include "SpriteBase.h"
#include "SpriteBaseNode.h"
#include "Sprite/SpriteDefiner.h"
#include "Props/PropsDefiner.h"
#include "cocos2d.h"
#include "PropsDataCenter.h"

USING_NS_CC;

class TriggerEventListener
{
public:
	TriggerEventListener();
	virtual ~TriggerEventListener();
	virtual void OnTriggerEnter(SpriteBase* pNode,SpriteType type) = 0;
	virtual CCAreaData GetColliderArea() = 0;
};

class PropTriggerBase : public CCNode,public TriggerEventListener
{
public:
	PropTriggerBase(CCNode* pParentNode,std::string frameFileName,PropsType propType,PropTriggerData _triggerData);
	virtual ~PropTriggerBase();

	virtual void Update(float dt,bool &bDeleteSelf);
	virtual void OnTriggerEnter(SpriteBase* pNode,SpriteType type) = 0;
	virtual CCAreaData GetColliderArea();

	virtual void setPosition(const CCPoint &position);
	virtual const CCPoint& getPosition();
	virtual void setScale(float fScale);
	virtual void setVisible(bool visible);

	virtual void destroy();
	PropsType GetPropType(){
		return propType;
	}

	CCSprite* GetDisplaySprite(){
		return displaySprite;
	}
	void SetIsPreload(bool bPreload){
		m_isPreload = bPreload;
	}
protected:
	enum PropAnimationType
	{
		kType_Prop_Born = 0,
		kType_Prop_Move,
		kType_Prop_UnKnow
	};
	// Note: Animation
	virtual void StartAnimation(PropAnimationType animationType);
	virtual void StartBornAnimation();
	virtual void StartMoveAnimation();
	virtual void ScaleAnimationOver();	
protected:
	float runningTime;
	bool  isDeleteSelf;		
	CCSprite* displaySprite;
	PropTriggerData triggerData;
	PropsType propType;
	PropAnimationType animationType;
	bool m_isPreload;
};

#endif	//_PROPS_TRIGGER_BASE_H_