#include "MathShapeLine.h"

MathShapeLine::MathShapeLine()
{
	m_shapeEnum = kType_Shape_Line;

	mStartPoint = CCPointZero;
	mEndPoint = CCPointZero;

	mSegmentNums = 1;
}

MathShapeLine::MathShapeLine(CCPoint startPoint,CCPoint endPoint)
{
	m_shapeEnum = kType_Shape_Line;
	
	mStartPoint = startPoint;
	mEndPoint = endPoint;

	CalLineLength();
}

MathShapeLine::~MathShapeLine()
{

}

bool MathShapeLine::operator==(MathShapeLine &line)
{
	CCPoint startPoint = line.GetStartPoint();
	CCPoint endPoint = line.GetEndPoint();

	if (mStartPoint.x == startPoint.x && 
		mStartPoint.y == startPoint.y && 
		mEndPoint.x == endPoint.x && 
		mEndPoint.y == endPoint.y
		)
	{
		return true;
	}
	return false;
}

bool MathShapeLine::operator!=(MathShapeLine &line)
{
	return !(this->operator==(line));
}

void MathShapeLine::CalLineLength()
{
	CCPoint subPoint = ccpSub(mEndPoint,mStartPoint);
	mRealLength = sqrt(subPoint.x*subPoint.x + subPoint.y*subPoint.y);

	// Note: 计算直线在水平线上的投影（可扩展为任意线上的投影）
	mProjectLength = subPoint.x;
}

void MathShapeLine::SetStartPoint(CCPoint p)
{
	if (p.x != mStartPoint.x || p.y != mStartPoint.y)
	{
		mStartPoint = p;
		CalLineLength();
	}
}

void MathShapeLine::SetEndPoint(CCPoint p)
{
	if (p.x != mEndPoint.x || p.y != mEndPoint.y)
	{
		mEndPoint = p;
		CalLineLength();
	}
}

void MathShapeLine::SetLine(CCPoint startPoint,CCPoint endPoint)
{
	bool bRelCalLength = false;

	if (startPoint.x != mStartPoint.x || startPoint.y != mStartPoint.y)
	{
		bRelCalLength = true;
		mStartPoint = startPoint;
	}

	if (endPoint.x != mEndPoint.x || endPoint.y != mEndPoint.y)
	{
		bRelCalLength = true;
		mEndPoint = endPoint;
	}

	if (bRelCalLength)
	{
		CalLineLength();
	}
}

void MathShapeLine::SetLine(MathShapeLine line)
{
	SetLine(line.mStartPoint,line.mEndPoint);
}

CCPoint MathShapeLine::GetStartPoint()
{
	return mStartPoint;
}

CCPoint MathShapeLine::GetEndPoint()
{
	return mEndPoint;
}

float MathShapeLine::GetProjectLength()
{
	return mProjectLength;
}

float MathShapeLine::GetRealLength()
{
	return mRealLength;
}

CCPoint	MathShapeLine::GetMinPoint()
{
	return mStartPoint;
}

CCPoint	MathShapeLine::GetMaxPoint()
{
	return mEndPoint;
}

std::vector<MathShapeBase*> MathShapeLine::GetShapeItems()
{
	std::vector<MathShapeBase*> vec;
	vec.push_back(this);
	return vec;
}