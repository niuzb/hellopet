#ifndef _LOADING_LAYER_H_
#define _LOADING_LAYER_H_

#include "NetWork/BaseMsgHandler.h"
#include "LayerAutoAdaptiveBase.h"
#include "cocos2d.h"

USING_NS_CC;

class LoadingLayer : public CCLayer , public InterfaceMsgHandle , public LayerAutoAdaptiveBase
{
public:
	enum EGoToLayerType
	{
		E_CREATOR_ENTER_BATTLE,
		E_JOINER_ENTER_BATTLE,
		E_PALYER_ENTER_MAIN_MENU,
		E_UNKnow
	};
public:
	LoadingLayer();
	virtual ~LoadingLayer();

	CREATE_FUNC(LoadingLayer);
	virtual bool init();
	virtual void AdjustWidgetForScreen(Layout* pLayout);

	virtual void SetLoadingPercent(float percent);
	float GetLoadingPercent(){
		return m_loadingPercent;
	}
	virtual void LoadingStart(){

	}
	virtual void LoadingEnd(){

	}
	virtual void LoadingUpdate(float dt){

	}
	virtual void SetGotoLayerType(EGoToLayerType type)
	{
		m_eGotoLayerType = type;
	}
protected:
	virtual void					registerWithTouchDispatcher();
	virtual bool					ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void					ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void					ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void createLayer();
	virtual void HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg);
protected:
	// Note: loading 百分比 0 - 100
	float m_loadingPercent;
	// Note: 标识玩家进入地图的方式
	EGoToLayerType m_eGotoLayerType;
};

#endif	//_LOADING_LAYER_H_