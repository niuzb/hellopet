#include "CommonLookUpUtils.h"
#include "Layers/Game/BattleLayer.h"
#include "GameManager/BattleManger.h"
#include "Layers/Game/LayerCommonEnum.h"
#include "cocos2d.h"

USING_NS_CC;

BattleLayer* CommonLookUpUtils::GetBattleLayer()
{
	CCScene* pRunningScene = CCDirector::sharedDirector()->getRunningScene();
	if (pRunningScene)
	{
		CCNode* pNode = pRunningScene->getChildByTag(TAG_LAYER_BATTLE);
		if (pNode)
		{
			BattleLayer* pBattleLayer = dynamic_cast<BattleLayer*>(pNode);
			return pBattleLayer;			
		}				
	}

	return NULL;
}

BattleManager* CommonLookUpUtils::GetBattleManager()
{
	BattleManager* pMgr = NULL;
	BattleLayer* pLayer = GetBattleLayer();
	if (pLayer)
	{
		pMgr = pLayer->GetBattleManager();
	}
	return pMgr;
}