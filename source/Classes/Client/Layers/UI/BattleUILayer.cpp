#include "Layers/UI/BattleUILayer.h"
#include "Map/MapDataCenter.h"
#include "Sprite/SpriteHero.h"
#include "GameManager/CommonLookUpUtils.h"
#include "Layers/UI/MessageBox.h"
#include "cocos-ext.h"
#include "Layers/UI/UIManager.h"
#include "Layers/Game/LayerCommonEnum.h"
#include "Sprite/SpriteArmyPool.h"
#include "BattleUIArmyHeadIconPanel.h"
#include "BattleUISkillIconPanel.h"
#include "BattleUISmallMapPanel.h"
#include "ExtendUI/UIScrollList.h"
#include "SkeletonAnimRcsManager.h"
#include "SpriteCreatorFactory.h"

USING_NS_CC_EXT;

BattleUILayer::BattleUILayer():
	m_battleUIArmyHeadIconPanel(NULL),
	m_battleUISkillIconPanel(NULL),
	m_battleUISmallMapPanel(NULL)
{
}

BattleUILayer::~BattleUILayer()
{
#if WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setAccelerometerKeyHook(NULL);
#endif
	if (m_battleUIArmyHeadIconPanel)
	{
		m_battleUIArmyHeadIconPanel->release();
		m_battleUIArmyHeadIconPanel = NULL;
	}
	if (m_battleUISkillIconPanel)
	{
		m_battleUISkillIconPanel->release();
		m_battleUISkillIconPanel = NULL;
	}
	if (m_battleUISmallMapPanel)
	{
		m_battleUISmallMapPanel->release();
		m_battleUISmallMapPanel = NULL;
	}
}

bool BattleUILayer::init()
{
	bool bRet = false;
	do {
		CC_BREAK_IF(! cocos2d::CCLayer::init());
		bRet = true;
	}while(0);

	createLayer(); 	

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);
	this->scheduleUpdate();
#if WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setAccelerometerKeyHook(BattleUILayer::keyboardHook);
#endif

	return true;
}

void BattleUILayer::AdjustWidgetForScreen(Layout* pLayout)
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
					if (strcmp(pName,"PanelHeadIcon") == 0)
					{
						UIManager::Get()->AdjustWidgetForScreen(pWidget,UIManager::E_LEFT_DOWN,UIManager::E_LEFT_DOWN);
					}
					else if (strcmp(pName,"PanelSkillIcon") == 0)
					{
						UIManager::Get()->AdjustWidgetForScreen(pWidget,UIManager::E_RIGHT_DOWN,UIManager::E_RIGHT_DOWN);
					}
					else if (strcmp(pName,"PanelSmallMap") == 0)
					{
						UIManager::Get()->AdjustWidgetForScreen(pWidget,UIManager::E_MID_UP,UIManager::E_MID_UP);
					}
					else if (strcmp(pName,"ListViewPanel") == 0)
					{
						UIManager::Get()->AdjustWidgetForScreen(pWidget,UIManager::E_LEFT_UP,UIManager::E_LEFT_UP);
					}
					else if (strcmp(pName,"ListViewPanel_0") == 0)
					{
						UIManager::Get()->AdjustWidgetForScreen(pWidget,UIManager::E_RIGHT_UP,UIManager::E_RIGHT_UP);
					}
				}
			}  
		}
	}
}

