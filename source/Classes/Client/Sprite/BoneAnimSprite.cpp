#include "BoneAnimSprite.h"
#include "cocos2d.h"
#include <string.h>
#include "CConnectionData.h"
#include "SkeletonAnimRcsManager.h"
#include "BoneAniManager/AnimABBoxDataCenter.h"

USING_NS_CC;

BoneAnimSprite::BoneAnimSprite(int id)
		: m_nCurFrame(-1),
		m_nRoleTypeId(id),
		m_armatureNameAndActorMap(NULL),
		m_armatureActionData(NULL),
		m_curRoleActorBase(NULL)
{	
	m_armatureNameAndActorMap = SkeletonAnimRcsManager::Get()->CreateOneRoleArmatures(id,false);
	m_armatureActionData = SkeletonAnimRcsManager::Get()->GetOneRoleArmatureActionData(id);

	AnimABBoxDataCenter* animABBoxDataCenter = SkeletonAnimRcsManager::Get()->GetABBoxDataCenter();
	if (animABBoxDataCenter)
	{
		animABBoxDataCenter->GetRoleColliderData(id,m_colliderData);
	}
}

BoneAnimSprite::~BoneAnimSprite()
{
	if (0 != m_armatureNameAndActorMap)
	{
		for (std::map<std::string,RoleActorBase*>::iterator iter = m_armatureNameAndActorMap->begin();
			iter != m_armatureNameAndActorMap->end(); iter++)
		{
			RoleActorBase* roleActorBase = (*iter).second;
			roleActorBase->removeFromParentAndCleanup(true);
		}
		m_armatureNameAndActorMap->clear();
		CC_SAFE_DELETE(m_armatureNameAndActorMap);
	}
}

void BoneAnimSprite::addArmatureNodeToParentNode(CCNode *root,int depth)
{
	if (0 != root && m_armatureNameAndActorMap != NULL)
	{
		std::map<std::string,RoleActorBase*>::iterator iter = m_armatureNameAndActorMap->begin();
		for (;iter != m_armatureNameAndActorMap->end(); iter++)
		{
			root->addChild((*iter).second->getBatchNode(),depth);
			root->addChild((*iter).second,depth);
		}
	}
}

void BoneAnimSprite::SetAnimFlipX(bool bFlipsX /* = false */)
{
	if (0 != m_curRoleActorBase)
	{
		m_bCurAnimFlip = bFlipsX;

		float angle = 0;		
		if (bFlipsX)
		{
			angle = 180;
		}
		m_curRoleActorBase->getDisplay()->setRotationY(angle);
	}
}

void BoneAnimSprite::SetAnimPauseOnOver(bool bPause /* = false */)
{
	if (m_curRoleActorBase)
	{
		m_curRoleActorBase->getAnimation()->setIsPauseOnOver(bPause);
	}
}

void BoneAnimSprite::PauseAllArmatureAnim()
{
	std::map<std::string,RoleActorBase*>::iterator role_iter = m_armatureNameAndActorMap->begin();
	if (role_iter != m_armatureNameAndActorMap->end())
	{
		(*role_iter).second->pauseAllAnimation();
		role_iter ++;
	}
}

void BoneAnimSprite::SetAnim(int animId, int nloop, bool isLoop)
{
	m_bCurAnimLoop = isLoop;
	m_nCurAnimId = animId;

	RoleActorBase *preActorBase = m_curRoleActorBase;

	const std::map<int,OneAnimActorData > oneRoleActors = m_armatureActionData->GetOneRoleActorData();
	std::map<int,OneAnimActorData>::const_iterator action_iter = oneRoleActors.find(animId);		
	if (action_iter == oneRoleActors.end())
	{
		return ;
	}

	OneAnimActorData animActor = (*action_iter).second;
	std::string armature_name = animActor.GetXmlFileName();
	std::string actionName = animActor.GetActionName();

	std::map<std::string,RoleActorBase*>::iterator role_iter = m_armatureNameAndActorMap->find(armature_name);
	if (role_iter != m_armatureNameAndActorMap->end())
	{
		m_curRoleActorBase = (*role_iter).second;
		if (NULL != preActorBase && preActorBase != m_curRoleActorBase)
		{		
			preActorBase->pauseAllAnimation();
		}

		SetAnimFlipX(false);	
		m_curRoleActorBase->getAnimation()->playTo((void *)actionName.c_str(),-1,-1,isLoop);	
		m_curRoleActorBase->resumeAllAnimation();
		m_curRoleActorBase->getCurBoneLst();

		// Note: 拉取当前动画所对应的ABBox信息
		AnimABBoxDataCenter* animABBoxDataCenter = SkeletonAnimRcsManager::Get()->GetABBoxDataCenter();
		if (animABBoxDataCenter)
		{
			std::map<int,CCMoveAreaData>::iterator moveAreaIter = m_colliderData.kvMoveIdAndAreaData.find(animId);
			if (moveAreaIter != m_colliderData.kvMoveIdAndAreaData.end())
			{
				m_moveAreaData = (*moveAreaIter).second;
			}        
			else
			{
				m_moveAreaData.reset();
			}

			bool bNeedCehckViewRect = false;
			if (preActorBase == NULL)
			{
				bNeedCehckViewRect = true;
			}
			else
			{
				if (preActorBase != m_curRoleActorBase)
				{
					bNeedCehckViewRect = true;
				}
			}
			if (bNeedCehckViewRect)
			{
				std::map<std::string,CCAreaData>::iterator viewAreaIter = m_kvViewData.find(armature_name);
				if (viewAreaIter != m_kvViewData.end())
				{
					m_viewAreaData = (*viewAreaIter).second;
				}  
			}		
		}	
	}
	else
	{
        char buffer[100];
        sprintf("Armature Not Found %s",armature_name.c_str());
		CCAssert(true,buffer);
	}
}

