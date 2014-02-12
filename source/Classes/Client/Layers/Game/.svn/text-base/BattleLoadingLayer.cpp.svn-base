#include "BattleLoadingLayer.h"
#include "NetWork/MessageHandler.h"
#include "NetWork/NetWorkUtil.h"
#include "NetWork/OnlineNetworkManager.h"
#include "SkeletonAnimRcsManager.h"
#include "GameManager/XLogicManager.h"
#include "Layers/Game/BattleLayer.h"
#include "Layers/UI/BattleUILayer.h"
#include "Layers/Game/LayerCommonEnum.h"
#include "Lua/LuaTinkerManager.h"
#include "GameManager/CommonLookUpUtils.h"
#include "Props/PropManager.h"
#include "Sound/GameAudioManager.h"

BattleLoadingLayer::BattleLoadingLayer():
	m_iCurStep(E_UNKNOW),
	m_bSendBattleCreateMessage(false),
	m_bSendJoinBattleMessage(false),
	m_bSendLoadCompleteMessage(false)
{
	m_nRoomId = 0;
}

BattleLoadingLayer::~BattleLoadingLayer()
{
}

void BattleLoadingLayer::SetInitData(EGoToLayerType gotoType,unsigned int roomId)
{
	m_eGotoLayerType = gotoType;
	m_nRoomId = roomId;

	if (m_eGotoLayerType == LoadingLayer::E_CREATOR_ENTER_BATTLE)
	{
		m_iCurStep = E_REQ_CREATE_BATTLE;
	}	
	else
	{
		m_iCurStep = E_CREATE_BATTLE_LAYER;
	}
}

void BattleLoadingLayer::LoadingStart()
{
	MessageHandler::sShareInstance()->registerMessageHandle(head_msg::CSBattleCreateRsp,this);
	MessageHandler::sShareInstance()->registerMessageHandle(head_msg::CSBattleUserJoinRsp,this);	
	MessageHandler::sShareInstance()->registerMessageHandle(head_msg::CSBattleLoadCompleteRsp,this);	
}

void BattleLoadingLayer::LoadingEnd()
{
	//this->removeFromParent();
	this->setVisible(false);
}

void BattleLoadingLayer::SendCreateBattleReq()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance(head_msg::CSBattleCreateReq);
	CSBattleCreateReq* bodyMsg = dynamic_cast<CSBattleCreateReq*>(msg);
	if (bodyMsg)
	{
		bodyMsg->set_map_id(100001);
		KSendMessageResult result = OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, OnlineNetworkManager::PKG_TIMEOUT, NETWORK_TAG_CREATE_BATTLE, true, true);
	}	
}

void BattleLoadingLayer::SendJoinBattleReq()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance(head_msg::CSBattleUserJoinReq);
	CSBattleUserJoinReq* bodyMsg = dynamic_cast<CSBattleUserJoinReq*>(msg);
	if (bodyMsg)
	{		
		if (m_nRoomId != 0)
		{
			bodyMsg->set_roomid(m_nRoomId);
		}
		else
		{
			bodyMsg->set_roomid(-1);
		}		
		KSendMessageResult result = OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, OnlineNetworkManager::PKG_TIMEOUT, NETWORK_TAG_JOIN_BATTLE, true, true);
	}	
}

void BattleLoadingLayer::SendLoadCompleteReq()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance(head_msg::CSBattleLoadCompleteReq);
	CSBattleLoadCompleteReq* bodyMsg = dynamic_cast<CSBattleLoadCompleteReq*>(msg);
	if (bodyMsg)
	{		
		KSendMessageResult result = OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, OnlineNetworkManager::PKG_TIMEOUT, NETWORK_TAG_BATTLE_LOAD_COMPLETE, true, true);
	}	
}

