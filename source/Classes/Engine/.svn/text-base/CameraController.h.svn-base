#ifndef _CAMERA_CONTROLL_H_
#define _CAMERA_CONTROLL_H_

#include "cocos2d.h"

using namespace cocos2d;

class CameraController : public CCLayer
{
public:

	enum CameraFollowType
	{
		E_FollowHero = 0,
		E_FixPoint,
		E_CameraFollowUnKnow
	};
    
    static CameraController *sharedCameraController();
	static void purgeInstance();

	void ResetValue();

	CameraController();
	virtual ~CameraController();

	void Update(float dt);
    
    void shakeAndScale(float shakeTime);
    
    void shakeOnly(float shakeTime, float magnitude);
    void levelScale();

	void SetFollowPoint(CCPoint p)
	{
		m_followPoint = p;
	}

	void SetFollowType(CameraFollowType followType)
	{
		m_eCameraFollowType = followType;
	}
	void followToOnePoint(cocos2d::CCPoint p,float dt = 0);
private:
    void shakeUpdate(float dt);	
    
    void revertArch();
    void setarch();
protected:
    
    static CameraController *s_pSharedCameraController;

	float m_fLastUpdateTime;
    
    float mShakeTime;
    float mShakeMagnitude;
    float mShakeOffsetY;
    
    double m_accumulator;
    double m_lastTickTime;

	CCPoint m_followPoint;
	CameraFollowType m_eCameraFollowType;
};

#endif 