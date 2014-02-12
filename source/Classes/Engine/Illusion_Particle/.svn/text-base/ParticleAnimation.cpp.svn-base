#include "tinyxml.h"
#include "ParticleAnimation.h"
#include "GameResourceManager.h"

ParticleAnimation::ParticleAnimation(const char* fileName):
	m_rcsFileName(fileName),
	m_offsetSpirtePoint(CCPointZero)
{
	reset();
	init();
	m_bPause = true;
}

ParticleAnimation::~ParticleAnimation()
{
	m_vecParticleSpritesInfo.clear();
}

void ParticleAnimation::init()
{
	std::string tmpPath = "particles/" + m_rcsFileName + ".xml";
	std::string pPath = 
		GameResourceManager::sharedManager()->storedFullPathFromRelativePath(tmpPath.c_str());

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
			const char* elementName = childElement->Value();
			if (strcmp(elementName,"TotalFrames") == 0)
			{
				unsigned int totalFrames = atoi(childElement->Attribute("value"));
				m_nTotalFrames = totalFrames;
			}
			else if(strcmp(elementName,"Frames") == 0)
			{
				TiXmlElement *subChildElement = childElement->FirstChildElement();
				while (subChildElement)
				{
					OneParticleSpritesInfo oneParticleSpriteInfo;
					TiXmlAttribute* pAttribute = subChildElement->FirstAttribute();
					while(pAttribute)
					{
						std::string strName(pAttribute->Name());
						std::string content = subChildElement->Attribute(strName.c_str());
						if (strName == "fileName")
						{
							oneParticleSpriteInfo.spriteName = content;
						}
						else if (strName == "offsetX")
						{
							float pos = atof(content.c_str());
							oneParticleSpriteInfo.offsetPoint.x = pos;
						}
						else if (strName == "offsetY")
						{
							float pos = atof(content.c_str());
							oneParticleSpriteInfo.offsetPoint.y = pos;
						}
						pAttribute = pAttribute->Next();
					}
					m_vecParticleSpritesInfo.push_back(oneParticleSpriteInfo);

					subChildElement = subChildElement->NextSiblingElement();
				}
			}

			childElement = childElement->NextSiblingElement();
		}

		TiXmlDocument *doc = RootElement->GetDocument();
		doc->Clear();
		CC_SAFE_DELETE(doc);
	}
}

void ParticleAnimation::reset()
{
	m_bPause = false;
	m_bLoop = false;
	m_nLoopCount = 0;
	m_currentFrame = 0.0;
	m_currentPrecent = 0.0;

	m_particleSpriteName = "";
}

void ParticleAnimation::update(float deletaTime)
{
	if (m_bPause)
	{
		return ;
	}

	m_currentFrame += 1 * (deletaTime/(1.0 / ANIMATION_FRAMES_PER_SEC));
	if( m_currentFrame > (m_nTotalFrames-1) ){
		if (m_bLoop)
		{
			m_currentFrame = (int)(m_currentFrame) % (m_nTotalFrames-1);
		}
		else
		{
			m_currentFrame = m_nTotalFrames - 1;
		}
	}

	OneParticleSpritesInfo spriteInfo = m_vecParticleSpritesInfo[m_currentFrame];
	m_particleSpriteName = spriteInfo.spriteName;
	m_offsetSpirtePoint = spriteInfo.offsetPoint;
}

void ParticleAnimation::play(unsigned int nLoop,bool bLoop)
{
	reset();

	m_bLoop = bLoop;
	m_nLoopCount = nLoop;
}

void ParticleAnimation::playAtOneFrame(unsigned int nFrame)
{
	reset();
}

void ParticleAnimation::pause()
{
	m_bPause = true;
}

void ParticleAnimation::resume()
{
	m_bPause = false;
}