#ifndef _SPRITE_PARTICLE_H
#define _SPRITE_PARTICLE_H

#include "cocos2d.h"
#include "IParticleAnimationInterface.h"
#include "ParticleAnimation.h"

USING_NS_CC;

class SpriteParticle : public cocos2d::CCNode,public IParticleAnimationInterface
{
public: 
	SpriteParticle(int id,const char* rcsFileName);
	virtual ~SpriteParticle();

public:
	virtual void play(unsigned int nLoop,bool bLoop);
	virtual void playAtOneFrame(unsigned int nFrame);
	virtual void pause();
	virtual void resume();

	virtual void update(float delta);
private:
	void Init();
private:
	unsigned int m_id;
	std::string m_rcsFileName;

	CCSprite* m_particleSprite;
	CCSpriteBatchNode* m_batchNode;
	ParticleAnimation* m_animation;

	std::string m_particleSpriteName;
};

#endif	//_SPRITE_PARTICLE_H