#ifndef _MAP_PHYSICAL_LAYER_H_
#define	_MAP_PHYSICAL_LAYER_H_

#include "cocos2d.h"
#include "SpriteBase.h"
#include "MapDataCenter.h"
#include "Props/PropsTriggerSprite.h"
#include "Singleton_t.h"
#include <set>
#include <vector>
#include "cocos2d.h"
#include "../Common/Array.h"
#include "../Sprite/SpriteHeroBase.h"


USING_NS_CC;

//class MapPhysicalLayer : public CCNode
//{
//public:
//	MapPhysicalLayer();
//	virtual ~MapPhysicalLayer();
//
//	static MapPhysicalLayer* GetInstance();
//
//	void InitMapPhysicalLayer(const CCSize& mapSize,const CCPoint& mapLeftDownPt);
//
//	void Update(float dt,const std::vector<SpriteHeroBase*>& vecHeros);
//	void UpdateItemPos(CCNode* pNode);
//
//	// Note: 查询接口，查询附加玩家
//	bool SearchNearByItems(CCNode* pNode,int xOffset,int yOffset,std::vector<CCNode*> &outNodes);
//protected:
//	unsigned int getPosXInCell(float posX);
//private:
//	static MapPhysicalLayer* s_instance;
//	// Note: 物理层数据信息
//	static const int ONE_CELL_MAX_PLAYER_COUNT = 10;
//	CCNode ****arrayPhysicalData;
//	int **arrayCellHeroNums;
//
//	CCPoint m_mapLeftDownPt;
//	CCSize m_mapSize;
//	static const int CELL_WIDTH = 16;
//	unsigned int m_mapCellWidthNums;
//	unsigned int m_mapCellHeightNums;
//};


// --------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
class CHeroPhysicalLayer : public TSingleton<CHeroPhysicalLayer>
{
public:
	CHeroPhysicalLayer(void);
	~CHeroPhysicalLayer(void);

	void Register(SpriteHeroBase* pNode);
	void UnRegister(SpriteHeroBase* pNode);

	void ChangePos(SpriteHeroBase* pNode);

	SpriteHeroBase* FindNearestHero(const CCPoint& startPos, int range, SpriteHeroBase::SIDE side);

	
private:
	CCPoint ConvertToArrayCoordate(const CCPoint heroPos);

protected:
	Array2D<SpriteHeroBase*> m_leftHeros;
	Array2D<SpriteHeroBase*> m_rightHeros;
	// 现在是每一个物理格子只是存了一个Hero，相同格子的Hero，只用ID号最小的
	std::map<SpriteHeroBase*, SpriteHeroBase*> m_rigisterHeros;
};

#endif	//_MAP_PHYSICAL_LAYER_H_