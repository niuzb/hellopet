#include "SpriteParticle.h"
#include "GameResourceManager.h"

SpriteParticle::SpriteParticle(int id,const char* rcsFileName):
	m_id(id),
	m_rcsFileName(rcsFileName),
	m_animation(NULL),
	m_batchNode(NULL),
	m_particleSprite(NULL)
{
	Init();

	scheduleUpdate();
}

SpriteParticle:: ~SpriteParticle()
{

}

void SpriteParticle::Init()
{
	// Note: Add Resource To Frame Cache
	std::string tmpPlistFilePath = "particles/" + m_rcsFileName + ".plist";
	std::string tmpPngFilePath = "particles/" + m_rcsFileName + ".png";
	std::string pListFilePath = 
		GameResourceManager::sharedManager()->storedFullPathFromRelativePath(tmpPlistFilePath.c_str());	
	std::string pngFilePath = 
		GameResourceManager::sharedManager()->storedFullPathFromRelativePath(tmpPngFilePath.c_str());

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(pListFilePath.c_str(),pngFilePath.c_str());  

	m_batchNode = CCSpriteBatchNode::create(pngFilePath.c_str());
	this->addChild(m_batchNode);

	m_animation = new ParticleAnimation(m_rcsFileName.c_str());
}

void SpriteParticle::play(unsigned int nLoop,bool bLoop)
{
	if (m_animation)
	{
		m_animation->play(nLoop,bLoop);
	}
}

void SpriteParticle::playAtOneFrame(unsigned int nFrame)
{
	if (m_animation)
	{
		m_animation->playAtOneFrame(nFrame);
	}
}

void SpriteParticle::pause()
{
	if (m_animation)
	{
		m_animation->pause();
	}
}

void SpriteParticle::resume()
{
	if (m_animation)
	{
		m_animation->resume();
	}
}

void SpriteParticle::update(float delta)
{
	if (m_animation)
	{
		m_animation->update(delta);

		// Note: ÇÐ»»Display
		std::string particleSpriteName = m_animation->getParticleSpriteName();
		if (particleSpriteName != m_particleSpriteName)
		{
			CCPoint offset = m_animation->getParticleSpriteOffsetPoint();

			if (m_particleSprite)
			{
				m_particleSprite->removeFromParentAndCleanup(true);
				m_particleSprite = NULL;
			}

			std::string pngFileName = particleSpriteName + ".png";
			CCSprite *_newSprite = CCSprite::createWithSpriteFrameName(pngFileName.c_str());
			m_batchNode->addChild(_newSprite); 
			m_particleSprite = _newSprite;

			m_particleSpriteName = particleSpriteName;
		}
	}
}