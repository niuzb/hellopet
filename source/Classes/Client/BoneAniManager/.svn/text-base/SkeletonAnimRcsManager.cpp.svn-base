#include "SkeletonAnimRcsManager.h"
#include "GameResourceManager.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "CConnectionData.h"
#include "CProcessBase.h"
#include "CommonUtils.h"
#include "RoleActorBase.h"
#include "AnimABBoxDataCenter.h"

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

USING_NS_CC;

SkeletonAnimRcsManager::SkeletonAnimRcsManager():
						rolesActorRcsDataCollection(NULL),
						rolesAnimRcsDataCollection(NULL),
						mapAttachAnimRcsData(NULL),
						abBoxDataCenter(NULL),
						m_isLoadAllData(false)
{
	rolesActorRcsDataCollection = new RolesActorDataCollection();
	rolesAnimRcsDataCollection = new RolesAnimRcsDataCollection();
	mapAttachAnimRcsData = new MapAttachedAniRcsData();
}

SkeletonAnimRcsManager::~SkeletonAnimRcsManager()
{
	CC_SAFE_DELETE(rolesActorRcsDataCollection);
	CC_SAFE_DELETE(rolesAnimRcsDataCollection);
	CC_SAFE_DELETE(mapAttachAnimRcsData);
	CC_SAFE_DELETE(abBoxDataCenter);

	CCConnectionData::purgeConnectionData();
}

TiXmlElement * SkeletonAnimRcsManager::initXML(const char * filePath)
{
	std::string fullFilePath = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(filePath);

	unsigned long	_size;
	char			*_pFileContent = (char*)CCFileUtils::sharedFileUtils()->getFileData(fullFilePath.c_str() , "r", &_size);
	TiXmlDocument	*_document = new TiXmlDocument();
	_document->Parse(_pFileContent, 0, TIXML_ENCODING_UTF8);

	CC_SAFE_DELETE_ARRAY(_pFileContent);

	TiXmlElement *RootElement = _document->RootElement();
	return RootElement;
}

void SkeletonAnimRcsManager::LoadRoleAnimConfigFile()
{
	std::string filePath = std::string("Data/") + std::string("RoleActionConfig.xml");
	TiXmlElement *RootElement = initXML(filePath.c_str());
	if (NULL != RootElement)
	{
		TiXmlElement *childElement = RootElement->FirstChildElement();
		while (0 != childElement)
		{
			const char *elementValue = childElement->Value();
			if (0 == strcmp(elementValue,"Map"))
			{
				readMapAttachedRcsDataFromFile(childElement);
			}
			else if (0 == strcmp(elementValue,"RcsFiles"))
			{
				readRolesAnimRcsDataFromFile(childElement);
			}
			else if (0 == strcmp(elementValue,"RoleActions"))
			{
				readRolesActorDataFromFile(childElement);
			}
			childElement = childElement->NextSiblingElement();
		}
	}
	TiXmlDocument *doc = RootElement->GetDocument();
	doc->Clear();
	CC_SAFE_DELETE(doc);
}

bool SkeletonAnimRcsManager::readRolesAnimRcsDataFromFile(TiXmlElement *root)
{
	if (NULL != root && NULL != rolesAnimRcsDataCollection)
	{
		TiXmlElement *childElement = root->FirstChildElement();
		while (NULL != childElement)
		{						
			int roleId = atoi(childElement->Attribute("id"));
			
			OneRoleAniRcsData *oneRoleAnimData = new OneRoleAniRcsData();
			if (oneRoleAnimData)
			{
				TiXmlElement * grandChildElement = childElement->FirstChildElement();
				while(NULL != grandChildElement)
				{
					const char *name = grandChildElement->Value();
					if (0 == strcmp(name,"AttachEffects"))
					{
						TiXmlElement * subElement = grandChildElement->FirstChildElement();
						while(NULL != subElement)
						{
							int id = atoi(subElement->Attribute("id"));
							oneRoleAnimData->AddOneEffectID(id);
							subElement = subElement->NextSiblingElement();
						}
					}
					else if (0 == strcmp(name,"MainLand"))
					{
						TiXmlElement * subElement = grandChildElement->FirstChildElement();
						while(NULL != subElement)
						{
							const char *xmlName = subElement->Attribute("xml_name");
							oneRoleAnimData->AddOneElement(std::string(xmlName),false);
							subElement = subElement->NextSiblingElement();
						}
					}
					else if (0 == strcmp(name,"OtherLand"))
					{
						TiXmlElement * subElement = grandChildElement->FirstChildElement();
						while(NULL != subElement)
						{
							const char *xmlName = subElement->Attribute("xml_name");
							oneRoleAnimData->AddOneElement(std::string(xmlName),true);
							subElement = subElement->NextSiblingElement();
						}
					}
					else
					{
						const char *xmlName = grandChildElement->Attribute("xml_name");
						oneRoleAnimData->AddOneElement(std::string(xmlName),true);
					}
					grandChildElement = grandChildElement->NextSiblingElement();
				}
			}
			rolesAnimRcsDataCollection->AddOneElement(roleId,oneRoleAnimData);
				
			childElement = childElement->NextSiblingElement();
		}
	}
	return true;
}

