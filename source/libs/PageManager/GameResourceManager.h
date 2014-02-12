/********************************************************************
	created:	2013/09/01
	created:	1:9:2013   8:57
	filename: 	source\libs\PageManager\GameResourceManager.h
	file path:	source\libs\PageManager
	file base:	GameResourceManager
	file ext:	h
	author:		jackran
	
	purpose:	game resources manager;
*********************************************************************/
#pragma once

#include <string>
#include "cocos2d.h"
#include "IExResourceMgr.h"
#include "FileUtilsExpansion.h"
USING_NS_CC;

class GameResourceManager : public IExResourceMgr

{
public:
	static GameResourceManager *sharedManager();
	static void purgeInstance();

	~GameResourceManager();

	/**need relative path!
	*absolute path passed in will give out wrong result!
	*/
	const char *writablePathFromRelativePath(const char *path);
	/**need relative path!
	*absolute path passed in will give out wrong result!
	*/
	const char *storedFullPathFromRelativePath(const char *path);

	/**need relative path! relative path = additionalPath + path
	*absolute path passed in will give out wrong result!
	*/
	const char *storedFullPathFromRelativePath(const char *additionalPath, const char *path);

	/**need absolute path or it'll always fail to read data from cache*/
	CCArray *		arrayFromCache(const char *path);
	/**need absolute path or it'll always fail to read data from cache*/
	CCDictionary *	dictionaryFromCache(const char *path);

	bool createDirectory(const char *path);

	/*
	*@prototype, loadXml()
	*@fileName,
	*@isEncrypt,
	*@note,
	*		注意当调用这个函数后，需要自己对返回的指针进行释放
	*/
	const char* loadXml(const char *fileName,bool isEncrypt = true);
private:
	void init();    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	void loadSDCardInfo();
#endif    
private:
	static GameResourceManager *s_pSharedManager;
	unsigned char m_xmlEncryptKey[16];
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	bool m_bHasSDCard;
	std::string m_strSDCardPath;
#endif
};