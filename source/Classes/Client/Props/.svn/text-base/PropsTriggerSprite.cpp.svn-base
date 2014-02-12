#include "PropsTriggerSprite.h"
#include "PropsTriggerManager.h"
#include "Map/MapPhysicalLayer.h"
#include "Sprite/SpriteHero.h"

PropTriggerSprite::PropTriggerSprite(CCNode* pParentNode,std::string frameFileName,PropsType propType,PropTriggerData _triggerData):
	PropTriggerBase(pParentNode,frameFileName,propType,_triggerData)
{
}

PropTriggerSprite::~PropTriggerSprite()
{

}

void PropTriggerSprite::OnTriggerEnter(SpriteBase* pNode,SpriteType type)
{
	if (pNode)
	{
		if (triggerData.isExplosionSelf)
		{
			return ;
		}
		
		switch (type)
		{
		case kType_Sprite_Hero:
			{
				CCLog("kType_Sprite_Hero Trigger Enter");
				SpriteHero* pHero = dynamic_cast<SpriteHero*>(pNode);
				if (pHero)
				{
					//pHero->UseProp(propType,this->getPosition());
				}
				isDeleteSelf = true;
			}
			break;
		case kType_Sprite_Oth_Hero:
			break;
		case kType_Sprite_Trigger:
			break;
		case kType_Sprite_Prop:
			break;
		case kType_Sprite_UnKnow:
			break;
		default:
			break;
		}
	}	
}