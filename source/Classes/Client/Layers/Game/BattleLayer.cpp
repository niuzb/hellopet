#include "NetWork/OnlineNetworkManager.h"
#include "NetWork/MessageHandler.h"
#include "Engine/NetWork/cs_basic.pb.h"
#include "Engine/NetWork/cs_core.pb.h"
#include "Engine/NetWork/cs_battle.pb.h"
#include "Layers/Game/BattleLayer.h"
#include "SkeletonAnimRcsManager.h"
#include "SpriteBase.h"
#include "SpriteCreatorFactory.h"
#include "Map/MapDataCenter.h"
#include "CommonUtils.h"
#include "Map/MapDataCenter.h"
#include "Props/PropsTriggerManager.h"
#include "Sound/GameAudioManager.h"
#include "Timer/TimeSynchronizer.h"
#include "cocos-ext.h"
#include "cocos2d.h"
#include "CameraController.h"
#include "Layers/Game/LayerCommonEnum.h"
#include "math.h"
#include "Sprite/SpriteArmyPool.h"
#include "BattleLayerMoveController.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "PlayerController.h"
#include "SceneController.h"
USING_NS_CC;
USING_NS_CC_EXT;

BattleLayer::BattleLayer():
	battleManager(NULL),
	pTimerLabel(NULL),
	isStartTimerSync(false)
{
//	m_pBattleLayerMoveController = new BattleLayerMoveController(this);
//	if (m_pBattleLayerMoveController)
//	{
//		m_pBattleLayerMoveController->SetLayerMoveSpeed(800);
//	}
}

BattleLayer::~BattleLayer()
{
	// Note: ’Ω∂∑Ω· ¯∫Û Õ∑≈À˘”–µƒÕº∆¨◊ ‘¥
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();

	if (battleManager)
	{
		battleManager->RemoveAllHeroFromBattleAndCleanUp();
		CC_SAFE_DELETE(battleManager);
	}
	//CC_SAFE_DELETE(m_pBattleLayerMoveController);
	// Note: «Âø’∫Õ’Ω∂∑œ‡πÿµƒ ˝æ›
	//PropsTriggerManager::Get()->ClearAttachRcsData();
}

bool BattleLayer::init()
{
//	bool bRet = false;
//	do {
//		CC_BREAK_IF(! cocos2d::CCLayer::init());
//        ComponentsTestLayer *layer = ComponentsTestLayer::create();
//		CC_BREAK_IF(! layer);
//        
//        addChild(layer, 50);
//		bRet = true;
//	}while(0);
	
	
	bool bRet = false;
	do
	{
        CC_BREAK_IF(! CCLayer::init(  ) );
        
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 50, 50);
        
        root->getChildByTag(1)->addComponent(CCComAudio::create());
        root->getChildByTag(1)->addComponent(PlayerController::create());
        
        root->addComponent(CCComAudio::create());
        root->addComponent(CCComAttribute::create());
        root->addComponent(SceneController::create());
        this->setTouchEnabled(true);
        
        
        MessageHandler::sShareInstance()->registerMessageHandle(head_msg::CSEnterMapRsp,this);//  Ω¯»ÎµÿÕº
        MessageHandler::sShareInstance()->registerMessageHandle(head_msg::CSBattleMoveRsp,this);//  move rsp
        MessageHandler::sShareInstance()->registerMessageHandle(head_msg::CSBattleUserJoinRsp,this);//  ∆‰À˚ÕÊº“Ω¯»Î’Ω∂∑ rsp
        
        battleManager = new BattleManager();
        scheduleUpdate();
		bRet = true;
	} while (0);
    
	
	
	return bRet;
}

