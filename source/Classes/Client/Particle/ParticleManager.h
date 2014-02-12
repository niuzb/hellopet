#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_

#include "Singleton_t.h"
#include "Particle/ParticleDefine.h"
#include "Particle/BoneAniParticle/BoneParticle.h"
#include "map"

/// <summary>
//	用来产生特效的系统，特效工厂
/// </summary>
class ParticleManager:public TSingleton<ParticleManager>
{
public:
	ParticleManager();
	~ParticleManager();

	BoneParticle* CreateOneBoneParticle(unsigned int animTypeId,unsigned int nLoop = 0,bool isLoop = true);
	// Note: 从粒子存储列表中删除一个特效
	//void RemoveOneBoneFromStorage(BoneParticle* pParticle);
private:
	//std::map<BoneParticle*,EParticleType> mapParticles;
};

#endif	// _PARTICLE_MANAGER_H_