bool SkeletonAnimRcsManager::readRolesActorDataFromFile(TiXmlElement *root)
{
	if (NULL != root)
	{
		TiXmlElement *childElement = root->FirstChildElement();
		while (NULL != childElement)
		{
			const char *roleTypeValue = childElement->Attribute("value");
			if(0 != roleTypeValue)
			{
				OneRoleActorData * oneRoleActorData = new OneRoleActorData();
				if (0 != oneRoleActorData)
				{
					TiXmlElement *actionElement = childElement->FirstChildElement();
					while(NULL != actionElement)
					{								
						TiXmlElement *actionContentElement = actionElement->FirstChildElement();
						const char * xml_file_name = actionContentElement->Attribute("xml_name");
						const char * action_name = actionContentElement->Attribute("action_name");

						OneAnimActorData oneAnimationActorData(xml_file_name,action_name);

						const char *actionTypeValue = actionElement->Attribute("value");
						int actionId = getOneActionId(actionTypeValue);
						oneRoleActorData->PushOneElement(actionId,oneAnimationActorData);

						actionElement = actionElement->NextSiblingElement();
					}
				}

				int roleId = 0;
				{
					std::string typeStr(roleTypeValue);
					int startPos = typeStr.find("_");
					typeStr = typeStr.substr(startPos+1,typeStr.length()-startPos);
					roleId = atoi(typeStr.c_str());
				}

				if (NULL != rolesActorRcsDataCollection)
				{
					rolesActorRcsDataCollection->PushOneElement(roleId,oneRoleActorData);
				}
			}
			childElement = childElement->NextSiblingElement();
		}
	}

	return true;
}

bool SkeletonAnimRcsManager::readMapAttachedRcsDataFromFile(TiXmlElement *root)
{
	if (NULL != root && NULL != mapAttachAnimRcsData)
	{
		TiXmlElement *childElement = root->FirstChildElement();		
		while (0 != childElement)
		{
			const char *elementName = childElement->Value();

			if (0 == strcmp(elementName,"effect_common"))
			{
				TiXmlElement *one_element = childElement->FirstChildElement();
				while(0 != one_element)
				{
					int id = atoi(one_element->Attribute("id"));
					mapAttachAnimRcsData->PushOneEffectId(id);
					one_element = one_element->NextSiblingElement();
				}
			}

			childElement = childElement->NextSiblingElement();
		}
		return true;
	}
	return false;
}

/// <summary>
//	从XML表中加载数据，得到所有骨骼的动画数据，并存储
/// </summary>
void SkeletonAnimRcsManager::LoadAllAnimConnectionData()
{
	if (m_isLoadAllData)
	{
		return ;
	}
	m_isLoadAllData = true;

	LoadRoleAnimConfigFile();

	//if (rolesAnimRcsDataCollection)
	//{
	//	std::map<int,OneRoleAniRcsData *> roleAnimRcsMap = rolesAnimRcsDataCollection->GetRolesAnimRcsData();
	//	for(std::map<int,OneRoleAniRcsData *>::iterator roleRcsMapIter = roleAnimRcsMap.begin();
	//													roleRcsMapIter != roleAnimRcsMap.end();
	//													roleRcsMapIter ++)
	//	{
	//		const std::vector<std::string>* pVecFileNames = (((*roleRcsMapIter).second)->GetMainLandNames());
	//		for (size_t index = 0;index<pVecFileNames->size();index++)
	//		{
	//			std::string fileName = (*pVecFileNames)[index];
	//			// 骨骼动画XML资源Load
	//			std::string rcsPath = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(SKELETON_ANIMATION_DIR,					
	//																	CommonUtils::StringAppendMethod(fileName,".ani").c_str());
	//			CCConnectionData::sharedConnectionData()->addData((rcsPath).c_str());
	//		}		

	//		pVecFileNames = (((*roleRcsMapIter).second)->GetOtherLandNames());
	//		for (size_t index = 0;index<pVecFileNames->size();index++)
	//		{
	//			std::string fileName = (*pVecFileNames)[index];
	//			// 骨骼动画XML资源Load
	//			std::string rcsPath = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(SKELETON_ANIMATION_DIR,					
	//																	CommonUtils::StringAppendMethod(fileName,".ani").c_str());
	//			CCConnectionData::sharedConnectionData()->addData((rcsPath).c_str());
	//		}
	//	}
	//}
}

