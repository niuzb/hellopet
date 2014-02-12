#ifndef _RENDER_SHAPE_BASE_H_
#define _RENDER_SHAPE_BASE_H_

#include "cocos2d.h"

#include "ShapeEnum.h"

USING_NS_CC;

class RenderShapeBase
{
public:
	RenderShapeBase();
	virtual ~RenderShapeBase();

	virtual void draw() = 0;

	void SetColor(ccColor4B color);
	void SetDotSize(float size);
protected:
	ccColor4B mDrawColor;
	float mDotSize;

	E_ShapeEnum mShapeEnum;
};

#endif	// _RENDER_SHAPE_BASE_H_