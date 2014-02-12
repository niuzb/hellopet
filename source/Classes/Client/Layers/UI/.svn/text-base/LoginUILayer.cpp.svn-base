#include "LoginUILayer.h"
#include "cocos-ext.h"
#include "GameManager/XLogicManager.h"
#include "NetWork/MessageHandler.h"
#include "NetWork/NetWorkUtil.h"
#include "NetWork/OnlineNetworkManager.h"
#include "Sprite/UserData.h"
#include "Layers/UI/UIManager.h"
#include "Layers/UI/MessageBox.h"

USING_NS_CC_EXT;

#define SHOW_LAYER

LoginUILayer::LoginUILayer()
{
}

LoginUILayer::~LoginUILayer()
{
	CCUIHELPER->purgeUIHelper();
}

bool LoginUILayer::init()
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
	sendLoginMessage();
#endif
	
	MessageHandler::sShareInstance()->registerMessageHandle(head_msg::CSLoginRsp,this);
	return true;
}

void LoginUILayer::createLayer()
{
	// Note: 创建画布
	UILayer* uiLayer = UILayer::create();
	if (uiLayer)
	{
		Layout* myLayout =	dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("UI/PetUI/PetUI_2.ExportJson"));	
		if (myLayout)
		{
			uiLayer->addWidget(myLayout);
			AdjustWidgetForScreen(myLayout);

			// Note: 注册回调函数
			UIButton* btn_back = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("TextButton")); 
			btn_back->addReleaseEvent(this, SEL_ReleaseEvent(&LoginUILayer::onButtonLoginGame));
			btn_back->setTouchEnabled(true);
		}

		this->addChild(uiLayer,1);
	}	
}

void LoginUILayer::AdjustWidgetForScreen(Layout* pLayout)
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
					if (strcmp(pName,"TextButton") == 0)
					{
						UIManager::Get()->AdjustWidgetForScreen(pWidget,UIManager::E_MID_CEN,UIManager::E_MID_CEN);
					}
				}
			}  
		}
	}
}

/////
void LoginUILayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{	
}

void LoginUILayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{

}

void LoginUILayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{

}

void LoginUILayer::onButtonLoginGame(CCObject* pSender)
{
	CCLog("LoginUILayer::onButtonLoginGame(CCObject* pSender)");
	sendLoginMessage();
}

void LoginUILayer::sendLoginMessage()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance(head_msg::CSLoginReq);
	CSLoginReq  * bodyMsg = (CSLoginReq  *)msg;
	bodyMsg->set_uid(1001);
	bodyMsg->set_reg_time(0);
	bodyMsg->set_channel_id(0);
	bodyMsg->set_server_id(0);

	KSendMessageResult result = OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, OnlineNetworkManager::PKG_TIMEOUT, NETWORK_TAG_LOGIN, true, true);
}

void LoginUILayer::HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg)
{	
	if (cmd == head_msg::CSLoginRsp)
	{
		CSLoginRsp* _msg = dynamic_cast<CSLoginRsp*>(msg->msg);
		USERINFO userInfo = UserData::Get()->GetUserInfo();
		userInfo.player_name = _msg->name();
		userInfo.channel_id = _msg->channel_id();
		userInfo.player_id = _msg->userid();
		userInfo.reg_time = _msg->reg_time();
		UserData::Get()->SetUserInfo(userInfo);

		XLogicManager::sharedManager()->goToLayer(XLogicManager::E_UI_MAIN_LAYER,NULL);
	}
}