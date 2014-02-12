#include "BattleUIArmyHeadIconPanel.h"
#include "GameManager/CommonLookUpUtils.h"
#include "GameManager/BattleManger.h"
#include "Sprite/SpriteDefiner.h"
#include "BattleUILayer.h"
#include "UIManager.h"
#include "NetWork/MessageHandler.h"
#include "NetWork/NetWorkUtil.h"
#include "NetWork/OnlineNetworkManager.h"

BattleUIArmyHeadIconPanel::BattleUIArmyHeadIconPanel(CCLayer* parentLayer,UILayer* uiLayer,Layout* layout):
	UIPanelEventDelegateInterface(parentLayer,uiLayer,layout),
	m_touchEvent(NULL),
	m_touchHero(NULL)
{
}

BattleUIArmyHeadIconPanel::~BattleUIArmyHeadIconPanel()
{
}

void BattleUIArmyHeadIconPanel::Init()
{
	if (m_layout != NULL && m_uiLayer != NULL && m_parentLayer != NULL)
	{
		// Note: ×¢²á»Øµ÷º¯Êý
		int ArmyHeadIconNums = 5;
		for (int index = 0;index < ArmyHeadIconNums;index++)
		{
			char headIconNameBuffer[100];
			sprintf(headIconNameBuffer,"ButtonHead0%d",index+1);
			UIButton* btn = dynamic_cast<UIButton*>(m_uiLayer->getWidgetByName(headIconNameBuffer)); 
			if (btn)
			{
				equipOneArmyBtnIcon(btn,index);
				btn->addPushDownEvent(this,SEL_PushEvent(&BattleUIArmyHeadIconPanel::onHeadPanelOneBtnClickedEvent));
				btn->setTouchEnabled(true);
			}
		}

		MessageHandler::sShareInstance()->registerMessageHandle(head_msg::CSMonsterCreateRsp,this);
	}
}

void BattleUIArmyHeadIconPanel::equipOneArmyBtnIcon(UIButton* pBtn,int index)
{
	if (pBtn)
	{
		char buffer[100];
		sprintf(buffer,"icon/armyHeadIcon_%d.PNG",index+1);		
		pBtn->setNormalTexture(buffer,UI_TEX_TYPE_PLIST);
		sprintf(buffer,"icon/armyHeadIconSelect_%d.PNG",index+1);
		pBtn->setPressedTexture(buffer,UI_TEX_TYPE_PLIST);
	}
}

void BattleUIArmyHeadIconPanel::onHeadPanelOneBtnClickedEvent(CCObject* pSender)
{
	if (m_touchHero == NULL)
	{
		UIWidget* pWidget = dynamic_cast<UIWidget*>(pSender);
		if (pWidget)
		{
			const char* name = pWidget->getName();
			if (name)
			{
				CCLog("click one btn %s",name);
				unsigned int btnIndex = 0;
				sscanf(name,"ButtonHead0%d",&btnIndex);

				if (m_touchEvent)
				{
					BattleLayer* pBattleLayer = CommonLookUpUtils::GetBattleLayer();
					if (pBattleLayer)
					{
						BattleManager* battleManager = pBattleLayer->GetBattleManager();
						if (battleManager)
						{
							CCPoint touchPt = m_parentLayer->convertTouchToNodeSpace(m_touchEvent);						
							unsigned int heroTypeId = 0;
							switch (btnIndex)
							{
							case 1:
								heroTypeId = 10001;
								break;
							case 2:
								heroTypeId = 10002;
								break;
							case 3:
								heroTypeId = 10003;
								break;
							case 4:
								heroTypeId = 10004;
								break;
							case 5:
								heroTypeId = 10005;
								break;
							default:
								break;
							}
							SpriteHero* pHero = battleManager->AddOneHeroToBattle(m_parentLayer,heroTypeId);
							if (pHero)
							{
								pHero->setScale(UIManager::Get()->GetMapScaleFactor());
								pHero->setPosition(touchPt);
								pHero->PlayOneAnimation(kTypeIdle_FaceHor_OTH,0,true);
								m_touchHero = pHero;
							}
						}
					}				
				}					
			}
		}	
	}
}

