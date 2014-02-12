#include "SpriteDecorationBatchNode.h"
#include "GameResourceManager.h"
#include "CommonUtils.h"
#include "GameManager/CommonLookUpUtils.h"
#include "Sprite/SpriteHeroBase.h"
#include "Layers/Game/LayerCommonEnum.h"

BloodBar::BloodBar()
	:m_bgFrame(NULL)
	,m_frFrame(NULL)
	,m_fDefaultXScale(0)
{
}

BloodBar::~BloodBar()
{
	if (m_bgFrame)
	{
		CCNode* pParent = m_bgFrame->getParent();
		if (pParent)
		{
			pParent->removeChild(m_bgFrame);
		}
	}
	if (m_frFrame)
	{
		CCNode* pParent = m_frFrame->getParent();
		if (pParent)
		{
			pParent->removeChild(m_frFrame);
		}		
	}
}

void BloodBar::update(CCNode* pNode)
{
	if (pNode)
	{
		SpriteHeroBase* pHero = dynamic_cast<SpriteHeroBase*>(pNode);
		if (pHero)
		{
			CCPoint pt = pHero->getPosition();
			pt.y += 100;

			m_bgFrame->setPosition(pt);

			CCSize bgFrameSize = m_bgFrame->getContentSize();
			if (pHero->GetBattleSide() == SpriteHeroBase::LEFT)
			{
				m_frFrame->setPosition(ccp(pt.x-bgFrameSize.width/2,pt.y));
			}
			else
			{
				m_frFrame->setPosition(ccp(pt.x+bgFrameSize.width/2,pt.y));
			}
		}
	}
}

void BloodBar::SetBloodPercentage(float percentage)
{
	if (m_frFrame)
	{
		if (percentage < 0)
		{
			percentage = 0;
		}
		else if (percentage > 1)
		{
			percentage = 1;
		}

		m_frFrame->setScaleX(m_fDefaultXScale * percentage);
	}
}

void BloodBar::setVisible(bool visible)
{
	if (m_frFrame)
	{
		m_frFrame->setVisible(visible);
	}
	if (m_bgFrame)
	{
		m_bgFrame->setVisible(visible);
	}
}

SpriteDecorationBatchNode::SpriteDecorationBatchNode()
	: m_batchNode(NULL)
	, m_shadowBatchNode(NULL)
{
	m_parentNode = (CCNode*)(CommonLookUpUtils::GetBattleLayer());	
}

SpriteDecorationBatchNode::~SpriteDecorationBatchNode()
{
	for (std::map<CCNode*,BloodBar*>::iterator iter = m_playerBloodBars.begin();
		iter != m_playerBloodBars.end(); iter++)
	{
		if ((*iter).second)
		{
			delete (*iter).second;
		}
	}
	m_playerBloodBars.clear();

	if (m_batchNode)
	{
		m_batchNode->removeFromParent();
		m_batchNode = NULL;
	}
	if (m_shadowBatchNode)
	{
		m_shadowBatchNode->removeFromParent();
		m_shadowBatchNode = NULL;
	}
}

void SpriteDecorationBatchNode::LoadAttachRcs()
{
	std::string pListFilePath = 
		GameResourceManager::sharedManager()->storedFullPathFromRelativePath(
		CommonUtils::StringAppendMethod("UI/battle_ui",".plist").c_str());
	std::string pngFilePath = 
		GameResourceManager::sharedManager()->storedFullPathFromRelativePath(
		CommonUtils::StringAppendMethod("UI/battle_ui",".png").c_str());

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pListFilePath.c_str(),pngFilePath.c_str());

	if (m_parentNode)
	{
		m_batchNode = CCSpriteBatchNode::create(pngFilePath.c_str());
		m_parentNode->addChild(m_batchNode,Z_ORDER_BATTLE_HERO_BLOOD);

		m_shadowBatchNode = CCSpriteBatchNode::create(pngFilePath.c_str());
		m_parentNode->addChild(m_shadowBatchNode,Z_ORDER_BATTLE_HERO_SHADOW);
	}
}

