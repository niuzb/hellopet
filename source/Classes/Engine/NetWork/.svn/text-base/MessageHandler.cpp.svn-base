#include "MessageHandler.h"
#include "cocos2d.h"

using namespace cocos2d;

MessageHandler* MessageHandler::sInstance = NULL;

MessageHandler::MessageHandler()
	:mCurWildMsgPackage(NULL)
	,mCurNormMsgPackage(NULL)
{	
	
}

MessageHandler::~MessageHandler()
{
	mCmd2HandlerObjectList.clear();
}

MessageHandler* MessageHandler::sShareInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new MessageHandler();
	}

	return sInstance;
}

void MessageHandler::Destroy()
{
	if (sInstance)
	{
		delete sInstance;
		sInstance = NULL;
	}
}

void MessageHandler::registerMessageHandlerFunction()
{

}

void MessageHandler::handleMessage(NORMAL_MSG_PACKAGE* package)
{
	mCurNormMsgPackage = package;
	unsigned int cmd = mCurNormMsgPackage->header.cmd;
	HANDLER_OBJECT_LIST::iterator itor = mCmd2HandlerObjectList.find(cmd);
	if (itor != mCmd2HandlerObjectList.end())
	{
		std::set<InterfaceMsgHandle*>::iterator pre_iter = (*itor).second.begin();
		for (std::set<InterfaceMsgHandle*>::iterator set_iter = (*itor).second.begin();
			set_iter != (*itor).second.end(); )
		{
			set_iter++;
			(*pre_iter)->HandlerMessage(cmd,mCurNormMsgPackage);
			pre_iter = set_iter;
		}
	}

	postHandleMsg();
}


bool  MessageHandler::handleMessage(WILD_MSG_PACKAGE* package)
{	
	return true;
}

//----------------------------------------------------------------------
//		register all message hander functions here
//----------------------------------------------------------------------
void MessageHandler::registerMessageHandle(unsigned int message_type, InterfaceMsgHandle* pHandler)
{    
	if (pHandler)
	{
		HANDLER_OBJECT_LIST::iterator iter = mCmd2HandlerObjectList.find(message_type);
		if (iter == mCmd2HandlerObjectList.end())
		{
			std::set<InterfaceMsgHandle*> set_obj;
			set_obj.insert(pHandler);
			mCmd2HandlerObjectList.insert(std::pair<unsigned int, std::set<InterfaceMsgHandle*> >(message_type,set_obj));
		}
		else
		{
			(*iter).second.insert(pHandler);
		}
	}
}

void MessageHandler::unRegisterMessageHandle(unsigned int message_type)
{
	HANDLER_OBJECT_LIST::iterator iter = mCmd2HandlerObjectList.find(message_type);
	if (iter != mCmd2HandlerObjectList.end())
	{
		mCmd2HandlerObjectList.erase(iter);
	}
}

void MessageHandler::unRegisterMessageHandle(unsigned int message_type,InterfaceMsgHandle* pHandler)
{
	HANDLER_OBJECT_LIST::iterator iter = mCmd2HandlerObjectList.find(message_type);
	if (iter != mCmd2HandlerObjectList.end())
	{
		std::set<InterfaceMsgHandle*>::iterator set_iter = (*iter).second.find(pHandler);
		if (set_iter != (*iter).second.end())
		{
			(*iter).second.erase(set_iter);
		}
	}
}

void MessageHandler::unRegisterMessageHandle(InterfaceMsgHandle* pHandler)
{
	for (HANDLER_OBJECT_LIST::iterator itor = mCmd2HandlerObjectList.begin();
		 itor != mCmd2HandlerObjectList.end();)
	{
		for (std::set<InterfaceMsgHandle*>::iterator set_iter = (*itor).second.begin();
			set_iter != (*itor).second.end(); )
		{
			if (pHandler == (*set_iter))
			{
				(*itor).second.erase(set_iter++);
			}
			else
			{
				set_iter++;
			}
		}

		size_t count = (*itor).second.size();
		if (count == 0)
		{
			mCmd2HandlerObjectList.erase(itor++);
		}
		else
		{
			itor ++;
		}
	}
}

//----------------------------------------------------------------------
void MessageHandler::postHandleMsg()
{
	mCurNormMsgPackage = NULL;
}
