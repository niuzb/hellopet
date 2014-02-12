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
#include "NetWorkUtil.h"
#include "proto_encry.h"
#include "MessageHandler.h"
#include "MessageCache.h"
#include "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "MessageLog.h"
#endif

//#include "LuaTinkerManager.h"
#include "head.pb.h"

NetWorkUtil::NetWorkUtil()
	:m_canSend(false)
	,m_bRecvQueueLen(0)
	, m_curReconnectCount(0)
	, m_maxReconnectCount(3)
{
	
	memset(&m_bSocketInfo, 0, sizeof(SocketInfo_t));
	memset(&m_bRecvQueue, 0, KRecvQueueLen);	
	resetTimeOut();

	m_pMessageCache = new MessageCache();

#ifdef USE_BOOST_ASIO
	m_bSocket.SetDelegate(this);

	m_curWritingMsgInfo.header = NULL;
	m_curWritingMsgInfo.body = NULL;
	m_curWritingMsgInfo.tag = 0;
	m_curWritingMsgInfo.timeOut = 0.0f;
#endif

	//NotificationCenter::defaultCenter()->registerMsgObserver(this, GM_APPLICATION_ENTER_BACKGROUND);
}


NetWorkUtil::~NetWorkUtil()
{
	delete m_pMessageCache;

	MessageHandler::Destroy();
	MessageUtil::Destroy();
#ifdef _DEBUG_LOG
	MessageLog::Destroy();
#endif
	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();

	//NotificationCenter::defaultCenter()->unregisterAllMsgObserver(this);
}

//Э�������غ���
int cur_seqno = 0;

inline uint32_t calc_seqno(uint32_t pkglen, uint32_t seqno, uint8_t crc8_val)
{
    return seqno - seqno / 7 + 147 + pkglen % 21 + crc8_val; 
}

inline uint8_t calc_crc8(uint8_t* body, uint32_t body_len)
{
    uint8_t crc8_val = 0;
    for (uint32_t i = 0; i < body_len; i++) {
//      KDEBUG_LOG(0,"body %d",body[i]);
		//CCLOG("body %d",body[i]);
        crc8_val ^= (body[i] & 0xff);
    }
    return crc8_val;
}


//------------------------------------------------------------------------
void NetWorkUtil::connect2Server(const char *ip,const int port,float timeout,int tag)
{	
	if(m_pMessageCache)
    {
        m_pMessageCache->clearCacheMessages();
    }

    connect(ip, port, timeout, tag);
}

void NetWorkUtil::connect(const char *ip,const int port,float timeout,int tag)
{
	//
	memset(&m_bRecvQueue, 0, KRecvQueueLen);
    
	//
	m_bScoketStatus = KSocketDisconnect;
	strcpy(m_bSocketInfo.ip, ip);
	m_bSocketInfo.port = port;
	m_bSocketInfo.timeOut = timeout;
    
	//
	m_timeOut.tag        = tag;
	m_timeOut.cmd        = "connect2Server";
	m_timeOut.timeout    = timeout;
	
#ifdef USE_BOOST_ASIO
    
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(NetWorkUtil::update), this);
    
	m_bSocket.Close();
	m_bSocket.Create();
	
	// �첽������ �ڻص� DidConnected �ﴦ�����ӵĽ��
	m_bSocket.ConnectTo((char*)ip, port, timeout);
   
#else
	if(m_bSocket.getSocketID() != -1)
	{
		m_bSocket.CancelSocket();
	}
	m_bSocket.CreateSocket();
	
    
	int ret = m_bSocket.ConnectTo((char*)ip, port);
	//connect error
	if (ret == -1)
	{
		onConnectResult(KSocketDisconnect, 0);
	}
    m_bSocket.SetBlockMode(1);


	//
	m_canSend = false;
    
#endif
    
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(NetWorkUtil::update),
                                                                   this,
                                                                   0.01f,
                                                                   false);
}

