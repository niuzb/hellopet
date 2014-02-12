#ifndef MESSAGE_HANDER_H
#define MESSAGE_HANDER_H

#include <set>
#include <map>
#include <string>
#include "BaseMsgHandler.h"

using namespace std;

class BaseMsgHandler;
//------------------------------------------------------------------------
//				message handler
//------------------------------------------------------------------------

class MessageHandler
{
public:
	static MessageHandler*			sShareInstance();
	static void Destroy();

	//------------------------------------------------------------------------
	//				handle message
	//------------------------------------------------------------------------
	void							handleMessage(NORMAL_MSG_PACKAGE* package);
	//this func call lua to process the msg . return false means lua process fail
	bool 							handleMessage(WILD_MSG_PACKAGE* package);

	//------------------------------------------------------------------------
	//				only valid at cur frame
	//------------------------------------------------------------------------
	WILD_MSG_PACKAGE*				getWildMsgPackage()			{return mCurWildMsgPackage;}

	/**
	* Instruction : 注册一个消息处理对象
	* @param ： message_name 消息名称
	* @param ： pHandler 消息处理对象
	*/	
	void	registerMessageHandle(unsigned int message_type, InterfaceMsgHandle* pHandler);
	/**
	* Instruction : 消息反注册（反注册该对象上绑定的所有消息）
	* @param ：pHandler消息处理对象
	*/	
	void	unRegisterMessageHandle(InterfaceMsgHandle* pHandler);
	/**
	* Instruction : 消息反注册（反注册message对应的所有对象）
	* @param ：message_name消息名称
	*/	
	void	unRegisterMessageHandle(unsigned int message_type);
	/**
	* Instruction : 消息反注册（反注册message对应的pHandler对象）
	* @param ：message_name消息名称 pHandler 消息处理对象
	*/	
	void	unRegisterMessageHandle(unsigned int message_type,InterfaceMsgHandle* pHandler);
protected:
	MessageHandler();
	~MessageHandler();	

	void	postHandleMsg();
protected:
	void							registerMessageHandlerFunction();

	static MessageHandler*			sInstance;

	WILD_MSG_PACKAGE*				mCurWildMsgPackage;
	NORMAL_MSG_PACKAGE*				mCurNormMsgPackage;

	typedef std::map<unsigned int, std::set<InterfaceMsgHandle*> > HANDLER_OBJECT_LIST;
	HANDLER_OBJECT_LIST			mCmd2HandlerObjectList;
};



#endif
