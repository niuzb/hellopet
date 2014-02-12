#ifndef _SPRITE_DECORATION_BATCH_NODE_
#define _SPRITE_DECORATION_BATCH_NODE_

#include "cocos2d.h"
#include "map"
#include "set"
#include "Singleton_t.h"

USING_NS_CC;

class BloodBar
{
public:
	BloodBar();
	virtual ~BloodBar();		

	void update(CCNode* pNode);
	/**
	* Instruction : 设置血量的百分比 
	* @param : percentage 范围 0 - 1
	*/	
	void SetBloodPercentage(float percentage);

	void setVisible(bool visible);
public:
	CCSprite* m_bgFrame;
	CCSprite* m_frFrame;
	float m_fDefaultXScale;
};

class SpriteDecorationBatchNode : public TSingleton<SpriteDecorationBatchNode>
{
public:
	SpriteDecorationBatchNode();
	~SpriteDecorationBatchNode();

	BloodBar* CreateBloodBar(CCNode* pNode);
	void RemoveBloodBar(CCNode* pNode);

	CCSprite* CreateShadow(CCNode* pNode);
	void RemoveShadow(CCNode* pNode);

	void LoadAttachRcs();
private:
	CCSpriteBatchNode* m_batchNode;
	CCSpriteBatchNode* m_shadowBatchNode;
	CCNode* m_parentNode;
	// Note: 
	std::map<CCNode*,BloodBar*> m_playerBloodBars;
	std::map<CCNode*,CCSprite*> m_playerShadows;
};

#endif	//_SPRITE_DECORATION_BATCH_NODE_