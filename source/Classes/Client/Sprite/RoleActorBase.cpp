#include "RoleActorBase.h"

CCSpriteBatchNode * RoleActorBase::createBatchNode(std::string png_file_name)
{
	CCSpriteBatchNode * batchNode = CCSpriteBatchNode::create( png_file_name.c_str() );
	return batchNode;
}

RoleActorBase *RoleActorBase::create(std::string _name, std::string _animationName, 									
									 std::string png_file_name, int _index /* = 0 */)
{
	RoleActorBase *pArmature = new RoleActorBase();
	CCSpriteBatchNode * _batchNode = pArmature->createBatchNode(png_file_name);
	if (pArmature && pArmature->init(_name, _animationName,_batchNode, _index))
	{
		pArmature->autorelease();
		return pArmature;
	}
	CC_SAFE_DELETE(pArmature);
	return NULL;
}


RoleActorBase::RoleActorBase()
{
	mBatchNode = NULL;
	mAnimationEventListener = NULL;
}

RoleActorBase::~RoleActorBase(void)
{
}

bool RoleActorBase::init(std::string _name, std::string _animationName,
						 CCSpriteBatchNode *_batchNodeL, int _index)
{
	mBatchNode = _batchNodeL;
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! MyCCArmature::init(_name.c_str(),_animationName.c_str(),_batchNodeL,_index));		
		mAnimation->setAniEventListener(this);
		bRet = true;
	} while (0);

	return bRet;
}

void RoleActorBase::animationHandler(const char* aniType, const char* aniID, const char* frameID)
{
	if (mAnimationEventListener != NULL)
	{
		mAnimationEventListener->animationHandler(aniType,aniID,frameID);
	}
}