#include "LocalBattleLoadingLayer.h"
#include "SkeletonAnimRcsManager.h"
#include "GameManager/XLogicManager.h"
#include "Layers/Game/BattleLayer.h"
#include "Layers/UI/BattleUILayer.h"
#include "Layers/Game/LayerCommonEnum.h"
#include "Lua/LuaTinkerManager.h"
#include "GameManager/CommonLookUpUtils.h"
#include "Props/PropManager.h"
#include "Sound/GameAudioManager.h"

LocalBattleLoadingLayer::LocalBattleLoadingLayer():
	m_iCurStep(E_UNKNOW)
{
	m_iCurStep = E_CREATE_BATTLE_LAYER;
}

LocalBattleLoadingLayer::~LocalBattleLoadingLayer()
{
}

void LocalBattleLoadingLayer::LoadingStart()
{
	
}

void LocalBattleLoadingLayer::LoadingEnd()
{
	this->removeFromParent();
}

void LocalBattleLoadingLayer::LoadSkeletonAnim()
{
	// Note: 加载主城动画资源

	// Note: 加载英雄资源
	BattleManager* pBattleMgr = CommonLookUpUtils::GetBattleManager();
	if (pBattleMgr)
	{
		for (std::map<unsigned int,HeroInfo>::const_iterator iter = pBattleMgr->GetHeroMapInfo().begin();
			iter != pBattleMgr->GetHeroMapInfo().end();iter++)
		{
			SkeletonAnimRcsManager::Get()->LoadOneRoleRcs((*iter).second.animId,true);
			//CCLog("------------- Load One Role %d",(*iter).second.animId);
		}		
	}

	// Note: 加载自身的道具资源
	BattleLayer* pBattleLayer = CommonLookUpUtils::GetBattleLayer();
	if (pBattleLayer)
	{
		SkeletonAnimRcsManager::Get()->LoadOneRoleRcs(112,true);
		PropManager::Get()->AddOneProp(kType_Prop_LOCAL_ICE_EXPLOSION,NULL,pBattleLayer,false,true);
	}
}

void LocalBattleLoadingLayer::CreateBattleLayer()
{
	CCScene* pRunningScene = CCDirector::sharedDirector()->getRunningScene();
	if (pRunningScene)
	{
		BattleLayer* pBattleLayer = BattleLayer::create();
		if (pBattleLayer)
		{
			pRunningScene->addChild(pBattleLayer,Z_ORDER_BATTLE,TAG_LAYER_BATTLE);
			pBattleLayer->CreateLayerObjects();
		} 
		BattleUILayer* pBattleUILayer = BattleUILayer::create();
		if (pBattleUILayer)
		{					
			pRunningScene->addChild(pBattleUILayer,Z_ORDER_BATTLE_UI,TAG_LAYER_BATTLE_UI);
		}	
	}
}

void LocalBattleLoadingLayer::PreloadAllNeedMusic()
{
	unsigned int bgMusicId = 10000;
	std::vector<unsigned int> vecEffects;
	vecEffects.push_back(20000);

	GameAudioManager::Get()->PreLoadAllNeedMusic(bgMusicId,vecEffects);
}

void LocalBattleLoadingLayer::SimulationRolesCreator()
{
	BattleLayer* pLayer = CommonLookUpUtils::GetBattleLayer();
	if (pLayer)
	{
		BattleManager* pBattleManager = pLayer->GetBattleManager();
		if (pBattleManager)
		{
			// Note: 模拟加载人物
			HeroInfo heroInfo;
			heroInfo.typeID = 10001;
			heroInfo.animId = 1;
			heroInfo.level = 0;
			heroInfo.speed = 0;
			heroInfo.skillID =  LuaTinkerManager::Get()->callLuaFunc<unsigned int>("Script/HeroConfig/HeroConfigParser.lua", "HeroConfigParser_GetSkillID", heroInfo.typeID);
			pBattleManager->AddHeroInfo(heroInfo.typeID,heroInfo);

			heroInfo.id = 2;					
			pBattleManager->AddOthHeroInfo(heroInfo.typeID,heroInfo);

			SkeletonAnimRcsManager::Get()->LoadOneRoleRcs(heroInfo.animId,true);

			SpriteHeroBase* pHero = pBattleManager->AddOneHeroToBattle(pLayer,heroInfo.typeID);
			if (pHero)
			{
				pHero->setPosition(ccp(100,300));
				pHero->SetYPosInCell(1);
				pHero->StartStateMachine();
			}
			pHero = pBattleManager->AddOneOthHeroToBattle(pLayer,heroInfo.typeID);
			if (pHero)
			{
				pHero->setPosition(ccp(700,300));
				pHero->SetYPosInCell(1);
				pHero->StartStateMachine();
			}

			// Note: 模拟创建城堡
			CastleInfo _castleInfo;
			_castleInfo.id = 1000;
			_castleInfo.level = 0;
			_castleInfo.blood = 100;
			// Note: 查询主城的的资源ID
			_castleInfo.animId = LuaTinkerManager::Get()->callLuaFunc<int>("Script/CastleConfig/CastleConfigParser.lua", 
				"CastleConfigParser_GetOneCastleAnimID",_castleInfo.id);
			pBattleManager->SetCastleInfo(_castleInfo);

			SkeletonAnimRcsManager::Get()->LoadOneRoleRcs(_castleInfo.animId,true);
			SpriteCastleBase* selfCastle = pBattleManager->AddCastleToBattle(pLayer,true);
			if (selfCastle)
			{
				selfCastle->PlayOneAnimation(1003,0,true);
				//selfCastle->setPosition(ccp(50,300));
				const CCRect castleRect = pLayer->GetSelfCastleRect();
				selfCastle->setPosition(ccp(castleRect.getMidX(),castleRect.getMidY()));
			}

			_castleInfo.id = 1001;
			_castleInfo.level = 0;
			_castleInfo.blood = 100;
			// Note: 查询主城的的资源ID
			_castleInfo.animId = LuaTinkerManager::Get()->callLuaFunc<int>("Script/CastleConfig/CastleConfigParser.lua", 
				"CastleConfigParser_GetOneCastleAnimID",_castleInfo.id);
			pBattleManager->SetOthCastleInfo(_castleInfo);

			SkeletonAnimRcsManager::Get()->LoadOneRoleRcs(_castleInfo.animId,true);
			SpriteCastleBase* selfOthCastle = pBattleManager->AddCastleToBattle(pLayer,false);
			if (selfOthCastle)
			{
				selfOthCastle->PlayOneAnimation(1003,0,true);
				//selfOthCastle->setPosition(ccp(450,300));
				const CCRect castleRect = pLayer->GetOthCastleRect();
				selfOthCastle->setPosition(ccp(castleRect.getMidX(),castleRect.getMidY()));
			}
		}
	}
}

void LocalBattleLoadingLayer::LoadingUpdate(float dt)
{	
	switch(m_iCurStep)
	{
	case E_CREATE_BATTLE_LAYER:
		{
			CreateBattleLayer();
			m_iCurStep = E_LOAD_ANIM;
			this->SetLoadingPercent(30);
		}
		break;
	case E_LOAD_ANIM:
		{
			SimulationRolesCreator();

			LoadSkeletonAnim();
			PreloadAllNeedMusic();
			m_iCurStep = E_END;
			this->SetLoadingPercent(90);
		}
		break;
	case E_END:
		{
			this->SetLoadingPercent(100);
		}
		break;
	};
}