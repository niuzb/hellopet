#ifndef _SHAPE_CREATER_FACTORY_H_
#define _SHAPE_CREATER_FACTORY_H_

#include "Singleton_t.h"
#include "ShapeEnum.h"
#include "vector"
#include "map"
#include "string"
#include <queue>
#include "list"
#include "MathShapeBase.h"
#include "MathShapeLine.h"

#include "cocos2d.h"

class ShapeCreaterFactory : public TSingleton<ShapeCreaterFactory>
{
public:
	ShapeCreaterFactory();
	~ShapeCreaterFactory();

	void update(float dt);
	void draw();

	void SetState(E_ShapeCreaterStateEnum state);
	void SetHeroPos(cocos2d::CCPoint p);

	void SetDistanceToRightScreen(float distance){
		mDistanceToRightScreen = distance;
	}
	void SetHeroDistanceToRightScreen(float distance){
		mHeroDistanceToLeftScreen = distance;
	}
private:
	MathShapeBase* CreateShapeRandom();
	void updateRightScreenPoint();
	void delLeftNotUsedNode();
	void delLeftLineFromVec(MathShapeBase* p);
	void addRightNode();
	void addOneShape(MathShapeBase* p);
	CCPoint* getDrawPoints(int &count);
private:
	E_ShapeCreaterStateEnum mState;

	cocos2d::CCPoint mHeroPoint;
	cocos2d::CCPoint mRightScreenPoint;
	cocos2d::CCPoint mLeftScreenPoint;
	unsigned int mScreenWidth;
	unsigned int mScreenHeight;

	std::list<MathShapeBase*> mVecMathShapes;
	std::list<MathShapeLine*> mVecMathLines;

	cocos2d::CCPoint mPathStartPoint;
	float mPathTotalLength;

	float mDistanceToRightScreen;
	float mHeroDistanceToLeftScreen;
};

#endif	// _SHAPE_CREATER_FACTORY_H_