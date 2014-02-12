#include "BattleManger.h"
#include "SkeletonAnimRcsManager.h"
#include "SpriteCreatorFactory.h"
#include "Particle/ParticleManager.h"
#include "Layers/Game/LayerCommonEnum.h"
#include "Map/MapPhysicalLayer.h"
#include "Props/PropsTriggerManager.h"
#include "Props/PropManager.h"
#include "Sound/GameAudioManager.h"
#include "Sprite/SpriteArmyPool.h"
#include "Sprite/SpriteDecorationBatchNode.h"

BattleManager::BattleManager():
	//m_pMapPhysicalLayer(NULL) ,
	m_selfCastle(NULL) ,
	m_othCastle(NULL)
{
	m_state = BEFORE_BATTLE;
}

BattleManager::~BattleManager()
{
	PropManager::Destroy();
	SpriteArmyPool::Destroy();
	SpriteDecorationBatchNode::Destroy();
}

SpriteHero* BattleManager::AddOneHeroToBattle(CCLayer* battleLayer,int heroId)
{
	SpriteHero* sprite = NULL;
	if (battleLayer)
	{
		bool ret = false;
		HeroInfo heroInfo;
		if (GetHeroInfo(heroId,heroInfo))
		{
			sprite = SpriteCreatorFactory::Get()->CreateOneRoleByID(heroInfo.animId);
			if (sprite)
			{
				heroInfo.curBlood = heroInfo.totalBlood;
				sprite->SetHeroInfo(heroInfo);
				battleLayer->addChild(sprite,(int)Z_ORDER_BATTLE_HERO);
				m_vecHeros.push_back(sprite);
			}
		}
	}

	return sprite;
}

SpriteOthHero* BattleManager::AddOneOthHeroToBattle(CCLayer* battleLayer,int heroId)
{
	SpriteOthHero* sprite = NULL;
	if (battleLayer)
	{
		bool ret = false;
		HeroInfo heroInfo;
		if (GetOthHeroInfo(heroId,heroInfo))
		{
			sprite = SpriteCreatorFactory::Get()->CreateOneOthRoleByID(heroInfo.animId);
			if (sprite)
			{
				heroInfo.curBlood = heroInfo.totalBlood;
				sprite->SetHeroInfo(heroInfo);
				battleLayer->addChild(sprite,(int)Z_ORDER_BATTLE_HERO);
				m_vecHeros.push_back(sprite);
			}
		}
	}

	return sprite;
}

SpriteCastleBase* BattleManager::AddCastleToBattle(CCLayer* battleLayer,bool isSide)
{
	SpriteCastleBase* sprite = NULL;
	if (battleLayer)
	{		
		if (isSide)
		{
			sprite = new SpriteCastle(m_castleInfo.animId);	
			CCAssert(sprite != NULL,"BattleManager::AddCastleToBattle NULL");
			sprite->SetCastleInfo(m_castleInfo);
			m_selfCastle = dynamic_cast<SpriteCastle*>(sprite);
		}
		else
		{
			sprite = new SpriteOthCastle(m_othCastleInfo.animId);	
			CCAssert(sprite != NULL,"BattleManager::AddCastleToBattle NULL");
			sprite->SetCastleInfo(m_othCastleInfo);
			m_othCastle = dynamic_cast<SpriteOthCastle*>(sprite);
		}

		sprite->autorelease();	
		battleLayer->addChild(sprite,(int)Z_ORDER_BATTLE_HERO);
	}
	return sprite;
}

void BattleManager::RemoveCastleFromBattle(SpriteCastleBase* pCastle)
{
	if (pCastle)
	{
		if (pCastle->GetBattleSide() == SpriteCastleBase::LEFT)
		{
			m_selfCastle = NULL;
		}
		else
		{
			m_othCastle = NULL;
		}
	}
}

void BattleManager::RemoveOneHeroFromBattle(SpriteHeroBase* pHero)
{
	for (std::vector<SpriteHeroBase*>::iterator iter = m_vecHeros.begin();
		 iter != m_vecHeros.end(); iter++)
	{
		if ((*iter) == pHero)
		{
			m_vecHeros.erase(iter);
			return ;
		}
	}
}

