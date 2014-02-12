#ifndef _MAIN_MENU_LAYER_H_
#define _MAIN_MENU_LAYER_H_

#include "cocos2d.h"
#include "LayerAutoAdaptiveBase.h"
#include "NetWork/BaseMsgHandler.h"

USING_NS_CC;

class MainMenuUILayer : public CCLayer , public LayerAutoAdaptiveBase , public InterfaceMsgHandle 
{
public:
	MainMenuUILayer();
	virtual ~MainMenuUILayer();	

	CREATE_FUNC(MainMenuUILayer);
	virtual bool init();  	
protected:
	// Note: Events
	virtual void					ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);	
	virtual void					ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void					ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	virtual void AdjustWidgetForScreen(Layout* pLayout);
	virtual void HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg);
	
	void sendGetRoomListMessage();
protected:
	void createLayer();
	// Note: 事件回调
	void onButtonEnterGame(CCObject* pSender);
};

#endif	//_MAIN_MENU_LAYER_H_