#include "MathARectShape.h"

MathARectShape::MathARectShape():
	MathShapeBase()
{
	m_shapeEnum = kType_Shape_ARect;

	mSegmentNums = 3;
}

MathARectShape::~MathARectShape()
{
}

void MathARectShape::CalLineLength()
{
	CCPoint startPoint = mFirstLine.GetStartPoint();
	CCPoint endPoint = mThirdLine.GetEndPoint();

	CCPoint subPoint = ccpSub(endPoint,startPoint);
	mRealLength = sqrt(subPoint.x*subPoint.x + subPoint.y*subPoint.y);

	// Note: 计算直线在水平线上的投影（可扩展为任意线上的投影）
	mProjectLength = subPoint.x;
}

void MathARectShape::SetARect(MathShapeLine firstLine,MathShapeLine secLine,MathShapeLine thirdLine)
{
	bool bReCalLength = false;
	if (mFirstLine != firstLine)
	{
		bReCalLength = true;
		mFirstLine = firstLine;
	}
	if (mSecondLine != secLine)
	{
		bReCalLength = true;
		mSecondLine = secLine;
	}
	if (mThirdLine != thirdLine)
	{
		bReCalLength = true;
		mThirdLine = thirdLine;
	}

	if (bReCalLength)
	{
		CalLineLength();
	}		
}

float MathARectShape::GetProjectLength()
{
	return mProjectLength;
}

float MathARectShape::GetRealLength()
{
	return mRealLength;
}

CCPoint	MathARectShape::GetMinPoint()
{
	return mFirstLine.GetStartPoint();
}

CCPoint	MathARectShape::GetMaxPoint()
{
	return mThirdLine.GetEndPoint();
}

std::vector<MathShapeBase*> MathARectShape::GetShapeItems()
{
	std::vector<MathShapeBase*> vec;
	vec.push_back(&mFirstLine);
	vec.push_back(&mSecondLine);
	vec.push_back(&mThirdLine);
	return vec;
}