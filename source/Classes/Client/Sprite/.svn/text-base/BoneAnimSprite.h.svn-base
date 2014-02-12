#pragma once

#include "cocos2d.h"
#include "SkeletonAnimCommonDefine.h"
#include "RoleActorBase.h"
#include "Client/BoneAniManager/BoxDefine.h"

class RoleActorBase;

/// <summary>
//	中间层，用于管理角色所有的动作
/// </summary>
class BoneAnimSprite
{
public:
	BoneAnimSprite(int Type);	
	virtual ~BoneAnimSprite();

	void SetAnim(int animId, int nloop, bool isLoop);
	void SetAnimPauseOnOver(bool bPause = false);
	void PauseAllArmatureAnim();
	void SetAnimFlipX(bool bFlipsX = false);
	void SetOpacity(int opacity);

	unsigned int GetCurAnimId()
	{
		return m_nCurAnimId;
	}
	RoleActorBase * getCurRoleActorBase()
	{
		return m_curRoleActorBase;
	}	

	bool IsCurAnimFlipX()
	{
		return m_bCurAnimFlip;
	}

	int GetRcsTypeId(){
		return m_nRoleTypeId;
	}

	void addArmatureNodeToParentNode(CCNode *root,int depth);
	void SetArmatureOpacity(GLubyte var);

	void SetAnimUpdateOrNot(bool bUpdate);
	void SetAnimationEventListener(CCAnimationEventListener* pListener);

	// Note: abbox info getter
	CCAreaData GetCurViewRect();
	CCAreaData GetCurColliderRect();
	CCAreaData GetCurAttackBox();

	unsigned int GetCurAnimFrame();

	void ReSchedualArmature();
protected:
	unsigned int m_nRoleTypeId;
	bool m_bCurAnimLoop;
	bool m_bCurAnimFlip;
	int	 m_nCurAnimId;
	int m_nCurFrame;
	std::map<std::string,RoleActorBase*> *m_armatureNameAndActorMap;
	OneRoleActorData *m_armatureActionData;
	RoleActorBase *m_curRoleActorBase;	
	// Note: abbox info
	//std::map<unsigned int,CCMoveAreaData> m_animIdAndMoveAreaData;
	//std::map<std::string,CCAreaData> m_armatureNameAndAreaData;
	CCMoveAreaData	m_moveAreaData;
	CCAreaData		m_viewAreaData;
	// Note: 优化碰撞框获取速度
	CCColliderData m_colliderData;
	std::map<std::string,CCAreaData> m_kvViewData;
};