#ifndef _BATTLE_UI_ARMY_HEADICON_PANEL_H_
#define _BATTLE_UI_ARMY_HEADICON_PANEL_H_

#include "UIPanelEventDelegateInterface.h"
#include "Sprite/SpriteHero.h"
#include "NetWork/BaseMsgHandler.h"

class BattleUIArmyHeadIconPanel : public UIPanelEventDelegateInterface, public InterfaceMsgHandle
{
public:
	BattleUIArmyHeadIconPanel(CCLayer* parentLayer,UILayer* uiLayer,Layout* layout);
	virtual ~BattleUIArmyHeadIconPanel();

	virtual void Init();

	virtual bool					ccTouchBegan(CCTouch *pTouches, CCEvent *pEvent);
	virtual void					ccTouchMoved(CCTouch *pTouches, CCEvent *pEvent);
	virtual void					ccTouchEnded(CCTouch *pTouches, CCEvent *pEvent);
protected:
	// Note: ¸øButtonÌí¼ÓIcon£¬index start from 0
	void equipOneArmyBtnIcon(UIButton* pBtn,int index);
	void onHeadPanelOneBtnClickedEvent(CCObject* pSender);

	void sendHeroCreatorMsg(unsigned int id,unsigned int pos);
	virtual void HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg);
private:
	CCTouch* m_touchEvent;
	SpriteHero* m_touchHero;
};

#endif	//_BATTLE_UI_ARMY_HEADICON_PANEL_H_