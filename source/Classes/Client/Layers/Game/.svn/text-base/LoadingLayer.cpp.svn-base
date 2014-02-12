#include "LoadingLayer.h"
#include "LayerCommonEnum.h"

#define SHOW_LAYER

LoadingLayer::LoadingLayer():
	m_loadingPercent(0.0),
	m_eGotoLayerType(E_UNKnow)
{

}

LoadingLayer::~LoadingLayer()
{

}

bool LoadingLayer::init()
{
	bool bRet = false;
	do {
		CC_BREAK_IF(! cocos2d::CCLayer::init());
		bRet = true;
	}while(0);

	this->setTouchEnabled(true);
#ifdef SHOW_LAYER
	this->createLayer();
#endif

	return true;
}

void LoadingLayer::createLayer()
{
	// Note: 加载UI界面
	// Note: 1 加载背景图片
	// Note: 2 加载UI控件

	AdjustWidgetForScreen(NULL);
	SetLoadingPercent(0);
}

void LoadingLayer::SetLoadingPercent(float percent){
	m_loadingPercent = percent;
	if (percent <= 0)
	{
		schedule(schedule_selector(LoadingLayer::LoadingUpdate), 0.1f);
		LoadingStart();		
	}
	else if (percent >= 100)
	{
		unschedule(schedule_selector(LoadingLayer::LoadingUpdate));
		LoadingEnd();		
	}
}

void LoadingLayer::AdjustWidgetForScreen(Layout* pLayout)
{

}

void LoadingLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, TOUCH_PRIORITY_LOADING_UI, true);
}

bool LoadingLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (isVisible())
	{
		return true;
	}	
	else
	{
		return false;
	}
}

void LoadingLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void LoadingLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void LoadingLayer::HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg)
{

}