//------------------------------------------------------------------------
void NetWorkUtil::reconnect2Server()
{
	if (strlen(m_bSocketInfo.ip) > 0 && m_bSocketInfo.port != 0) 
	{
		m_curReconnectCount++;
		if(m_curReconnectCount < m_maxReconnectCount)
		{
			connect(m_bSocketInfo.ip, m_bSocketInfo.port, m_bSocketInfo.timeOut, 0);

		}
		else
		{
			m_curReconnectCount = 0;
			onDisconnect();
		}
	}
}


//------------------------------------------------------------------------
void NetWorkUtil::cleanServerConnect(bool needReconnect)
{
	CCLOG("disconnect, clean data");
	//
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(NetWorkUtil::update), this);

	//
	m_canSend = false;

	//
	m_bRecvQueueLen = 0;
	memset(m_bRecvQueue, 0, KRecvQueueLen);	

	//
	m_bScoketStatus = KSocketDisconnect;

#ifdef USE_BOOST_ASIO

	m_bSocket.Close();
#else
	m_bSocket.CancelSocket();
#endif

	this->resetTimeOut();
	if (m_pMessageCache)
	{
		m_pMessageCache->clearCacheMessages();
	}
}

//------------------------------------------------------------------------
bool NetWorkUtil::encodeMessage(MessageHeader* headerMsg, Message* bodyMsg, byte_array_t& outBuffer)
{
	if (headerMsg == NULL || bodyMsg == NULL)	
		return false;


	//write len(u32)
	uint32_t len = 4 + 4 + headerMsg->ByteSize() + bodyMsg->ByteSize();
	outBuffer.write_uint32(htonl(len));
	
	//write hlen(u32)
	uint32_t hlen = headerMsg->ByteSize() + 4;
	outBuffer.write_int32(htonl(hlen));

	//write header buffer
	char* headerBuffer = NULL;
	int headerLen = 0;
	bool result = MessageUtil::sShareInstance()->encodeMessage2Buffer(headerMsg, headerBuffer, headerLen);
	if (result)
	{
		outBuffer.write_buf(headerBuffer, headerLen);
		delete headerBuffer;
	}
	else
	{
		CCError("encode header message to buffer error");
		MessageUtil::sShareInstance()->printMessage(headerMsg);

		delete headerBuffer;

		return false;
	}

	//write body buffer
	char* bodyBuffer = NULL;
	int bodyLen = 0;
	result = MessageUtil::sShareInstance()->encodeMessage2Buffer(bodyMsg, bodyBuffer, bodyLen);
	if (result)
	{
		outBuffer.write_buf(bodyBuffer, bodyLen);
		delete bodyBuffer;
	}
	else
	{
		CCError("encode body message to buffer error");
		MessageUtil::sShareInstance()->printMessage(bodyMsg);

		delete bodyBuffer;

		return false;
	}

	//write check sum
	//cur not used
	//outBuffer.write_uint32(htonl(0));

	return true;
}

//------------------------------------------------------------------------
bool NetWorkUtil::encodeCRCMessage(MessageHeader* headerMsg, Message* bodyMsg, byte_array_t& outBuffer)
{
	if (headerMsg == NULL || bodyMsg == NULL)	
		return false;


	//write len(u32)
	uint32_t len = 4 + 4 + 4 + headerMsg->ByteSize() + bodyMsg->ByteSize();
	outBuffer.write_uint32(htonl(len));
	//CCLOG("---------- pkg len : %d ------",len);
	
	//write hlen(u32)
	uint32_t hlen = headerMsg->ByteSize() + 4 + 4;
	outBuffer.write_int32(htonl(hlen));
	//CCLOG("---------- head len : %d ------",hlen);



	//write header buffer
	char* headerBuffer = NULL;
	int headerLen = 0;
	bool resultHeader = MessageUtil::sShareInstance()->encodeMessage2Buffer(headerMsg, headerBuffer, headerLen);

	//write body buffer
	char* bodyBuffer = NULL;
	int bodyLen = 0;
	bool resultBody = MessageUtil::sShareInstance()->encodeMessage2Buffer(bodyMsg, bodyBuffer, bodyLen);

	//���������crc
	char  * totalBuff = new char[headerLen + bodyLen];
	memcpy(totalBuff, headerBuffer, headerLen);
	memcpy(totalBuff + headerLen, bodyBuffer, bodyLen);

	uint32_t crcTotalNum = calc_crc8((uint8_t *)totalBuff, headerLen + bodyLen);
	delete totalBuff;

	cur_seqno = calc_seqno(len, cur_seqno, crcTotalNum);
	outBuffer.write_int32(htonl(cur_seqno));

	if (resultHeader)
	{
		outBuffer.write_buf(headerBuffer, headerLen);
		delete headerBuffer;
	}
	else
	{
		CCError("encode header message to buffer error");
		MessageUtil::sShareInstance()->printMessage(headerMsg);

		delete headerBuffer;

		return false;
	}


	if (resultBody)
	{
		outBuffer.write_buf(bodyBuffer, bodyLen);
		delete bodyBuffer;
	}
	else
	{
		CCError("encode body message to buffer error");
		MessageUtil::sShareInstance()->printMessage(bodyMsg);

		delete bodyBuffer;

		return false;
	}

	return true;
}


