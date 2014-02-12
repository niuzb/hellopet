#ifndef _PROPS_MANAGER_H_
#define _PROPS_MANAGER_H_

#include "Singleton_t.h"
#include "map"
#include "PropsTriggerSprite.h"
#include "PropsTriggerBase.h"
#include "Props/PropsDefiner.h"
#include "cocos2d.h"

class PropsDataCenter;

USING_NS_CC;

/// <summary>
//	用来产生道具触发器
/// </summary>
class PropsTriggerManager:public TSingleton<PropsTriggerManager>
{
public:
	PropsTriggerManager();
	~PropsTriggerManager();

	// Note: 创建一个道具触发器
	PropTriggerBase* AddPropTrigger(PropsType propType,bool isPreload = false);
	// Note: 从道具产生器中移除一个
	void RemoveOnePropFromStorage(PropTriggerBase* pPropTrigger);
	// Note: 目前不需要，废弃
	//void RandomCreateProps(CCNode* pNode);

	void Update(float dt,CCNode* pNode);

	void AddBatchNodes(CCNode* pParent,int zorder);
	// Note: 加载Trigger相关图片资源
	void LoadAttachRcs();
protected:	
	void getBatchNodeFromPropType(PropsType propType,CCSpriteBatchNode* &pBatchNode,std::string &frameFileName);
	PropTriggerBase* createOnePropTrigger(PropsType propType);
private:
	//std::map<PropTriggerBase*,PropsType> mapPropTriggers;
	std::map<PropsType,PropTriggerBase*> mapPreloadTriggers;
	std::map<std::string,CCSpriteBatchNode*> mapBatchNodes;
};

#endif	//_PROPS_MANAGER_H_