void SkeletonAnimRcsManager::loadOneRoleAttachEffectRcs(int roleId)
{
	std::map<int,OneRoleAniRcsData *> roleAnimRcsMap = rolesAnimRcsDataCollection->GetRolesAnimRcsData();
	std::map<int,OneRoleAniRcsData *>::iterator roleRcsMapIter = roleAnimRcsMap.find(roleId);
	if (roleRcsMapIter != roleAnimRcsMap.end())
	{
		const std::vector<std::string> * pVecFileNames = NULL;
		const std::vector<int> * pVecAttachEffects = (((*roleRcsMapIter).second)->GetAttachEffects());
		if (pVecAttachEffects)
		{
			// 加载Effects
			for (size_t index = 0;index<pVecAttachEffects->size();index++)
			{
				int effectId = (*pVecAttachEffects)[index];

				std::map<int,OneRoleAniRcsData *>::iterator effectRcsMapIter = roleAnimRcsMap.find(effectId);
				if (effectRcsMapIter != roleAnimRcsMap.end())
				{
					pVecFileNames = (((*effectRcsMapIter).second)->GetOtherLandNames());

					for (size_t index = 0;index<pVecFileNames->size();index++)
					{
						std::string fileName = ((*pVecFileNames)[index]);
						loadOneRcs(fileName);
					}
				}
			}
		}
	}
}

/// <summary>
//	加载某主角相关的资源
//	ADD
/// </summary>
void SkeletonAnimRcsManager::LoadOneRoleRcs(int roleId,bool bInOtherLand)
{
	std::set<unsigned int>::iterator iter = setLoadRoles.find(roleId);
	if (iter != setLoadRoles.end())
	{
		return ;
	}
	setLoadRoles.insert(roleId);

	const std::map<int,OneRoleAniRcsData *> roleAnimRcsMap = rolesAnimRcsDataCollection->GetRolesAnimRcsData();
	std::map<int,OneRoleAniRcsData *>::const_iterator roleRcsMapIter = roleAnimRcsMap.find(roleId);
	if (roleRcsMapIter != roleAnimRcsMap.end())
	{
		const std::vector<std::string> * pVecFileNames = NULL;
		if (bInOtherLand)
		{
			pVecFileNames = (((*roleRcsMapIter).second)->GetOtherLandNames());
			loadOneRoleAttachEffectRcs(roleId);
		}
		else
		{
			pVecFileNames = (((*roleRcsMapIter).second)->GetMainLandNames());
		}
		for (size_t index = 0;index<pVecFileNames->size();index++)
		{
			std::string fileName = ((*pVecFileNames)[index]);
			loadOneRcs(fileName);
		}
	}
}

/// <summary>
//	加载公用的动画资源 例如UI特效 等..
/// </summary>
void SkeletonAnimRcsManager::LoadCommonRcs(bool bInOtherLand)
{
	if (mapAttachAnimRcsData)
	{
		const std::vector<int> vecCommondEffect = mapAttachAnimRcsData->GetCommonEffects();
		const std::map<int,OneRoleAniRcsData *> roleAnimRcsMap = rolesAnimRcsDataCollection->GetRolesAnimRcsData();
		for (std::vector<int>::const_iterator iter = vecCommondEffect.begin();
			iter != vecCommondEffect.end(); iter++)
		{
			int id = (*iter);
			std::map<int,OneRoleAniRcsData *>::const_iterator roleRcsMapIter = roleAnimRcsMap.find(id);
			if (roleRcsMapIter != roleAnimRcsMap.end())
			{
				const std::vector<std::string> * pVecFileNames = NULL;
				if (bInOtherLand)
				{
					pVecFileNames = (((*roleRcsMapIter).second)->GetOtherLandNames());
				}
				else
				{
					pVecFileNames = (((*roleRcsMapIter).second)->GetMainLandNames());
				}
				for (size_t index = 0;index<pVecFileNames->size();index++)
				{
					std::string fileName = ((*pVecFileNames)[index]);
					loadOneRcs(fileName);
				}
			}
		}
	}
}

