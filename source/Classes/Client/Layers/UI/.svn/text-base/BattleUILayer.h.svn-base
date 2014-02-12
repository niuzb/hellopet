#ifndef _BATTLE_UI_LAYER_H_
#define _BATTLE_UI_LAYER_H_

#include "Layers/UI/LayerAutoAdaptiveBase.h"
#include "cocos2d.h"
#include "Sprite/SpriteHero.h"
#include "Layers/Game/BattleLayer.h"

USING_NS_CC;

class BattleUIArmyHeadIconPanel;
class BattleUISkillIconPanel;
class BattleUISmallMapPanel;

class BattleUILayer : public CCLayer, public LayerAutoAdaptiveBase
{
public:
	BattleUILayer();
	virtual ~BattleUILayer();	

	CREATE_FUNC(BattleUILayer);
	virtual bool init();  
	virtual void AdjustWidgetForScreen(Layout* pLayout);

	BattleUIArmyHeadIconPanel* GetBattleUIArmyPanel(){
		return m_battleUIArmyHeadIconPanel;
	}
	BattleUISkillIconPanel* GetBattleUISkillPanel(){
		return m_battleUISkillIconPanel;
	}
	BattleUISmallMapPanel* GetBattleUISmallPanel(){
		return m_battleUISmallMapPanel;
	}

	virtual void update(float delta);
protected:
	// Note: Events
	virtual void					registerWithTouchDispatcher();
	virtual bool					ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void					ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void					ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void					visit();
protected:
	void createLayer();
#if WIN32
	static void keyboardHook(UINT message, WPARAM wParam, LPARAM lParam);
#endif
	virtual void keyBackClicked();//¼àÌýAndroid ·µ»Ø¼ü
	virtual void keyMenuClicked();//¼àÌýAndroid ²Ëµ¥¼ü
	void onMessageBoxOkButtonClick(CCObject* pSender);
private:
	BattleUIArmyHeadIconPanel* m_battleUIArmyHeadIconPanel;
	BattleUISkillIconPanel* m_battleUISkillIconPanel;
	BattleUISmallMapPanel* m_battleUISmallMapPanel;
};

#endif	//_BATTLE_UI_LAYER_H_