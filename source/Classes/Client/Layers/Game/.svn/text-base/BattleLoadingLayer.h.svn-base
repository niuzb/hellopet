#ifndef _BATTLE_LOADING_LAYER_H_
#define _BATTLE_LOADING_LAYER_H_

#include "LoadingLayer.h"
#include "Sprite/UserData.h"

class BattleLoadingLayer : public LoadingLayer
{
public:
	BattleLoadingLayer();
	virtual ~BattleLoadingLayer();
	CREATE_FUNC(BattleLoadingLayer);

	void SetInitData(EGoToLayerType gotoType,unsigned int roomId);
	virtual void LoadingStart();
	virtual void LoadingEnd();
	virtual void LoadingUpdate(float dt);
protected:
	void SendCreateBattleReq();
	void SendJoinBattleReq();
	void SendLoadCompleteReq();
	void LoadSkeletonAnim();
	void CreateBattleLayer();
	void PreloadAllNeedMusic();
	void CreateLayerCastles();

	virtual void HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg);
protected:
	enum STATE
	{
		E_UNKNOW,
		E_REQ_CREATE_BATTLE,
		E_CREATE_BATTLE_LAYER,
		E_REQ_JOIN_BATTLE,		
		E_LOAD_ANIM,	
		E_CREATE_CASTLE,
		E_END,
	};
	/// current loading step, -1 means finished
	STATE m_iCurStep;
	bool m_bSendBattleCreateMessage;
	bool m_bSendJoinBattleMessage;
	bool m_bSendLoadCompleteMessage;
	// Note: RoomId
	unsigned int m_nRoomId;
};

#endif	//_BATTLE_LOADING_LAYER_H_