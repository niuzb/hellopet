#include "BoneParticle.h"
#include "Particle/ParticleManager.h"

BoneParticle::BoneParticle(unsigned int animTypeId,unsigned int nLoop,bool isLoop):
	SpriteBase(animTypeId),
	onePropInstance(NULL)
{
	//this->eParticleType = particleType;
	this->nLoop = nLoop;
	this->isParticleLoop = isLoop;
}

BoneParticle::~BoneParticle()
{
}

void BoneParticle::animationHandler(const char* _aniType, const char* _aniID, const char* _frameID)
{
	SpriteBase::animationHandler(_aniType,_aniID,_frameID);
	if (onePropInstance)
	{
		onePropInstance->animationHandler(this,_aniType,_aniID,_frameID);
	}
	
}