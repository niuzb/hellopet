#ifndef SPRITE_BASE_H
#define SPRITE_BASE_H

#include "cocos2d.h"
#include "BoneAnimSprite.h"
#include "SpriteBaseNode.h"

class SkillStateMachine;
class StateFactory;

USING_NS_CC;

class SpriteBase : public CCNode, public cocos2d::CCTargetedTouchDelegate,public CCAnimationEventListener
{
public: 
	SpriteBase(int type);
	virtual ~SpriteBase();

	virtual void PlayOneAnimation(int animId, int nloop, bool isLoop = true);
	//virtual void SetAnimPauseOnOver(bool bPauseOnOver = false);
	virtual void PauseAnimation();
	virtual void SetAnimFlipX(bool bFlipsX = false );
	virtual bool IsAnimFlipX();
	virtual void animationHandler(const char* _aniType, const char* _aniID, const char* _frameID);
	//virtual void SetUpdateOrNot(bool bUpdate);

	//unsigned int GetAnimID(void);
	//bool IsAnimFlipX(void);
	//void SetSpriteOpacity(GLubyte var);	

	void SetIsNeedCalAttachBox(bool _isNeedCalAttachBox);
	virtual CCRect GetCurColliderRect(bool bRelativeSelf = false);
	virtual CCRect GetCurAttackBox(bool bRelativeSelf = false);
	virtual CCRect GetCurViewRect(bool bRelativeSelf = false);
	virtual unsigned int GetCurAnimId();

	unsigned int GetCurAnimFrame();

	int GetRcsTypeId(){
		if (m_anim)
		{
			return m_anim->GetRcsTypeId();
		}
		return 0;
	}
	virtual void MoveToTargetPos(const CCPoint &pt,bool bPixelPos = true);
	virtual void InitName(CCNode* pParentNode,std::string name,int zOrder);
	virtual void update(float dt);
	// Note: 重新让Armature Update工作
	void ReSchedualArmature();
	// Note: 和绘制相关接口
	virtual void draw();
	void drawEditorRect();
protected:
	//check touch event
	virtual cocos2d::CCRect		getRect();
	virtual bool				canDealWithTouch(cocos2d::CCTouch* touch);
	virtual bool				containsTouchLocation(cocos2d::CCTouch* touch);	
	virtual bool				isTouchSelf(cocos2d::CCPoint pt);
protected:
	BoneAnimSprite*	m_anim;
	CCLabelTTF* nameLabel;
	bool	isNeedCalAttachBox;
	bool	isAnimFlip;
};

#endif