#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include <SimpleAudioEngine.h>
#include "Lua_extensions_CCB.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//#include "Lua_web_socket.h"
#endif

#include "GameResourceManager.h"
//#include "Client/Layers/Game/MainScene.h"
//#include "Client/BoneAniManager/SkeletonAnimRcsManager.h"
#include "Client/GameManager/XLogicManager.h"

#include <vector>
#include <string>
#include "AppMacros.h"

using namespace std;
using namespace CocosDenshion;
USING_NS_CC;

#define ENABLE_LUA_ENGINE

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	pDirector->setOpenGLView(pEGLView);

//	CCSize frameSize = pEGLView->getFrameSize();

//	// Set the design resolution
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
//	pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
//#else
//	pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
//#endif
//
	vector<string> searchPath;
//
//	// In this demo, we select resource according to the frame's height.
//	// If the resource size is different from design resolution size, you need to set contentScaleFactor.
//	// We use the ratio of resource's height to the height of design resolution,
//	// this can make sure that the resource's height could fit for the height of design resolution.
//
//	// if the frame's height is larger than the height of medium resource size, select large resource.
//	if (frameSize.height > mediumResource.size.height)
//	{
//		searchPath.push_back(largeResource.directory);
//
//		pDirector->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
//	}
//	// if the frame's height is larger than the height of small resource size, select medium resource.
//	else if (frameSize.height > smallResource.size.height)
//	{
//		searchPath.push_back(mediumResource.directory);
//
//		pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
//	}
//	// if the frame's height is smaller than the height of medium resource size, select small resource.
//	else
//	{
//		searchPath.push_back(smallResource.directory);
//
//		pDirector->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
//	}
//
//
	// set searching path
	searchPath.push_back("BattleScene01/Resources");	
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
    CCSize designSize = CCSizeMake(960, 640);

    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
//    CCEGLView *pView=pDirector->getOpenGLView();
//    pView->setDesignResolutionSize(480,320,kResolutionNoBorder);
//    CCDirector::sharedDirector()->setContentScaleFactor(2.0);
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	InitGameConfig();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	// set resource folder
	std::string exeWin32Path = CCFileUtils::sharedFileUtils()->getWritablePath();
	exeWin32Path = exeWin32Path + "..\\..\\Resources";
	this->setResourceRootPath(exeWin32Path);
#endif

	//SkeletonAnimRcsManager::Get()->LoadAllAnimConnectionData();
	//std::string _path = GameResourceManager::sharedManager()->storedFullPathFromRelativePath("Data");
	//CCScene* pScene = CCScene::create();
	//MainScene* pLayer = MainScene::create();
	//pScene->addChild(pLayer);
	//pLayer->Run();
	//pLayer->TestParticle();
	//CCDirector::sharedDirector()->runWithScene(pScene);
	
	XLogicManager::sharedManager()->startGame();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	XLogicManager::sharedManager()->DidEnterBackground();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	XLogicManager::sharedManager()->WillEnterForeground();
}

void AppDelegate::InitGameConfig()
{
	initLuaEngine();
}

void AppDelegate::initLuaEngine()
{
#ifdef ENABLE_LUA_ENGINE
		// register lua engine
		CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
		CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
		// Note: init lua search path
		string path = GameResourceManager::sharedManager()->storedFullPathFromRelativePath("Script/main.lua");
		string scriptPath = path.substr(0, path.find_last_of("S"));
		pEngine->addSearchPath(scriptPath.c_str());

		CCLuaStack *pStack = pEngine->getLuaStack();
		lua_State *tolua_s = pStack->getLuaState();
		tolua_extensions_ccb_open(tolua_s);
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		pStack = pEngine->getLuaStack();
		tolua_s = pStack->getLuaState();
		//tolua_web_socket_open(tolua_s);
	#endif
#endif
}