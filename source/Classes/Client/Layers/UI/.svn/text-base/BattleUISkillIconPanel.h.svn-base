#ifndef _BATTLE_UI_SKILL_ICON_PANEL_H_
#define _BATTLE_UI_SKILL_ICON_PANEL_H_

#include "UIPanelEventDelegateInterface.h"
#include "Sprite/SpriteHero.h"
#include "Props/PropsTriggerManager.h"

class BattleUISkillIconPanel : public UIPanelEventDelegateInterface
{
public:
	BattleUISkillIconPanel(CCLayer* parentLayer,UILayer* uiLayer,Layout* layout);
	virtual ~BattleUISkillIconPanel();

	virtual void Init();

	virtual bool					ccTouchBegan(CCTouch *pTouches, CCEvent *pEvent);
	virtual void					ccTouchMoved(CCTouch *pTouches, CCEvent *pEvent);
	virtual void					ccTouchEnded(CCTouch *pTouches, CCEvent *pEvent);
protected:
	// Note: ¸øButtonÌí¼ÓIcon£¬index start from 0
	void equipOneSkillBtnIcon(UIButton* pBtn,int index);
	void onSkillPanelOneBtnClickedEvent(CCObject* pSender);
private:
	CCTouch* m_touchEvent;
	PropTriggerBase* m_propTrigger;
};

#endif	//_BATTLE_UI_SKILL_ICON_PANEL_H_