#ifndef _HEART_BEAT_PACKAGE_SENDER_H_
#define _HEART_BEAT_PACKAGE_SENDER_H_

#include "Singleton_t.h"
#include "cocos2d.h"
#include "NetWork/BaseMsgHandler.h"

USING_NS_CC;

class HeartBeatPackageSender : public TSingleton<HeartBeatPackageSender>, public CCNode, public InterfaceMsgHandle
{
public:
	HeartBeatPackageSender();
	virtual ~HeartBeatPackageSender();

	// Note: 设置发送心跳包的频率，次/s
	void SetMessageDeltaTimer(float t);
	// Note: 设置是否进行时间校准
	void SetTimeAdjustmentOrNot(bool bTimeAdjust);
	// Note: 开始发送
	void StartSender();
	// Note: 结束发送
	void EndSender();

	virtual void HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg);
protected:
	// Note: 向服务器端发射心跳包
	void SendHeartBeatMessage(float dt);
private:
	bool isTimerAdjust;
	unsigned int messageSenderDeltaTimer;
};

#endif	//_HEART_BEAT_PACKAGE_SENDER_H_