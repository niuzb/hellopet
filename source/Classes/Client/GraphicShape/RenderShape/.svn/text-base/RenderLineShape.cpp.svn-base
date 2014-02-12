#include "RenderLineShape.h"

RenderLineShape::RenderLineShape():
	RenderShapeBase()
{
	mShapeEnum = kType_Shape_Line;
}

RenderLineShape::~RenderLineShape()
{
}

void RenderLineShape::SetLine(CCPoint startPoint,CCPoint endPoint)
{
	mLineShape.SetLine(startPoint,endPoint);
}

void RenderLineShape::draw()
{
	ccDrawColor4B(mDrawColor.r,mDrawColor.g,mDrawColor.b,mDrawColor.a);
	glLineWidth(mDotSize);	
	ccDrawLine(mLineShape.GetStartPoint(),mLineShape.GetEndPoint());
}