//------------------------------------------------------------------------
bool NetWorkUtil::decodeMessage(char* inputBuffer, int bufferLen, char*& headerBuffer, int& headerLen,char*& bodyBuffer,
								int& bodyLen, 
								int& totalLen)
{
	//package length
	uint32_t* currPackageLen = (uint32_t*)inputBuffer;
	totalLen = ntohl(*currPackageLen);
	inputBuffer += 4;

	//invalid message package
	if (totalLen > bufferLen || totalLen < 12)
	{
		CCError("invalid message package length : %d", totalLen);				
		return false;
	}

	//head length
	uint32_t* currHeadLen = (uint32_t*)inputBuffer;
	headerLen = ntohl(*currHeadLen) - 4;
	inputBuffer += 4;

	//invalid message header
	if (headerLen > totalLen || headerLen < 0)
	{
		CCError("invalid message header length : %d", headerLen);	
		return false;
	}

	//head buffer
	headerBuffer = (char*)inputBuffer;	
	inputBuffer += headerLen;

	//body buffer
	bodyBuffer = (char*)inputBuffer;
	bodyLen = totalLen - 4 - 4 - headerLen;
	inputBuffer += bodyLen;

	//invalid message body
	if (bodyLen < 0)
	{
		CCError("invalid message body length : %d", bodyLen);	
		return false;
	}	

	//check sum	
	//uint32_t* checkSum = (uint32_t*)inputBuffer;
	//inputBuffer += 4;
	//check sum valid
	if (false)
	{
		CCError("check sum failure, drop the package");	
		return false;
	}

	return true;
}



//------------------------------------------------------------------------
MessageHeader* NetWorkUtil::encodeMessageHeader(unsigned int userid, int userRoleTm)
{
	MessageHeader* msgHeader = MessageUtil::sShareInstance()->createMessageHeader();
	CCAssert(msgHeader != NULL, "create message header fail");

	// TODO: check this
	
	msgHeader->set_msg_id(static_cast<head_msg::CSMsgName>(0));
	//msgHeader->set_uid(userid);
	//msgHeader->set_ret(0);
	//msgHeader->set_seq(0);

	return msgHeader;
}

KSendMessageResult NetWorkUtil::HandleLocalMessage(MessageHeader* headerMsg, Message* bodyMsg, float timeout, int tag)
{
	CCAssert(headerMsg != NULL, "message header is null");
	CCAssert(bodyMsg != NULL, "message header is null");
	string SMsgName  ;

	//���ط��������ȹ��ˣ�����PVE�ı�����Ϣ����
	CCLog("filter message : %s", bodyMsg->GetTypeName().c_str());
	string typeName = bodyMsg->GetTypeName();

	MessageHeader * filterHeader = MessageUtil::sShareInstance()->createMessageHeader();
	filterHeader->CopyFrom(*headerMsg);

	Message* filterMsg = MessageUtil::sShareInstance()->createMessageInstanceByName(bodyMsg->GetTypeName().c_str());
	filterMsg->CopyFrom(*bodyMsg);

	return KResultSuccess;
}

