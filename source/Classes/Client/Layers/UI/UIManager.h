#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_

#include "Singleton_t.h"
#include "cocos-ext.h"
#include "cocos2d.h"
#include "../../Sprite/UserData.h"
USING_NS_CC;
USING_NS_CC_EXT;

class UIManager : public TSingleton<UIManager>
{
public:
	enum EAnchorPtType
	{
		// Note: ����
		E_LEFT_UP,
		// Note: ����
		E_MID_UP,
		// Note: ����
		E_RIGHT_UP,
		// Note: ����
		E_LEFT_CEN,
		// Note: ����
		E_MID_CEN,
		// Note: ����
		E_RIGHT_CEN,
		// Note: ����
		E_LEFT_DOWN,
		// Note: ����
		E_MID_DOWN,
		// Note: ����
		E_RIGHT_DOWN,
		E_UNKnow
	};
public:
	UIManager();
	~UIManager();

	float GetScaleFactor();
	float GetScaleFactorX();
	float GetScaleFactorY();

	float GetMapScaleFactor();

	// Note: �򵥵���Ļ����Ӧ�������ᵼ��UI����
	void ScaleWidgetToScreen(Layout* pLayout);
	// Note: ������������UI����Ӧ������ʹ����Ļê���UIê��
	void AdjustWidgetForScreen(UIWidget* pWidget,const CCPoint& toScreenAnchorPt,const CCPoint& widgetAnchorPt);
	void AdjustWidgetForScreen(UIWidget* pWidget,EAnchorPtType toScreenAnchorPtType,EAnchorPtType widgetAnchorPtType);
private:
	CCPoint GetAnchorPointByEnum(EAnchorPtType type);
private:
	static const int DESIGN_PANEL_WIDTH = 1136;
	static const int DESIGN_PANEL_HEIGHT = 640;
};

#endif	//_UIMANAGER_H_