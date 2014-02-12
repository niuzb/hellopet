#include "PropsTriggerManager.h"
#include "BoneAniManager/SkeletonAnimCommonDefine.h"
#include <ctime>
#include <cstdlib>
#include "Map/MapDataCenter.h"
#include "BoneAniManager/SkeletonAnimRcsManager.h"
#include "PropsDataCenter.h"
#include "GameResourceManager.h"
#include "CommonUtils.h"
#include "CConstValue.h"
#include "Sprite/SpriteHero.h"
#include "GameManager/CommonLookUpUtils.h"

//#define random(x) (rand()%x)

PropsTriggerManager::PropsTriggerManager()
{
}

PropsTriggerManager::~PropsTriggerManager()
{
	for (std::map<PropsType,PropTriggerBase*>::iterator iter = mapPreloadTriggers.begin();
		iter != mapPreloadTriggers.end(); iter++)
	{
		(*iter).second->release();
	}
	mapPreloadTriggers.clear();
}

void PropsTriggerManager::LoadAttachRcs()
{
	//if (propDataCenter)
	{
		const std::set<std::string> &propBatchFiles = PropsDataCenter::Get()->GetPropBatchFiles();
		for (std::set<std::string>::const_iterator iter = propBatchFiles.begin();
			 iter != propBatchFiles.end(); iter++)
		{
			std::string pListFilePath = 
				GameResourceManager::sharedManager()->storedFullPathFromRelativePath(
				CommonUtils::StringAppendMethod((*iter),".plist").c_str());
			std::string pngFilePath = 
				GameResourceManager::sharedManager()->storedFullPathFromRelativePath(
				CommonUtils::StringAppendMethod((*iter),".png").c_str());

			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pListFilePath.c_str(),pngFilePath.c_str());
		}
	}
}

void PropsTriggerManager::AddBatchNodes(CCNode* pParent,int zorder)
{
	if (pParent)
	{
		const std::set<std::string> &propBatchFiles = PropsDataCenter::Get()->GetPropBatchFiles();
		for (std::set<std::string>::const_iterator iter = propBatchFiles.begin();
			iter != propBatchFiles.end(); iter++)
		{
			std::string pngFilePath = 
				GameResourceManager::sharedManager()->storedFullPathFromRelativePath(
				CommonUtils::StringAppendMethod((*iter),".png").c_str());

			std::map<std::string,CCSpriteBatchNode*>::iterator batchNodeIter = mapBatchNodes.find(pngFilePath);
			if (batchNodeIter == mapBatchNodes.end())
			{
				CCSpriteBatchNode* pBatchNode = CCSpriteBatchNode::create(pngFilePath.c_str());
				if (pBatchNode)
				{
					mapBatchNodes.insert(std::make_pair((*iter),pBatchNode));
					pParent->addChild(pBatchNode,zorder);
				}
			}
		}
	}
}

void PropsTriggerManager::getBatchNodeFromPropType(PropsType propType,CCSpriteBatchNode* &pBatchNode,std::string &frameFileName)
{
	pBatchNode = NULL;
	//if (propDataCenter)
	{
		std::string batchFileName = "";
		PropsDataCenter::Get()->GetBatchFileNameAndFrameName(propType,batchFileName,frameFileName);
		std::map<std::string,CCSpriteBatchNode*>::iterator iter = mapBatchNodes.find(batchFileName);
		if (iter != mapBatchNodes.end())
		{
			pBatchNode = (*iter).second;
		}
	}
}

PropTriggerBase* PropsTriggerManager::createOnePropTrigger(PropsType propType)
{
	PropTriggerBase* _pProp = NULL;
	std::string frameFileName = "";
	CCSpriteBatchNode* pParentBatchNode = NULL;
	this->getBatchNodeFromPropType(propType,pParentBatchNode,frameFileName);

	PropTriggerData triggerData;
	if (PropsDataCenter::Get()->GetTriggerData(propType,triggerData))
	{
		PropTriggerBase* pProp = (new PropTriggerSprite(pParentBatchNode,frameFileName,propType,triggerData));
		CCAssert(pProp != NULL,"pProp != NULL");
		//pProp->autorelease();

		_pProp = pProp;
	}

	return (_pProp);
}

PropTriggerBase* PropsTriggerManager::AddPropTrigger(PropsType propType,bool isPreload /* = false */)
{
	PropTriggerBase* pTriggerBase = NULL;
	if (isPreload)
	{
		std::map<PropsType,PropTriggerBase*>::iterator iter = mapPreloadTriggers.find(propType);
		if (iter == mapPreloadTriggers.end())
		{
			pTriggerBase = createOnePropTrigger(propType);
			pTriggerBase->SetIsPreload(true);			
			mapPreloadTriggers.insert(std::make_pair(propType,pTriggerBase));
		}
		else
		{
			pTriggerBase = (*iter).second;
			pTriggerBase->setVisible(true);
		}
	}
	else
	{
		pTriggerBase = createOnePropTrigger(propType);
	}
	
	return pTriggerBase;
}

void PropsTriggerManager::RemoveOnePropFromStorage(PropTriggerBase* pPropTrigger)
{
	//if (pPropTrigger)
	//{
	//	std::map<PropTriggerBase*,PropsType>::iterator iter = mapPropTriggers.find(pPropTrigger);
	//	if (iter != mapPropTriggers.end())
	//	{
	//		mapPropTriggers.erase(iter);
	//	}
	//}	
}

//void PropsTriggerManager::RandomCreateProps(CCNode* pNode)
//{
//	if (pNode)
//	{
//		srand(time(0));
//		unsigned int maxPropNums = PropsDataCenter::Get()->GetMaxPropNums();
//		unsigned int propType = rand() % maxPropNums;
//		PropTriggerBase* pSprite = CreateOnePropTrigger((PropsType)propType);
//		if (pSprite)
//		{
//			pNode->addChild(pSprite,1);
//
//			srand((int)time(0));
//			unsigned int posx = rand()%(MapDataCenter::Get()->GetMapCellNumsHor());
//			unsigned int posy = rand()%(MapDataCenter::Get()->GetMapCellNumsVer());
//			pSprite->setPosition(ccp(posx,posy));
//		}		
//	}	
//}

void PropsTriggerManager::Update(float dt,CCNode* pNode)
{
	//static float runningTime = 0;
	//runningTime += dt;
	//if (runningTime > 1)
	//{
	//	RandomCreateProps(pNode);
	//	runningTime = 0;
	//}	

	//std::map<PropTriggerBase*,PropsType>::iterator pre_iter = mapPropTriggers.begin();
	//for (std::map<PropTriggerBase*,PropsType>::iterator iter = mapPropTriggers.begin();
	//	iter != mapPropTriggers.end(); )
	//{		
	//	iter++;

	//	bool bDeleteProp = false;
	//	(*pre_iter).first->Update(dt,bDeleteProp);
	//	
	//	pre_iter = iter;
	//}
}