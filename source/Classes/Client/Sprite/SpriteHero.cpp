#include "SpriteHero.h"
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

SpriteHero::SpriteHero(int type):
	SpriteHeroBase(type,SpriteHeroBase::LEFT)
{
}

SpriteHero::~SpriteHero()
{
}

void SpriteHero::update(float dt)
{
	SpriteHeroBase::update(dt);
}

void SpriteHero::animationHandler(const char* _aniType, const char* _aniID, const char* _frameID)
{
	SpriteHeroBase::animationHandler(_aniType,_aniID,_frameID);
}

void SpriteHero::HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg)
{
	SpriteHeroBase::HandlerMessage(cmd,msg);
}

void SpriteHero::Die()
{
	SpriteHeroBase::Die();
}