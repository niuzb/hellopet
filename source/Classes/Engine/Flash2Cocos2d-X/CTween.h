#pragma once

#include "CProcessBase.h"
#include "CTweenNode.h"
#include "CFrameNodeList.h"
#include <math.h>

using namespace cocos2d;

#define  HALF_PI  (M_PI * 0.5f)

//骨骼缓动控制，处理关键帧数据并渲染到骨骼
class MyCCTween : public MyCCProcessBase
{
public:
	/*创建 Tween 实例，Tween 做为常用的实例，用对象池管理创建回收*/
	static MyCCTween* create();

	static void removePoolObject();
private:
	static void recycle(MyCCTween* _tween);

public:
	MyCCTween(void);
	~MyCCTween(void);

	virtual bool init();
	
	/*删除，回收*/
	void remove();
	/*设置 mNode*/
	void setNode(CCTweenNode* _node);
	/**
	* 播放补间动画
	* @param _to FrameNodeList 实例
	* @param _toFrames 过渡到 FrameNodeList 需要花费的帧
	* @param _listFrames FrameNodeList 播放持续的帧
	* @param _loop 是否循环
	* @param _ease FrameNodeList 各个关键点的缓动方式，-1:SineOut，0:Line，1:SineIn，2:SineInOut
	*/
	void playTo(void * _to, int _toFrames, int _listFrames = 0, bool _loop = false, int _ease = 0);
	/*设置 mNode*/
	void updateHandler();
	
	void setActive(bool _active);
	bool getActive();

	void SetPauseOnOver(bool bPauseOnOver = false)
	{
		mPauseOnOver = bPauseOnOver;
	}
private:

	void updateCurrentPrecent();

private:
	/* Bone.tweenNode 的引用 */
	CCTweenNode* mNode;

	CCTweenNode* mFrom;

	CCTweenNode* mTo;

	CCFrameNodeList* mTweenList;

	bool mActive;

	bool mPauseOnOver;
private:	
	//static CCArray	*sObjectPool;

	//static int		sPoolIndex;
};