void BoneAnimSprite::SetArmatureOpacity(GLubyte var)
{
	for (std::map<std::string,RoleActorBase*>::iterator iter = m_armatureNameAndActorMap->begin();
		iter != m_armatureNameAndActorMap->end(); iter++)
	{
		(*iter).second->setArmaturetOpacity(var);
	}
}

void BoneAnimSprite::SetAnimUpdateOrNot(bool bUpdate)
{
	for (std::map<std::string,RoleActorBase*>::iterator iter = m_armatureNameAndActorMap->begin();
		iter != m_armatureNameAndActorMap->end(); iter++)
	{
		(*iter).second->SetUpdateEnableOrNot(bUpdate);
	}
}

void BoneAnimSprite::SetAnimationEventListener(CCAnimationEventListener* pListener)
{
	for (std::map<std::string,RoleActorBase*>::iterator iter = m_armatureNameAndActorMap->begin();
		iter != m_armatureNameAndActorMap->end(); iter++)
	{
		(*iter).second->SetAnimationEventListener((*iter).second);
	}
}

CCAreaData BoneAnimSprite::GetCurViewRect()
{
	if (m_bCurAnimFlip)
	{
		return m_viewAreaData.FlipArea();
	}
	else
	{
		return m_viewAreaData;
	}
}

CCAreaData BoneAnimSprite::GetCurColliderRect()
{
	if (m_bCurAnimFlip)
	{
		return m_moveAreaData.selfColliderArea.FlipArea();
	}
	else
	{
		return m_moveAreaData.selfColliderArea;
	}
}

CCAreaData BoneAnimSprite::GetCurAttackBox()
{
	if (m_curRoleActorBase)
	{
		int curFrame = m_curRoleActorBase->getAnimation()->getCurFrame() *
			(float)(m_curRoleActorBase->getAnimation()->getNoScaleListFrames()) /
			(float)(m_curRoleActorBase->getAnimation()->getDurationTween());

		// 如果有多个使用者在同一帧调用这个接口，那么第一使用者得到的结果是True，第二个得到的是False，显然，这是不对的。
		//if(m_curFrame != curFrame)
		{
			std::map<int,CCAreaData>::iterator iter = m_moveAreaData.kvFrameIndexAndAreaData.find(curFrame);
			if (iter != m_moveAreaData.kvFrameIndexAndAreaData.end())
			{				
				if (m_bCurAnimFlip)
				{
					return (*iter).second.FlipArea();
				}
				else
				{
					return (*iter).second;
				}			
			}
		}

	}
	return CCAreaData();
}

unsigned int BoneAnimSprite::GetCurAnimFrame()
{
	unsigned int nFrame = 0;
	if (m_curRoleActorBase)
	{
		nFrame = m_curRoleActorBase->getAnimation()->getCurFrame();
	}
	return nFrame;
}

void BoneAnimSprite::ReSchedualArmature()
{
	for (std::map<std::string,RoleActorBase*>::iterator iter = m_armatureNameAndActorMap->begin();
		iter != m_armatureNameAndActorMap->end(); iter++)
	{
		RoleActorBase* roleActorBase = (*iter).second;
		if (roleActorBase)
		{
			roleActorBase->scheduleUpdate();
		}
	}
}