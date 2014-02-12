#include "BattleUISmallMapPanel.h"
#include "GameManager/CommonLookUpUtils.h"
#include "GameManager/BattleManger.h"
#include "Sprite/SpriteDefiner.h"
#include "BattleUILayer.h"
#include "Layers/UI/UIManager.h"
#include "GameManager/NotificationCenterDefiner.h"

BattleUISmallMapPanel::BattleUISmallMapPanel(CCLayer* parentLayer,UILayer* uiLayer,Layout* layout):
	UIPanelEventDelegateInterface(parentLayer,uiLayer,layout),
	m_touchEvent(NULL),
	m_parentWidget(NULL)
{
	
}

BattleUISmallMapPanel::~BattleUISmallMapPanel()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,NotificationFlag[ENoticePlayerCreat]);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,NotificationFlag[ENoticePlayerDie]);
}

void BattleUISmallMapPanel::Init()
{
	if (m_layout != NULL && m_uiLayer != NULL && m_parentLayer != NULL)
	{
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(BattleUISmallMapPanel::playerCreaterEvent),
			NotificationFlag[ENoticePlayerCreat],NULL);
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(BattleUISmallMapPanel::playerDieEvent),
			NotificationFlag[ENoticePlayerDie],NULL);

		// Note: 得到玩家可移动Rect
		BattleLayer* pBattleLayer = CommonLookUpUtils::GetBattleLayer();
		if (pBattleLayer)
		{
			m_battleHeroMoveRect = pBattleLayer->GetHeroMoveRect();
		}

		m_parentWidget = dynamic_cast<UIImageView*>(m_uiLayer->getWidgetByName("smallMap")); 
		// Note: 得到可视区域大小	
		UIImageView* pViewRect = dynamic_cast<UIImageView*>(m_uiLayer->getWidgetByName("viewRect")); 
		if (pViewRect)
		{
			CCSize size = pViewRect->getSize();
			m_smallMapHeroMoveRect = CCRectMake(pViewRect->getPosition().x - size.width/2,
				pViewRect->getPosition().y - size.height/2,size.width,size.height);
		}
	}
}

void BattleUISmallMapPanel::playerCreaterEvent(CCObject* pObj)
{
	if (pObj)
	{
		SpriteHeroBase* pHero = dynamic_cast<SpriteHeroBase*>(pObj);
		if (pHero)
		{
			UIImageView* dotImage = createDot(pHero->GetBattleSide());
			if (dotImage)
			{
				m_playerDots.insert(std::make_pair(pHero,dotImage));
			}
		}
	}	
}

void BattleUISmallMapPanel::playerDieEvent(CCObject* pObj)
{
	if (pObj)
	{
		SpriteHeroBase* pHero = dynamic_cast<SpriteHeroBase*>(pObj);
		if (pHero)
		{
			std::map<SpriteHeroBase*,UIImageView*>::iterator iter = m_playerDots.find(pHero);
			if (iter != m_playerDots.end())
			{
				(*iter).second->removeFromParent();
				m_playerDots.erase(iter);
			}
		}
	}
}

UIImageView* BattleUISmallMapPanel::createDot(SpriteHeroBase::SIDE side)
{
	UIImageView *dotImage = NULL;
	if (m_layout)
	{
		dotImage = UIImageView::create();
		if (dotImage)
		{
			if (side == SpriteHeroBase::LEFT)
			{
				dotImage->setTexture("icon/smallMapGreenDot.png",UI_TEX_TYPE_PLIST);
			}			
			else
			{
				dotImage->setTexture("icon/smallMagRedDot.png",UI_TEX_TYPE_PLIST);
			}			
			if (m_parentWidget)
			{
				m_parentWidget->addChild(dotImage);
			}
			else
			{
				return NULL;
			}
		}	
	}
	return dotImage;
}

bool BattleUISmallMapPanel::ccTouchBegan(CCTouch *pTouches, CCEvent *pEvent)
{
	m_touchEvent = pTouches;
	return true;
}

void BattleUISmallMapPanel::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void BattleUISmallMapPanel::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

bool BattleUISmallMapPanel::transformHeroPtToSmallMap(SpriteHeroBase* pHero,CCPoint& pt)
{
	bool bRet = false;
	if (pHero)
	{
		CCPoint heroPos = pHero->getPosition();
		CCPoint heroRelativePos = ccpSub(heroPos,m_battleHeroMoveRect.origin);
		float x = heroRelativePos.x / (m_battleHeroMoveRect.getMaxX() - m_battleHeroMoveRect.getMinX());
		float y = heroRelativePos.y / (m_battleHeroMoveRect.getMaxY() - m_battleHeroMoveRect.getMinY());
		float posx = x * (m_smallMapHeroMoveRect.getMaxX() - m_smallMapHeroMoveRect.getMinX());
		float posy = y * (m_smallMapHeroMoveRect.getMaxY() - m_smallMapHeroMoveRect.getMinY());
		posx += m_smallMapHeroMoveRect.origin.x;
		posy += m_smallMapHeroMoveRect.origin.y;
		pt.x = posx;
		pt.y = posy;
	}
	return bRet;
}

void BattleUISmallMapPanel::Update(float dt)
{
	for (std::map<SpriteHeroBase*,UIImageView*>::iterator iter = m_playerDots.begin();
		iter != m_playerDots.end(); iter++)
	{
		CCPoint pt;
		transformHeroPtToSmallMap((*iter).first,pt);
		(*iter).second->setPosition(pt);
	}	
}