void BattleManager::RemoveAllHeroFromBattleAndCleanUp()
{
	for (std::vector<SpriteHeroBase*>::iterator iter = m_vecHeros.begin();
		iter != m_vecHeros.end(); iter++)
	{
		(*iter)->removeFromParent();
	}
	m_vecHeros.clear();
}

void BattleManager::AddPhysicalLayerToBattle(CCLayer* battleLayer,const CCSize& mapSize,const CCPoint& leftDownPt)
{
	//if (battleLayer)
	//{
	//	m_pMapPhysicalLayer = new MapPhysicalLayer();
	//	CCAssert(m_pMapPhysicalLayer != NULL,"m_pMapPhysicalLayer != NULL");
	//	m_pMapPhysicalLayer->autorelease();

	//	m_pMapPhysicalLayer->InitMapPhysicalLayer(mapSize,leftDownPt);
	//	battleLayer->addChild(m_pMapPhysicalLayer);
	//}
}

void BattleManager::AddPropTriggersToBattle(CCLayer* battleLayer)
{
	if (battleLayer)
	{
		PropsTriggerManager::Get()->AddBatchNodes(battleLayer,Z_ORDER_BATTLE_PROP_TRIGGER);
	}
}

void BattleManager::AddOnePropToBattle(CCLayer* battleLayer,PropsType propType,CCPoint pt)
{
	if (battleLayer)
	{
		PropBase* pProp = PropManager::Get()->AddOneProp(propType,NULL,battleLayer,true);
		if (pProp)
		{
			pProp->UseProp(pt);
		}
	}
}


void BattleManager::AddHeroInfo(unsigned int id, const HeroInfo& info)
{
	std::map<unsigned int,HeroInfo>::iterator iter = m_mapHeroIdAndInfo.find(id);
	if (iter == m_mapHeroIdAndInfo.end())
	{
		m_mapHeroIdAndInfo.insert(std::make_pair(id,info));
	}
	else
	{
		(*iter).second = info;
	}
}

bool BattleManager::GetHeroInfo(unsigned int id,HeroInfo& heroInfo)
{
	std::map<unsigned int,HeroInfo>::iterator iter = m_mapHeroIdAndInfo.find(id);
	if (iter != m_mapHeroIdAndInfo.end())
	{		
		heroInfo = (*iter).second;
		return true;
	}
	else
	{
		return false;
	}
}

void BattleManager::AddOthHeroInfo(unsigned int id, const HeroInfo& info)
{
	std::map<unsigned int,HeroInfo>::iterator iter = m_mapOthHeroIdAndInfo.find(id);
	if (iter == m_mapOthHeroIdAndInfo.end())
	{
		m_mapOthHeroIdAndInfo.insert(std::make_pair(id,info));
	}
	else
	{
		(*iter).second = info;
	}
}

bool BattleManager::GetOthHeroInfo(unsigned int id,HeroInfo& info)
{
	std::map<unsigned int,HeroInfo>::iterator iter = m_mapOthHeroIdAndInfo.find(id);
	if (iter != m_mapOthHeroIdAndInfo.end())
	{
		info = (*iter).second;
		return true;
	}
	else
	{
		return false;
	}
}

void BattleManager::SetCastleInfo(const CastleInfo& info)
{
	m_castleInfo = info;
}

const CastleInfo& BattleManager::GetCastleInfo()
{
	return m_castleInfo;
}

void BattleManager::SetOthCastleInfo(const CastleInfo& info)
{
	m_othCastleInfo = info;
}

const CastleInfo& BattleManager::GetOthCastleInfo()
{
	return m_othCastleInfo;
}

void BattleManager::Update(float dt,CCNode* pNode)
{
	PropsTriggerManager::Get()->Update(dt,pNode);
	//if (m_pMapPhysicalLayer)
	//{
	//	//m_pMapPhysicalLayer->Update(dt,m_vecHeros);
	//}
	PropManager::Get()->Update(dt);
	for (std::vector<SpriteHeroBase*>::iterator iter = m_vecHeros.begin();
		 iter != m_vecHeros.end(); iter++)
	{
		(*iter)->update(dt);
	}
	GameAudioManager::Get()->Update(dt);
}