//------------------------------------------------------------------------
KSendMessageResult NetWorkUtil::sendMessage(MessageHeader* headerMsg, Message* bodyMsg, float timeout, int tag)
{

	CCAssert(headerMsg != NULL, "message header is null");
	CCAssert(bodyMsg != NULL, "message header is null");
    string SMsgName  ;

    //record the msg info into message.log
	//only enabled in win32 platform. jackniu
//#ifdef _DEBUG_LOG
//		string dd= bodyMsg->GetTypeName();
//        if(dd.compare("CSPingReq") != 0) 
//        {
//    		MessageLog::Get()->Write("%s %-40s\n%s", "In", bodyMsg->GetTypeName().c_str(),
//    		bodyMsg->Utf8DebugString().c_str());
//        }
//#endif
   // CCLog("sendMessage : %s", bodyMsg->GetTypeName().c_str());
    
	//���ط��������ȹ��ˣ�����PVE�ı�����Ϣ����
//	bool needFilter = MessageFilter::Get()->checkFilterMsg(bodyMsg);
//	if (needFilter)
//	{
//		CCLog("filter message : %s", bodyMsg->GetTypeName().c_str());
//		string typeName = bodyMsg->GetTypeName();
//
//		bool isBothSend = MessageFilter::Get()->checkBothSendMsg(typeName);
//		if (!isBothSend)
//		{
//#ifdef USE_BOOST_ASIO
//			if(m_pMessageCache)
//			{
//				CacheMessageInfo info;
//				info.header = headerMsg;
//				info.body = bodyMsg;
//				info.timeOut = timeout;
//				info.tag = tag;
//
//				m_pMessageCache->removeMessage(info, true);
//			}
//#endif
//			return KResultSuccess;
//		}
//	}

	//������δ��ʼ��
	if (!m_canSend) 
	{
		return KResultCannotSendNow;
	}

#ifdef USE_BOOST_ASIO
#else
	//����Ƿ����ӳɹ�
	int ret = m_bSocket.CanWrite(5000);	
	if (ret != 0)
	{     
		//�����socket����Ϊû������
		//cleanServerConnect(true);

		onConnectResult(KSocketDisconnect, 0);
		return KResultSocketError;
	}
#endif

	static byte_array_t ba;
	ba.init_postion();
	head_msg::CSMsgName EMsgName ;
	 SMsgName = bodyMsg->GetTypeName() ;
	head_msg::CSMsgName_Parse(SMsgName ,&EMsgName);
	headerMsg->set_msg_id(EMsgName);

	//if (encodeCRCMessage(headerMsg, bodyMsg, ba) == false)
	if (encodeMessage(headerMsg, bodyMsg, ba) == false)
	{		
#ifdef USE_BOOST_ASIO
		if(m_pMessageCache)
		{
			CacheMessageInfo info;
			info.header = headerMsg;
			info.body = bodyMsg;
			info.timeOut = timeout;
			info.tag = tag;

			m_pMessageCache->removeMessage(info, true);
		}
#endif
		return KResultEncodeBufferError;
	}


    
    CCLOG("Send Message : %s", bodyMsg->GetTypeName().c_str());
    
	//����
	uint32_t totalSize = ba.get_postion();  
#ifdef USE_BOOST_ASIO
	// TODO : �������첽�Ĳ�����ʽ�����԰���һ������ʱ���͵ģ�����Ѱ�����������
	// �첽������������ص�ʱ��û����ķ��ͳɹ����ڻص�DidWrite���ж��Ƿ�ɹ�
	if(m_bSocket.CanWrite())
	{
		m_curWritingMsgInfo.header = headerMsg;
		m_curWritingMsgInfo.body = bodyMsg;
		m_curWritingMsgInfo.timeOut = timeout;
		m_curWritingMsgInfo.tag = tag;
		m_bSocket.Write((char*)ba.get_buf(), totalSize, timeout);
	}
#else

	ret = send(m_bSocket.getSocketID(), ba.get_buf(),totalSize, 0);

	//CCLOG("END SEND...");
	if (ret == -1 || ret == 0)
	{
		cocos2d::CCError("send message to server error");
		//cleanServerConnect(true);

		onConnectResult(KSocketDisconnect, 0);
		
		return KResultSocketError;
	}

#endif

	
	m_timeOut.tag        = tag;
	m_timeOut.cmd        =SMsgName;
	m_timeOut.timeout    = timeout;

#ifdef USE_BOOST_ASIO
	return KResultWaiting;
#else
	return KResultSuccess;
#endif
}


