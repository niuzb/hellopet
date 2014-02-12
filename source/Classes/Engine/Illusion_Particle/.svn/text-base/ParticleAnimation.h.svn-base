#ifndef _PARTICLE_ANIMATION_H_
#define _PARTICLE_ANIMATION_H_

#include "string"
#include "cocos2d.h"
#include "vector"
#include "IParticleAnimationInterface.h"

USING_NS_CC;

class ParticleAnimation
{
	struct OneParticleSpritesInfo
	{
		std::string spriteName;
		CCPoint offsetPoint;
		OneParticleSpritesInfo():spriteName(""),offsetPoint(CCPointZero){

		}
	};
public:
	ParticleAnimation(const char* fileName);
	virtual ~ParticleAnimation();

	void update(float deletaTime);

	virtual void play(unsigned int nLoop,bool bLoop);
	virtual void playAtOneFrame(unsigned int nFrame);
	virtual void pause();
	virtual void resume();

	std::string getParticleSpriteName()
	{
		return m_particleSpriteName;
	}
	CCPoint getParticleSpriteOffsetPoint()
	{
		return m_offsetSpirtePoint;
	}
private:
	void init();
	void reset();
private:
	bool m_bLoop;
	bool m_bPause;
	unsigned int m_nTotalFrames;
	unsigned int m_nLoopCount;
	float m_currentFrame;
	float m_currentPrecent;
	std::string m_rcsFileName;
	const static int ANIMATION_FRAMES_PER_SEC = 24;
	std::vector<OneParticleSpritesInfo> m_vecParticleSpritesInfo;

	// Note: outter 
	std::string m_particleSpriteName;
	CCPoint m_offsetSpirtePoint;
};

#endif	// _PARTICLE_ANIMATION_H_