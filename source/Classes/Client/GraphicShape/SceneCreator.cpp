#include "SceneCreator.h"
#include "ShapeCreaterFactory.h"
#include "CameraController.h"

#include "cocos2d.h"

USING_NS_CC;

SceneCreator::SceneCreator()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();	
	mHeroPos = ccp(0,screenSize.height/2.0);
	mHeroVec = ccp(100,0);
	mParentNode = NULL;
	mHeroDistanceToLeftScreen = 0;

	CameraController::sharedCameraController()->SetFollowType(CameraController::E_FixPoint);
}

SceneCreator::~SceneCreator()
{
}

void SceneCreator::SetParentNode(CCNode* parentNode)
{
	mParentNode = parentNode;
}

void SceneCreator::updateHeroPos(float dt)
{
	mHeroPos.x += mHeroVec.x * dt;
	mHeroPos.y += mHeroVec.y * dt;
}

// Note: 更新摄像机（需要添加摄像机管理类）
void SceneCreator::updateCameraByHero()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();	
	CCPoint newPos = ccp(mHeroPos.x+screenSize.width/2-mHeroDistanceToLeftScreen,mHeroPos.y);
	CameraController::sharedCameraController()->SetFollowPoint(newPos);
}

void SceneCreator::update(float dt)
{
	updateHeroPos(dt);
	updateCameraByHero();

	ShapeCreaterFactory::Get()->SetState(kType_ShapeCreateState_Running);
	ShapeCreaterFactory::Get()->SetHeroPos(mHeroPos);
	ShapeCreaterFactory::Get()->update(dt);	
}

void SceneCreator::draw()
{
	ShapeCreaterFactory::Get()->draw();
}