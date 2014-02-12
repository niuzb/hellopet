#include "OnlineNetworkManager.h"
#include "NetStateChecker.h"
#include "cocos2d.h"

USING_NS_CC;

NetStateChecker::~NetStateChecker()
{

}

NetStateChecker::NetStateChecker()
	:counter(0)
{
	mTimeInMs = GetTimeWithLua();
}


void NetStateChecker::Start()
{
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(SEL_SCHEDULE(&NetStateChecker::Update),this,0,false);
}

void NetStateChecker::Stop()
{
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(SEL_SCHEDULE(&NetStateChecker::Update), this);
}

void NetStateChecker::SendRqsToServer()
{
	//CCLOG("---Send Ping---");
	mTimeInMs = GetTimeWithLua();	
	counter = -1;
}

void NetStateChecker::RecieveRqsFromServer()
{	
	//CCLOG("---Recieve Ping---");
	long time = GetTimeWithLua();
	long mDeltaTime = abs(time - mTimeInMs);
	//CCDirector::sharedDirector()->SetNetDelayTime(mDeltaTime);  
	counter = 0;
}

void NetStateChecker::Update(float dt)
{
	if (counter >= 0)
	{
		counter += dt;
		if (counter >= 10)
		{
			SendRqsToServer();
		}
	}
}

long NetStateChecker::GetTimeWithLua()
{
	struct cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now,0);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}