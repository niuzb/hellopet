#include "MainMenuLayer.h"
#include "cocos-ext.h"
#include "GameManager/XLogicManager.h"
#include "Layers/UI/UIManager.h"
#include "NetWork/MessageHandler.h"
#include "NetWork/NetWorkUtil.h"
#include "NetWork/OnlineNetworkManager.h"

USING_NS_CC_EXT;

#define SHOW_LAYER

MainMenuUILayer::MainMenuUILayer()
{
}

MainMenuUILayer::~MainMenuUILayer()
{
	CCUIHELPER->purgeUIHelper();
}

bool MainMenuUILayer::init()
{
	bool bRet = false;
	do {
		CC_BREAK_IF(! cocos2d::CCLayer::init());
		bRet = true;
	}while(0);

	this->setTouchEnabled(true);
#ifdef SHOW_LAYER
	this->createLayer();
#else
	onButtonEnterGame(NULL);
#endif	

	MessageHandler::sShareInstance()->registerMessageHandle(head_msg::CSPVPQueryRoomRsp,this);
	return true;
}

void MainMenuUILayer::createLayer()
{
	// Note: 创建画布
	UILayer* uiLayer = UILayer::create();
	if (uiLayer)
	{
		Layout* myLayout =	dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("UI/PetUI/PetUI_1.ExportJson"));	
		if (myLayout)
		{
			uiLayer->addWidget(myLayout);
			AdjustWidgetForScreen(myLayout);

			// Note: 注册回调函数
			UIButton* btn_back = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("TextButton")); 
			btn_back->addReleaseEvent(this, SEL_ReleaseEvent(&MainMenuUILayer::onButtonEnterGame));						
		}

		this->addChild(uiLayer,1);
	}
}

void MainMenuUILayer::AdjustWidgetForScreen(Layout* pLayout)
{
	if (pLayout)
	{
		CCArray* pArray = pLayout->getChildren();
		if (pArray)
		{
			CCObject* pObject = NULL;  
			CCARRAY_FOREACH(pArray, pObject)  
			{  
				UIWidget* pWidget = dynamic_cast<UIWidget*>(pObject);
				if (pWidget)
				{
					const char* pName = pWidget->getName();
					if (strcmp(pName,"Panel") == 0)
					{
						UIManager::Get()->AdjustWidgetForScreen(pWidget,UIManager::E_MID_CEN,UIManager::E_MID_CEN);
					}	
				}
			}  
		}
	}
}

/////
void MainMenuUILayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
}

void MainMenuUILayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{

}

void MainMenuUILayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{

}

void MainMenuUILayer::onButtonEnterGame(CCObject* pSender)
{
	CCLog("MainMenuUILayer::onButtonEnterGame(CCObject* pSender)");
	sendGetRoomListMessage();	
}

void MainMenuUILayer::sendGetRoomListMessage()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance(head_msg::CSPVPQueryRoomReq);
	CSPVPQueryRoomReq  * bodyMsg = (CSPVPQueryRoomReq  *)msg;
	KSendMessageResult result = OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, OnlineNetworkManager::PKG_TIMEOUT, NETWORK_TAG_PVPQUERYROOM, true, true);
}

void MainMenuUILayer::HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg)
{
	if (cmd == head_msg::CSPVPQueryRoomRsp)
	{
		CSPVPQueryRoomRsp* _msg = dynamic_cast<CSPVPQueryRoomRsp*>(msg->msg);
		if (_msg)
		{
			int size = _msg->rooms_size();
			if (size <= 0)
			{
				XLogicManager::sharedManager()->goToLayer(XLogicManager::E_ENTER_GAME,NULL);
			}
			else
			{
				PVPRoomBase pBase = _msg->rooms(0);
				unsigned int roomId = pBase.room_id();
				unsigned int *pValue = new unsigned int(roomId);
				if (pValue)
				{
					XLogicManager::sharedManager()->goToLayer(XLogicManager::E_ENTER_GAME,pValue);
					delete pValue;
					pValue = NULL;
				}
			}
		}
	}
}