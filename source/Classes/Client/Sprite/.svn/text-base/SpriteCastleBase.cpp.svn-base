#include "SpriteCastleBase.h"
#include "CommonUtils.h"
#include "GameManager/BattleManger.h"
#include "Layers/Game/BattleLayer.h"
#include "GameManager/CommonLookUpUtils.h"
#include "../../Engine/Network/OnlineNetworkManager.h"
#include "../../Engine/NetWork/cs_battle.pb.h"
#include "../../Engine/Network/MessageHandler.h"
#include "Layers/Game/LayerCommonEnum.h"
#include "cocos-ext.h"
#include "Map/MapPhysicalLayer.h"
#include "../SpriteBehavior/RoleState/BaseAttackState.h"

USING_NS_CC_EXT;

SpriteCastleBase::SpriteCastleBase(int typeId,SpriteCastleBase::SIDE side)
	: SpriteBase(typeId)
	, m_battleSide(side)
	, m_pBloorBar(NULL)
{
	isNeedCalAttachBox = true;
	m_pBloorBar = SpriteDecorationBatchNode::Get()->CreateBloodBar(this);
}

SpriteCastleBase::~SpriteCastleBase()
{
	BattleLayer* pBattleLayer = CommonLookUpUtils::GetBattleLayer();
	if (pBattleLayer)
	{
		BattleManager* pBattleMgr = pBattleLayer->GetBattleManager();
		if (pBattleMgr)
		{
			pBattleMgr->RemoveCastleFromBattle(this);
		}
	}	

	// Note: 删除血量跳
	SpriteDecorationBatchNode::Get()->RemoveBloodBar(this);
	m_pBloorBar = NULL;
}

void SpriteCastleBase::PlayOneAnimation(int animId, int nloop, bool isLoop /* = true */)
{
	SpriteBase::PlayOneAnimation(animId,nloop,isLoop);
	if (m_battleSide == SpriteCastleBase::LEFT)
	{
		this->SetAnimFlipX(true);
	}
	else
	{
		this->SetAnimFlipX(false);
	}
}

void SpriteCastleBase::update(float dt)
{
	SpriteBase::update(dt);

	// Note: 更新血条的位置
	if (m_pBloorBar)
	{
		m_pBloorBar->update(this);
		float bloodPercentage = 0;
		if (m_castleInfo.blood != 0)
		{
			bloodPercentage = m_castleInfo.curBlood / ((float)m_castleInfo.blood);
		}		
		m_pBloorBar->SetBloodPercentage(bloodPercentage);
	}
}

void SpriteCastleBase::animationHandler(const char* _aniType, const char* _aniID, const char* _frameID)
{
	SpriteBase::animationHandler(_aniType,_aniID,_frameID);
}

void SpriteCastleBase::HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg)
{
}

void SpriteCastleBase::Die()
{
}

void SpriteCastleBase::setVisible(bool visible)
{
	if (m_pBloorBar)
	{
		m_pBloorBar->setVisible(visible);
	}
	CCNode::setVisible(visible);
}