void BattleLoadingLayer::HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg)
{
	switch(cmd)
	{
	case head_msg::CSBattleCreateRsp:
		{
			CSBattleCreateRsp* _msg = dynamic_cast<CSBattleCreateRsp*>(msg->msg);
			if (_msg)
			{
				unsigned int mapId = _msg->map_id();
				m_iCurStep = E_CREATE_BATTLE_LAYER;
			}
		}
		break;
	case head_msg::CSBattleUserJoinRsp:
		{
			CSBattleUserJoinRsp* _msg = dynamic_cast<CSBattleUserJoinRsp*>(msg->msg);
			if (_msg)
			{
				BattleManager* pBattleManager = CommonLookUpUtils::GetBattleManager();
				if (pBattleManager)
				{
					BasicUserInfo userInfo = _msg->userinfo();
					unsigned int userId = userInfo.uid();
					CSCastleInfo castleInfo = _msg->castleinfo();
					if (UserData::Get()->GetUserInfo().player_id == userId)
					{						
						CastleInfo _castleInfo;
						_castleInfo.id = castleInfo.id();
						_castleInfo.level = castleInfo.level();
						_castleInfo.blood = castleInfo.blood();
						// Note: 查询主城的的资源ID
						_castleInfo.animId = LuaTinkerManager::Get()->callLuaFunc<int>("Script/CastleConfig/CastleConfigParser.lua", 
								"CastleConfigParser_GetOneCastleAnimID",castleInfo.id());
						pBattleManager->SetCastleInfo(_castleInfo);

						int heroSize = _msg->monsterinfo().size();
						for (int index = 0;index < heroSize;index++)
						{
							MonsterInfo info = _msg->monsterinfo(index);
							// Note: 查询英雄的资源ID
							int animId = LuaTinkerManager::Get()->callLuaFunc<int>("Script/HeroConfig/HeroConfigParser.lua", 
									"HeroConfigParser_GetOneHeroAnimID",info.id());
							if (animId != 0)
							{
								HeroInfo heroInfo;
								heroInfo.typeID = info.id();
								heroInfo.animId = animId;
								heroInfo.level = info.level();
								heroInfo.totalBlood = info.blood();
								heroInfo.speed = info.speed();
								heroInfo.skillID =  LuaTinkerManager::Get()->callLuaFunc<unsigned int>("Script/HeroConfig/HeroConfigParser.lua", 
										"HeroConfigParser_GetSkillID", info.id());
								pBattleManager->AddHeroInfo(heroInfo.typeID,heroInfo);
							}
							else
							{
								CCAssert(false,"not found one role anim");
							}
						}
						m_iCurStep = E_LOAD_ANIM;
					}
					// Note: 其他玩家信息
					else
					{
						CastleInfo _castleInfo;
						_castleInfo.id = castleInfo.id();
						_castleInfo.level = castleInfo.level();
						_castleInfo.blood = castleInfo.blood();
						// Note: 查询主城的的资源ID
						_castleInfo.animId = LuaTinkerManager::Get()->callLuaFunc<int>("Script/CastleConfig/CastleConfigParser.lua", 
							"CastleConfigParser_GetOneCastleAnimID",castleInfo.id());
						pBattleManager->SetOthCastleInfo(_castleInfo);

						int heroSize = _msg->monsterinfo().size();
						for (int index = 0;index < heroSize;index++)
						{
							MonsterInfo info = _msg->monsterinfo(index);
							// Note: 查询英雄的资源ID
							int animId = LuaTinkerManager::Get()->callLuaFunc<int>("Script/HeroConfig/HeroConfigParser.lua", 
									"HeroConfigParser_GetOneHeroAnimID",info.id());
							if (animId != 0)
							{
								HeroInfo heroInfo;
								heroInfo.typeID = info.id();
								heroInfo.animId = animId;
								heroInfo.level = info.level();
								heroInfo.totalBlood = info.blood();
								heroInfo.speed = info.speed();
								heroInfo.skillID =  LuaTinkerManager::Get()->callLuaFunc<unsigned int>("Script/HeroConfig/HeroConfigParser.lua", 
										"HeroConfigParser_GetSkillID", info.id());
					
								pBattleManager->AddOthHeroInfo(heroInfo.typeID,heroInfo);
								// Note: 加载其他玩家的英雄资源ID
								SkeletonAnimRcsManager::Get()->LoadOneRoleRcs(heroInfo.animId,true);
							}
							else
							{
								CCAssert(false,"not found one other role anim");
							}
						}
					}
				}
			}
		}
		break;
	case head_msg::CSBattleLoadCompleteRsp:
		{
			this->SetLoadingPercent(100);
		}
		break;
	};
}