cocos2d::CCNode* BattleLayer::createGameScene()
{
    CCNode *root = NULL;
    do
	{
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
        
        
        CCSprite *player = CCSprite::create("Batch/Player.png", CCRectMake(0, 0, 27, 40) );
        
        player->setPosition( ccp(origin.x + player->getContentSize().width/2,
                                 origin.y + visibleSize.height/2) );
        
        root = cocos2d::CCNode::create();
        root->addChild(player, 1, 1);
        
        
//        CCMenuItemFont *itemBack = CCMenuItemFont::create("Back", this, menu_selector(ComponentsTestLayer::toExtensionsMainLayer));
//        itemBack->setColor(ccc3(0, 0, 0));
//        itemBack->setPosition(ccp(origin.x + visibleSize.width - 50, origin.y + 25));
//        CCMenu *menuBack = CCMenu::create(itemBack, NULL);
//        menuBack->setPosition(CCPointZero);
//        addChild(menuBack);
        
    }while (0);
    
    return root;
}

//convert 
bool BattleLayer::CreateLayerObjects()
{
	SpriteDecorationBatchNode::Get()->LoadAttachRcs();
	// Note: º”‘ÿ’Ω∂∑÷–“¿¿µµƒ◊ ‘¥	
	bool bMapSuc = createMap();
	//bool bHeroSuc = createHero();
	//bool bActorSuc = createActor();
	bool bPhysicalSuc = createPhysicalLayer();
	//bool bCreatePropTrigger = createPropTriggers();

	//SendEnterMapReq();
	GameAudioManager::Get()->PlayOneBgMusic(10000);

	//return bMapSuc && bHeroSuc && bActorSuc && bPhysicalSuc && bCreatePropTrigger;
	return bMapSuc;
}

bool BattleLayer::createMap()
{
	CCNode *pNode = CCSSceneReader::sharedSceneReader()->createNodeWithSceneFile("BattleScene01/Resources/SceneDemo.json");
	if (pNode != NULL)
	{
		this->addChild(pNode);

		int nBgSpriteTag = 10000;
		CCNode* pBgNode = dynamic_cast<CCNode*>(pNode->getChildByTag(nBgSpriteTag));
		if (pBgNode)
		{
			CCSprite* pSprite = dynamic_cast<CCSprite*>(pBgNode->getComponent("CCSprite")->getNode());
			if (pSprite)
			{
                CCSize mapSize = pSprite->getContentSize();
                SetMapRealSize(mapSize);
//
//				if (m_pBattleLayerMoveController)
//				{
//					CCSize mapSize = pSprite->getContentSize();
//					SetMapRealSize(mapSize);
//					m_pBattleLayerMoveController->SetMapRealSize(mapSize);
//				}
			}

			// Note: µ√µΩ”¢–€≥ˆ…˙µ„
			for (int index = 1;index <= 3;index++)
			{
				CCNode* startPtSprite = pBgNode->getChildByTag(index);
				if (startPtSprite)
				{
					CCSprite* pSprite = dynamic_cast<CCSprite*>(startPtSprite->getComponent("CCSprite")->getNode());
					if(pSprite)
					{
						pSprite->setOpacity(100);
						CCPoint pos = startPtSprite->getPosition();
						pos = startPtSprite->convertToWorldSpace(CCPointZero);
						pos = this->convertToNodeSpace(pos);
						CCSize size = pSprite->getContentSize();
						size.width *= startPtSprite->getScaleX();
						size.height *= startPtSprite->getScaleY();
						CCRect rect = CCRectMake(pos.x - size.width/2.0,pos.y - size.height/2.0,
							size.width,size.height);
						vecStartRects.push_back(rect);
					}
				}
			}
			// Note: º∆À„”¢–€ø…“∆∂Ø∑∂Œß
			float startPosX = vecStartRects[0].getMinX();
			float startPosY = vecStartRects[0].getMinY();
			float width = m_mapRealSize.width - startPosX * 2;
			float height = m_mapRealSize.height;
			SetHeroMoveRect(CCRectMake(startPosX,startPosY,width,height));

			// Note: µ√µΩ≥«±§µƒŒª÷√
			unsigned int castleTag = 4;
			CCNode* castlePtSprite = pBgNode->getChildByTag(castleTag);
			if (castlePtSprite)
			{
				CCSprite* pSprite = dynamic_cast<CCSprite*>(castlePtSprite->getComponent("CCSprite")->getNode());
				if(pSprite)
				{
					CCPoint pos = castlePtSprite->getPosition();
					pos = castlePtSprite->convertToWorldSpace(CCPointZero);
					pos = this->convertToNodeSpace(pos);
					CCSize size = pSprite->getContentSize();
					size.width *= castlePtSprite->getScaleX();
					size.height *= castlePtSprite->getScaleY();
					CCRect rect = CCRectMake(pos.x - size.width/2.0,pos.y - size.height/2.0,
						size.width,size.height);
					m_selfCastleRect = rect;

					float newPosX = m_mapRealSize.width - pos.x;
					rect = CCRectMake(newPosX - size.width/2.0,pos.y - size.height/2.0,
						size.width,size.height);
					m_othCastleRect = rect;
				}
			}
		}
	}
	return true;
}

