#ifndef _PROP_BASE_H_
#define _PROP_BASE_H_

#include "PropsDefiner.h"
#include "Sprite/SpriteHero.h"
#include "Sprite/SpriteBaseNode.h"

class CCParticleAnimationEventListener{
public:
	virtual void animationHandler(CCNode* pNode,const char* _aniType, const char* _aniID, const char* _frameID) = 0;
};

class PropBase : public CCParticleAnimationEventListener,public CCNode
{
public:
	PropBase(PropsType propType,SpriteBase* pUserSprite,CCNode* pParentNode,bool isHero);
	virtual ~PropBase();
	virtual void UseProp(CCPoint pt,bool bPlaySound = true);

	virtual void Update(float dt) = 0;	
	virtual void animationHandler(CCNode* pNode,const char* _aniType, const char* _aniID, const char* _frameID) = 0;
	virtual void PreloadAnimRcs() = 0;
	/**
	* Instruction : Ïú»Ù×ÔÉí
	* @param : 
	* @result : 
	*/
	virtual void DestroySelf();

	PropsType GetPropType(){
		return mPropType;
	}
	CCNode* GetUserSprite(){
		return mUserSprite;
	}
	void SetIsDestroySelfWhenEnd(bool bDestorySelfWhenEnd){
		m_isDestorySelfWhenEnd = bDestorySelfWhenEnd;
	}
	bool GetIsDestroySelfWhenEnd(){
		return m_isDestorySelfWhenEnd;
	}
protected:
	PropsType mPropType;
	bool mIsHero;
	SpriteBase* mUserSprite;
	unsigned int mAnimRcsId;
	CCNode* mParentNode;
	CCPoint mDirection;
	bool m_isDestorySelfWhenEnd;
	unsigned int m_nSoundId;
};

#endif	//_PROP_BASE_H_