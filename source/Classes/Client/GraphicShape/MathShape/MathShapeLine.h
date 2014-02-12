#ifndef _MATH_SHAPE_LINE_H_
#define _MATH_SHAPE_LINE_H_

#include "cocos2d.h"

#include "MathShapeBase.h"

USING_NS_CC;

class MathShapeLine : public MathShapeBase
{
public:
	MathShapeLine();
	MathShapeLine(CCPoint startPoint,CCPoint endPoint);
	~MathShapeLine();

	void SetStartPoint(CCPoint p);
	void SetEndPoint(CCPoint p);
	void SetLine(CCPoint startPoint,CCPoint endPoint);
	void SetLine(MathShapeLine line);

	CCPoint GetStartPoint();
	CCPoint GetEndPoint();

	virtual float	GetProjectLength();
	virtual float	GetRealLength();
	virtual CCPoint	GetMinPoint();
	virtual CCPoint	GetMaxPoint();
	virtual std::vector<MathShapeBase*> GetShapeItems();

	bool operator==(MathShapeLine &line);
	bool operator!=(MathShapeLine &line);
private:
	void CalLineLength();
private:
	CCPoint mStartPoint;
	CCPoint mEndPoint;

};

#endif	//_MATH_SHAPE_LINE_H_