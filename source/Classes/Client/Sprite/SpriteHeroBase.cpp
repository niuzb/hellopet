#include "Sprite/SpriteHeroBase.h"
#include "CommonUtils.h"
#include "../SpriteBehavior/HeroBehavior/HeroRunState.h"
#include "../SpriteBehavior/RoleState/BaseAttackState.h"
#include "../SpriteBehavior/RoleState/IdleState.h"
#include "../SpriteBehavior/RoleState/DieState.h"
#include "GameManager/BattleManger.h"
#include "Layers/Game/BattleLayer.h"
#include "GameManager/CommonLookUpUtils.h"
#include "../../Engine/Network/OnlineNetworkManager.h"
#include "../../Engine/NetWork/cs_battle.pb.h"
#include "../../Engine/Network/MessageHandler.h"
#include "Props/PropBase.h"
#include "Props/PropManager.h"
#include "Layers/Game/LayerCommonEnum.h"
#include "cocos-ext.h"
#include "Map/MapPhysicalLayer.h"
#include "GameManager/NotificationCenterDefiner.h"

USING_NS_CC_EXT;

SpriteHeroBase::SpriteHeroBase(int type,SpriteHeroBase::SIDE side)
	: SpriteBase(type)
	, m_battleSide(side)
	, m_isStateMachineStart(false)
	, m_posYInCell(0)
	, m_pBloorBar(NULL)
	, m_pShadowSprite(NULL)
	, m_pStateMachine(NULL)
	, m_pStateFactory(NULL)
{
	CHeroPhysicalLayer::Get()->Register(this);

	isNeedCalAttachBox = true;
	m_pBloorBar = SpriteDecorationBatchNode::Get()->CreateBloodBar(this);
	m_pShadowSprite = SpriteDecorationBatchNode::Get()->CreateShadow(this);

	m_pStateMachine = new SkillStateMachine(); 
	m_pStateFactory = new StateFactory(this);

	CCNotificationCenter::sharedNotificationCenter()->postNotification(NotificationFlag[ENoticePlayerCreat],this);
}

SpriteHeroBase::~SpriteHeroBase()
{
	CHeroPhysicalLayer::Get()->UnRegister(this);

	CC_SAFE_DELETE(m_pStateFactory);
	CC_SAFE_DELETE(m_pStateMachine);

	BattleLayer* pBattleLayer = CommonLookUpUtils::GetBattleLayer();
	if (pBattleLayer)
	{
		BattleManager* pBattleMgr = pBattleLayer->GetBattleManager();
		if (pBattleMgr)
		{
			pBattleMgr->RemoveOneHeroFromBattle(this);
		}
	}

	// Note: 删除血量跳
	SpriteDecorationBatchNode::Get()->RemoveBloodBar(this);
	m_pBloorBar = NULL;
	SpriteDecorationBatchNode::Get()->RemoveShadow(this);
	m_pShadowSprite = NULL;

	CCNotificationCenter::sharedNotificationCenter()->postNotification(NotificationFlag[ENoticePlayerDie],this);
}

void SpriteHeroBase::StartStateMachine()
{
	if (m_pStateMachine && m_pStateFactory)
	{
		if(!m_pStateMachine->CheckStateRuning(ToRun))
			m_pStateMachine->Push(m_pStateFactory->Create(ToRun, m_heroInfo.skillID));

		m_isStateMachineStart = true;
	}
}

void SpriteHeroBase::PlayOneAnimation(int animId, int nloop, bool isLoop /* = true */)
{
	SpriteBase::PlayOneAnimation(animId,nloop,isLoop);
	if (m_battleSide == SpriteHeroBase::LEFT)
	{
		this->SetAnimFlipX(true);
	}
	else
	{
		this->SetAnimFlipX(false);
	}
}

void SpriteHeroBase::update(float dt)
{
	SpriteBase::update(dt);

	if(m_pStateMachine)
	{
		m_pStateMachine->Update(dt);
	}
	// Note: 更新血条的位置
	if (m_pBloorBar)
	{
		m_pBloorBar->update(this);
		float bloodPercentage = 0;
		if (m_heroInfo.totalBlood != 0)
		{
			bloodPercentage = m_heroInfo.curBlood / ((float)m_heroInfo.totalBlood);
		}		
		m_pBloorBar->SetBloodPercentage(bloodPercentage);
	}
	if (m_pShadowSprite)
	{
		m_pShadowSprite->setPosition(this->getPosition());
	}
}

void SpriteHeroBase::animationHandler(const char* _aniType, const char* _aniID, const char* _frameID)
{
	SpriteBase::animationHandler(_aniType,_aniID,_frameID);
}

void SpriteHeroBase::HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg)
{
}

void SpriteHeroBase::Die()
{
}

void SpriteHeroBase::setVisible(bool visible)
{
	if (m_pBloorBar)
	{
		m_pBloorBar->setVisible(visible);
	}
	if (m_pShadowSprite)
	{
		m_pShadowSprite->setVisible(visible);
	}
	CCNode::setVisible(visible);
}

void SpriteHeroBase::setPosition(const CCPoint &position)
{
	m_prevPos = this->getPosition();
	CCNode::setPosition(position);

	CHeroPhysicalLayer::Get()->ChangePos(this);
}