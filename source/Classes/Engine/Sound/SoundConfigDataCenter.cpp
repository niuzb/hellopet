#include "SoundConfigDataCenter.h"
#include "GameResourceManager.h"
#include <libxml/parser.h>
//#include <parser.h>


SoundConfigDataCenter::SoundConfigDataCenter()
{

}

SoundConfigDataCenter::~SoundConfigDataCenter()
{

}

void SoundConfigDataCenter::ReadData()
{
	const char* pFile = "Data/soundConfig.bin";
	char *xmlString =(char*) GameResourceManager::sharedManager()->loadXml(pFile);
	xmlDocPtr pDoc = xmlReadMemory(xmlString, strlen(xmlString), NULL, "UTF-8", XML_PARSE_RECOVER);
	xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);

	if(pRoot != NULL)
	{
		xmlNodePtr pChildrenNode = pRoot->children;
		while (pChildrenNode != NULL)
		{
			if(xmlStrcmp(pChildrenNode->name, BAD_CAST"sound") == 0)
			{
				xmlAttrPtr attrPtr = pChildrenNode->properties;
				
				unsigned int soundId = 0;
				float lastTimer = 0;

				while (attrPtr != NULL)
				{
					if (!xmlStrcmp(attrPtr->name, BAD_CAST "ID"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "ID");
						soundId = (unsigned int)atoi((const char*)szAttr);						
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "lastTime"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "lastTime");
						lastTimer = (unsigned int)atoi((const char*)szAttr);						
						xmlFree(szAttr);
					}

					attrPtr = attrPtr->next;
				}

				SoundData data;				
				data.soundId = soundId;
				data.lastTimer = lastTimer;

				mapSoundData.insert(std::make_pair(soundId,data));
			}
			pChildrenNode = pChildrenNode->next;
		}
	}

	free(xmlString);
	xmlFreeDoc(pDoc);
}

bool SoundConfigDataCenter::GetOneSoundData(unsigned int soundId,SoundData &data)
{	
	std::map<unsigned int,SoundData>::iterator iter = mapSoundData.find(soundId);
	if (iter != mapSoundData.end())
	{
		data = (*iter).second;
		return true;
	}
	return false;
}