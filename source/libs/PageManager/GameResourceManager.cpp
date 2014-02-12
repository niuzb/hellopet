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

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <errno.h>
#include "CCCommon.h"
#include "CCFileUtils.h"
#include "GameResourceManager.h"
#include "ResourceCache.h"
#include "ResourcePlistArray.h"
#include "ResourcePlistDictionary.h"
#include "AES.h"
#include "CCFileData.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <direct.h>
#include <io.h>

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "SystemInfoJni.h"
#include <sys/stat.h>
#include <sys/types.h>

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#endif

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <dirent.h>
#include <sys/stat.h>
#endif


#define MAX_SIZE 1024

#if (!defined ANDROID && !defined PATH_MAX)
#define PATH_MAX 512
#endif

#define BUFFER_SIZE    8192
#define MAX_FILENAME   512


using namespace cocos2d;
using namespace std;

GameResourceManager* GameResourceManager::s_pSharedManager = NULL;

GameResourceManager *GameResourceManager::sharedManager()
{
	if(s_pSharedManager == NULL)
	{
		s_pSharedManager = new GameResourceManager();
		s_pSharedManager->init();
	}
    
	return s_pSharedManager;
}

void GameResourceManager::purgeInstance()
{
	if (s_pSharedManager)
	{
		delete s_pSharedManager;
		s_pSharedManager = NULL;
	}
}

GameResourceManager::~GameResourceManager()
{
	
}

const char *GameResourceManager::writablePathFromRelativePath(const char *path)
{
	string writablePath;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//on android check sd card first
	//if(m_bHasSDCard)
	//{
	//	writablePath = m_strSDCardPath;
	//	writablePath.append("/");
	//	writablePath.append(path);
	//}
	//else
	//{
	//	writablePath = CCFileUtils::sharedFileUtils()->getWriteablePath();
	//	writablePath.append(path);
	//}
#else
	writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();	
	writablePath.append(path);
#endif
	CCString *pRet = new CCString();
	pRet->autorelease();
	pRet->m_sString = writablePath;
	return pRet->m_sString.c_str();
}

const char *GameResourceManager::storedFullPathFromRelativePath(const char *additionalPath,const char *path)
{
	return storedFullPathFromRelativePath((std::string(additionalPath)+std::string(path)).c_str());
}

const char *GameResourceManager::storedFullPathFromRelativePath(const char *path)
{
	CCString *pRet = new CCString();
	pRet->autorelease();
    
//	//check writable space first
//	std::string resPath = writablePathFromRelativePath(path);
//	if(access(resPath.c_str(), 0) == 0)
//	{
//		pRet->m_sString = resPath;
//		return pRet->m_sString.c_str();
//	}
//    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	//on android then check /data/data
//	resPath = CCFileUtils::sharedFileUtils()->getWriteablePath();
//	resPath.append(path);
//
//	if(access(resPath.c_str(), 0) == 0)
//	{
//		pRet->m_sString = resPath;
//		return pRet->m_sString.c_str();
//	}
//#endif
	
	//resPath = FileUtilsExpansion::Get()->fullPathFromRelativePath(path);	
	std::string resPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(path);
	CCLog("resPath %s",resPath.c_str());
    
	pRet->m_sString = resPath;
	return pRet->m_sString.c_str();
}

void GameResourceManager::init()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//loadSDCardInfo();
#endif

	m_xmlEncryptKey[0] = 0x2b;
	m_xmlEncryptKey[1] = 0x7e;
	m_xmlEncryptKey[2] = 0x15;
	m_xmlEncryptKey[3] = 0x16; 
	m_xmlEncryptKey[4] = 0x28;
	m_xmlEncryptKey[5] = 0xae;
	m_xmlEncryptKey[6] = 0xd2;
	m_xmlEncryptKey[7] = 0xa6; 
	m_xmlEncryptKey[8] = 0xab;
	m_xmlEncryptKey[9] = 0xf7;
	m_xmlEncryptKey[10] = 0x15;
	m_xmlEncryptKey[11] = 0x88; 
	m_xmlEncryptKey[12] = 0x09;
	m_xmlEncryptKey[13] = 0xcf;
	m_xmlEncryptKey[14] = 0x4f;
	m_xmlEncryptKey[15] = 0x3c;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//void GameResourceManager::loadSDCardInfo()
//{
//	m_bHasSDCard = hasSDCard();
//	m_strSDCardPath = getSDCardPath();
//	CCLog("sd path: %s", m_strSDCardPath.c_str());
//}
#endif

/*
 * Create a direcotry is platform depended.
 */
bool GameResourceManager::createDirectory(const char *path)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    mode_t processMask = umask(0);
    int ret = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
    umask(processMask);
    if (ret != 0 && (errno != EEXIST))
    {
        return false;
    }
    
    return true;
#else
    BOOL ret = CreateDirectoryA(path, NULL);
	if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
	{
		return false;
	}
    return true;
#endif
}

CCArray *GameResourceManager::arrayFromCache(const char *path)
{
	CCArray* ret;

	ResourcePlistArray *cache = 
		(ResourcePlistArray*)ResourceCache::sharedResourceCache()->getResource(path);

	if(cache != NULL)
	{
		ret = cache->getData();
	}
	else
	{
		cache = ResourcePlistArray::resourceWithFile(path);
		ret = cache->getData();
	}

	return ret;
}

CCDictionary *GameResourceManager::dictionaryFromCache(const char *path)
{
	CCDictionary* ret;

	ResourcePlistDictionary *cache = 
		(ResourcePlistDictionary*)ResourceCache::sharedResourceCache()->getResource(path);

	if(cache != NULL)
	{
		ret = cache->getData();
	}
	else
	{
		cache = ResourcePlistDictionary::resourceWithFile(path);
		ret = cache->getData();
	}

	return ret;
}

const char* GameResourceManager::loadXml(const char *fileName,bool isEncrypt)
{    
	CCFileData data(this->storedFullPathFromRelativePath(fileName), "rb");
	size_t size = data.getSize();
	char* out = (char*)malloc(size);
	memcpy(out, data.getBuffer(),size);
	if (isEncrypt) 
	{
		AES aes(m_xmlEncryptKey);  
		aes.InvCipher((void *)out,size);
	} 
	return out;
}