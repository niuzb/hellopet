#include "ShapeCreaterFactory.h"

#include <cstdlib>
#include <ctime>

#include "MathATriangleShape.h"
#include "MathARectShape.h"

ShapeCreaterFactory::ShapeCreaterFactory()
{
	mState = kType_ShapeCreateState_UnKnow;

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	mScreenWidth = screenSize.width;
	mScreenHeight = screenSize.height;

	mHeroPoint = CCPointZero;
	mRightScreenPoint = CCPointZero;
	mLeftScreenPoint = CCPointZero;
	mPathStartPoint = CCPointZero;
	mPathTotalLength = 0;

	mDistanceToRightScreen = 0;
	mHeroDistanceToLeftScreen = 0;
}

ShapeCreaterFactory::~ShapeCreaterFactory()
{
	for (std::list<MathShapeBase*>::iterator iter = mVecMathShapes.begin();
		 iter != mVecMathShapes.end(); iter++)
	{
		delete (*iter);
	}
	mVecMathShapes.clear();
	mVecMathLines.clear();
}

void ShapeCreaterFactory::SetState(E_ShapeCreaterStateEnum state)
{
	mState = state;
}

void ShapeCreaterFactory::SetHeroPos(CCPoint p)
{
	mHeroPoint = p;
}

MathShapeBase* ShapeCreaterFactory::CreateShapeRandom()
{
	MathShapeBase* pShape = NULL;
	srand((unsigned)(time(NULL)));

	CCPoint startPoint = ccp(0,388);
	if (mVecMathShapes.size() > 0)
	{
		MathShapeBase* p = mVecMathShapes.back();
		startPoint = p->GetMaxPoint();
	}	

	int type = rand()%(3);
	int delValue = rand() % 100 + 10;
	int hDelValue = rand() % 70 + 20;
	int nReverse = rand()%(2);
	if (nReverse == 0)
	{
		hDelValue = -hDelValue;
	}
	switch (type)
	{
	case 0:
		{
			pShape = new MathShapeLine();
			if (pShape)
			{
				((MathShapeLine*)(pShape))->SetLine(ccp(startPoint.x,startPoint.y),ccp(startPoint.x+delValue,startPoint.y));
			}
		}		
		break;
	case 1:
		{
			pShape = new MathATriangleShape();
			if (pShape)
			{
				((MathATriangleShape*)(pShape))->SetATriangle(MathShapeLine(ccp(startPoint.x,startPoint.y),ccp(startPoint.x+delValue,startPoint.y+hDelValue)),
					MathShapeLine(ccp(startPoint.x+delValue,startPoint.y+hDelValue),ccp(startPoint.x+2*delValue,startPoint.y)));
			}
		}
		break;
	case 2:
		{
			pShape = new MathARectShape();
			if (pShape)
			{
				((MathARectShape*)(pShape))->SetARect(MathShapeLine(ccp(startPoint.x,startPoint.y),ccp(startPoint.x,startPoint.y+hDelValue)),
					MathShapeLine(ccp(startPoint.x,startPoint.y+hDelValue),ccp(startPoint.x+delValue,startPoint.y+hDelValue)),
					MathShapeLine(ccp(startPoint.x+delValue,startPoint.y+hDelValue),ccp(startPoint.x+2*delValue,startPoint.y)));
			}
		}
		break;
	default:
		{
			pShape = new MathShapeLine();
			if (pShape)
			{
				((MathShapeLine*)(pShape))->SetLine(ccp(startPoint.x,startPoint.y),ccp(startPoint.x+10,startPoint.y+5));
			}
		}
		break;
	}

	CCAssert(pShape != NULL,"create shape error");
	return pShape;
}

void ShapeCreaterFactory::updateRightScreenPoint()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint cameraLeftCornerPoint = ccp(mHeroPoint.x - mHeroDistanceToLeftScreen,0);
	mRightScreenPoint = ccp(cameraLeftCornerPoint.x + screenSize.width - mDistanceToRightScreen,0);
	mLeftScreenPoint = cameraLeftCornerPoint;
}

void ShapeCreaterFactory::delLeftLineFromVec(MathShapeBase* p)
{
	if (p)
	{
		int sum = p->GetSegmentNums();
		if (sum > 0)
		{
			int count = 0;
			for (std::list<MathShapeLine*>::iterator iter = mVecMathLines.begin();
				iter != mVecMathLines.end();)
			{
				iter = mVecMathLines.erase(iter);

				count ++;
				if (count >= sum)
				{
					break;
				}
			}
		}
	}
}

