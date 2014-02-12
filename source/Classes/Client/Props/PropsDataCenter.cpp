#include "PropsDataCenter.h"
#include "GameResourceManager.h"
#include <libxml/parser.h>
//#include <parser.h>


PropsDataCenter::PropsDataCenter()
{

}

PropsDataCenter::~PropsDataCenter()
{
	mapPropsData.clear();
	setPropBatchFileNames.clear();
}

void PropsDataCenter::ReadData()
{
	const char* pFile = "Data/propTriggerConfig.bin";
	char *xmlString =(char*) GameResourceManager::sharedManager()->loadXml(pFile);
	xmlDocPtr pDoc = xmlReadMemory(xmlString, strlen(xmlString), NULL, "UTF-8", XML_PARSE_RECOVER);
	xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);

	if(pRoot != NULL)
	{
		xmlNodePtr pChildrenNode = pRoot->children;
		while (pChildrenNode != NULL)
		{
			if(xmlStrcmp(pChildrenNode->name, BAD_CAST"prop") == 0)
			{
				xmlAttrPtr attrPtr = pChildrenNode->properties;

				unsigned int id = 0;
				unsigned int animRcsId = 0;
				unsigned int soundId = 0;
				std::string batchFileName = "";
				std::string frameFileName = "";
				bool isExplosionSelf = false;

				while (attrPtr != NULL)
				{
					if (!xmlStrcmp(attrPtr->name, BAD_CAST "ID"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "ID");
						id = (unsigned int)atoi((const char*)szAttr);						
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "aniRcsID"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "aniRcsID");
						animRcsId = (unsigned int)atoi((const char*)szAttr);						
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "soundId"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "soundId");
						soundId = (unsigned int)atoi((const char*)szAttr);						
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "batchFileName"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "batchFileName");
						batchFileName = std::string((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "frameFileName"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "frameFileName");
						frameFileName = std::string((const char*)szAttr);
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "isExplosionSelf"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "isExplosionSelf");
						if (strcmp((const char*)szAttr,"true") == 0)
						{
							isExplosionSelf = true;
						}
						xmlFree(szAttr);
					}

					attrPtr = attrPtr->next;
				}

				PropTriggerData data;
				data.type = id;
				data.aniRcsId = animRcsId;
				data.soundId = soundId;
				data.batchFileName = batchFileName;
				data.frameFileName = frameFileName;
				data.isExplosionSelf = isExplosionSelf;

				mapPropsData.insert(std::make_pair(id,data));
				setPropBatchFileNames.insert(batchFileName);
				
			}
			pChildrenNode = pChildrenNode->next;
		}
	}

	free(xmlString);
	xmlFreeDoc(pDoc);
}

bool PropsDataCenter::GetBatchFileNameAndFrameName(PropsType type,std::string &batchFileName,std::string &frameFileName)
{
	std::map<unsigned int,PropTriggerData>::iterator iter = mapPropsData.find((int)type);
	if (iter == mapPropsData.end())
	{
		return false;
	}

	batchFileName = (*iter).second.batchFileName;
	frameFileName = (*iter).second.frameFileName;
	return true;
}

bool PropsDataCenter::GetAnimRcsIdByPropType(PropsType type,unsigned int &id)
{
	std::map<unsigned int,PropTriggerData>::iterator iter = mapPropsData.find((int)type);
	if (iter == mapPropsData.end())
	{
		return false;
	}
	else
	{
		id = (*iter).second.aniRcsId;
	}
	return true;
}

bool PropsDataCenter::GetSoundIdByPropType(PropsType type,unsigned int &id)
{
	std::map<unsigned int,PropTriggerData>::iterator iter = mapPropsData.find((int)type);
	if (iter == mapPropsData.end())
	{
		id = 0;
		return false;
	}
	else
	{
		id = (*iter).second.soundId;
	}
	return true;
}

unsigned int PropsDataCenter::GetMaxPropNums()
{
	return mapPropsData.size();
}

bool PropsDataCenter::GetTriggerData(PropsType propType,PropTriggerData &data)
{
	std::map<unsigned int,PropTriggerData>::iterator iter = mapPropsData.find((int)propType);
	if (iter == mapPropsData.end())
	{
		return false;
	}
	data = (*iter).second;
	return true;
}