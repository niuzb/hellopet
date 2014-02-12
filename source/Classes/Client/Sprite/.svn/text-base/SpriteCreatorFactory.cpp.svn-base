#include "SpriteCreatorFactory.h"

SpriteCreatorFactory::SpriteCreatorFactory()
{
}

SpriteCreatorFactory::~SpriteCreatorFactory()
{
}

SpriteHero* SpriteCreatorFactory::CreateOneRoleByID(int typeId)
{
	SpriteHero* sprite = new SpriteHero(typeId);	
	CCAssert(sprite != NULL,"SpriteCreatorFactory::CreateOneRoleByID NULL");
	sprite->autorelease();
	return sprite;
}

SpriteOthHero* SpriteCreatorFactory::CreateOneOthRoleByID(int typeId)
{
	SpriteOthHero* sprite = new SpriteOthHero(typeId);	
	CCAssert(sprite != NULL,"SpriteCreatorFactory::CreateOneRoleByID NULL");
	sprite->autorelease();
	return sprite;
}