//------------------------------------------------------------------------
KSendMessageResult NetWorkUtil::sendMessage(MessageHeader* headerMsg, Message* bodyMsg, float timeout, int tag, 
											bool isFailedCache,
											bool cleanUp)
{
	

#ifdef USE_BOOST_ASIO
	if (m_pMessageCache != NULL)
	{
		bool needFilter = MessageFilter::Get()->checkFilterMsg(bodyMsg);
		if (needFilter)
		{
    		#ifdef _DEBUG_LOG
    		string dd= bodyMsg->GetTypeName();
            if(dd.compare("CSPingReq") != 0) 
            {
        		MessageLog::Get()->Write("%s %-40s\n%s", "In local", bodyMsg->GetTypeName().c_str(),
        		bodyMsg->Utf8DebugString().c_str());
            }
            #endif

			HandleLocalMessage(headerMsg,bodyMsg,timeout,tag);

			string typeName = bodyMsg->GetTypeName();
			bool isBothSend = MessageFilter::Get()->checkBothSendMsg(typeName);
			if (isBothSend)
			{
				// ������Ϣ�ķ��Ͷ����첽�ģ���������֪�����
				m_pMessageCache->addMessage(headerMsg, bodyMsg, timeout, tag);
				return KResultWaiting;
			}			
			return KResultSuccess;
		}
		else
		{
			// ������Ϣ�ķ��Ͷ����첽�ģ���������֪�����
			m_pMessageCache->addMessage(headerMsg, bodyMsg, timeout, tag);
			return KResultWaiting;
		}
	}

	return KResultCannotSendNow ;
#else

	KSendMessageResult result = sendMessage(headerMsg, bodyMsg, timeout, tag);
	if (result != KResultSuccess && isFailedCache && cleanUp)
	{
		m_pMessageCache->addMessage(headerMsg, bodyMsg, timeout, tag);
	}
	else if(cleanUp)
	{
		//
		delete headerMsg;
		delete bodyMsg;
	}


	return result;
#endif
}



//------------------------------------------------------------------------
KSendMessageResult NetWorkUtil::sendMessage(Message* bodyMsg,float timeout, int tag, bool isFailedCache, bool cleanUp)
{
	//MessageHeader* headerMsg = NULL;	//encodeMessageHeader(UserData::getUserId().getID(), UserData::getUserId().getRegTime());
	MessageHeader* headerMsg = encodeMessageHeader(0, 0);
	return sendMessage(headerMsg, bodyMsg, timeout, tag, isFailedCache, cleanUp);
}
KSendMessageResult	NetWorkUtil::sendMessage(Message* bodyMsg)
{
	MessageHeader* headerMsg = encodeMessageHeader(0, 0);
	return sendMessage(headerMsg, bodyMsg, 30, 1, true, true);
}
//-----------------------------------------
//used by lua sending msg
bool NetWorkUtil::sendMessage(
		char *msgName,
		void *bodyBuff,
		int bodylen,
        bool isFailedCache)
{
    Message* msg = NULL;
    msg = MessageUtil::sShareInstance()->createMessageInstanceByName(msgName);
    bool result = MessageUtil::sShareInstance()->decodeBuffer2Message(msg, (const char *)bodyBuff, bodylen);
	if (result == false)
	{
		CCError("sendMessage decode message buffer error");
        return false;
    }
    
    KSendMessageResult ret = sendMessage(msg, 10, LUA_MSG, isFailedCache, true);
    if(ret == KResultSuccess)
        return true;
    else 
        return false;
}

