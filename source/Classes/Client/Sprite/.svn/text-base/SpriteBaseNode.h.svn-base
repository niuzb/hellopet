#ifndef _SPRITE_BASE_NODE_H_
#define _SPRITE_BASE_NODE_H_

#include "cocos2d.h"

USING_NS_CC;

class SpriteBaseNode : public CCNode
{
public:
	SpriteBaseNode();
	virtual ~SpriteBaseNode();

	virtual void setPosition(const CCPoint &position,bool bUsePixelPt = true);
	virtual const CCPoint& getPosition();
	const CCPoint& getPositionPixel();
	virtual void SetDirection(CCPoint dir){
		direction = dir;
	}
	CCPoint GetDirection(){
		return direction;
	}
protected:
	CCPoint posPt;
	CCPoint posPixelPt;
	CCPoint direction;
};

#endif	// _SPRITE_BASE_NODE_H_