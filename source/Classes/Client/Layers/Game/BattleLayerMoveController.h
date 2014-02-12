#ifndef _BATTLE_LAYER_MOVE_CONTROLLER_H_
#define _BATTLE_LAYER_MOVE_CONTROLLER_H_

#include "cocos2d.h"

USING_NS_CC;

class BattleLayerMoveController
{
public:
	BattleLayerMoveController(CCLayer* pLayer);
	~BattleLayerMoveController();

	void SetLayerMoveSpeed(float moveSpeed){
		m_fMoveSpeed = moveSpeed;
	}
	void SetMapRealSize(CCSize size){
		m_mapRealSize = size;
	}

	void					update(float dt);
	bool					ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);	
	void					ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void					ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
private:
	// Note: 和BattleLayer的移动相关的数据
	CCSize		m_mapRealSize;
	CCPoint		m_moveDstPt;
	bool		m_isStartMove;	
	float		m_fMoveSpeed;

	CCLayer*	m_battleLayer;
	float		m_distance;
};

#endif	//_BATTLE_LAYER_MOVE_CONTROLLER_H_