#ifndef _UI_PANEL_EVENT_DELEGATE_INTERFACE_H_
#define _UI_PANEL_EVENT_DELEGATE_INTERFACE_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class UIPanelEventDelegateInterface : public CCNode
{
public:
	UIPanelEventDelegateInterface(CCLayer* parentLayer,UILayer* uiLayer,Layout* layout){
		m_parentLayer = parentLayer;
		m_uiLayer = uiLayer;
		m_layout = layout;
	}
	virtual ~UIPanelEventDelegateInterface(){

	}

	virtual void Init() = 0;

	virtual bool					ccTouchBegan(CCTouch *pTouches, CCEvent *pEvent) = 0;
	virtual void					ccTouchMoved(CCTouch *pTouches, CCEvent *pEvent) = 0;
	virtual void					ccTouchEnded(CCTouch *pTouches, CCEvent *pEvent) = 0;
protected:
	CCLayer* m_parentLayer;
	UILayer* m_uiLayer;
	Layout* m_layout;
};

#endif	//_UI_PANEL_EVENT_DELEGATE_INTERFACE_H_