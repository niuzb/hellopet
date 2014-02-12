#include "LocalExplosionParticle.h"

LocalExplosionParticle::LocalExplosionParticle(unsigned int animTypeId,EParticleType particleType,unsigned int nLoop,bool isLoop):
	BoneParticle(animTypeId,nLoop,isLoop)
{

}

LocalExplosionParticle::~LocalExplosionParticle()
{
}

void LocalExplosionParticle::animationHandler(const char* _aniType, const char* _aniID, const char* _frameID)
{
	if (false == isParticleLoop)
	{
		if (0 == strcmp(_aniType,"loopComplete") ||
			0 == strcmp(_aniType,"complete"))
		{
			this->removeFromParent();
		}
	}
}