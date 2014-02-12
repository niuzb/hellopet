#ifndef _BONE_PARTICLE_H_
#define _BONE_PARTICLE_H_

#include "Sprite/SpriteBase.h"
#include "Particle/ParticleDefine.h"
#include "Props/PropBase.h"

class BoneParticle : public SpriteBase
{
public:
	//BoneParticle(unsigned int animTypeId,EParticleType particleType,unsigned int nLoop,bool isLoop);
	BoneParticle(unsigned int animTypeId,unsigned int nLoop,bool isLoop);
	virtual ~BoneParticle();

	//EParticleType GetParticleType(){
	//	return eParticleType;
	//}
	unsigned int GetParticleLoopCounts(){
		return nLoop;
	}
	bool GetIsParticleLoop(){
		return isParticleLoop;
	}
	void SetUserProp(PropBase* pProp){
		onePropInstance = pProp;
	}

	virtual void animationHandler(const char* _aniType, const char* _aniID, const char* _frameID);
protected:
	//EParticleType eParticleType;
	unsigned int nLoop;
	bool	isParticleLoop;
	PropBase* onePropInstance;
};

#endif	// _BONE_PARTICLE_H_