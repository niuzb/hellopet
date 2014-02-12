#ifndef _MATH_ATRIANGLE_SHAPE_H_
#define _MATH_ATRIANGLE_SHAPE_H_

#include "MathShapeBase.h"
#include "MathShapeLine.h"

class MathATriangleShape : public MathShapeBase
{
public:
	MathATriangleShape();
	virtual ~MathATriangleShape();

	void SetATriangle(MathShapeLine firstLine,MathShapeLine secLine);

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
};

#endif	//_MATH_ATRIANGLE_SHAPE_H_