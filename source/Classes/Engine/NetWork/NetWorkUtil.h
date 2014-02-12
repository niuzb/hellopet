// TAOMEE GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Taomee Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 2012-2015 Taomee Game Technologies. 
//      All Rights Reserved.
//
// Taomee Game Technologies, Shanghai, China
// http://www.taomee.com
//
#ifndef NETWORK_UTIL_H
#define NETWORK_UTIL_H


#include "byte_array_t.h"
#include "google/protobuf/message.h"
#include "CSocketUtil.h"
#include "MessageUtil.h"
#include "MessageCache.h"

// this line should be the last when try to include the <winsock2.h>
#include "cocos2d.h"

#include "IEvent.h"
//#include "CCNotificationCenter.h"

using namespace google::protobuf;
using namespace cocos2d;

class MessageCache;

//////////////////////////////////////////////////////////////////////////
typedef struct
{	
	float			timeout;
	int				tag;

	std::string		cmd;

}Timeout_t;

//////////////////////////////////////////////////////////////////////////
typedef  enum
{
    KSocketNone  = -1,
	KSocketDisconnect	= 0	,
	KSocketTimeout		,
	KSocketConnecting	,
    KSocketCancel

}KSocketStatus;

//////////////////////////////////////////////////////////////////////////
typedef enum
{	
	ES_ERR_CONNECT		= 0	,
	ES_ERR_SEND			,
	ES_ERR_RECIVE		,		

}KSocketError;

//////////////////////////////////////////////////////////////////////////

typedef enum
{
	KResultSuccess				= 0,
	KResultSocketError			,
	KResultEncodeBufferError	,
	KResultCannotSendNow		,
	KResultWaiting

}KSendMessageResult;


//------------------------------------------------------------------
//				tags
//------------------------------------------------------------------
enum NetWorkTags
{
	NETWORK_TAG_CONNECT				= 0,
	NETWORK_TAG_LOGIN,
	NETWORK_TAG_ENTER_MAP,
	NETWORK_TAG_PLAYER_WALK,
	NETWORK_TAG_PING,
	NETWORK_TAG_CREATE_BATTLE,
	NETWORK_TAG_JOIN_BATTLE,
	NETWORK_TAG_PVPQUERYROOM,
	NETWORK_TAG_HERO_CREATE,
	NETWORK_TAG_BATTLE_LOAD_COMPLETE,
	LUA_MSG,
};


//////////////////////////////////////////////////////////////////////////
typedef struct
{
	char ip[16];
	int port;
	float timeOut;

}SocketInfo_t;




//////////////////////////////////////////////////////////////////////////
//NetWorkUtil
//////////////////////////////////////////////////////////////////////////
class NetWorkUtil : public CCObject , public EventProducer<ISocketEvent>
#ifdef USE_BOOST_ASIO
	, public CSocketUtilDelegate
	, public TXGUI::ObserverProtocol
#endif