void BattleLoadingLayer::LoadSkeletonAnim()
{
	BattleLayer* pBattleLayer = CommonLookUpUtils::GetBattleLayer();
	if (pBattleLayer)
	{
		BattleManager* pBattleMgr = pBattleLayer->GetBattleManager();
		if (pBattleMgr)
		{
			// Note: 加载主城动画资源
			const CastleInfo& selfCastleInfo = pBattleMgr->GetCastleInfo();
			SkeletonAnimRcsManager::Get()->LoadOneRoleRcs(selfCastleInfo.animId,true);
			const CastleInfo& othCastleInfo = pBattleMgr->GetOthCastleInfo();
			SkeletonAnimRcsManager::Get()->LoadOneRoleRcs(othCastleInfo.animId,true);

			// Note: 加载英雄资源
			for (std::map<unsigned int,HeroInfo>::const_iterator iter = pBattleMgr->GetHeroMapInfo().begin();
				iter != pBattleMgr->GetHeroMapInfo().end();iter++)
			{
				SkeletonAnimRcsManager::Get()->LoadOneRoleRcs((*iter).second.animId,true);
				//CCLog("------------- Load One Role %d",(*iter).second.animId);
			}

			// Note: 加载自身的道具资源
			SkeletonAnimRcsManager::Get()->LoadOneRoleRcs(112,true);
			PropManager::Get()->AddOneProp(kType_Prop_LOCAL_ICE_EXPLOSION,NULL,pBattleLayer,false,true);
		}
	}
}

void BattleLoadingLayer::CreateBattleLayer()
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

void BattleLoadingLayer::PreloadAllNeedMusic()
{
	unsigned int bgMusicId = 10000;
	std::vector<unsigned int> vecEffects;
	vecEffects.push_back(20000);

	GameAudioManager::Get()->PreLoadAllNeedMusic(bgMusicId,vecEffects);
}

void BattleLoadingLayer::CreateLayerCastles()
{
	BattleLayer* pLayer = CommonLookUpUtils::GetBattleLayer();
	if (pLayer)
	{
		BattleManager* pBattleManager = pLayer->GetBattleManager();
		if (pBattleManager)
		{
			SpriteCastleBase* selfCastle = pBattleManager->AddCastleToBattle(pLayer,true);
			if (selfCastle)
			{
				selfCastle->PlayOneAnimation(1003,0,true);
				const CCRect castleRect = pLayer->GetSelfCastleRect();
				selfCastle->setPosition(ccp(castleRect.getMidX(),castleRect.getMidY()));
			}

			SpriteCastleBase* selfOthCastle = pBattleManager->AddCastleToBattle(pLayer,false);
			if (selfOthCastle)
			{
				selfOthCastle->PlayOneAnimation(1003,0,true);
				const CCRect castleRect = pLayer->GetOthCastleRect();
				selfOthCastle->setPosition(ccp(castleRect.getMidX(),castleRect.getMidY()));
			}
		}
	}
}

void BattleLoadingLayer::LoadingUpdate(float dt)
{	
	switch(m_iCurStep)
	{
	case E_REQ_CREATE_BATTLE:
		{
			if (m_bSendBattleCreateMessage == false)
			{
				SendCreateBattleReq();
				this->SetLoadingPercent(5);
				m_bSendBattleCreateMessage = true;
			}
		}
		break;
	case E_CREATE_BATTLE_LAYER:
		{
			CreateBattleLayer();
			m_iCurStep = E_REQ_JOIN_BATTLE;
			this->SetLoadingPercent(30);
		}
		break;
	case E_REQ_JOIN_BATTLE:
		{
			if (m_bSendJoinBattleMessage == false)
			{
				SendJoinBattleReq();
				this->SetLoadingPercent(50);
				m_bSendJoinBattleMessage = true;
			}
		}
		break;
	case E_LOAD_ANIM:
		{
			LoadSkeletonAnim();
			PreloadAllNeedMusic();
			m_iCurStep = E_CREATE_CASTLE;
			this->SetLoadingPercent(80);
		}
		break;
	case E_CREATE_CASTLE:
		{
			CreateLayerCastles();
			m_iCurStep = E_END;
			this->SetLoadingPercent(90);
		}
		break;
	case E_END:
		{
			if (m_bSendLoadCompleteMessage == false)
			{
				SendLoadCompleteReq();			
				m_bSendLoadCompleteMessage = true;
			}			
		}
		break;
	};
}