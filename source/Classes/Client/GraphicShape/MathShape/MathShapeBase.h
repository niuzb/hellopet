#ifndef _MATH_SHAPE_BASE_
#define _MATH_SHAPE_BASE_

#include "ShapeEnum.h"
#include "vector"

#include "cocos2d.h"

USING_NS_CC;

class  MathShapeBase
{
public:
	 MathShapeBase();
	virtual ~ MathShapeBase();

	virtual float	GetProjectLength() = 0;
	virtual float	GetRealLength() = 0;
	virtual CCPoint	GetMinPoint() = 0;
	virtual CCPoint	GetMaxPoint() = 0;

	E_ShapeEnum		GetShapeEnum();
	int				GetSegmentNums();

	virtual std::vector<MathShapeBase*> GetShapeItems() = 0;
protected:
	E_ShapeEnum m_shapeEnum;

	float   mProjectLength;
	float	mRealLength;

	int		mSegmentNums;
};

#endif	//_MATH_SHAPE_BASE_