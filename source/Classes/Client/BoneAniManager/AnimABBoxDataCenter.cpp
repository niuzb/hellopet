#include "AnimABBoxDataCenter.h"
#include "SkeletonAnimCommonDefine.h"
#include "GameResourceManager.h"
#include "CommonUtils.h"
//#include "tinyxml.h"
#include "Engine/XmlParser/TinyXml/tinyxml.h"
#include "string"
#include "SkeletonAnimRcsManager.h"

AnimABBoxDataCenter::AnimABBoxDataCenter()
{
	kvRoleIdAndColliderData = new std::map<int,CCColliderData>();
	kvRoleIdAndAttachPointsData = new std::map<int,std::map<int,CCPoint> >();
}

AnimABBoxDataCenter::~AnimABBoxDataCenter()
{
	delete kvRoleIdAndColliderData;
	kvRoleIdAndColliderData = NULL;

	delete kvRoleIdAndAttachPointsData;
	kvRoleIdAndAttachPointsData = NULL;
}

void AnimABBoxDataCenter::ReadData()
{
	std::string rcsPath = 
		GameResourceManager::sharedManager()->storedFullPathFromRelativePath(SKELETON_ANIMATION_DIR,
		CommonUtils::StringAppendMethod("AreaConfigTable",".xml").c_str());

	unsigned long	_size;
	CCFileUtils::sharedFileUtils()->setPopupNotify(false);
	char			*_pFileContent = (char*)CCFileUtils::sharedFileUtils()->getFileData(rcsPath.c_str() , "r", &_size);
	CCFileUtils::sharedFileUtils()->setPopupNotify(true);

	if (_pFileContent == NULL)
	{
		return ;
	}

	TiXmlDocument	_document;
	_document.Parse(_pFileContent, 0, TIXML_ENCODING_UTF8);

	TiXmlElement	*_root = _document.RootElement();
	CCAssert(_root, "XML error  or  XML is empty.");

	decodeColliderAreaAndPointData(_root);

	CC_SAFE_DELETE_ARRAY(_pFileContent);
	_document.Clear();
}

void AnimABBoxDataCenter::decodeColliderAreaAndPointData(TiXmlElement *_rootXML)
{
	if (_rootXML == 0)
	{
		return ;
	}
	TiXmlElement *roleEle = _rootXML->FirstChildElement();
	while(roleEle)
	{
		int roleID = atoi(roleEle->Attribute("id"));		
		TiXmlElement *childEle = roleEle->FirstChildElement();
		while(childEle)
		{
			const char *eleName = childEle->Value();
			if (strcmp(eleName,"Actions") == 0)
			{
				if (kvRoleIdAndColliderData->end() == kvRoleIdAndColliderData->find(roleID))
				{					
					CCColliderData colliderData;
					decodeColliderAreas(childEle,colliderData);
					kvRoleIdAndColliderData->insert(std::make_pair(roleID,colliderData));
				}
			}
			else if (strcmp(eleName,"PT") == 0)
			{
				if (kvRoleIdAndAttachPointsData->end() == kvRoleIdAndAttachPointsData->find(roleID))
				{
					std::map<int,CCPoint> mapPoints;
					decodeAttachPointData(childEle,mapPoints);
					kvRoleIdAndAttachPointsData->insert(std::make_pair(roleID,mapPoints));
				}
			}
			childEle = childEle->NextSiblingElement();
		}

		roleEle = roleEle->NextSiblingElement();
	}
}

void AnimABBoxDataCenter::decodeColliderAreas(TiXmlElement *_collidersXML,CCColliderData &data)
{
	TiXmlElement *moveElement = _collidersXML->FirstChildElement();
	while(moveElement)
	{
		CCMoveAreaData moveAreaData;
		int movId = atoi(moveElement->Attribute("id"));

		TiXmlElement *colliderAreaElement = moveElement->FirstChildElement();
		while(colliderAreaElement)
		{
			int index = 0;
			int upLeftPosX = 0;
			int upLeftPosY = 0;
			int downRightPosX = 0;
			int downRightPosY = 0;

			upLeftPosX = atoi(colliderAreaElement->Attribute("upLeftPX"));
			upLeftPosY = atoi(colliderAreaElement->Attribute("upLeftPY"));
			downRightPosX = atoi(colliderAreaElement->Attribute("downRightPX"));
			downRightPosY = atoi(colliderAreaElement->Attribute("downRightPY"));

			CCAreaData areaData;
			areaData.upLeftX = upLeftPosX;
			areaData.upLeftY = upLeftPosY;
			areaData.downRightX = downRightPosX;
			areaData.downRightY = downRightPosY;

			std::string colliderNodeName = colliderAreaElement->Value();
			if (colliderNodeName == "C")
			{
				moveAreaData.selfColliderArea = areaData;
			}
			else if (colliderNodeName == "V")
			{
				moveAreaData.selfViewRectArea = areaData;
			}
			else if (colliderNodeName == "A")
			{
				index = atoi(colliderAreaElement->Attribute("startFrame"));
				moveAreaData.kvFrameIndexAndAreaData.insert(std::make_pair(index,areaData));
			}
			colliderAreaElement = colliderAreaElement->NextSiblingElement();
		}
		moveElement = moveElement->NextSiblingElement();

		data.kvMoveIdAndAreaData.insert(std::make_pair(movId,moveAreaData));
	}
}

