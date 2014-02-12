#include "TimeSynchronizer.h"
#include <time.h>
#include "NetWork/MessageHandler.h"
#include "NetWork/NetWorkUtil.h"
#include "NetWork/OnlineNetworkManager.h"

TimerSynchronizer* TimerSynchronizer::s_instance = NULL;

TimerSynchronizer::TimerSynchronizer():
	clientTimer(0),
	isTimeSyncOk(false)
{	
	this->retain();
	MessageHandler::sShareInstance()->registerMessageHandle(head_msg::CSPingRsp,this);
}

TimerSynchronizer::~TimerSynchronizer()
{
}

void TimerSynchronizer::Destory()
{
	if (s_instance != NULL)
	{
		delete s_instance;
		s_instance = NULL;
	}
}

TimerSynchronizer* TimerSynchronizer::shareSynchronizer()
{
	if (s_instance == NULL)
	{
		s_instance = new TimerSynchronizer();
		s_instance->autorelease();
	}
	return s_instance;
}

void TimerSynchronizer::update(float dt)
{
	if (isTimeSyncOk)
	{
		this->clientTimer += dt;
	}
}

// Note: 获取当前系统时间,单位ms
unsigned long TimerSynchronizer::getCurrentTime()    
{    
	struct timeval tv;    
	gettimeofday(&tv,NULL);    
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;    
}

void TimerSynchronizer::StartTimerSync()
{
	isTimeSyncOk = false;
	vecDeltaTimer.clear();
	this->clientTimer = getCurrentTime() / 1000.0;

	sendTimerSyncProto();
}

void TimerSynchronizer::EndTimerSync()
{
	isTimeSyncOk = true;
}

void TimerSynchronizer::sendTimerSyncProto()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance(head_msg::CSPingReq);
	CSPingReq  * bodyMsg = (CSPingReq  *)msg;
	bodyMsg->set_clienttime(getCurrentTime());

	KSendMessageResult result = OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, OnlineNetworkManager::PKG_TIMEOUT, NETWORK_TAG_PING, true, true);
}

bool TimerSynchronizer::isNetWorkStable(unsigned long &dt)
{
	return false;
}

int TimerSynchronizer::getMinDeltaTimerIndex()
{
	bool bFirstCheck = true;
	unsigned long min = 0;
	size_t vecSize = vecDeltaTimer.size();
	int minIndex = 0;
	for (size_t index = 0;index < vecSize;index++)
	{
		if (bFirstCheck)
		{
			min = vecDeltaTimer[index].deltaTimer;
			bFirstCheck = false;			
		}
		else
		{
			if (vecDeltaTimer[index].deltaTimer < min)
			{
				min = vecDeltaTimer[index].deltaTimer;
				minIndex = index;
			}
		}
	}
	return minIndex;
}

bool TimerSynchronizer::IsTimerSyncOk()
{
	return isTimeSyncOk;
}

void TimerSynchronizer::HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg)
{	
	if (cmd == head_msg::CSPingRsp)
	{
		CSPingRsp* _msg = dynamic_cast<CSPingRsp*>(msg->msg);
		if (_msg)
		{
			unsigned long clientTimer = _msg->clienttime();
			unsigned long serverTimer = _msg->servertime();

			unsigned long currentClientTimer = getCurrentTime();
			unsigned long deltaTimer = currentClientTimer - clientTimer;
			
			oneFrameTimerInfo oneInfo;
			oneInfo.clientTimer = clientTimer;
			oneInfo.serverTimer = serverTimer;
			oneInfo.deltaTimer = deltaTimer;

			vecDeltaTimer.push_back(oneInfo);
			if (vecDeltaTimer.size() > 20)
			{
				int minIndex = getMinDeltaTimerIndex();
				this->clientTimer = this->getCurrentTime() - vecDeltaTimer[minIndex].deltaTimer / 2.0 -  \
					vecDeltaTimer[minIndex].clientTimer + vecDeltaTimer[minIndex].serverTimer;

				this->clientTimer = this->clientTimer / 1000.0;

				EndTimerSync();
			}
			else
			{
				sendTimerSyncProto();
			}
		}
	}
}