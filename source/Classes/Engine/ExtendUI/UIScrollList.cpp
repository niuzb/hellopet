#include "UIScrollList.h"
#include "cocos2d.h"
#include "Layers/UI/UIManager.h"

USING_NS_CC;

UIScrollList::UIScrollList(UILayer* pLayer,Layout* pLayout,const char* listContainerName, const char* listItemContainerName,
	const char* listItemTemplateFileName,LISTVIEW_DIR listViewDir /* = LISTVIEW_DIR_VERTICAL */)
	: m_uiLayer(pLayer)
	, m_layout(pLayout)
	, m_listView(NULL)
	, m_listContainer(NULL)
	, m_nItemsCount(0)
	, m_listViewDir(listViewDir)
	, m_listItemTemplateFileName(listItemTemplateFileName)
	, m_listContainerName(listContainerName)
	, m_listItemContainerName(listItemContainerName)
	, m_bEnableScale9Mode(true)
	, m_bgImageName("")
	, m_spaceAtStart(0)
	, m_spaceAtEnd(0)
	, m_spaceBetweenTwoItem(0)
{
	findListTemplateByName(listContainerName);
	init();
}

UIScrollList::~UIScrollList()
{
	if (m_listView && m_listContainer)
	{
		m_listView->removeFromParent();
		m_listContainer->removeFromParent();
	}
}

void UIScrollList::init()
{
	UIListView *pListView = UIListView::create();
	if (pListView)
	{
		m_listView = pListView;

		pListView->setTouchEnable(true);
		if (m_listViewDir == LISTVIEW_DIR_HORIZONTAL)
		{
			m_listView->setDirection(LISTVIEW_DIR_HORIZONTAL);
		}
		else
		{
			m_listView->setDirection(LISTVIEW_DIR_VERTICAL);
		}
		SetPanelBgImageName(m_bgImageName);
		CCSize listViewSize = m_listContainer->getSize();
		
		float scaleX = 1;
		float scaleY =1;
		listViewSize.width *= scaleX;
		listViewSize.height *= scaleY;
		m_listViewSize = listViewSize;
		pListView->setSize(listViewSize);
		pListView->setPosition(CCPointZero);
		m_listContainer->addChild(pListView);		

		m_listView->addEventListenter(this, listvieweventselector(UIScrollList::listViewEvent));
	}
}

void UIScrollList::findListTemplateByName(const char* listContainerName)
{
	if (m_layout)
	{
		CCArray* pArray = m_layout->getChildren();
		if (pArray)
		{
			CCObject* pObject = NULL;  
			CCARRAY_FOREACH(pArray, pObject)  
			{  
				UIWidget* pWidget = dynamic_cast<UIWidget*>(pObject);
				if (pWidget)
				{
					const char* pName = pWidget->getName();
					if (strcmp(pName,listContainerName) == 0)
					{
						m_listContainer = pWidget;
					}
				}
			}  
		}
	}
}

void UIScrollList::SetPanelBgImageName(const char* panelImageName)
{
	if (panelImageName && m_listView)
	{		
		if (panelImageName == "")
		{
			m_listView->setBackGroundColor(ccc3(255,255,255));
			m_listView->setBackGroundColorOpacity(122);
		}
		else
		{
			if (strcmp(m_bgImageName,panelImageName) == 0)
			{
				m_listView->setBackGroundImageScale9Enabled(m_bEnableScale9Mode);
				m_listView->setBackGroundImage(panelImageName);
			}
		}
		m_bgImageName = panelImageName;
	}
}

UIWidget* UIScrollList::AddListItem()
{
	UIWidget* pWidget = NULL;
	if (m_listViewDir == LISTVIEW_DIR_VERTICAL)
	{
		pWidget = addListItemVer();
	}
	else
	{
		pWidget = addListItemHor();
	}
	if (pWidget)
	{
		m_nItemsCount ++;
		m_listView->initChildWithDataLength(m_nItemsCount);
	}
	return pWidget;
}

