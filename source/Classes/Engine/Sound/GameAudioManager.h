#ifndef _GAME_AUDIO_MANAGER_H_
#define _GAME_AUDIO_MANAGER_H_

#include "Singleton_t.h"
#include "map"
#include "vector"
#include "SoundConfigDataCenter.h"

class GameAudioManager : public TSingleton<GameAudioManager>
{
public:
	GameAudioManager();
	~GameAudioManager();

	bool PlayOneBgMusic(unsigned int id,const char* fileSuffix = ".mp3");
	bool PlayOneEffect(unsigned int id,const char* fileSuffix = ".mp3");
	bool PlayOneEffectInBattle(unsigned int id,const char* fileSuffix = ".mp3");
	void SetBgVolume(float value);
	void SetEffectVolume(float value);

	// Note: 预加载所有的背景音乐和音效
	void PreLoadAllNeedMusic(unsigned int bgMusicId,const std::vector<unsigned int>& effectMusicIds);

	bool IsBattleEffectPlaying(unsigned int id);

	void Update(float dt);
protected:
	std::string getBgMusicPath(unsigned int id,const char* fileSuffix = ".mp3");
	std::string getEffectMusicPath(unsigned int id,const char* fileSuffix = ".mp3");
private:
	float backGroundVolume;
	float effectVolume;
	std::map<unsigned int,SoundData> mapSoundInBattle;
};

#endif	//_GAME_AUDIO_MANAGER_H_