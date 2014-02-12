// TAOMEE GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Taomee Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 2012-2015 Taomee Game Technologies. 
//      All Rights Reserved.
//
// Taomee Game Technologies, Shanghai, China
// http://www.taomee.com
//
#include "../../../Engine/NetWork/OnlineNetworkManager.h"
#include "NormalAttackState.h"
#include "SkillDispMgr.h"
#include "IdleState.h"
#include "../../Sprite/UserData.h"
#include "actions/CCActionInstant.h"
#include "../../Particle/ParticleManager.h"
#include "../../Map/MapPhysicalLayer.h"

NormalAttackState::NormalAttackState(BaseAttackEvt* pEvt) : BaseAttackState(pEvt)
{
	m_Type = ToNormalAttack;
}

bool NormalAttackState::Entered()
{
	if (false == BaseAttackState::Entered())
		return false;
	
	m_attackBoxFrame = -1;

	MagicAnimHandler* pAnimHandler = (MagicAnimHandler*)m_pStateFactory->Create(ToMagicAnimHandler, m_skillID);

	Push(pAnimHandler);
	
	m_attackDir = pAnimHandler->GetAttackDir();
	m_attackDisplacement = pAnimHandler->GetEffectDisplacement();

	bool bAttackChecker = true;
	if(bAttackChecker)
	{
		Push(m_pStateFactory->Create(ToAttackCheckerHandler, m_pEvt->m_skillId));

	}
	

	//Push(m_pStateFactory->Create(ToAttackSenderHandler, m_skillID));
	
	//Push(m_pStateFactory->Create(ToSkillBeginSenderHandler, m_skillID));
	

	return true;
}

void NormalAttackState::Exited()
{
	BaseAttackState::Exited();
	StatePoller::Exit();
}

void NormalAttackState::Update(float dt)
{
	BaseAttackState::Update(dt);
	StatePoller::Update(dt);

	// ÇÐ»»µ½ËÀÍö×´Ì¬
	if(m_pRole)
	{
		if(m_pRole->GetHeroInfo().curBlood <= 0)
		{
			ChangeState(ToDie);
			return;
		}
	}


	if(m_pSkill->effectId > 0 && m_pSkill->longDistanceAttackRange)
	{
			cocos2d::CCRect heroAttackBox = m_pRole->GetCurAttackBox();
			if(heroAttackBox.size.width > 0 || heroAttackBox.size.height > 0)
			{
				if(m_pSkillStateMachine)
				{
					int curFrame = m_pRole->GetCurAnimId();
					if(m_attackBoxFrame == -1)
					{
						m_attackBoxFrame = curFrame;
						NormalMagicFireBallState* pNormalMagicFireBall = (NormalMagicFireBallState*)m_pStateFactory->Create(ToNormalMagicFireBall, m_skillID);
						pNormalMagicFireBall->SetAttackDir(m_attackDir, m_attackDisplacement);
						
						m_pSkillStateMachine->Push(pNormalMagicFireBall);
					}

					
				}
			}
		
	}
}


void NormalAttackState::Reset()
{

}


// ---------------------------------------------------------------------------------------------------------------------


NormalMagicFireBallState::NormalMagicFireBallState(BaseAttackEvt * pEvt) : BaseAttackState(pEvt)

{
	m_Type = ToNormalMagicFireBall;
//	m_HighPriority.push_back(ToSpecialAttack);
}


bool NormalMagicFireBallState::Entered()
{
	if (false == BaseAttackState::Entered())
		return false;
	EffectAnimHandler* pEffectAnimHandler = dynamic_cast<EffectAnimHandler*>(m_pStateFactory->Create(ToEffectAnimHandler, m_skillID));
	if(pEffectAnimHandler)
	{
		pEffectAnimHandler->SetAttackDir( m_attackDir, m_attackDisplacement);
		Push(pEffectAnimHandler);
	}

	if(m_pSkill->effectId > 0)
	{
		MagicCheckerHandler* pMagicChecker = dynamic_cast<MagicCheckerHandler*>(m_pStateFactory->Create(ToMagicCheckHandler, m_skillID));
		if(pMagicChecker)
		{
			if(pEffectAnimHandler)
			{
				pMagicChecker->SetEffect(pEffectAnimHandler->GetEffect());
			}
			Push(pMagicChecker);
		}
	}
	return true;
}

void NormalMagicFireBallState::Exited()
{
	BaseAttackState::Exited();
	StatePoller::Exit();
}

void NormalMagicFireBallState::Update(float dt)
{
	BaseAttackState::Update(dt);
	StatePoller::Update(dt);
}


void NormalMagicFireBallState::Reset()
{
	BaseAttackState::Reset();
}

void NormalMagicFireBallState::SetAttackDir( CCPoint dir, float displacement )
{
	m_attackDir = dir;
	m_attackDisplacement = displacement;

}


