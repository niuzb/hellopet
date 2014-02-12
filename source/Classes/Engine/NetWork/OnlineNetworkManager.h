#ifndef ONLINE_NETWORK_MANAGER_H
#define ONLINE_NETWORK_MANAGER_H

#include "NetWorkUtil.h"

class OnlineNetworkManager : public NetWorkUtil
{
public:
	static OnlineNetworkManager*	sShareInstance();
	static void Destroy();

	void	setServerIP(const uint32_t serverIP);
	void	setServerIP(const char *serverIP);
	void	setServerPort(const uint32_t serverPort);

	void	LostConnection2Server(const char * msg = "");
public:
	/**
	* Instruction : start socket connect to online server
	* @param 
	*/	
	void	startConnect();
protected:
	OnlineNetworkManager();
	~OnlineNetworkManager();	
public:
#ifdef WIN32
	static const int PKG_TIMEOUT = 30;
#else
	static const int PKG_TIMEOUT = 10; 
#endif
private:
	static OnlineNetworkManager* sInstance;

	std::string m_serverIP;
	uint32_t m_serverPort;
};



#endif