UIWidget* UIScrollList::addListItemVer()
{
	UIWidget* pWidget = NULL;
	// Note: 从plist中进行创建
	UILayer* uiLayer = UILayer::create();
	Layout* myLayout =	dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(m_listItemTemplateFileName));	
	if (myLayout && uiLayer)
	{
		uiLayer->addWidget(myLayout);
		// Note: 注册回调函数
		pWidget = dynamic_cast<UIWidget*>(uiLayer->getWidgetByName(m_listItemContainerName)); 
		pWidget->setTouchEnable(true);
		pWidget->addPushDownEvent(this,SEL_PushEvent(&UIScrollList::pushDownEvent));
		pWidget->addReleaseEvent(this,SEL_ReleaseEvent(&UIScrollList::releaseEvent));
		if (pWidget)
		{
			pWidget->removeFromParent();
		}
	}

	if (pWidget)
	{
		CCSize panel_size = pWidget->getSize();
		panel_size.width *= pWidget->getScaleX();
		panel_size.height *= pWidget->getScaleY();
		pWidget->setPosition(ccp((m_listViewSize.width - panel_size.width) / 2,
			(m_listViewSize.height - (panel_size.height + m_spaceAtStart)) - m_nItemsCount * (panel_size.height + m_spaceBetweenTwoItem)));

		pWidget->setTag(m_nItemsCount);
		m_listView->addChild(pWidget);
	}

	uiLayer->release();	

	return pWidget;
}

UIWidget* UIScrollList::addListItemHor()
{
	UIWidget* pWidget = NULL;
	// Note: 从plist中进行创建
	UILayer* uiLayer = UILayer::create();
	Layout* myLayout =	dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(m_listItemTemplateFileName));	
	if (myLayout && uiLayer)
	{
		uiLayer->addWidget(myLayout);
		// Note: 注册回调函数
		pWidget = dynamic_cast<UIWidget*>(uiLayer->getWidgetByName(m_listItemContainerName)); 
		pWidget->setTouchEnable(true);
		pWidget->addPushDownEvent(this,SEL_PushEvent(&UIScrollList::pushDownEvent));
		pWidget->addReleaseEvent(this,SEL_ReleaseEvent(&UIScrollList::releaseEvent));
		if (pWidget)
		{
			pWidget->removeFromParent();
		}
	}

	if (pWidget)
	{
		CCSize panel_size = pWidget->getSize();
		panel_size.width *= pWidget->getScaleX();
		panel_size.height *= pWidget->getScaleY();
		pWidget->setPosition(ccp(0 + (m_spaceAtStart) + m_nItemsCount * (panel_size.width + m_spaceBetweenTwoItem),
			(m_listViewSize.height - m_listViewSize.height) / 2));

		pWidget->setTag(m_nItemsCount);
		m_listView->addChild(pWidget);
	}

	uiLayer->release();	

	return pWidget;
}

UIWidget* UIScrollList::GetListItem(unsigned int index)
{
	UIWidget* pWidget = NULL;
	if (m_listView)
	{
		pWidget = (m_listView->getChildByTag(index));
	}
	return pWidget;
}

void UIScrollList::listViewEvent(CCObject* pSender, ListViewEventType type)
{
	switch (type)
	{
	case LISTVIEW_EVENT_INIT_CHILD:
		{
		}
		break;
	case LISTVIEW_EVENT_UPDATE_CHILD:
		{
		}
		break;
	default:
		break;
	}
}

void UIScrollList::pushDownEvent(CCObject* pObj)
{
	if (pObj)
	{
		UIWidget* pWidget = dynamic_cast<UIWidget*>(pObj);
		if (pWidget)
		{
			int nTag = pWidget->getTag();
		}		
	}
}

void UIScrollList::releaseEvent(CCObject* pObj)
{
	if (pObj)
	{
		UIWidget* pWidget = dynamic_cast<UIWidget*>(pObj);
		if (pWidget)
		{
			int nTag = pWidget->getTag();
		}	
	}
}