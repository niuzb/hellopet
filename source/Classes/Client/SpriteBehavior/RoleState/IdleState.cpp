
#include "IdleState.h"

IdleState::IdleState(BaseAttackEvt *pEvt) : FState(FState::ExclusiveStates, NULL)
{
	m_Type = ToIdle;
	//m_pRole = (SpriteBase *) pEvt->m_pRole;
	
	m_pEvt = pEvt;

	m_HighPriority.push_back(ToRun);
}



IdleState::~IdleState( void )
{
	if(m_pEvt)
	{
		delete m_pEvt;
		m_pEvt = NULL;
	}
	

}

bool IdleState::Entered()
{
	//CCLog("IdleState::Entered()----------------------------------");
	//if (false == FState::Entered())
	//	return false;

	//bool bMainLandLevel = MainLandManager::Get()->isMainLand(LevelManager::sShareInstance()->getCurMapId());
	//SetActorDirAndAnimation(bMainLandLevel);
	//
	//// TODO : ���˸����ǣ�����������һ�û�н�����ʱ�������Ѿ����ƶ��ˡ�
	///*if (MainMenuLayer::getUILayerByTag<BattleCoverLayer>(MainMenuLayer::getLayerTagByName("BattleCoverLayer")))
	//{
	//	MainMenuLayer::getUILayerByTag<BattleCoverLayer>(MainMenuLayer::getLayerTagByName("BattleCoverLayer"))->closeBattleCoverLayer(NULL);
	//}*/

	return true;
}

void IdleState::Exited()
{
	FState::Exited();
}

void IdleState::Update(float dt)
{
	FState::Update(dt);
}

void IdleState::Reset()
{

}