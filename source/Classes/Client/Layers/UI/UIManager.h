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
		// Note: 左上
		E_LEFT_UP,
		// Note: 中上
		E_MID_UP,
		// Note: 右上
		E_RIGHT_UP,
		// Note: 左中
		E_LEFT_CEN,
		// Note: 中中
		E_MID_CEN,
		// Note: 右中
		E_RIGHT_CEN,
		// Note: 左下
		E_LEFT_DOWN,
		// Note: 中下
		E_MID_DOWN,
		// Note: 右下
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

	// Note: 简单的屏幕自适应方法，会导致UI变形
	void ScaleWidgetToScreen(Layout* pLayout);
	// Note: 用来做不变形UI自适应方案，使用屏幕锚点和UI锚点
	void AdjustWidgetForScreen(UIWidget* pWidget,const CCPoint& toScreenAnchorPt,const CCPoint& widgetAnchorPt);
	void AdjustWidgetForScreen(UIWidget* pWidget,EAnchorPtType toScreenAnchorPtType,EAnchorPtType widgetAnchorPtType);
private:
	CCPoint GetAnchorPointByEnum(EAnchorPtType type);
private:
	static const int DESIGN_PANEL_WIDTH = 1136;
	static const int DESIGN_PANEL_HEIGHT = 640;
};

#endif	//_UIMANAGER_H_