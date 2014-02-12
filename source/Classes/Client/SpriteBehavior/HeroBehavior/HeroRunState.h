#ifndef _HERO_RUN_STATE_H_
#define _HERO_RUN_STATE_H_

#include "vector"
#include "cocos2d.h"

class SpriteBase;

USING_NS_CC;

class HeroRunState
{
public:
	HeroRunState(SpriteBase* pHero);
	virtual ~HeroRunState();

	void update(float dt);
	bool UpdateMoveSteps(const CCPoint& dstPt,CCPoint &cellDestPt,bool bPixelPos = true );
protected:
	void ReCalMoveSteps(const CCPoint& oldPt,const CCPoint& dstPt);
	bool CheckMoveOverOrNot();
private:
	SpriteBase* heroInstance;
	bool isRunOver;
	CCPoint moveDirection;
	CCPoint destPt;
	CCPoint destCellPt;
};

#endif	//_HERO_RUN_STATE_H_