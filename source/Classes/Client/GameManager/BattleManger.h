#ifndef _BATTLE_MANAGER_H_
#define _BATTLE_MANAGER_H_

#include "SpriteHero.h"
#include "SpriteOthHero.h"
#include "SpriteHeroBase.h"
#include "vector"
#include "cocos2d.h"
#include "Particle/ParticleDefine.h"
#include "Sprite/SpriteDefiner.h"
#include "Sprite/SpriteCastle.h"
#include "Sprite/SpriteOthCastle.h"
#include "map"

USING_NS_CC;

class ParticleManager;
//class MapPhysicalLayer;
class PropBase;

/// <summary>
//	作为战斗时的中间层使用，不作为静态实例
/// </summary>
class BattleManager
{
public:
	enum State{
		BEFORE_BATTLE,
		IN_BATTLE,
		AFTER_BATTLE,
	} m_state;
	BattleManager();
	~BattleManager();

	SpriteHero* AddOneHeroToBattle(CCLayer* battleLayer,int heroId);
	SpriteOthHero* AddOneOthHeroToBattle(CCLayer* battleLayer,int heroId);
	void RemoveOneHeroFromBattle(SpriteHeroBase* pHero);
	void RemoveAllHeroFromBattleAndCleanUp();
	// Note: 添加一个玩家的基本信息
	void AddHeroInfo(unsigned int id, const HeroInfo& info);
	bool GetHeroInfo(unsigned int id,HeroInfo& heroInfo);
	void AddOthHeroInfo(unsigned int id, const HeroInfo& info);
	bool GetOthHeroInfo(unsigned int id,HeroInfo& info);
	const std::map<unsigned int,HeroInfo>& GetHeroMapInfo(){
		return m_mapHeroIdAndInfo;
	}
	// Note: 设置城堡基本信息
	void SetCastleInfo(const CastleInfo& info);
	const CastleInfo& GetCastleInfo();
	void SetOthCastleInfo(const CastleInfo& info);
	const CastleInfo& GetOthCastleInfo();
	// Note: 创建城堡
	SpriteCastleBase* AddCastleToBattle(CCLayer* battleLayer,bool isSide);
	void RemoveCastleFromBattle(SpriteCastleBase* pCastle);

	void AddPhysicalLayerToBattle(CCLayer* battleLayer,const CCSize& mapSize,const CCPoint& leftDownPt);
	void AddPropTriggersToBattle(CCLayer* battleLayer);

	void AddOnePropToBattle(CCLayer* battleLayer,PropsType propType,CCPoint pt);

	void Update(float dt,CCNode* pNode);
private:
	CastleInfo m_castleInfo;
	CastleInfo m_othCastleInfo;
	SpriteCastle* m_selfCastle;
	SpriteOthCastle* m_othCastle;
	std::vector<SpriteHeroBase*> m_vecHeros;
	std::map<unsigned int,HeroInfo> m_mapHeroIdAndInfo;
	std::map<unsigned int,HeroInfo> m_mapOthHeroIdAndInfo;
	//MapPhysicalLayer* m_pMapPhysicalLayer;	

};

#endif	//_BATTLE_MANAGER_H_