void SkeletonAnimRcsManager::loadOneRcs(std::string rcsPath)
{
	std::set<std::string>::iterator iter = setLoadedAnimFiles.find(rcsPath.c_str());
	if (iter != setLoadedAnimFiles.end())
	{
		return ;
	}
	setLoadedAnimFiles.insert(rcsPath);
	
	// 骨骼动画XML资源Load
	std::string pXmlFilePath = 
		GameResourceManager::sharedManager()->storedFullPathFromRelativePath(SKELETON_ANIMATION_DIR,
		CommonUtils::StringAppendMethod(rcsPath,".ani").c_str());
	CCConnectionData::sharedConnectionData()->addData((pXmlFilePath).c_str());

	std::string pListFilePath = 
		GameResourceManager::sharedManager()->storedFullPathFromRelativePath(SKELETON_ANIMATION_DIR,
		CommonUtils::StringAppendMethod(rcsPath,".plist").c_str());
	std::string pngFilePath = 
		GameResourceManager::sharedManager()->storedFullPathFromRelativePath(SKELETON_ANIMATION_DIR,
		CommonUtils::StringAppendMethod(rcsPath,SKELETON_IMAGE_FILE_SUFFIX).c_str());

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pListFilePath.c_str(),pngFilePath.c_str());
}

bool SkeletonAnimRcsManager::IsOneActorRcsExist(int typeId)
{
	const std::map<int,OneRoleAniRcsData *> roleAnimRcsMap = rolesAnimRcsDataCollection->GetRolesAnimRcsData();
	std::map<int,OneRoleAniRcsData *>::const_iterator roleRcsMapIter = roleAnimRcsMap.find(typeId);
	if (roleRcsMapIter == roleAnimRcsMap.end())
	{
		return false;
	}
	return true;
}


int SkeletonAnimRcsManager::GetOneRoleActorFrames(int roleId,int animId)
{
	std::map<int,OneRoleActorData *> rolesActorMap = rolesActorRcsDataCollection->GetRolesActorData();
	std::map<int,OneRoleActorData *>::const_iterator iter = rolesActorMap.find(roleId);
	if (iter != rolesActorMap.end())
	{
		OneRoleActorData *pData = (*iter).second;
		const std::map<int,OneAnimActorData > oneRoleActorMap = pData->GetOneRoleActorData();
		std::map<int,OneAnimActorData >::const_iterator _iter = oneRoleActorMap.find(animId);
		if (_iter != oneRoleActorMap.end())
		{
			OneAnimActorData armature_data = (*_iter).second;
			std::string name = armature_data.GetActionName();
			std::string animation_name = armature_data.GetXmlFileName();
			CCArmatureAniData* _animationData = CCConnectionData::sharedConnectionData()->getAnimationData(animation_name.c_str());
			if (_animationData != 0)
			{
				CCBoneAniData *pAniData = _animationData->getAnimation( name.c_str() );
				if (pAniData == 0)
				{
					return -1;
				}
				return pAniData->getDurationTween();
			}
		}		
	}

	return -1;
}

float SkeletonAnimRcsManager::GetOneRoleActorDuration(int roleId,int animId)
{
	int frame = GetOneRoleActorFrames(roleId,animId);
	if (-1 == frame)
	{
		return 0;
	}
	return ((float)frame) / (FRAME_RATES);
}

int SkeletonAnimRcsManager::getOneActionId(const char* actionTypeStr)
{
	int actionType = 0;
	std::string actionTypeString(actionTypeStr);
	int startPos = actionTypeString.rfind("_");
	if (std::string::npos != startPos)
	{
		std::string identityFlagString = actionTypeString.substr(startPos+1,actionTypeString.length()-startPos-1);
		actionType = atoi(identityFlagString.c_str());
		return actionType;
	}
	return actionType;
}

