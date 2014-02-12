#include "MessageBox.h"
#include "Layers/Game/LayerCommonEnum.h"
#include "Layers/UI/UIManager.h"

using namespace GUI;

MessageBox::MessageBox()
{
	s_layer = NULL;
	s_handler = NULL;
	s_ok_selector = NULL;
	s_cancel_selector = NULL;
}

MessageBox::~MessageBox()
{
}

void MessageBox::Show(const char* content,const char* okBtnContent /* = "" */, 
					  const char* cancelBtnContent /* = "" */,
					  CCObject* handler /* = NULL */,
					  SEL_ReleaseEvent ok_selector /* = NULL */, 
					  SEL_ReleaseEvent cancel_selector /* = NULL */)
{
	if (s_layer)
	{
		Destory();
	}

	this->s_handler = handler;
	this->s_ok_selector = ok_selector;
	this->s_cancel_selector = cancel_selector;

	CCNode* pParentNode = GetParentNode();
	if (pParentNode)
	{
		UILayer* uiLayer = UILayer::create();
		if (uiLayer)
		{
			uiLayer->setTouchPriority(TOUCH_PRIORITY_MESSAGEBOX_UI);
			uiLayer->SetIsModeLayer(true);
			s_layer = uiLayer;

			Layout* myLayout =	dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("UI/PetUI/PetUI_3.ExportJson"));	
			if (myLayout)
			{
				uiLayer->addWidget(myLayout);
				AdjustWidgetForScreen(myLayout);

				// Note: ×¢²á»Øµ÷º¯Êý
				UIButton* btn_ok = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("OkButton")); 
				UIButton* btn_cancel = dynamic_cast<UIButton*>(uiLayer->getWidgetByName("CancelButton")); 
				{
					if (btn_ok)
					{
						btn_ok->addReleaseEvent(this, SEL_ReleaseEvent(&MessageBox::onOkButtonClick));
						btn_ok->setTouchEnabled(true);
					}
					if (btn_cancel)
					{
						btn_cancel->addReleaseEvent(this, SEL_ReleaseEvent(&MessageBox::onCancelLoginClick));
						btn_cancel->setTouchEnabled(true);
					}
				}
			}
			pParentNode->addChild(uiLayer,Z_OREDER_MESSAGEBOX);	
		}				
	}
}

void MessageBox::AdjustWidgetForScreen(Layout* pLayout)
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
					if (strcmp(pName,"Panel_Clone") == 0)
					{
						UIManager::Get()->AdjustWidgetForScreen(pWidget,UIManager::E_MID_CEN,UIManager::E_MID_CEN);
					}	
				}
			}  
		}
	}
}

void MessageBox::Destory()
{
	if (s_layer)
	{
		s_layer->removeFromParent();
		s_layer = NULL;
		s_handler = NULL;
		s_ok_selector = NULL;
		s_cancel_selector = NULL;
	}
}
	
CCNode* MessageBox::GetParentNode()
{
	CCNode* pParentNode = NULL;
	CCScene* pRunningScene = CCDirector::sharedDirector()->getRunningScene();
	if (pRunningScene)
	{
		pParentNode = pRunningScene->getChildByTag(TAG_LAYER_LOGIN);
		if (pParentNode == NULL)
		{
			pParentNode = pRunningScene->getChildByTag(TAG_LAYER_MAINMENU);
		}
		if (pParentNode == NULL)
		{
			pParentNode = pRunningScene->getChildByTag(TAG_LAYER_BATTLE_UI);
		}
	}

	return pParentNode;
}

void MessageBox::onOkButtonClick(CCObject* pSender)
{
	if (this->s_handler != NULL && this->s_ok_selector != NULL)
	{
		(this->s_handler->*s_ok_selector)(pSender);
	}
	this->Destory();
}

void MessageBox::onCancelLoginClick(CCObject* pSender)
{
	if (this->s_handler != NULL && this->s_cancel_selector != NULL)
	{
		(this->s_handler->*s_cancel_selector)(pSender);
	}
	this->Destory();
}