bool BattleLayer::IsOnePointInStartRects(const CCPoint &pt,CCPoint & startPt,unsigned int &startIndex)
{
	startIndex = 0;
	for (std::vector<CCRect>::iterator iter = vecStartRects.begin();
		iter != vecStartRects.end(); iter++)
	{
		float minY = (*iter).getMinY();
		float maxY = (*iter).getMaxY();
		if (pt.y >= minY && pt.y <= maxY)
		{
			startPt = ccp((*iter).getMinX(),(*iter).getMidY());
			return true;
		}
		startIndex ++;
	}
	return false;
}

bool BattleLayer::createHero()
{
	if (NULL == battleManager)
	{
		return false;
	}

	return true;
}

bool BattleLayer::createActor()
{
	return true;
}

bool BattleLayer::createPhysicalLayer()
{
	if (NULL == battleManager)
	{
		return false;
	}

	battleManager->AddPhysicalLayerToBattle(this,m_mapRealSize,ccp(vecStartRects[0].getMinX(),vecStartRects[0].getMidY()));

	return true;
}

bool BattleLayer::createPropTriggers()
{
	if (NULL == battleManager)
	{
		return false;
	}

	battleManager->AddPropTriggersToBattle(this);

	return true;
}

BattleManager* BattleLayer::GetBattleManager()
{
	return battleManager;
}

void BattleLayer::registerWithTouchDispatcher()
{
//	CCDirector* pDirector = CCDirector::sharedDirector();
//	pDirector->getTouchDispatcher()->addTargetedDelegate(this, TOUCH_PRIORITY_BATTLE, true);
	//CCLayer::registerWithTouchDispatcher();
}

bool BattleLayer::ccTouchBegan(CCTouch *pTouches, CCEvent *pEvent)
{
//	if (m_pBattleLayerMoveController)
//	{
//		m_pBattleLayerMoveController->ccTouchBegan(pTouches,pEvent);
//	}
	return true;
}

void BattleLayer::ccTouchMoved(CCTouch *pTouches, CCEvent *pEvent)
{
//	if (m_pBattleLayerMoveController)
//	{
//		m_pBattleLayerMoveController->ccTouchMoved(pTouches,pEvent);
//	}

	return CCLayer::ccTouchMoved(pTouches,pEvent);
}

void BattleLayer::ccTouchEnded(CCTouch *pTouches, CCEvent *pEvent)
{
//	if (m_pBattleLayerMoveController)
//	{
//		m_pBattleLayerMoveController->ccTouchEnded(pTouches,pEvent);
//	}
	return CCLayer::ccTouchEnded(pTouches,pEvent);
}

