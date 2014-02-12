#ifndef _LINE_SHAPE_H_
#define _LINE_SHAPE_H_ 

#include "RenderShapeBase.h"
#include "MathShapeLine.h"

class RenderLineShape : public RenderShapeBase
{
public:
	RenderLineShape();
	~RenderLineShape();

	virtual void draw();
	
	void SetLine(CCPoint startPoint,CCPoint endPoint);
private:
	MathShapeLine mLineShape;
};

#endif	// _LINE_SHAPE_H_