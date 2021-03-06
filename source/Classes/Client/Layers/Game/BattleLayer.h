#ifndef _BATTLE_LAYER_H_
#define _BATTLE_LAYER_H_

#include "cocos2d.h"
#include "NetWork/BaseMsgHandler.h"
#include "GameManager/BattleManger.h"

USING_NS_CC;

class BattleLayerMoveController;

class BattleLayer : public CCLayer , public InterfaceMsgHandle
{
public:
	BattleLayer();
	virtual ~BattleLayer();	

	CREATE_FUNC(BattleLayer);
	virtual bool init();  
	virtual void update(float delta);

	bool CreateLayerObjects();
	BattleManager* GetBattleManager();

	// Note: Message
	void SendEnterMapReq();
	virtual void HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg);

	bool IsOnePointInStartRects(const CCPoint &pt,CCPoint & startPt,unsigned int &startIndex);

	CCPoint ConvertTouchToMap(cocos2d::CCTouch* touch);
	CCPoint ConvertUIPointToMap(const cocos2d::CCPoint& winPt);
	CCPoint ConvertMapPointToUI(const cocos2d::CCPoint& mapPt);

	bool GetStartPointByIndex(unsigned int index,bool bSide,CCPoint &pt);

	void SetMapRealSize(const CCSize& size){
		m_mapRealSize = size;
	}
	const CCSize& GetMapRealSize(){
		return m_mapRealSize;
	}
	void SetHeroMoveRect(const CCRect& rect){
		m_heroMoveRect = rect;
	}
	const CCRect& GetHeroMoveRect(){
		return m_heroMoveRect;
	}

	const CCRect& GetSelfCastleRect(){
		return m_selfCastleRect;
	}
	const CCRect& GetOthCastleRect(){
		return m_othCastleRect;
	}
protected:
	// Note: Events
	virtual void					registerWithTouchDispatcher();
	virtual bool					ccTouchBegan(CCTouch *pTouches, CCEvent *pEvent);	
	virtual void					ccTouchMoved(CCTouch *pTouches, CCEvent *pEvent);
	virtual void					ccTouchEnded(CCTouch *pTouches, CCEvent *pEvent);

	virtual void					visit();
protected:
	bool createMap();
	bool createHero();
	bool createActor();
	bool createPhysicalLayer();
	bool createPropTriggers();
private:
    cocos2d::CCNode* createGameScene();
	CCSize m_mapRealSize;
	CCRect m_heroMoveRect;

	CCLabelTTF* pTimerLabel;
	bool isStartTimerSync;

	BattleManager* battleManager;
	// Note: 英雄出生点
	std::vector<CCRect> vecStartRects;
	// Note: 城堡位置
	CCRect m_selfCastleRect;
	CCRect m_othCastleRect;
	BattleLayerMoveController* m_pBattleLayerMoveController;
};

#endif	//_BATTLE_LAYER_H_