bool BattleUIArmyHeadIconPanel::ccTouchBegan(CCTouch *pTouches, CCEvent *pEvent)
{
	m_touchEvent = pTouches;
	return true;
}

void BattleUIArmyHeadIconPanel::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_touchHero && m_touchEvent)
	{
		CCPoint pt = m_parentLayer->convertTouchToNodeSpace(pTouch);
		m_touchHero->setPosition(pt);
	}
}

void BattleUIArmyHeadIconPanel::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_touchHero && m_touchEvent)
	{
		BattleLayer* pBattleLayer = CommonLookUpUtils::GetBattleLayer();
		if (pBattleLayer)
		{
			m_touchHero->retain();
			m_touchHero->removeFromParent();
			pBattleLayer->addChild(m_touchHero,1);
			m_touchHero->release();
			m_touchHero->ReSchedualArmature();
			//CCPoint pt = pBattleLayer->convertTouchToNodeSpace(m_touchEvent);
			CCPoint pt = pBattleLayer->ConvertTouchToMap(pTouch);			
			CCPoint startPt = CCPointZero;
			unsigned int startPos = 0;
			if (pBattleLayer->IsOnePointInStartRects(pt,startPt,startPos))
			{
				m_touchHero->setScale(1.0f);
				m_touchHero->setPosition(startPt);			
				m_touchHero->SetYPosInCell(startPos);
				sendHeroCreatorMsg(m_touchHero->GetHeroInfo().typeID,startPos);
			}
			else
			{
				m_touchHero->removeFromParent();				
				m_touchHero = NULL;
			}
		}
		
		m_touchEvent = NULL;
	}
}

void BattleUIArmyHeadIconPanel::sendHeroCreatorMsg(unsigned int id,unsigned int pos)
{
	Message* msg = MessageUtil::sShareInstance()->createMessageInstance(head_msg::CSMonsterCreateReq);
	CSMonsterCreateReq  * bodyMsg = dynamic_cast<CSMonsterCreateReq  *>(msg);	
	if (bodyMsg)
	{
		bodyMsg->set_id(id);
		CSPoint* p = bodyMsg->mutable_pos();
		p->set_xpos(0);
		p->set_ypos(pos);
	}

	KSendMessageResult result = OnlineNetworkManager::sShareInstance()->sendMessage(bodyMsg, OnlineNetworkManager::PKG_TIMEOUT, NETWORK_TAG_HERO_CREATE, true, true);
}

void BattleUIArmyHeadIconPanel::HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg)
{
	switch(cmd)
	{
	case head_msg::CSMonsterCreateRsp :
		{
			CSMonsterCreateRsp* _msg = dynamic_cast<CSMonsterCreateRsp*>(msg->msg);
			if (_msg)
			{
				if (_msg->side())
				{
					if (m_touchHero)
					{
						m_touchHero->SetId(_msg->id_in_map());
						m_touchHero->StartStateMachine();
						m_touchHero->SetBattleSide(SpriteHeroBase::LEFT);
						m_touchHero = NULL;
					}
				}
				else
				{
					BattleLayer* pBattleLayer = CommonLookUpUtils::GetBattleLayer();
					if (pBattleLayer)
					{
						BattleManager* battleManager = pBattleLayer->GetBattleManager();
						if (battleManager)
						{
							SpriteOthHero* pHero = battleManager->AddOneOthHeroToBattle(pBattleLayer,_msg->id());
							if (pHero)
							{
								CCPoint startPt;
								if (pBattleLayer->GetStartPointByIndex(_msg->pos().ypos(),false,startPt))
								{
									pHero->SetId(_msg->id_in_map());
									pHero->SetYPosInCell(_msg->pos().ypos());
									pHero->SetAnimFlipX(false);
									pHero->setScale(1.0f);
									pHero->setPosition(startPt);
									pHero->SetBattleSide(SpriteHeroBase::RIGHT);
									pHero->StartStateMachine();
								}
								else
								{
									pHero->removeFromParent();
									pHero = NULL;
								}
							}
						}
					}
				}
			}
		}
		break;
	};
}