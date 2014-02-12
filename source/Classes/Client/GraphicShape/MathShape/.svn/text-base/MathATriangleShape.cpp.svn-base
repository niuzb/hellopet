#include "MathATriangleShape.h"

MathATriangleShape::MathATriangleShape():
	MathShapeBase()
{
	m_shapeEnum = kType_Shape_ATriangle;

	mSegmentNums = 2;
}

MathATriangleShape::~MathATriangleShape()
{
}

void MathATriangleShape::CalLineLength()
{
	CCPoint startPoint = mFirstLine.GetStartPoint();
	CCPoint endPoint = mSecondLine.GetEndPoint();

	CCPoint subPoint = ccpSub(endPoint,startPoint);
	mRealLength = sqrt(subPoint.x*subPoint.x + subPoint.y*subPoint.y);

	// Note: 计算直线在水平线上的投影（可扩展为任意线上的投影）
	mProjectLength = subPoint.x;
}

void MathATriangleShape::SetATriangle(MathShapeLine firstLine,MathShapeLine secLine)
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

	if (bReCalLength)
	{
		CalLineLength();
	}		
}

float MathATriangleShape::GetProjectLength()
{
	return mProjectLength;
}

float MathATriangleShape::GetRealLength()
{
	return mRealLength;
}

CCPoint	MathATriangleShape::GetMinPoint()
{
	return mFirstLine.GetStartPoint();
}

CCPoint	MathATriangleShape::GetMaxPoint()
{
	return mSecondLine.GetEndPoint();
}

std::vector<MathShapeBase*> MathATriangleShape::GetShapeItems()
{
	std::vector<MathShapeBase*> vec;
	vec.push_back(&mFirstLine);
	vec.push_back(&mSecondLine);
	return vec;
}