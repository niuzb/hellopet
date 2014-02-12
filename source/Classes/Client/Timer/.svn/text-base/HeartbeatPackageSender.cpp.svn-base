#include "HeartbeatPackageSender.h"
#include "NetWork/MessageHandler.h"

HeartBeatPackageSender::HeartBeatPackageSender():
	isTimerAdjust(false),
	messageSenderDeltaTimer(10)
{
	//MessageHandler::sShareInstance()->registerMessageHandle("CSPingRsp",this);
}

HeartBeatPackageSender::~HeartBeatPackageSender()
{
}

void HeartBeatPackageSender::SendHeartBeatMessage(float dt)
{
	if (isTimerAdjust)
	{
	}
	else
	{

	}
}

void HeartBeatPackageSender::SetMessageDeltaTimer(float t)
{
	if (t >= 0)
	{
		messageSenderDeltaTimer = t;
	}
	else
	{
		CCAssert(false,"HeartBeatPackageSender::SetMessageDeltaTimer time lower 0");
	}
}

void HeartBeatPackageSender::StartSender()
{
	CCScheduler * pSchedule = CCDirector::sharedDirector()->getScheduler();
	if (pSchedule)
	{
		pSchedule->scheduleSelector(schedule_selector(HeartBeatPackageSender::SendHeartBeatMessage), 
			this, 
			messageSenderDeltaTimer,
			false);
	}
}

void HeartBeatPackageSender::EndSender()
{
	CCScheduler * pSchedule = CCDirector::sharedDirector()->getScheduler();
	if (pSchedule)
	{
		pSchedule->unscheduleSelector(schedule_selector(HeartBeatPackageSender::SendHeartBeatMessage), 
			this);
	}
}

void HeartBeatPackageSender::HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg)
{	
	//if (cmd == "CSPingRsp")
	//{
	//	CSPingRsp* _msg = dynamic_cast<CSPingRsp*>(msg->msg);
	//	if (_msg)
	//	{

	//	}
	//}
}