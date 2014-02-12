#include "SpriteOthCastle.h"
#include "CommonUtils.h"
#include "GameManager/BattleManger.h"
#include "Layers/Game/BattleLayer.h"
#include "GameManager/CommonLookUpUtils.h"
#include "../../Engine/Network/OnlineNetworkManager.h"
#include "../../Engine/NetWork/cs_battle.pb.h"
#include "../../Engine/Network/MessageHandler.h"
#include "Layers/Game/LayerCommonEnum.h"

SpriteOthCastle::SpriteOthCastle(int type):
	SpriteCastleBase(type,SpriteCastleBase::RIGHT)
{
}

SpriteOthCastle::~SpriteOthCastle()
{
}

void SpriteOthCastle::update(float dt)
{
	SpriteCastleBase::update(dt);
}

void SpriteOthCastle::animationHandler(const char* _aniType, const char* _aniID, const char* _frameID)
{
	SpriteCastleBase::animationHandler(_aniType,_aniID,_frameID);
}

void SpriteOthCastle::HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg)
{
	SpriteCastleBase::HandlerMessage(cmd,msg);
}

void SpriteOthCastle::Die()
{
	SpriteCastleBase::Die();
}