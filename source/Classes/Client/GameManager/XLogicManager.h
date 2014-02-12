#ifndef _XLOGIC_MANAGER_H_
#define _XLOGIC_MANAGER_H_

#include "ILogicManager.h"
#include "cocos2d.h"

USING_NS_CC;

/// <summary>
//	��Ϸ�����࣬������Ϸ����
/// </summary>
class XLogicManager : 
	public CCNode,
	public ILogicManager
{
public:
	/// ҳ��ѡ��
	typedef enum  
	{
		E_NOE          = 0,
		E_UI_LOGIN_LAYER,
		E_UI_MAIN_LAYER ,
		E_ENTER_GAME,
		E_UI_GAME_OVER,
		E_XLOGICMANAGER,

		// add more...

	}GAME_LOGIC_LAYER;
public:
	XLogicManager();
	virtual ~XLogicManager();

	void  WillEnterForeground();
	void  DidEnterBackground();
	
	virtual void startGame();
	virtual void exitGame();

	// static instance
	static XLogicManager* sharedManager();

	// functions
	// go to a specific scene
	void  goToLayer(GAME_LOGIC_LAYER sceneTag, void *userData = NULL); 

	void connectToServer();
protected:
	// Note: ��ʼ����Ϸ��Ҫ�Ĺ̶�����
	void initFixedConfigData();
	void initGameConfigData();
protected:
	GAME_LOGIC_LAYER  m_eCurLayer;
	bool isGameStart;
};

#endif	// _XLOGIC_MANAGER_H_