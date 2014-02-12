#pragma once

#include "cocos2d.h"
#include "iostream"
#include "Client/BoneAniManager/SkeletonAnimCommonDefine.h"
#include "CArmature.h"
using namespace cocos2d;

/*骨架动画层次管理*/
class RoleActorBase : public MyCCArmature,
					  public CCAnimationEventListener
{
	
public:
	RoleActorBase();
	virtual ~RoleActorBase(void);

	/**
	* Instruction : 
	* @param : _name: 骨架名 _animationName: 动画名 _plistPath: pList路径 _imagePath: png路径 png_file_name: 资源文件名
	* @result : 
	*/
	static RoleActorBase *create(std::string _name, std::string _animationName, 
								 std::string png_file_name, int _index = 0);
	
	/**
	* Instruction : 初始化骨骼动画
	* @param : 
	* @result : 
	*/
	virtual bool init(std::string _name, std::string _animationName,
					  CCSpriteBatchNode * _batchNodeL, int _index = 0);

	/**
	* Instruction : 
	* @param : _aniType: start , complete , loopComplete , inFrame _aniID: 动画名 _frameID: 帧ID	
	* @result : 
	*/
	virtual void animationHandler(const char* _aniType, const char* _aniID, const char* _frameID);

	CCSpriteBatchNode *getBatchNode(){return mBatchNode;}

	void SetAnimationEventListener(CCAnimationEventListener* pListener)
	{
		mAnimationEventListener = pListener;
	}
protected:	
	CCSpriteBatchNode * createBatchNode(std::string png_file_name);
private:	
	CCSpriteBatchNode *mBatchNode;	
	CCAnimationEventListener* mAnimationEventListener;
};