//
//  Define.h
//  iSeer
//
//  Created by arthurgong on 11-12-8.
//  Copyright 2011�� __MyCompanyName__. All rights reserved.
//

// this file include all define 


#ifndef _SEER_DEFINE_H_UI
#define _SEER_DEFINE_H_UI


#define kGameAutorotationNone				0
#define kGameAutorotationCCDirector			1
#define kGameAutorotationUIViewController	2

// UI Layer Touch event Priority
enum {
	//* priority used by the menu
	kCCScrollTouchBgPriority			= -129, //Ϊ��ʹ������ڵ�������menu�����Ը���menu,
	kCCScrollMenuPriority				= -130, //��������ϵ�menu
	kCCScrollTouchPriority				= -131,//Ϊ��ʹmenu����scrollview�Ϲ���,scrollview�����ȼ��ø���menu��
	kCCLayerTouchPriority				= -132,//���ϼ���scrollviewʱ,�Ѳ㼶�����ȼ��������
	kCCLayerMenuTouchPriority			= -133,//�����ϻ��а�ťʱ,���ȼ��ñȲ��	
	kCCTipsLayerTouchPriority			= -143,
	kCCTipsMenuTouchPriority			= -144,
	KCCMenuOnMessageBoxPripority		= -145,
	KCCMessageBoxPripority				= -146,
	KCCMessageBoxContorlPripority		= -147,
	KCCLayerTutorialPripority			= -148,
	KCCLayerTutorialControlPripority	= -149,
	KCCMessageBoxPripority_2			= -150,
	KCCMessageBoxContorlPripority_2		= -151,
	KCCWaitingLayerPripority			= -152,
};

enum EUiZOrder{
	Z_Order_Normal	= 0,
	Z_Order_Task	= 4,
    Z_Order_BackPackUI  = 5,
    Z_Order_TaskChatLayer   = 6,
	Z_Order_ChatLayer		= 80,
	Z_Order_MessageLayer	= 90,
	Z_Order_DragLayer		= 100,
	Z_Order_DiamondWarningLayer	= 105,		
	Z_Order_PopupDialogLayer	= 109,
	Z_Order_MessageBox		= 110,
	Z_Order_TutorialLayer	= 111,	
    Z_Order_LoadingLayer	= 120,
	Z_Order_MessageBox_2		= 121,
	Z_Order_WaitingLayer	= 122,
};

//enum EUITag{
//	kUITag_PopupReward = 80001,
//	kUITag_StoryInstance = 80002,
//};

// ScrollView Direction
typedef enum {
	SWScrollViewDirectionHorizontal,
	SWScrollViewDirectionVertical,
	SWScrollViewDirectionBoth
} SWScrollViewDirection;


//
// Define here the type of autorotation that you want for your game
//

// 3rd generation and newer devices: Rotate using UIViewController. Rotation should be supported on iPad apps.
// TIP:
// To improve the performance, you should set this value to "kGameAutorotationNone" or "kGameAutorotationCCDirector"
#if defined(__ARM_NEON__) || TARGET_IPHONE_SIMULATOR
#define GAME_AUTOROTATION kGameAutorotationUIViewController

// ARMv6 (1st and 2nd generation devices): Don't rotate. It is very expensive
#elif __arm__
#define GAME_AUTOROTATION kGameAutorotationUIViewController


// Ignore this value on Mac
#elif defined(__MAC_OS_X_VERSION_MAX_ALLOWED)

#else

#endif

#define FPS 1.0f/24.0f

#define NET_CHECKER_TIME 30.0f

#define LEVEL_MAX 100
#define LEARN_FULL 510

#define MAX_SPRITES_PAGE 11
#define SP_INPAGE_MAX 9

#define KMAX_UUID_LEN 36


#define KPLAYER_NAME_NIM_LEN	4  //��ɫ�ĳ���
#define KPLAYER_NAME_MAX_LEN	10
#define ASSIGN_EXP_TEXT_FIELD	101

#define CAPTURE_LEVEL_ITEM_COUNT 10
#define LARGEMAP_STAR_COUNT      10

#define HERO_LEVEL_ITEM_COUNT	10


#define TEXT_RECT_BIG (IsIpad()?32:16)

#define MAP_CYAN ccc3(0, 255, 255)
#define MAP_GREEN ccc3(76, 198, 15)
#define MAP_GRAY ccc3(176, 176, 176)

enum MAPOFFSET
{
	IPHONE_HD_OFFSET_X = 32,
	IPHONE_HD_OFFSET_Y = 64,
};
const static int CELL_W = 32;


#if (!defined ANDROID && !defined PATH_MAX)
#define PATH_MAX 512
#endif

#if (!defined ANDROID && !defined NAME_MAX)
#define NAME_MAX 255
#endif


typedef unsigned short in_port_t;

#ifdef WIN32

#define fmaxf(a,b) ((a>b)?a:b)
#define fminf(a,b) ((a>b)?b:a)

#include <stdlib.h>
inline int arc4random()
{
	return rand();
}

#include <time.h>
inline void localtime_r(time_t *curtime, struct tm *time)
{
	localtime_s(time, curtime);
}

#endif


// default ui resources file
#define KUI_CN_BIN "UI/ui_cn.bin"


#endif // _SEER_DEFINE_H_UI