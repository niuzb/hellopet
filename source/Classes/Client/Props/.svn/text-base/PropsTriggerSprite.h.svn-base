#ifndef _PROPS_SPRITE_H_
#define _PROPS_SPRITE_H_

#include "SpriteBase.h"
#include "SpriteBaseNode.h"
#include "Sprite/SpriteDefiner.h"
#include "Props/PropsDefiner.h"
#include "cocos2d.h"
#include "PropsDataCenter.h"
#include "PropsTriggerBase.h"

USING_NS_CC;

class PropTriggerSprite : public PropTriggerBase
{
public:
	PropTriggerSprite(CCNode* pParentNode,std::string frameFileName,PropsType propType,PropTriggerData _triggerData);
	virtual ~PropTriggerSprite();

	virtual void OnTriggerEnter(SpriteBase* pNode,SpriteType type);
};

#endif	//_PROPS_SPRITE_H_