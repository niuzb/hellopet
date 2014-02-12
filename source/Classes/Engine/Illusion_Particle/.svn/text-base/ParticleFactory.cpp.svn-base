#include "tinyxml.h"
#include "ParticleFactory.h"
#include "GameResourceManager.h"

ParticleFactory::ParticleFactory()
{
	InitXML();
}

ParticleFactory::~ParticleFactory()
{
	m_particleListInfo.clear();
}

void ParticleFactory::InitXML()
{
	std::string pPath = 
		GameResourceManager::sharedManager()->storedFullPathFromRelativePath("Data/particles.xml");

	unsigned long	_size;
	char			*_pFileContent = (char*)CCFileUtils::sharedFileUtils()->getFileData(pPath.c_str() , "r", &_size);
	TiXmlDocument	*_document = new TiXmlDocument();
	_document->Parse(_pFileContent, 0, TIXML_ENCODING_UTF8);

	CC_SAFE_DELETE_ARRAY(_pFileContent);

	TiXmlElement *RootElement = _document->RootElement();
	if (RootElement)
	{
		TiXmlElement *childElement = RootElement->FirstChildElement();
		while (0 != childElement)
		{
			OneParticleInfo oneParticleInfo;
			TiXmlAttribute* pAttribute = childElement->FirstAttribute();
			while(pAttribute)
			{
				std::string strName(pAttribute->Name());
				std::string content = childElement->Attribute(strName.c_str());
				if (strName == "ID")
				{
					unsigned int id = atoi(content.c_str());
					oneParticleInfo.id = id;
				}
				else if (strName == "fileName")
				{
					oneParticleInfo.fileName = content;
				}
				pAttribute = pAttribute->Next();
			}
			m_particleListInfo.insert(std::make_pair(oneParticleInfo.id,oneParticleInfo));

			childElement = childElement->NextSiblingElement();
		}

		TiXmlDocument *doc = RootElement->GetDocument();
		doc->Clear();
		CC_SAFE_DELETE(doc);
	}
}

SpriteParticle* ParticleFactory::CreateParticle(unsigned int id)
{
	std::map<unsigned int,OneParticleInfo>::iterator iter = m_particleListInfo.find(id);
	if (iter == m_particleListInfo.end())
	{
		return NULL;
	}	

	std::string fileName = (*iter).second.fileName;
	SpriteParticle* particle = new SpriteParticle(id,fileName.c_str());
	return particle;
}