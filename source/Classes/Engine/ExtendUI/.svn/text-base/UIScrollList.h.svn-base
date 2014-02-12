#ifndef _UI_SCROLL_LIST_H_
#define _UI_SCROLL_LIST_H_

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

class UIScrollList : public CCObject
{
public:
	UIScrollList(UILayer* pLayer,Layout* pLayout,const char* listContainerName,
		const char* listItemContainerName,const char* listItemTemplateFileName,LISTVIEW_DIR listViewDir = LISTVIEW_DIR_VERTICAL);
	virtual ~UIScrollList();

	UIWidget* AddListItem();
	/**
	* Instruction : 根据index来获取对应的ListItem
	* @param index start from 0
	*/	
	UIWidget* GetListItem(unsigned int index);

	void SetSpaceAtStart(float space){
		m_spaceAtStart = space;
	}
	void SetSpaceAtEnd(float space){
		m_spaceAtEnd = space;
	}
	void SetSpaceBetweenTwoItem(float space){
		m_spaceBetweenTwoItem = space;
	}

protected:
	void init();
	void findListTemplateByName(const char* listContainerName);
	void listViewEvent(CCObject* pSender, ListViewEventType type);

	UIWidget* addListItemVer();
	UIWidget* addListItemHor();

	// Note: Call Back
	void pushDownEvent(CCObject* pObj);
	void releaseEvent(CCObject* pObj);	

	// Note: Panel背景设置相关
	void SetEnableScale9Mode(bool bEnableScale9Mode){
		m_bEnableScale9Mode = bEnableScale9Mode;
	}
	void SetPanelBgImageName(const char* panelImageName);
protected:
	LISTVIEW_DIR m_listViewDir;

	UILayer* m_uiLayer;
	Layout* m_layout;
	UIListView* m_listView;
	UIWidget* m_listContainer;

	unsigned int m_nItemsCount;
	CCSize m_listViewSize;

	const char* m_listItemTemplateFileName;
	const char* m_listContainerName;
	const char* m_listItemContainerName;

	// Note: Panel背景设置相关
	bool m_bEnableScale9Mode;
	const char* m_bgImageName;

	// Note: 设置和间隔相关
	float m_spaceAtStart;
	float m_spaceAtEnd;
	float m_spaceBetweenTwoItem;
};

#endif	//_UI_SCROLL_LIST_H_