#ifndef _SOUND_CONFIG_DATA_CENTER_H_
#define _SOUND_CONFIG_DATA_CENTER_H_

#include "map"
#include "set"
#include "string"
#include "Props/PropsDefiner.h"
#include "Singleton_t.h"

struct SoundData{	
	unsigned int soundId;
	float lastTimer;
	float runningTimer;
	SoundData(){		
		soundId = 0;
		lastTimer = 0;
		runningTimer = 0;
	}
};

class SoundConfigDataCenter : public TSingleton<SoundConfigDataCenter>
{
public:
	SoundConfigDataCenter();
	~SoundConfigDataCenter();

	void ReadData();
	bool GetOneSoundData(unsigned int soundId,SoundData &data);
private:
	std::map<unsigned int,SoundData> mapSoundData;
};

#endif	//_SOUND_CONFIG_DATA_CENTER_H_