{
	friend class MessageCache;

public:
	
	//------------------------------------------------------------------------
	//					connect / disconnect
	//------------------------------------------------------------------------
	virtual void						connect2Server(const char *ip,const int port,float timeout,int tag);
	
	//------------------------------------------------------------------------
	//			@isFailedCache flag determine whether to cache message
	//			if message send failed
	//			@clean up flag determine whether memory delegate
	//			if cleanup be false, isFailedCache will make no sense
	//------------------------------------------------------------------------
	KSendMessageResult					sendMessage(Message* bodyMsg,
		float timeout, 
		int tag,
		bool isFailedCache,
		bool cleanUp = true);
	//true for sucess , false failed
	bool  sendMessage(
		char *msgName,
		void *bodyBuff,
		int bodylen,
        bool isFailedCache);


	KSendMessageResult					sendMessage(MessageHeader* headerMsg,
		Message* bodyMsg, 
		float timeout,
		int tag,
		bool isFailedCache,
		bool cleanUp = true);	

	KSendMessageResult	sendMessage(Message* bodyMsg);	

	MessageHeader*	encodeMessageHeader(unsigned int userid, int userRoleTm);
	
	
	//------------------------------------------------------------------------
	//					register time out handler
	//------------------------------------------------------------------------
	//void								registerTimeOutEventHandler(CCObject* handler, SEL_CallFuncND callBackfunc);


	//------------------------------------------------------------------------
	//					socket status
	//------------------------------------------------------------------------
	inline  KSocketStatus				getSocketStatus() { return m_bScoketStatus;}


#ifdef USE_BOOST_ASIO
	// 从服务器收到回报的回调。
	virtual void DidReadCompleted(unsigned int uBytes, CSocketUtilDelegate::ERROR_CODE error);
	// 发送数据到服务器结束的回调。
	virtual void DidWriteCompleted(unsigned int uBytes, CSocketUtilDelegate::ERROR_CODE error);

	virtual void DidConnected(CSocketUtilDelegate::ERROR_CODE error);
	void onBroadcastMessage(TXGUI::BroadcastMessage* msg);

#endif

	

protected:

	NetWorkUtil();
	virtual ~NetWorkUtil();

	void								update(float dt);

	//------------------------------------------------------------------------
	//				filter messages
	//------------------------------------------------------------------------
	void								filter();
	
	//------------------------------------------------------------------------
	//				dispatch message
	//------------------------------------------------------------------------
	void								dispatchMessage(char *headBuff,int headlen, char *bodyBuff,int bodylen,int tag);

	//------------------------------------------------------------------------
	//				@headerMsg & bodyMsg is input message content
	//				@headerMsg & bodyMsg must not be null
	//				@outBuffer is for out
	//------------------------------------------------------------------------
	bool								encodeMessage(MessageHeader* headerMsg, Message* bodyMsg, byte_array_t& outBuffer);
	bool								encodeCRCMessage(MessageHeader* headerMsg, Message* bodyMsg, byte_array_t& outBuffer);

	//------------------------------------------------------------------------
	//				@inputBuffer is for in	
	//				@bufferLen is the length of the inputBuffer
	//				@totalLen is the total length for cur message
	//------------------------------------------------------------------------
	bool								decodeMessage(char* inputBuffer, 
		int bufferLen, 
		char*& headerBuffer,
		int& headerLen,
		char*& bodyBuffer, 
		int& bodyLen, 
		int& totalLen);

	//------------------------------------------------------------------------
	//				event interfaces
	//------------------------------------------------------------------------
	//virtual void						onTimeOut(std::string cmd,int tag);
	virtual void						onConnectResult(KSocketStatus status, int tag);

	// 真正的断线
	virtual void						onDisconnect(void);

	void								resetTimeOut();

	virtual void						cleanServerConnect(bool needReconnect);
	virtual void						reconnect2Server(void);
    virtual void						connect(const char *ip,const int port,float timeout,int tag);
    

	KSendMessageResult	sendMessage(MessageHeader* headerMsg, Message* bodyMsg, float timeout, int tag);

	KSendMessageResult	HandleLocalMessage(MessageHeader* headerMsg, Message* bodyMsg, float timeout, int tag);

private:
		
	//
	static const int					KRecvQueueLen = 1024*1024*2;
	int									m_bRecvQueueLen;
	char								m_bRecvQueue[KRecvQueueLen];

	//
	CSocketUtil		m_bSocket;		// 用的是异步的方式。且只能一个一个包的来收和发。
	KSocketStatus	m_bScoketStatus;
	SocketInfo_t	m_bSocketInfo;
	Timeout_t		m_timeOut;


	//
	bool			m_canSend;

	//
	//CCObject*					m_timeOutEventHandler;
	//SEL_CallFuncND				m_timeOutCallBackFun;
	MessageCache* m_pMessageCache;

#ifdef USE_BOOST_ASIO
	CacheMessageInfo m_curWritingMsgInfo;
#endif

	unsigned int m_maxReconnectCount; 
	unsigned int m_curReconnectCount;
};



#endif