void AnimABBoxDataCenter::decodeAttachPointData(TiXmlElement *_attachPointsXML,std::map<int,CCPoint> &pointsMap)
{
	if (0 != _attachPointsXML)
	{
		TiXmlElement *pointEle = _attachPointsXML->FirstChildElement();
		while(pointEle)
		{
			float posx = atof(pointEle->Attribute("posX"));
			float posy = atof(pointEle->Attribute("posY"));
			int cellWidth = 16;
			posx = posx*cellWidth;
			posy = posy*cellWidth;
			int	  index = atoi(pointEle->Attribute("Type"));
			CCPoint p(posx,posy);
			pointsMap.insert(std::make_pair(index,p));
			pointEle = pointEle->NextSiblingElement();
		}
	}	
}

bool AnimABBoxDataCenter::GetColliderData(int role_id,int action_id,CCMoveAreaData &data)
{
	std::map<int,CCColliderData>::iterator iter;
	iter = kvRoleIdAndColliderData->find(role_id);
	if (iter == kvRoleIdAndColliderData->end())
	{
		return false;
	}
	std::map<int,CCMoveAreaData>::iterator mov_iter;
	mov_iter = (*iter).second.kvMoveIdAndAreaData.find(action_id);
	if (mov_iter == ((*iter).second.kvMoveIdAndAreaData).end())
	{
		return false;
	}
	data = (*mov_iter).second;
	return true;
}

bool AnimABBoxDataCenter::GetViewRectData(int role_id,std::string armatureName,CCAreaData &areaData)
{
	std::map<int,CCColliderData>::iterator iter;
	iter = kvRoleIdAndColliderData->find(role_id);
	if (iter == kvRoleIdAndColliderData->end())
	{
		return false;
	}
	OneRoleActorData *pData = SkeletonAnimRcsManager::Get()->GetOneRoleArmatureActionData(role_id);
	if (pData == 0)
	{
		return false;
	}
	const std::map<int,OneAnimActorData > roleAnimsData = pData->GetOneRoleActorData();
	for (std::map<int,OneAnimActorData >::const_iterator _iter = roleAnimsData.begin();
		_iter != roleAnimsData.end();_iter++)
	{
		OneAnimActorData armatureData = (*_iter).second;
		if (armatureData.GetXmlFileName() == armatureName)
		{
			int actionType = (*_iter).first;

			std::map<int,CCMoveAreaData>::iterator mov_iter;
			mov_iter = (*iter).second.kvMoveIdAndAreaData.find(actionType);
			if (mov_iter != ((*iter).second.kvMoveIdAndAreaData).end())
			{
				CCAreaData tmpAreaData = (*mov_iter).second.selfViewRectArea;
				if (tmpAreaData.IsValid())
				{
					areaData = tmpAreaData;
					return true;
				}
			}								
		}
	}		
	return false;
}

bool AnimABBoxDataCenter::GetRoleColliderData(unsigned int id,CCColliderData& colliderData)
{
	if (kvRoleIdAndColliderData)
	{
		std::map<int,CCColliderData>::iterator iter = kvRoleIdAndColliderData->find(id);
		if (iter != kvRoleIdAndColliderData->end())
		{
			colliderData = (*iter).second;
			return true;
		}
	}
	return false;
}

bool AnimABBoxDataCenter::GetRoleViewRectData(unsigned int role_id,std::map<std::string,CCAreaData> & areaData)
{
	areaData.clear();

	std::map<int,CCColliderData>::iterator iter;
	iter = kvRoleIdAndColliderData->find(role_id);
	if (iter == kvRoleIdAndColliderData->end())
	{
		return false;
	}
	OneRoleActorData *pData = SkeletonAnimRcsManager::Get()->GetOneRoleArmatureActionData(role_id);
	if (pData == 0)
	{
		return false;
	}
	const std::map<int,OneAnimActorData > roleAnimsData = pData->GetOneRoleActorData();
	for (std::map<int,OneAnimActorData >::const_iterator _iter = roleAnimsData.begin();
		_iter != roleAnimsData.end();_iter++)
	{
		OneAnimActorData armatureData = (*_iter).second;
		//if (armatureData.GetXmlFileName() == armatureName)
		{
			int actionType = (*_iter).first;

			std::map<int,CCMoveAreaData>::iterator mov_iter;
			mov_iter = (*iter).second.kvMoveIdAndAreaData.find(actionType);
			if (mov_iter != ((*iter).second.kvMoveIdAndAreaData).end())
			{
				CCAreaData tmpAreaData = (*mov_iter).second.selfViewRectArea;
				if (tmpAreaData.IsValid())
				{
					areaData[armatureData.GetXmlFileName()] = tmpAreaData;
				}
			}								
		}
	}		
	return true;
}