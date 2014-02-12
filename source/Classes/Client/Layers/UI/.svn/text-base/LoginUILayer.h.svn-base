#ifndef _LOGIN_UI_LAYER_H_
#define _LOGIN_UI_LAYER_H_

#include "NetWork/BaseMsgHandler.h"
#include "LayerAutoAdaptiveBase.h"
#include "cocos2d.h"

USING_NS_CC;

class LoginUILayer : public CCLayer , public InterfaceMsgHandle , public LayerAutoAdaptiveBase
{
public:
	LoginUILayer();
	virtual ~LoginUILayer();	

	CREATE_FUNC(LoginUILayer);
	virtual bool init();  

	virtual void AdjustWidgetForScreen(Layout* pLayout);
protected:
	// Note: Events
	virtual void					ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);	
	virtual void					ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void					ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
protected:
	void createLayer();
	void sendLoginMessage();
	virtual void HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg);
	// Note: 事件回调
	void onButtonLoginGame(CCObject* pSender);
};
#endif	//_LOGIN_UI_LAYER_H_