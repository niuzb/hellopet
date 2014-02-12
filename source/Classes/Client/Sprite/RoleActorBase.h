#pragma once

#include "cocos2d.h"
#include "iostream"
#include "Client/BoneAniManager/SkeletonAnimCommonDefine.h"
#include "CArmature.h"
using namespace cocos2d;

/*�Ǽܶ�����ι���*/
class RoleActorBase : public MyCCArmature,
					  public CCAnimationEventListener
{
	
public:
	RoleActorBase();
	virtual ~RoleActorBase(void);

	/**
	* Instruction : 
	* @param : _name: �Ǽ��� _animationName: ������ _plistPath: pList·�� _imagePath: png·�� png_file_name: ��Դ�ļ���
	* @result : 
	*/
	static RoleActorBase *create(std::string _name, std::string _animationName, 
								 std::string png_file_name, int _index = 0);
	
	/**
	* Instruction : ��ʼ����������
	* @param : 
	* @result : 
	*/
	virtual bool init(std::string _name, std::string _animationName,
					  CCSpriteBatchNode * _batchNodeL, int _index = 0);

	/**
	* Instruction : 
	* @param : _aniType: start , complete , loopComplete , inFrame _aniID: ������ _frameID: ֡ID	
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