//�հ�����
void NetWorkUtil::dispatchMessage(char *headBuff,int headlen, char *bodyBuff,int bodylen,int tag)
{
    bool success=false;
    
	MessageHeader* msgHeader = MessageUtil::sShareInstance()->createMessageHeader();
	CCAssert(msgHeader != NULL, "create message header fail");
	MessageUtil::sShareInstance()->decodeBuffer2Message(msgHeader, headBuff, headlen);		
	//std::string cmd = CSMsgName_Name(msgHeader->msg_id());
	unsigned int cmd = msgHeader->msg_id();

	uint32_t ret = msgHeader->errcode();
	delete msgHeader;

	Message* msg = NULL;


	if(ret != 0)
	{
	    //error code handling
		NORMAL_MSG_PACKAGE package;
		package.msg = msg;
		package.header.cmd = cmd;
		//package.header.uid = uid;
		package.header.ret = ret;
		package.header.tag = tag;	
		MessageHandler::sShareInstance()->handleMessage(&package);
		return;
	}
	
	
    //check if we processed it by lua
    
	/*   processedbylua = LuaTinkerManager::Get()->callLuaFunc<bool>(
	"Script/handleMessage.lua",
	"processedByLua",
	cmd.c_str());*/
  //  if(processedbylua)
  //  {
		////lua handle message
		//WILD_MSG_PACKAGE package;
		//package.buffer = bodyBuff;
		//package.length = bodylen;
		//package.header.cmd = cmd;
		////package.header.uid = uid;
		//package.header.ret = ret;
		//package.header.tag = tag;	
		//success = MessageHandler::sShareInstance()->handleMessage(&package);
  //  }
    
    if(!success)
    {
        //message didn't processed by lua. we should move on the msg to 
        // c++ to go on process jackniu
        msg = MessageUtil::sShareInstance()->createMessageInstance((head_msg::CSMsgName)cmd);
    }
		
	
    // message handling
	if (msg)
	{
		//decode buffer to message
		bool result = MessageUtil::sShareInstance()->decodeBuffer2Message(msg, bodyBuff, bodylen);
		if (result == false)
		{
			//fix me there is no err handling jackniu 
			CCError("decode message buffer error");
		}
		
		//record the msg info into message.log
		//only enabled in win32 platform. jackniu
#ifdef _DEBUG_LOG
        string dd = msg->GetTypeName();
        if(dd.compare("CSPingRsp") != 0) {
    		/*MessageLog::Get()->Write("%s %-40s \n%s", "Out", msg->GetTypeName().c_str(),
    		msg->Utf8DebugString().c_str());*/
        }
#endif
		//handle message
		NORMAL_MSG_PACKAGE package;
		package.msg = msg;
		package.header.cmd = cmd;
		//package.header.uid = uid;
		//package.header.ret = ret;
		package.header.tag = tag;	
		MessageHandler::sShareInstance()->handleMessage(&package);

		//free msg
		delete msg;
	}
}


//------------------------------------------------------------------------