void ShapeCreaterFactory::delLeftNotUsedNode()
{
	for (std::list<MathShapeBase*>::iterator iter = mVecMathShapes.begin();
		iter != mVecMathShapes.end();)
	{
		CCPoint p = (*iter)->GetMaxPoint();
		if (p.x < mLeftScreenPoint.x)
		{			
			delLeftLineFromVec((*iter));
			delete (*iter);
			iter = (mVecMathShapes).erase(iter);
		}
		else
		{
			break;
		}
	}
}

void ShapeCreaterFactory::addRightNode()
{
	while (true)
	{
		if (mVecMathShapes.size() == 0)
		{
			MathShapeBase* p = CreateShapeRandom();
			addOneShape(p);
		}
		else
		{
			MathShapeBase* p = mVecMathShapes.back();
			CCPoint maxPoint = p->GetMaxPoint();
			if (maxPoint.x >= mRightScreenPoint.x)
			{
				break;
			}
			else
			{
				MathShapeBase* p = CreateShapeRandom();				
				addOneShape(p);
			}
		}	
	}
}

void ShapeCreaterFactory::addOneShape(MathShapeBase* p)
{
	mVecMathShapes.push_back(p);
	std::vector<MathShapeBase*> vec = p->GetShapeItems();
	for (std::vector<MathShapeBase*>::iterator iter = vec.begin();
		 iter != vec.end(); iter++)
	{
		mVecMathLines.push_back((MathShapeLine*)(*iter));
	}
}

void ShapeCreaterFactory::update(float dt)
{
	if (mState == kType_ShapeCreateState_UnKnow)
	{
		return ;
	}

	// Note: 
	updateRightScreenPoint();

	// Note: 删除左侧不需要的线段
	delLeftNotUsedNode();

	// Note: 添加新的节点
	addRightNode();
}

CCPoint* ShapeCreaterFactory::getDrawPoints(int &count)
{
	int vecSize = mVecMathLines.size();
	if (vecSize >= 1)
	{
		for (std::list<MathShapeLine*>::reverse_iterator iter = mVecMathLines.rbegin();
			 iter != mVecMathLines.rend(); iter++)
		{
			CCPoint p = (*iter)->GetEndPoint();
			if (p.x < mRightScreenPoint.x)
			{
				count = vecSize + 5;
				CCPoint* points = new CCPoint[count];

				MathShapeLine* pStartPoint = mVecMathLines.front();
				MathShapeLine* pEndPoint = mVecMathLines.back();
				points[0] = ccp(pStartPoint->GetStartPoint().x,- 500);

				int index = 0;
				for (std::list<MathShapeLine*>::iterator _iter = mVecMathLines.begin();
					_iter != mVecMathLines.end(); _iter++)
				{
					points[index+1] = (*_iter)->GetStartPoint();
					index ++;
					if (index == vecSize)
					{
						break;
					}
				}

				std::list<MathShapeLine*>::reverse_iterator nextIter = iter --;
				points[vecSize+1] = (*nextIter)->GetStartPoint();
				CCPoint nextEndPoint = (*nextIter)->GetEndPoint();				

				float t = (mRightScreenPoint.x - points[vecSize+1].x)/(nextEndPoint.x - points[vecSize+1].x);
				float y = t*(nextEndPoint.y - points[vecSize+1].y) + points[vecSize+1].y;
				points[vecSize+2] = ccp(mRightScreenPoint.x,y);

				points[vecSize+3] = ccp(points[vecSize+2].x, - 500);
				points[vecSize+4] = points[0];

				return points;
			}
			else
			{
				vecSize --;
			}
		}
	}
	else
	{
		return NULL;
	}	
	return NULL;
}

void ShapeCreaterFactory::draw()
{
	//for (std::list<MathShapeLine*>::iterator iter = mVecMathLines.begin();
	//	iter != mVecMathLines.end(); iter++)
	//{
	//	ccDrawColor4B(0, 255, 255, 0);
	//	glLineWidth( 2.0f );	
	//	ccDrawLine((*iter)->GetStartPoint(),(*iter)->GetEndPoint());		
	//}

	int count = 0;
	CCPoint * pDrawPoints = getDrawPoints(count);
	if (pDrawPoints)
	{
		ccDrawColor4B(0, 255, 255, 0);
		ccDrawPoly(pDrawPoints,count,true);

		delete []pDrawPoints;
	}
}