#include "SpriteCastle.h"
#include "CommonUtils.h"
#include "GameManager/BattleManger.h"
#include "Layers/Game/BattleLayer.h"
#include "GameManager/CommonLookUpUtils.h"
#include "../../Engine/Network/OnlineNetworkManager.h"
#include "../../Engine/NetWork/cs_battle.pb.h"
#include "../../Engine/Network/MessageHandler.h"
#include "Layers/Game/LayerCommonEnum.h"

SpriteCastle::SpriteCastle(int type):
	SpriteCastleBase(type,SpriteCastleBase::LEFT)
{
}

SpriteCastle::~SpriteCastle()
{
}

void SpriteCastle::update(float dt)
{
	SpriteCastleBase::update(dt);
}

void SpriteCastle::animationHandler(const char* _aniType, const char* _aniID, const char* _frameID)
{
	SpriteCastleBase::animationHandler(_aniType,_aniID,_frameID);
}

void SpriteCastle::HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg)
{
	SpriteCastleBase::HandlerMessage(cmd,msg);
}

void SpriteCastle::Die()
{
	SpriteCastleBase::Die();
}