#include "ParticleManager.h"
#include "Particle/BoneAniParticle/BoneParticle.h"
#include "BoneAniManager/SkeletonAnimCommonDefine.h"
#include "Particle/BoneAniParticle/LocalExplosionParticle.h"

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
}

BoneParticle* ParticleManager::CreateOneBoneParticle(unsigned int animTypeId,unsigned int nLoop /* = 0 */,bool isLoop /* = true */)
{
	BoneParticle* pParticle = new BoneParticle(animTypeId,nLoop,isLoop);
	CCAssert(pParticle != NULL,"pParticle != NULL");
	pParticle->autorelease();
	//pParticle->PlayOneAnimation(kType_ANI_Action_Play,nLoop,isLoop);
	return (pParticle);
}