void BattleLayer::update(float delta)
{
//	if (false == isStartTimerSync)
//	{
//		TimerSynchronizer::shareSynchronizer()->StartTimerSync();
//		isStartTimerSync = true;
//	}
	//if (TimerSynchronizer::shareSynchronizer()->IsTimerSyncOk())
	{
//		TimerSynchronizer::shareSynchronizer()->update(delta);
//		// Note: ‘⁄∆¡ƒª÷––ƒœ‘ æTime
//		char timeBuffer[100];
//		sprintf(timeBuffer,"time: %f",TimerSynchronizer::shareSynchronizer()->GetClientTimer());
//		if (pTimerLabel == NULL)
//		{
//			pTimerLabel = CCLabelTTF::create(timeBuffer,"Marker Felt",30);
//			CCSize wndSize = CCDirector::sharedDirector()->getWinSize();
//			pTimerLabel->setPosition(ccp(wndSize.width/2.0,wndSize.height/2.0));
//			pTimerLabel->setColor(ccc3(255,0,0));
//			this->addChild(pTimerLabel,100);
//		}
//		else
//		{
//			pTimerLabel->setString(timeBuffer);
//		}

		if (battleManager)
		{
			battleManager->Update(delta,this);
		}

//		if (m_pBattleLayerMoveController)
//		{
//			m_pBattleLayerMoveController->update(delta);
//		}
	}
}

void BattleLayer::SendEnterMapReq()
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance(head_msg::CSEnterMapReq);
	CSEnterMapReq  * bodyMsg = (CSEnterMapReq  *)msg;
	bodyMsg->set_mapid(1);
	bodyMsg->set_orient(1);
	bodyMsg->set_xpos(0);
	bodyMsg->set_ypos(0);

	KSendMessageResult result = OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, OnlineNetworkManager::PKG_TIMEOUT, NETWORK_TAG_ENTER_MAP, true, true);
}

void BattleLayer::HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg)
{
}

void BattleLayer::visit()
{
	// TODO : ”¶∏√∑≈µΩÕ‚√Êµƒ∏∏Ω⁄µ„…œ
	CCDirector::sharedDirector()->setRenderCameraForLevel();
	CCLayer::visit();
	CCDirector::sharedDirector()->setRenderCameraForUI();	
}

CCPoint BattleLayer::ConvertUIPointToMap(const cocos2d::CCPoint& uiPt)
{	
	CCSize winSize = CCDirector::sharedDirector()->getWinSizeInPixels();
	CCPoint newCenter = CCDirector::sharedDirector()->getLevelRenderCameraPos();

	CCSize renderSize = CCDirector::sharedDirector()->getRenderSize();
	CCPoint winPt;
	winPt.x = uiPt.x * renderSize.width / winSize.width;
	winPt.y = uiPt.y * renderSize.height / winSize.height;

	//CCPoint newPt = //ccpAdd(winPt, ccp(newCenter.x - winSize.width * 0.5, newCenter.y - winSize.height * 0.5));
	CCPoint newPt = ccpAdd(winPt, ccp(newCenter.x , newCenter.y));

	return newPt;
}

CCPoint BattleLayer::ConvertMapPointToUI(const cocos2d::CCPoint& mapPt)
{	
	CCSize winSize = CCDirector::sharedDirector()->getWinSizeInPixels();
	CCPoint newCenter = CCDirector::sharedDirector()->getLevelRenderCameraPos();
	CCSize renderSize = CCDirector::sharedDirector()->getRenderSize();

	//CCPoint newPt = ccpSub(mapPt, ccp(newCenter.x - renderSize.width * 0.5, newCenter.y - renderSize.height * 0.5));
	CCPoint newPt = ccpSub(mapPt, newCenter);

	newPt.x = newPt.x * winSize.width / renderSize.width;
	newPt.y = newPt.y * winSize.height / renderSize.height;

	return newPt;
}

CCPoint BattleLayer::ConvertTouchToMap(cocos2d::CCTouch* touch)
{
	CCPoint oldPT = touch->getLocationInView();
	oldPT = CCDirector::sharedDirector()->convertToGL(oldPT);
	CCPoint newPT = ConvertUIPointToMap(oldPT);
	return newPT;
}

bool BattleLayer::GetStartPointByIndex(unsigned int index,bool bSide,CCPoint &pt)
{
	unsigned int size = vecStartRects.size();
	if (index >= size)
	{
		return false;
	}
	CCRect rect = vecStartRects[index];
	if (bSide)
	{
		pt.x = rect.getMinX();
		pt.y = rect.getMidY();
	}
	else
	{
		pt.x = m_mapRealSize.width - rect.getMinX();
		pt.y = rect.getMidY();
	}
	return true;
}