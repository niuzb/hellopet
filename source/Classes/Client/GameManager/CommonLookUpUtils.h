#ifndef _COMMON_LOOKUP_UTILS_H_
#define _COMMON_LOOKUP_UTILS_H_

class SpriteHero;
class BattleLayer;
class BattleManager;

class CommonLookUpUtils
{
public:
	static BattleLayer* GetBattleLayer();
	static BattleManager* GetBattleManager();
};

#endif	//_COMMON_LOOKUP_UTILS_H_