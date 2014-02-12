// TAOMEE GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Taomee Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 2012-2015 Taomee Game Technologies. 
//      All Rights Reserved.
//
// Taomee Game Technologies, Shanghai, China
// http://www.taomee.com
//

#ifndef iSeer_UIScrollLayer_h
#define iSeer_UIScrollLayer_h

#include "cocos2d.h"

namespace TXGUI
{
	USING_NS_CC;

	typedef enum {
		ESD_Horizontal          = 0,    // �������
		ESD_Vertical            = 1,    // �������
	} EScrollDirection;

	typedef enum {
		ESS_TOUCHED				= 0,    // �����ʼ
		ESS_DRAGGING			= 1,    // �϶���
		ESS_IDLE				= 2,	// ����
	} EScrollStatus;

	class UIScrollLayer: public CCLayer
	{
	private:
		CCPoint m_TouchDownPoint;
		CCPoint m_TouchUpPoint;
		CCPoint m_TouchCurPoint;
		CCPoint m_CenterWorldPos;
		CCPoint m_ptCenter;
		CCPoint m_ptOrigio;
    
		EScrollDirection m_ScrollDir;
		EScrollStatus	m_ScrollStatus;

		int m_Page;
		int m_CurPage; // ǰ��ҳ
		int m_showPage; // ��¼��ʾ��ҳ�棬����m_CurPage��ͬʱ������ҳ���л�֪ͨ

		bool m_bShouldStolenTouch;
    
		CCArray *m_PageLayer;
    
		CCLayer* m_baseLayer;

		float m_localScale;

		// �����л�ʱ�ص�֪ͨ
		SEL_CallFunc m_pageChangeHandler;
		CCObject*	 m_pageChangeTarget;

		//����ҳ���־�����
		vector<CCSprite *> indicators;
    
		/** Whenever show or not white/grey dots under the scroll layer.
		 * If yes - dots will be rendered in parents transform (rendered after scroller visit).
		 */
		CC_SYNTHESIZE(bool, m_bShowPagesIndicator, ShowPagesIndicator);
    
		/** Position of dots center in parent coordinates. 
		 */
		CC_SYNTHESIZE(CCPoint, m_tPagesIndicatorPosition, PagesIndicatorPosition);
    
		/** Calibration property. Minimum moving touch length that is enough to change
		 * the page, without snapping back to the previous selected page.
		 */
		CC_SYNTHESIZE(CGFloat, m_fMinimumTouchLengthToChangePage, MinimumTouchLengthToChangePage);

		 CC_SYNTHESIZE(int,m_bPriority,Priority);
	private:
		void goToPage(bool animated = true);
		void checkChildrenPos();
		void checkLayersVisiable();

		//����ҳ���־�����
		void clearIndicators();
		void addIndicators(EScrollDirection dir);

	public:
		UIScrollLayer();
		~UIScrollLayer();

		static UIScrollLayer* nodeWithNoLayer(CCSize pageSize, EScrollDirection dir);
    
		static UIScrollLayer* nodeWithLayers(CCArray* layers, CCSize pageSize, EScrollDirection dir); 

		bool initWithNoLayer(CCSize pageSize, EScrollDirection dir);
    
		bool initWithLayers(CCArray* layers, CCSize pageSize, EScrollDirection dir); 

	protected:
		bool touchIsInContent(CCPoint point);
	public:
    
		void visit();
    
		void registerWithTouchDispatcher();
		virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
		void claimTouch(CCTouch* pTouch);
		void cancelAndStoleTouch(CCTouch* pTouch, CCEvent* pEvent);

		// ��������ʱcheck�ӽ���λ��
		virtual void onMoveEnd(CCNode* obj);

		void setDirection(EScrollDirection direction);

		CCLayer *getBaseLayer();

		//page related
		int getCurPage();
		int getPageCount();
		CCLayer * getPageLayer(int page);
		void moveToPage(int page, bool animated = true);

		//override
		virtual void setPosition(CCPoint point);
		virtual void setScale(float scale);
		virtual void setScale(float xScale, float yScale);

		// ע�ᷭҳʱ��֪ͨ����
		void registerPageChangeCallback(CCObject* target,SEL_CallFunc handler);
	public:
		void addPage(CCLayer *pPageLayer);
		void addPages(CCArray *layers);
		void removeAllPages();
	};

}
#endif
