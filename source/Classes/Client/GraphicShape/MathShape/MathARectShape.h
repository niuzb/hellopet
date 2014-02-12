#ifndef _MATH_ARECT_SHAPE_H_
#define _MATH_ARECT_SHAPE_H_

#include "MathShapeBase.h"
#include "MathShapeLine.h"

class MathARectShape : public MathShapeBase
{
public:
	MathARectShape();
	virtual ~MathARectShape();

	void SetARect(MathShapeLine firstLine,MathShapeLine secLine,MathShapeLine thirdLine);

	virtual float	GetProjectLength();
	virtual float	GetRealLength();
	virtual CCPoint	GetMinPoint();
	virtual CCPoint	GetMaxPoint();
	virtual std::vector<MathShapeBase*> GetShapeItems();
private:
	void CalLineLength();
private:
	MathShapeLine mFirstLine;
	MathShapeLine mSecondLine;
	MathShapeLine mThirdLine;
};

#endif	//_MATH_ARECT_SHAPE_H_