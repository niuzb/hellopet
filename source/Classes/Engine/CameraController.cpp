#include "CameraController.h"
#include "cocos2d.h"

USING_NS_CC;

#define SHAKE_FREQUENCY 45

CameraController *CameraController::s_pSharedCameraController = NULL;

CameraController *CameraController::sharedCameraController()
{
	if(s_pSharedCameraController == NULL)
	{
		s_pSharedCameraController = new CameraController();
	}
	return s_pSharedCameraController;
}

void CameraController::purgeInstance()
{
	if (s_pSharedCameraController)
	{
		delete s_pSharedCameraController;
		s_pSharedCameraController = NULL;
	}
}

CameraController::CameraController()
{
	m_fLastUpdateTime = 0;
    
    mShakeTime = 0.0f;
    mShakeMagnitude = 0.0f;
    mShakeOffsetY = 0.0f;

	m_eCameraFollowType = E_FollowHero;
	m_followPoint = CCPointZero;
}

CameraController::~CameraController()
{
}

void CameraController::ResetValue()
{
	m_eCameraFollowType = E_FollowHero;
}


void CameraController::revertArch()
{
    
}

void CameraController::setarch()
{
}


void CameraController::shakeAndScale(float shakeTime)
{
}

void CameraController::shakeOnly(float shakeTime, float magnitude)
{
    mShakeTime = shakeTime;
    mShakeMagnitude = magnitude;  
}

void CameraController::levelScale()
{

}

void CameraController::Update(float dt)
{
    //CCLog("cameraController update:%f\n", dt);
	if (m_eCameraFollowType == E_FollowHero)
	{
		// update position
	}
	else if(m_eCameraFollowType == E_FixPoint)
	{
		followToOnePoint(m_followPoint,dt);
	}
}

void CameraController::followToOnePoint(cocos2d::CCPoint p,float dt /* = 0 */)
{
	// update position
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint center = ccp(screenSize.width / 2 , screenSize.height / 2);
	CCPoint targetPos = ccpSub(p, center);
	CCDirector::sharedDirector()->setLevelRenderCameraOffset(targetPos);
}