void NetWorkUtil::update(float dt)
{
	Timeout_t *timeout = &m_timeOut;

#ifdef USE_BOOST_ASIO

    m_bSocket.Update();

	// TODO : ��ʱ����
	if(m_bSocket.CanRead())
	{
		CCAssert(m_bRecvQueueLen >= 0, "m_bRecvQueueLen Must >= 0");
		if(m_bRecvQueueLen >= 0)
		{
			// �첽������������ص�ʱ��û����ı�ʾ�յ����ݣ��ڻص�DidRead���ж��Ƿ�ɹ�
			m_bSocket.Read(m_bRecvQueue + m_bRecvQueueLen, KRecvQueueLen - m_bRecvQueueLen, timeout->timeout);
		}
		
	}

	if(m_bSocket.CanWrite())
	{
		m_pMessageCache->update(dt);
	}


    
	
#else // USE_BOOST_ASIO
	if (m_bScoketStatus == KSocketDisconnect)
	{
		int ret = m_bSocket.CanWrite(5000);
		//success
		if(ret == 0)
		{
			CCLOG("connect to server");

			m_bScoketStatus = KSocketConnecting;
			m_canSend = true;

			onConnectResult(KSocketConnecting, timeout->tag);
		}
		else if (timeout->timeout > 0.001)
		{
			timeout->timeout -= dt;
			if (timeout->timeout < 0)
			{				
				CCError("connect time out");
				std::string cmd = timeout->cmd;
				int tag = timeout->tag;
                //onTimeOut(cmd,tag);
				resetTimeOut();
                
                /// send package timeout, so the connection is down, can't send package now!
                /// wait for reconnect!
				m_canSend = false;

				//ShowMessage("NetWorkUtil : connect timeout");
				onConnectResult(KSocketTimeout,tag);
			}
		}
	}

	int len = 0;
	if (m_bScoketStatus == KSocketConnecting)
	{
		if (m_bSocket.DataArrival(5000) == 1) 
		{			
			do
			{
				m_bRecvQueueLen += len;
#ifdef USE_BOOST_ASIO
				len = m_bSocket.Read(m_bRecvQueue + m_bRecvQueueLen, KRecvQueueLen, timeout->timeout);
#else
				len = recv(m_bSocket.getSocketID(), m_bRecvQueue + m_bRecvQueueLen , KRecvQueueLen - m_bRecvQueueLen, 0);

	/*			if ( len > 0 )
					printf("Bytes received: %d\n", iResult);
				else if ( len == 0 )
					printf("Connection closed\n");
				else
					printf("recv failed: %d\n", WSAGetLastError());*/


#endif

			} while (len != -1 && len != 0);
			
			//data read over
			if (len == -1)
			{
				filter();

				m_canSend = true;
			}
			//disconnect
			else if(len == 0)
			{
				
				CCError("disconnect to server");

				int tag = timeout->tag;
				cleanServerConnect(false);

				m_bScoketStatus = KSocketDisconnect;

				//ShowMessage("NetWorkUtil : disconnect len = 0");
				onConnectResult(KSocketTimeout, tag);
			}
		}

		// ���գ����ͣ����Խ���ƶ����Ѽ�������
		m_pMessageCache->update(dt);
	}
	
#endif
}


//------------------------------------------------------------------------
//data format is "len(u32) + hlen(u32) + msghead + msgbody + checksum"
//len(u32) is the length from len(32) to checksum
//hen(u32) is the length from hen(32) to msghead
//------------------------------------------------------------------------
void NetWorkUtil::filter()
{
	while (m_bRecvQueueLen > 0)
	{		
		char* headerBuffer = NULL;
		char* bodyBuffer= NULL;
		int headerLen = 0;
		int bodyLen = 0;
		int totalLen = 0;

		bool result = decodeMessage((char*)m_bRecvQueue, m_bRecvQueueLen, headerBuffer, headerLen, bodyBuffer, bodyLen, totalLen);
		if (result)
		{			
			int tag = m_timeOut.tag;
			resetTimeOut();

			dispatchMessage(headerBuffer, headerLen, bodyBuffer, bodyLen, tag);

			memset(m_bRecvQueue, 0, totalLen);
			m_bRecvQueueLen  -= totalLen;

			//CCAssert(m_bRecvQueueLen >= 0, "m_bRecvQueueLen Must > 0");

			if(m_bRecvQueueLen < 0)
			{
				m_bRecvQueueLen = 0;
			}

			if (m_bRecvQueueLen > 0)
				memmove(m_bRecvQueue, m_bRecvQueue + totalLen, m_bRecvQueueLen);						

		}
		else
		{
			CCLOG("in-complete package received! continue to receive the data!");
			return;
		}
	}	
}

//------------------------------------------------------------------------
void NetWorkUtil::onConnectResult(KSocketStatus status, int tag)
{
	CCLOG("NetWorkUtil::onConnectResult(%d)", status);
	//if (KSocketDisconnect == status || KSocketConnecting == status)
	//{
	//	HideWaitingLayer();
	//}
    
	m_bScoketStatus = status;

    switch(status)
    {
        case KSocketCancel:
        case KSocketTimeout:
			{
				//ShowMessage("NetWorkUtil : connect timeout");
				resetTimeOut();
            
				/// socket error!
				m_bScoketStatus = KSocketNone;
            
				onDisconnect();
            
			}
			break;
        case KSocketDisconnect:
			{
				onDisconnect();
			}
			break;
		case KSocketConnecting:
			{
				// TODO : result ?
				FireEvent(&ISocketEvent::OnConnected, 1);
			}
			break;
        default:
            break;
    }
}



