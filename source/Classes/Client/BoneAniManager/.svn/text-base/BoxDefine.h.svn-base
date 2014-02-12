#ifndef _BOX_DEFINE_H_
#define _BOX_DEFINE_H_

#include "map"
#include "cocos2d.h"

USING_NS_CC;

struct _CCAreaData;

typedef struct _CCAreaData
{
	float upLeftX;
	float upLeftY;
	float downRightX;
	float downRightY;

	_CCAreaData()
	{
		reset();
	}
	_CCAreaData(int upLeftX,int upLeftY,int downRightX,int downRightY)
	{
		this->upLeftX = upLeftX;
		this->upLeftY = upLeftY;
		this->downRightX = downRightX;
		this->downRightY = downRightY;
	}
	void reset()
	{
		upLeftX = upLeftY = downRightX = downRightY = 0;
	}

	bool IsValid()
	{
		if (downRightX == upLeftX || downRightY == upLeftY)
		{
			return false;
		}
		return true;
	}
	bool intersectsArea(const _CCAreaData &area)
	{
		return !(     downRightX < area.upLeftX ||
			area.downRightX <      upLeftX ||
			upLeftY < area.downRightY ||
			area.upLeftY <      downRightY);			
	}
	_CCAreaData FlipArea()
	{
		float _upLeftX = -downRightX;
		float _upLeftY = upLeftY;
		float _downRightX = -upLeftX;
		float _downRightY = downRightY;

		return _CCAreaData(_upLeftX,_upLeftY,_downRightX,_downRightY);
	}

	CCRect ToRect(){
		return CCRectMake(this->upLeftX,this->downRightY,fabs(this->downRightX-this->upLeftX),fabs(this->upLeftY - this->downRightY));
	}
	
} CCAreaData, *PCCAreaData;

typedef struct _CCMoveAreaData
{
	CCAreaData selfColliderArea;
	CCAreaData selfViewRectArea;
	std::map<int,CCAreaData> kvFrameIndexAndAreaData;

	~_CCMoveAreaData()
	{
		reset();
	}
	void reset()
	{
		selfColliderArea.reset();
		selfViewRectArea.reset();
		kvFrameIndexAndAreaData.clear();
	}
} CCMoveAreaData, *PCCMoveAreaData;

typedef struct _CCColliderData
{
	// Note: 动作id&区域相关数据
	std::map<int,CCMoveAreaData> kvMoveIdAndAreaData;
} CCColliderData, *PCCColliderData;

#endif	//_BOX_DEFINE_H_