#include "OnlineNetworkManager.h"
#include "cs_basic.pb.h"
#include "NetStateChecker.h"

OnlineNetworkManager* OnlineNetworkManager::sInstance = NULL;

//#define NETWORK_OUTSIDE

// Note: change from 5 to 180 for network delay
const float CONNECT_TIMEOUT = 180.0f;

OnlineNetworkManager* OnlineNetworkManager::sShareInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new OnlineNetworkManager();
	}

	return sInstance;
}

void OnlineNetworkManager::Destroy()
{
	if (sInstance )
	{
		delete sInstance;
		sInstance = NULL;
	}
}

OnlineNetworkManager::OnlineNetworkManager()
{
#ifdef NETWORK_OUTSIDE
	//m_serverIP = "54.204.122.0";
	m_serverIP = "54.204.55.22";
	m_serverPort = 7878;
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	m_serverIP = "192.168.0.101";
	m_serverPort = 7878;
#else
	m_serverIP = "10.1.23.210";
	m_serverPort = 7878;
#endif
#endif
}

OnlineNetworkManager::~OnlineNetworkManager()
{
}

void OnlineNetworkManager::LostConnection2Server(const char * msg)
{	
	this->onConnectResult(KSocketTimeout, 0);
}

void OnlineNetworkManager::setServerIP(const uint32_t serverIP)
{
	in_addr tmpInAddr;
	tmpInAddr.s_addr = serverIP;
	m_serverIP = inet_ntoa(tmpInAddr);
}

void OnlineNetworkManager::setServerIP(const char *serverIP)
{
	m_serverIP = serverIP;
}

void OnlineNetworkManager::setServerPort(const uint32_t serverPort)
{
	m_serverPort = serverPort;
}

//------------------------------------------------------------------
//				gameLogic
//------------------------------------------------------------------
void OnlineNetworkManager::startConnect()
{
	CCLOG("server IP: %s", m_serverIP.c_str());
	CCLOG("server port: %u", m_serverPort);
	NetWorkUtil::connect2Server(m_serverIP.c_str(), m_serverPort, CONNECT_TIMEOUT, NETWORK_TAG_CONNECT);	
}