std::map<std::string,RoleActorBase*> * SkeletonAnimRcsManager::CreateOneRoleArmatures(int role_id,bool bMainLand /* = true */)
{
	std::map<std::string,RoleActorBase*>* roleActorDataMap = new std::map<std::string,RoleActorBase*>();
	if (NULL == roleActorDataMap)
	{
		return NULL;
	}

	const std::map<int,OneRoleActorData *> rolesActorMap = rolesActorRcsDataCollection->GetRolesActorData();
	const std::map<int,OneRoleAniRcsData *> roleAnimRcsMap = rolesAnimRcsDataCollection->GetRolesAnimRcsData();

	const std::vector<std::string> * pVecFileNames = NULL;
	std::map<int,OneRoleAniRcsData *>::const_iterator roleRcsMapIter = roleAnimRcsMap.find(role_id);
	if (roleRcsMapIter != roleAnimRcsMap.end())
	{
		bool bMainLandLevel = bMainLand;
		if (bMainLandLevel)
		{
			pVecFileNames = (*roleRcsMapIter).second->GetMainLandNames();
			if (pVecFileNames->size() == 0)
			{
				pVecFileNames = (*roleRcsMapIter).second->GetOtherLandNames();
			}
		}
		else
		{
			pVecFileNames = (*roleRcsMapIter).second->GetOtherLandNames();
		}

		for (std::vector<std::string>::const_iterator iter = pVecFileNames->begin();
			iter != pVecFileNames->end(); iter++)
		{
			std::string name = (*iter);
			std::string pngFilePath = GameResourceManager::sharedManager()->storedFullPathFromRelativePath
				(SKELETON_ANIMATION_DIR,CommonUtils::StringAppendMethod(name,SKELETON_IMAGE_FILE_SUFFIX).c_str());
			RoleActorBase * actorBase = RoleActorBase::create(name,name,pngFilePath);
			if (0 != actorBase)
			{
				actorBase->pauseAllAnimation();
				roleActorDataMap->insert(std::make_pair(name,actorBase));
			}
		}
	}

	std::map<int,OneRoleActorData *>::const_iterator iter = rolesActorMap.find(role_id);
	if (iter == rolesActorMap.end())
	{
		// 特效没有单独进行配置 使用默认添加的方式创建一个名为“play”的动作
		std::map<int,OneRoleAniRcsData *>::const_iterator roleRcsMapIter = roleAnimRcsMap.find(role_id);
		if (roleRcsMapIter != roleAnimRcsMap.end())
		{
			int actionType = 10000;
			OneRoleActorData *_armatureActionData = new OneRoleActorData();
			const std::vector<std::string> * pVecFileNames = (((*roleRcsMapIter).second)->GetOtherLandNames());
			for (size_t index = 0;index<pVecFileNames->size();index++)
			{				
				OneAnimActorData armatureData("play",(*pVecFileNames)[index]);
				_armatureActionData->PushOneElement(actionType,armatureData);
			}
			rolesActorRcsDataCollection->PushOneElement(role_id,_armatureActionData);
		}
	}

	return roleActorDataMap;
}

OneRoleActorData * SkeletonAnimRcsManager::GetOneRoleArmatureActionData(int id)
{
	const std::map<int,OneRoleActorData *> rolesActorMap = rolesActorRcsDataCollection->GetRolesActorData();
	std::map<int,OneRoleActorData *>::const_iterator iter = rolesActorMap.find(id);
	if (iter != rolesActorMap.end())
	{
		return (*iter).second;
	}

	return NULL;
}

void SkeletonAnimRcsManager::ReadABBoxData()
{
	if (abBoxDataCenter == NULL)
	{
		abBoxDataCenter = new AnimABBoxDataCenter();
		abBoxDataCenter->ReadData();
	}
	
}

AnimABBoxDataCenter* SkeletonAnimRcsManager::GetABBoxDataCenter()
{
	return abBoxDataCenter;
}

void SkeletonAnimRcsManager::ClearAllLoadedRcs()
{
	setLoadedAnimFiles.clear();
	setLoadRoles.clear();

	// Note: 销毁相关的XML信息数据
	CCConnectionData::sharedConnectionData()->ClearDataExceptColliderAndPointData();
}

//void SkeletonAnimRcsManager::LoadLayerNeedRcs(XLogicManager::GAME_LOGIC_LAYER sceneTag)
//{
//	std::vector<unsigned int> vec;
//	switch(sceneTag)
//	{
//	case XLogicManager::E_UI_MAIN_LAYER:
//		{			
//		}
//		break;
//	case XLogicManager::E_ENTER_GAME:
//		{
//			//vec.push_back(1);
//			vec.push_back(101);
//			vec.push_back(180);
//			vec.push_back(112);
//			vec.push_back(216);
//			vec.push_back(133);
//			vec.push_back(168);
//			vec.push_back(217);
//			vec.push_back(416);
//			vec.push_back(2023);
//			vec.push_back(10005);			
//			vec.push_back(10097);			
//			vec.push_back(19503);		
//			vec.push_back(10096);		
//			vec.push_back(10027);		
//		}
//		break;
//	case XLogicManager::E_UI_GAME_OVER:
//		{
//		}			
//		break;
//	default:
//		CCLOGWARN("invalid paramerter: %d", sceneTag);
//		break;
//	}
//
//	for (std::vector<unsigned int>::iterator iter = vec.begin();
//		 iter != vec.end(); iter++)
//	{
//		this->LoadOneRoleRcs((*iter),true);
//	}
//	
//}