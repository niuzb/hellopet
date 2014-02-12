#ifndef _BATTLE_UI_SMALL_MAP_PANEL_H_
#define _BATTLE_UI_SMALL_MAP_PANEL_H_

#include "UIPanelEventDelegateInterface.h"
#include "Sprite/SpriteHeroBase.h"

class BattleUISmallMapPanel : public UIPanelEventDelegateInterface
{
public:
	BattleUISmallMapPanel(CCLayer* parentLayer,UILayer* uiLayer,Layout* layout);
	virtual ~BattleUISmallMapPanel();

	virtual void Init();

	virtual bool					ccTouchBegan(CCTouch *pTouches, CCEvent *pEvent);
	virtual void					ccTouchMoved(CCTouch *pTouches, CCEvent *pEvent);
	virtual void					ccTouchEnded(CCTouch *pTouches, CCEvent *pEvent);

	void Update(float dt);

	//void SetParentWidget(UIWidget* parentWidget){
	//	m_parentWidget = parentWidget;
	//}
	void SetHeroMoveRect(const CCRect& rect){
		m_battleHeroMoveRect = rect;
	}
protected:
	void playerCreaterEvent(CCObject* pObj);
	void playerDieEvent(CCObject* pObj);
	UIImageView* createDot(SpriteHeroBase::SIDE side);
	bool transformHeroPtToSmallMap(SpriteHeroBase* pHero,CCPoint& pt);
private:
	CCTouch* m_touchEvent;
	UIWidget* m_parentWidget;
	CCRect m_battleHeroMoveRect;
	CCRect m_smallMapHeroMoveRect;
	std::map<SpriteHeroBase*,UIImageView*> m_playerDots;
};

#endif	//_BATTLE_UI_SMALL_MAP_PANEL_H_