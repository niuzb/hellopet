#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_

#include "Singleton_t.h"
#include "Particle/ParticleDefine.h"
#include "Particle/BoneAniParticle/BoneParticle.h"
#include "map"

/// <summary>
//	����������Ч��ϵͳ����Ч����
/// </summary>
class ParticleManager:public TSingleton<ParticleManager>
{
public:
	ParticleManager();
	~ParticleManager();

	BoneParticle* CreateOneBoneParticle(unsigned int animTypeId,unsigned int nLoop = 0,bool isLoop = true);
	// Note: �����Ӵ洢�б���ɾ��һ����Ч
	//void RemoveOneBoneFromStorage(BoneParticle* pParticle);
private:
	//std::map<BoneParticle*,EParticleType> mapParticles;
};

#endif	// _PARTICLE_MANAGER_H_