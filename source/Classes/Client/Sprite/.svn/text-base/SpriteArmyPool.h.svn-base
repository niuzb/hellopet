#ifndef _SPRITE_ARMY_POOL_H
#define _SPRITE_ARMY_POOL_H

#include "Singleton_t.h"
#include "vector"
#include "map"
#include "SpriteBase.h"
#include "Sprite/SpriteHero.h"
#include "Sprite/SpriteDefiner.h"

class SpriteArmyPool : public TSingleton<SpriteArmyPool>
{
public:
	struct OneSpriteState
	{
		SpriteHero* pSprite;
		// Note: nState 0表示可用 1表示已经使用
		unsigned int nState;
		OneSpriteState(){
			pSprite = NULL;
			nState = 0;
		}
	};
	struct SpriteStates
	{
		unsigned int usedCount;
		unsigned int sumCount;
		unsigned int notUsedCount;
		std::vector<OneSpriteState> vecSpriteState;
		SpriteStates()
		{
			usedCount = 0;
			sumCount = 0;
			notUsedCount = 0;
		}
	};
public:
	SpriteArmyPool();
	virtual ~SpriteArmyPool();

	void Reset();

	void AddOneTypeSprite(unsigned int typeId);
	SpriteHero* CreateOneArmy(unsigned int typeId);
	void DestroyOneArmy(SpriteHero* pSprite);
private:
	static const int PRE_LOAD_SPRITE_NUM = 5;
	static const int MAX_SPRITE_NUM = 10;
	std::map<unsigned int,SpriteStates > mapArmys;
};

#endif	//_SPRITE_ARMY_POOL_H