#include "SpriteBaseNode.h"
#include "Map/MapDataCenter.h"
#include "CommonUtils.h"

SpriteBaseNode::SpriteBaseNode()
{
	posPt = CCPointZero;
	posPixelPt = CCPointZero;
	direction = CCPointZero;
}

SpriteBaseNode::~SpriteBaseNode()
{

}

void SpriteBaseNode::setPosition(const CCPoint &position,bool bUsePixelPt /* = true */)
{
	if (bUsePixelPt)
	{
		// Note: ʹ�����ص�
		MapDataCenter::Get()->ConvertPtToCellPos(position,posPt);
		posPixelPt = position;		
		CCNode::setPosition(position);
	}
	else
	{
		// Note: ʹ�ø��ӵ�
		posPt = position;
		MapDataCenter::Get()->ConvertCellPosToWordPos(posPt.x,posPt.y,posPixelPt);
		CCNode::setPosition(posPixelPt);
	}
}

const CCPoint& SpriteBaseNode::getPosition()
{
	return posPt;
}

const CCPoint& SpriteBaseNode::getPositionPixel()
{
	return posPixelPt;
}