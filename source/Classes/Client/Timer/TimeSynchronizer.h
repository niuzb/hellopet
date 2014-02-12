#ifndef _TIMER_SYNCHORNIZER_H_
#define _TIMER_SYNCHORNIZER_H_

#include "Singleton_t.h"
#include "cocos2d.h"
#include "network/BaseMsgHandler.h"
#include "vector"

USING_NS_CC;

class TimerSynchronizer : public CCNode , public InterfaceMsgHandle
{
public:
	struct oneFrameTimerInfo
	{
		unsigned long clientTimer;
		unsigned long serverTimer;
		unsigned long deltaTimer;
		oneFrameTimerInfo(){
			clientTimer = 0;
			serverTimer = 0;
			deltaTimer = 0;
		}
	};
public:
	TimerSynchronizer();
	virtual ~TimerSynchronizer();
	static TimerSynchronizer* shareSynchronizer();
	static void Destory();

	virtual void update(float dt);

	void StartTimerSync();
	void EndTimerSync();

	bool IsTimerSyncOk();
	double GetClientTimer(){
		return clientTimer;
	}
protected:
	unsigned long getCurrentTime();
	void sendTimerSyncProto();
	bool isNetWorkStable(unsigned long &dt);
	int getMinDeltaTimerIndex();
	virtual void HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg);
private:
	bool isTimeSyncOk;
	// Note: 当前时间,单位s
	double clientTimer;
	std::vector<oneFrameTimerInfo> vecDeltaTimer;
	static TimerSynchronizer* s_instance;
};

#endif	//_TIMER_SYNCHORNIZER_H_