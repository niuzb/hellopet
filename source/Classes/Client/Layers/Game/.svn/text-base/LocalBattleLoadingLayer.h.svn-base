#ifndef _LOCAL_BATTLE_LOADING_LAYER_H_
#define _LOCAL_BATTLE_LOADING_LAYER_H_

#include "LoadingLayer.h"
#include "Sprite/UserData.h"

class LocalBattleLoadingLayer : public LoadingLayer
{
public:
	LocalBattleLoadingLayer();
	virtual ~LocalBattleLoadingLayer();
	CREATE_FUNC(LocalBattleLoadingLayer);

	virtual void LoadingStart();
	virtual void LoadingEnd();
	virtual void LoadingUpdate(float dt);
protected:
	void LoadSkeletonAnim();
	void CreateBattleLayer();
	void PreloadAllNeedMusic();

	void SimulationRolesCreator();
protected:
	enum STATE
	{
		E_UNKNOW,
		E_CREATE_BATTLE_LAYER,
		E_LOAD_ANIM,
		E_END,
	};
	/// current loading step, -1 means finished
	STATE m_iCurStep;
};

#endif	//_BATTLE_LOADING_LAYER_H_