#ifndef MESSAGE_UTIL_H
#define MESSAGE_UTIL_H

#include <map>
#include "google/protobuf/message.h"
#include "head.pb.h"
#include "cs_basic.pb.h"
#include "cs_battle.pb.h"

using namespace google::protobuf;

typedef CSMessageHeader MessageHeader;


class MessageUtil
{

public:

	static MessageUtil*				sShareInstance();
	static void Destroy();
		

	//Message creator
	Message*						createMessageInstanceByName(const std::string& typeName);
	Message*						createMessageInstance(const head_msg::CSMsgName& msgType);

	MessageHeader*					createMessageHeader();

	//message encode/decode
	bool							decodeString2Message(Message* msg, const std::string& msgStr);
	bool							decodeBuffer2Message(Message* msg, const char* buffer, const int length);
			

	bool							encodeMessage2Buffer(Message* msg, char*& outBuffer,int& length);
	bool							encodeMessage2String(Message* msg, std::string& str);	

	//Message debug
	void							printMessage(Message* msg);					
	

protected:

	MessageUtil();
	~MessageUtil();		

private:

	static MessageUtil*				sInstance;	

};


#endif