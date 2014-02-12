#ifndef _SCENE_CREATOR_H_
#define _SCENE_CREATOR_H_

#include "Singleton_t.h"
#include "SpriteBase.h"
#include "ShapeCreaterFactory.h"

#include "cocos2d.h"

USING_NS_CC;

class SceneCreator : public TSingleton<SceneCreator>
{
public:
	SceneCreator();
	~SceneCreator();

	void update(float dt);
	void draw();

	void SetParentNode(CCNode* parentNode);
	void SetHeroDistanceToLeftScreen(float distance){
		mHeroDistanceToLeftScreen = distance;
		ShapeCreaterFactory::Get()->SetHeroDistanceToRightScreen(distance);
	}
private:
	void updateHeroPos(float dt);
	void updateCameraByHero();
private:
	CCPoint mHeroPos;
	CCPoint mHeroVec;

	CCNode* mParentNode;

	float mHeroDistanceToLeftScreen;
};

#endif	// _SCENE_CREATOR_H_