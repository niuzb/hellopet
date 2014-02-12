#ifndef _SPRITE_CREATOR_FACTORY_H_
#define _SPRITE_CREATOR_FACTORY_H_

#include "Singleton_t.h"
#include "SpriteHero.h"
#include "SpriteOthHero.h"
#include "SkeletonAnimRcsManager.h"

class SpriteCreatorFactory:public TSingleton<SpriteCreatorFactory>
{
public:
	SpriteCreatorFactory();
	virtual ~SpriteCreatorFactory();

	SpriteHero* CreateOneRoleByID(int typeId);
	SpriteOthHero* CreateOneOthRoleByID(int typeId);
};

#endif //_SPRITE_CREATOR_FACTORY_H_