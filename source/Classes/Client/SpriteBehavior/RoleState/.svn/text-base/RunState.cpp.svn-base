#include "RunState.h"
#include "Sprite/SpriteDefiner.h"
#include "Sprite/SpriteBase.h"
#include "Sprite/SpriteHero.h"
#include "../../GameManager/CommonLookUpUtils.h"
#include "../../Layers/Game/BattleLayer.h"
#include "../../Map/MapPhysicalLayer.h"

RunState::RunState(BaseAttackEvt *pEvt) : BaseAttackState(pEvt)
	, m_fStartTime(0)
	, m_bPrepare(false)
{
	m_Type = ToRun;
	m_LowPriority.push_back(ToIdle);
}


RunState::~RunState( void )
{

}


unsigned int RunState::SetRunDir(bool bInMainLandLevel /* = true */)
{
	int actionID = 0;
	// 判断是否在主城中

	m_pRole->PlayOneAnimation(actionID, 1, true);
	return actionID;
}

bool RunState::Entered()
{
	if (false == BaseAttackState::Entered()) 
		return false;

	m_pRole->PlayOneAnimation(kTypeRun_FaceHor_OTH, 1, true);
	

	return true;
}

void RunState::Exited()
{
	BaseAttackState::Exited();
	//m_pRole->SetSpeed(1.0f);
	//m_bPrepare = true;
	//if(m_pRole->getTag() == MAP_TAG_SEER)
	//{
	//	//if(GameAudioManager::sharedManager()->isEffectIsPlaying(321009))
	//		GameAudioManager::sharedManager()->stopEffect(SOUND_EFFECT_WALK);
	//}
	//CCLog("RunState::Exited()");
}

void RunState::Update(float dt)
{
	BaseAttackState::Update(dt);
	
	// 切换到死亡状态
	if(m_pRole)
	{
		// TODO : 要服务器把血量发了过来。
		if(m_pRole->GetHeroInfo().curBlood <= 0)
		{
			ChangeState(ToDie);
			return;
		}
	}

	// 切换到战斗状态 
	SpriteHeroBase* pOtherHero = CHeroPhysicalLayer::Get()->FindNearestHero(m_pRole->GetBattlePos(), m_pSkill->longDistanceAttackRange, m_pRole->GetBattleSide());
	if(pOtherHero)
	{
		ChangeState(ToNormalAttack);
		return;
				
	}
	

	

	//if(m_pRole->getTag() == MAP_TAG_SEER)
	//{
	//	m_fSoundTime -= dt;
	//	if(m_fSoundTime <= 0.0f)
	//	{
	//		GameAudioManager::sharedManager()->playEffect(SOUND_EFFECT_WALK, false);
	//		m_fSoundTime = 1.0f;
	//	}
	//}
	//

	//// accumulate time 
	//m_fStartTime += dt;

	//if (m_fStartTime > 0.1f && m_bPrepare)
	//{
	//	m_pRole->SetSpeed(1.0f);
	//	m_bPrepare = false;
	//}
	//else
	//{
	//	/*if (m_pRole->getDirection() != m_CurfaceDir)
	//	{
	//	bool bMainLandLevel = MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId());

	//	SetRunDir(bMainLandLevel);
	//	}*/
	//}
	//	
	//if (MOVE_BY_JOY == m_pRole->GetMoveType())
	//{
	//	m_pRole->moveByJoystick(dt);
	//}

	if (m_pRole)
	{
		CCPoint pos = m_pRole->getPosition();
		SpriteHeroBase* pHero = dynamic_cast<SpriteHeroBase*>(m_pRole);
		if (pHero)
		{
			if (pHero->GetBattleSide() == SpriteHeroBase::LEFT)
			{
				m_pRole->setPosition(ccp(pos.x + dt*50,pos.y));
			}
			else
			{
				m_pRole->setPosition(ccp(pos.x - dt*50,pos.y));
			}
		}		
	}
	
}

void RunState::Reset()
{
	BaseAttackState::Reset();
}