void BattleUILayer::createLayer()
{
	// Note: 创建画布
	UILayer* uiLayer = UILayer::create();
	if (uiLayer)
	{
		Layout* myLayout =	dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("UI/PetUI/PetUI_4.ExportJson"));	
		if (myLayout)
		{
			uiLayer->addWidget(myLayout);
//			uiLayer->SetDelegateTouchEventLayer(this);
//			uiLayer->setTouchPriority(TOUCH_PRIORITY_WIDGET_UI);

			AdjustWidgetForScreen(myLayout);		

			m_battleUIArmyHeadIconPanel = new BattleUIArmyHeadIconPanel(this,uiLayer,myLayout);	
			if (m_battleUIArmyHeadIconPanel)
			{
				m_battleUIArmyHeadIconPanel->Init();
			}
			m_battleUISkillIconPanel = new BattleUISkillIconPanel(this,uiLayer,myLayout);
			if (m_battleUISkillIconPanel)
			{
				m_battleUISkillIconPanel->Init();
			}
//			m_battleUISmallMapPanel = new BattleUISmallMapPanel(this,uiLayer,myLayout);
//			if (m_battleUISmallMapPanel)
//			{
//				m_battleUISmallMapPanel->Init();
//			}
		}
		this->addChild(uiLayer,1);

//		UIScrollList* pScrollList = new UIScrollList(uiLayer,myLayout,"ListViewPanel","ListItem","UI/PetUI/PetUI_ListItem.ExportJson");
//		if (pScrollList)
//		{
//			unsigned int count = 10;
//			for (unsigned int index = 0;index < count;index++)
//			{
//				pScrollList->AddListItem();
//			}
//		}
//
//		UIScrollList* pHorScrollList = new UIScrollList(uiLayer,myLayout,"ListViewPanel_0","ListItem","UI/PetUI/PetUI_HeroCardItem.ExportJson",LISTVIEW_DIR_HORIZONTAL);
//		if (pHorScrollList)
//		{
//			unsigned int count = 10;
//			for (unsigned int index = 0;index < count;index++)
//			{
//				UIWidget* pWidget = pHorScrollList->AddListItem();
//				if (pWidget)
//				{
//					UIWidget* heroIconWidget = pWidget->getChildByTag(54);
//					if (heroIconWidget)
//					{
//						CCSize size = heroIconWidget->getSize();
//						SkeletonAnimRcsManager::Get()->LoadOneRoleRcs(1,true);
//						SpriteBase* pHero = new SpriteBase(1);
//						if (pHero)
//						{
//							pHero->autorelease();
//							heroIconWidget->addCCNode(pHero);
//							pHero->setPosition(ccp(size.width/2,0));
//							pHero->PlayOneAnimation(kTypeIdle_FaceHor_OTH,true);
//						}
//					}
//				}
//			}
//		}
	}
}

void BattleUILayer::registerWithTouchDispatcher()
{
//	CCDirector* pDirector = CCDirector::sharedDirector();
//	pDirector->getTouchDispatcher()->addTargetedDelegate(this, TOUCH_PRIORITY_BATTLE_UI, true);
	//CCLayer::registerWithTouchDispatcher();
}

bool BattleUILayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_battleUIArmyHeadIconPanel)
	{
		m_battleUIArmyHeadIconPanel->ccTouchBegan(pTouch,pEvent);
	}
	if (m_battleUISkillIconPanel)
	{
		m_battleUISkillIconPanel->ccTouchBegan(pTouch,pEvent);
	}
	if (m_battleUISmallMapPanel)
	{
		m_battleUISmallMapPanel->ccTouchBegan(pTouch,pEvent);
	}
	return false;
}

void BattleUILayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_battleUIArmyHeadIconPanel)
	{
		m_battleUIArmyHeadIconPanel->ccTouchMoved(pTouch,pEvent);
	}
	if (m_battleUISkillIconPanel)
	{
		m_battleUISkillIconPanel->ccTouchMoved(pTouch,pEvent);
	}
	if (m_battleUISmallMapPanel)
	{
		m_battleUISmallMapPanel->ccTouchMoved(pTouch,pEvent);
	}
}
void BattleUILayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_battleUIArmyHeadIconPanel)
	{
		m_battleUIArmyHeadIconPanel->ccTouchEnded(pTouch,pEvent);
	}
	if (m_battleUISkillIconPanel)
	{
		m_battleUISkillIconPanel->ccTouchEnded(pTouch,pEvent);
	}
	if (m_battleUISmallMapPanel)
	{
		m_battleUISmallMapPanel->ccTouchEnded(pTouch,pEvent);
	}
}

#if WIN32
void BattleUILayer::keyboardHook(UINT message, WPARAM wParam, LPARAM lParam)
{

}
#endif

void BattleUILayer::keyBackClicked()
{
	CCLog("keyBackClicked");	
	GUI::MessageBox::Get()->Show("","","",this,SEL_ReleaseEvent(&BattleUILayer::onMessageBoxOkButtonClick),NULL);
}

void BattleUILayer::keyMenuClicked()
{
}

void BattleUILayer::onMessageBoxOkButtonClick(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}

void BattleUILayer::visit()
{
	// TODO : 应该放到外面的父节点上	
	//CCDirector::sharedDirector()->setRenderCameraForUI();	
	CCLayer::visit();
}

void BattleUILayer::update(float delta)
{
	if (m_battleUISmallMapPanel)
	{
		m_battleUISmallMapPanel->Update(delta);
	}
}