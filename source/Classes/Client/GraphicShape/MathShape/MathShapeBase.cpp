#include "MathShapeBase.h"

MathShapeBase:: MathShapeBase():
	m_shapeEnum(kType_Shape_UnKnow)
{
	mProjectLength = 0;
	mRealLength = 0;
	mSegmentNums = 0;
}

MathShapeBase::~ MathShapeBase()
{
}

E_ShapeEnum	MathShapeBase::GetShapeEnum()
{
	return m_shapeEnum;
}

int	MathShapeBase::GetSegmentNums()
{
	return mSegmentNums;
}