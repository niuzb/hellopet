#ifndef _PARTICLE_FACTORY_H_
#define _PARTICLE_FACTORY_H_

#include "string"
#include "map"
#include "Singleton_t.h"
#include "SpriteParticle.h"

class ParticleFactory:public TSingleton<ParticleFactory>
{
	struct OneParticleInfo
	{
		unsigned int id;
		std::string fileName;
		OneParticleInfo():id(0){

		}
	};
public:
	ParticleFactory();
	~ParticleFactory();

	SpriteParticle* CreateParticle(unsigned int id);
private:
	void InitXML();
	std::map<unsigned int,OneParticleInfo> m_particleListInfo;
};

#endif	//_PARTICLE_FACTORY_H_