#include "BaseMsgHandler.h"
#include "MessageHandler.h"

InterfaceMsgHandle::~InterfaceMsgHandle()
{
	MessageHandler::sShareInstance()->unRegisterMessageHandle(this);
}