void NetWorkUtil::onDisconnect( void )
{
    CCLOG("NetWorkUtil::onDisconnect()");
	if(m_pMessageCache)
	{
		m_pMessageCache->clearCacheMessages();
	}

	FireEvent(&ISocketEvent::OnDisconnect);
    
    cleanServerConnect(false);

	//���к�����
	cur_seqno = 0;
}

//------------------------------------------------------------------------
void NetWorkUtil::resetTimeOut()
{
	m_timeOut.timeout = 0;
	m_timeOut.tag = 0;
	m_timeOut.cmd = "Dummy";
}

#ifdef USE_BOOST_ASIO
void NetWorkUtil::DidReadCompleted( unsigned int uBytes, CSocketUtilDelegate::ERROR_CODE error )
{
	if(error == CSocketUtilDelegate::E_ERROR)
	{
		onConnectResult(KSocketDisconnect, 0);
	}
	else
	{
		// �ӷ������յ��ر��Ļص���
		// TODO : ���ʱ�򣬲���ȷ���յ���uBytes��һ�������İ�������ֻ�ǰ������Ҳ�����Ǻü�������Ҫ������ͷ
		m_bRecvQueueLen += uBytes;

		CCAssert(m_bRecvQueueLen < sizeof(m_bRecvQueue), "m_bRecvQueueLen must < 1024 * 1024 * 2");

		//CCLOG("DidReadCompleted : %d", uBytes);
		filter();
		m_canSend = true;
	}


}

void NetWorkUtil::DidWriteCompleted( unsigned int uBytes, CSocketUtilDelegate::ERROR_CODE error )
{
	// �������ݵ������������Ļص���

    //CCLog("DidWriteCompleted : %s", m_curWritingMsgInfo.body->GetTypeName().c_str());
	switch(error)
	{
	case CSocketUtilDelegate::E_ERROR:
		{
            onConnectResult(KSocketDisconnect, 0);
            
		}
		break;
	case CSocketUtilDelegate::E_SUCESS:
		{
            
			if(m_pMessageCache)
			{
				if(!m_pMessageCache->removeMessage(m_curWritingMsgInfo, true))
				{
					if(m_bScoketStatus == KSocketConnecting)
					{
						CCAssert(false, "Send wrong msg !!!");
					}
				}
			}
			
			m_curWritingMsgInfo.header = NULL;
			m_curWritingMsgInfo.body = NULL;
			m_curWritingMsgInfo.timeOut = 0.0f;
			m_curWritingMsgInfo.tag = 0;

		}
		break;
        case CSocketUtilDelegate::E_TIMEOUT:
        {
            // disconnected
            CCLOG("Send Timeout!");
            
            onConnectResult(KSocketDisconnect, 0);
        }
        break;
	default:
		break;
	}

	
	if(m_pMessageCache)
	{
		m_pMessageCache->update(0.0f);
	}

}


void NetWorkUtil::DidConnected( CSocketUtilDelegate::ERROR_CODE error )
{
	switch(error)
	{
        case CSocketUtilDelegate::E_CANCEL:
		{
			onConnectResult(KSocketCancel, 0);
			// TODO : ����
            
		}
        break;
	case CSocketUtilDelegate::E_ERROR:
		{
			onConnectResult(KSocketDisconnect, 0);
			// TODO : ����

		}
		break;
	case CSocketUtilDelegate::E_SUCESS:
		{
			onConnectResult(KSocketConnecting, 0);
			m_canSend = true;
		}
		break;
	case CSocketUtilDelegate::E_TIMEOUT:
		{
			onConnectResult(KSocketTimeout, 0);	
			// TODO : ����
		}
		break;
	default:
        {
            onConnectResult(KSocketDisconnect, 0);
        }
		break;
	}
}

void NetWorkUtil::onBroadcastMessage( TXGUI::BroadcastMessage* msg )
{
	if(msg)
	{
		switch(msg->message)
		{
		case GM_APPLICATION_ENTER_BACKGROUND:
			m_bSocket.CancelAllTimer();
			break;
		default:
			break;
		}
	}
}


#endif
