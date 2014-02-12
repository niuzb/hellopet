#include "RenderShapeBase.h"

RenderShapeBase::RenderShapeBase()
{
	mDrawColor = ccc4(255,255,255,0);
	mDotSize = 1.0f;

	mShapeEnum = kType_Shape_UnKnow;
}

RenderShapeBase::~RenderShapeBase()
{
}

void RenderShapeBase::SetColor(ccColor4B color)
{
	mDrawColor = color;
}

void RenderShapeBase::SetDotSize(float size)
{
	if (size > 0.0)
	{
		mDotSize = size;
	}	
	else
	{
		CCLog("RenderShapeBase Error size ");
	}
}