BloodBar* SpriteDecorationBatchNode::CreateBloodBar(CCNode* pNode)
{		
	BloodBar* pBloodBar = NULL;
	if (pNode)
	{
		std::map<CCNode*,BloodBar*>::iterator iter = m_playerBloodBars.find(pNode);
		if (iter == m_playerBloodBars.end())
		{
			SpriteHeroBase* pHeroNode = dynamic_cast<SpriteHeroBase*>(pNode);
			if (pHeroNode)
			{
				pBloodBar = new BloodBar();
				pBloodBar->m_bgFrame =  CCSprite::createWithSpriteFrameName("monster_blood_frame.png");
				pBloodBar->m_frFrame =  CCSprite::createWithSpriteFrameName("monster_blood_piece.png");
				if (pBloodBar->m_bgFrame && pBloodBar->m_frFrame)
				{
					m_batchNode->addChild(pBloodBar->m_bgFrame);
					m_batchNode->addChild(pBloodBar->m_frFrame);
					if (pHeroNode->GetBattleSide() == SpriteHeroBase::LEFT)
					{
						pBloodBar->m_frFrame->setAnchorPoint(ccp(0,0.5));
					}					
					else
					{
						pBloodBar->m_frFrame->setAnchorPoint(ccp(1,0.5));
					}

					CCSize bgFrameSize = pBloodBar->m_bgFrame->getContentSize();
					CCSize frFrameSize = pBloodBar->m_frFrame->getContentSize();
					pBloodBar->m_fDefaultXScale = bgFrameSize.width / frFrameSize.width;
					pBloodBar->m_frFrame->setScaleX(pBloodBar->m_fDefaultXScale);
					pBloodBar->m_frFrame->setScaleY(bgFrameSize.height / frFrameSize.height);

					m_playerBloodBars.insert(std::make_pair(pNode,pBloodBar));
				}
				else
				{
					CC_SAFE_DELETE(pBloodBar);
				}
			}
		}
		else
		{
			CCError("SpriteDecorationBatchNode::CreateOneBloodBar repeat key");
		}
	}
	return pBloodBar;
}

void SpriteDecorationBatchNode::RemoveBloodBar(CCNode* pNode)
{
	if (pNode)
	{
		std::map<CCNode*,BloodBar*>::iterator iter = m_playerBloodBars.find(pNode);
		if (iter != m_playerBloodBars.end())
		{
			if ((*iter).second)
			{
				delete (*iter).second;
			}
			m_playerBloodBars.erase(iter);
		}
	}
}

CCSprite* SpriteDecorationBatchNode::CreateShadow(CCNode* pNode)
{
	CCSprite* pShadowSprite = NULL;
	if (pNode)
	{
		std::map<CCNode*,CCSprite*>::iterator iter = m_playerShadows.find(pNode);
		if (iter == m_playerShadows.end())
		{
			pShadowSprite =  CCSprite::createWithSpriteFrameName("shadow.png");
			if (pShadowSprite)
			{
				m_shadowBatchNode->addChild(pShadowSprite);
				m_playerShadows.insert(std::make_pair(pNode,pShadowSprite));
			}
		}
		else
		{
			CCError("SpriteDecorationBatchNode::CreateShadow repeat key");
		}
	}
	return pShadowSprite;
}

void SpriteDecorationBatchNode::RemoveShadow(CCNode* pNode)
{
	if (pNode)
	{
		std::map<CCNode*,CCSprite*>::iterator iter = m_playerShadows.find(pNode);
		if (iter != m_playerShadows.end())
		{
			CCSprite* pShadowSprite = (*iter).second;
			if (pShadowSprite)
			{
				CCNode* pParentNode = pShadowSprite->getParent();
				if (pParentNode)
				{
					pParentNode->removeChild(pShadowSprite);
				}
			}
			m_playerShadows.erase(iter);
		}
	}
}