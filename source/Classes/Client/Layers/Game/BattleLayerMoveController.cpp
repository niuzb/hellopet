#include "BattleLayerMoveController.h"
#include "BattleLayer.h"

BattleLayerMoveController::BattleLayerMoveController(CCLayer* pLayer)
	: m_battleLayer(pLayer)
	, m_isStartMove(false)
	, m_distance(0.0f)
{
	m_mapRealSize = CCSizeMake(0,0);
}

BattleLayerMoveController::~BattleLayerMoveController()
{
}

void BattleLayerMoveController::update(float dt)
{
	// Note: 更新Layer的移动
	if (m_battleLayer)
	{
		if(m_distance > 0.0f)
		{
			//CCPoint nowPos = m_battleLayer->getPosition();
			CCPoint nowPos = CCDirector::sharedDirector()->getLevelRenderCameraPos();		
			float deltaX = m_fMoveSpeed * dt;
			m_distance -= fabs(deltaX);
			CCPoint newPos = ccp(nowPos.x + deltaX,nowPos.y);
			if(newPos.x >= 0.0f && newPos.x <= m_mapRealSize.width - CCDirector::sharedDirector()->getRenderSize().width)
			{
				CCDirector::sharedDirector()->setLevelRenderCameraPos(newPos);
			}
		}
	}
}

bool BattleLayerMoveController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void BattleLayerMoveController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (pTouch && m_battleLayer)
	{
		{
			//CCPoint preOldTouchPos = pTouch->getPreviousLocation();
			//CCPoint nowTouchPos = pTouch->getLocation();

			CCPoint preOldTouchPos = pTouch->getPreviousLocationInView();
			preOldTouchPos = CCDirector::sharedDirector()->convertToGL(preOldTouchPos);

			CCPoint nowTouchPos = pTouch->getLocationInView();
			nowTouchPos = CCDirector::sharedDirector()->convertToGL(nowTouchPos);

			BattleLayer* pbtLayer = dynamic_cast<BattleLayer*>(m_battleLayer);
			if(pbtLayer)
			{
				preOldTouchPos = pbtLayer->ConvertUIPointToMap(preOldTouchPos);
				nowTouchPos = pbtLayer->ConvertUIPointToMap(nowTouchPos);

			}
			

			CCPoint deltaPt = ccpSub(preOldTouchPos, nowTouchPos);
			if (fabs(deltaPt.x) < 1)
			{
				return ;
			}
			/*CCPoint layerOldPos = m_battleLayer->getPosition();
			CCPoint layerNewPos = ccp(layerOldPos.x + deltaPt.x,layerOldPos.y);*/
			CCPoint oldPos = CCDirector::sharedDirector()->getLevelRenderCameraPos();
			CCPoint newPos = ccp(oldPos.x + deltaPt.x,oldPos.y);
			//float minXPos = CCDirector::sharedDirector()->getRenderSize().width - m_mapRealSize.width;
			if(newPos.x < 0.0f)
			{
				newPos.x = 0.0f;
			}
			else if(newPos.x > m_mapRealSize.width - CCDirector::sharedDirector()->getRenderSize().width)
			{
				newPos.x = m_mapRealSize.width - CCDirector::sharedDirector()->getRenderSize().width;
			}
			
			m_distance = fabs(newPos.x - oldPos.x);

			if (deltaPt.x < 0)
			{
				m_fMoveSpeed = fabs((double)m_fMoveSpeed);
				m_fMoveSpeed = -m_fMoveSpeed;
			}
			else
			{
				m_fMoveSpeed = fabs((double)m_fMoveSpeed);
			}
		}
	}
}

void BattleLayerMoveController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}