#include "BattleUISkillIconPanel.h"
#include "GameManager/CommonLookUpUtils.h"
#include "GameManager/BattleManger.h"
#include "Sprite/SpriteDefiner.h"
#include "BattleUILayer.h"
#include "Props/PropsTriggerManager.h"
#include "Layers/UI/UIManager.h"
#include "Props/PropManager.h"

BattleUISkillIconPanel::BattleUISkillIconPanel(CCLayer* parentLayer,UILayer* uiLayer,Layout* layout):
	UIPanelEventDelegateInterface(parentLayer,uiLayer,layout),
	m_touchEvent(NULL),
	m_propTrigger(NULL)
{
}

BattleUISkillIconPanel::~BattleUISkillIconPanel()
{
	PropsTriggerManager::Destroy();
}

void BattleUISkillIconPanel::Init()
{
	if (m_layout != NULL && m_uiLayer != NULL && m_parentLayer != NULL)
	{
		// Note: 注册回调函数
		int SkillIconNums = 3;
		for (int index = 0;index < SkillIconNums;index++)
		{
			char headIconNameBuffer[100];
			sprintf(headIconNameBuffer,"ButtonSkill0%d",index+1);
			UIButton* btn = dynamic_cast<UIButton*>(m_uiLayer->getWidgetByName(headIconNameBuffer)); 
			if (btn)
			{
				equipOneSkillBtnIcon(btn,index);
				btn->addPushDownEvent(this,SEL_PushEvent(&BattleUISkillIconPanel::onSkillPanelOneBtnClickedEvent));
				btn->setTouchEnabled(true);
			}
		}

		// Note: 加载道具的Trigger资源
		PropsTriggerManager::Get()->LoadAttachRcs();
		PropsTriggerManager::Get()->AddBatchNodes(m_parentLayer,1);
	}
}

void BattleUISkillIconPanel::equipOneSkillBtnIcon(UIButton* pBtn,int index)
{
}

void BattleUISkillIconPanel::onSkillPanelOneBtnClickedEvent(CCObject* pSender)
{
	UIWidget* pWidget = dynamic_cast<UIWidget*>(pSender);
	if (pWidget)
	{
		const char* name = pWidget->getName();
		if (name)
		{
			CCLog("click one btn %s",name);
			unsigned int btnIndex = 0;
			sscanf(name,"ButtonSkill0%d",&btnIndex);

			if (m_touchEvent)
			{
				CCPoint pt = m_parentLayer->convertTouchToNodeSpace(m_touchEvent);
				PropsType propType = kType_Prop_Type_UnKnow;
				switch (btnIndex)
				{
				case 1:
					propType = kType_Prop_LOCAL_ICE_EXPLOSION;
					break;
				case 2:
					propType = kType_Prop_LOCAL_CROSS_EXPLOSION;
					break;
				case 3:
					propType =  kType_Prop_ROUND_BOMB;
					break;
				case 4:
					propType = kType_Prop_DROP_FIRE_BALL;
					break;
				default:
					break;
				}
				PropTriggerBase* propTrigger = PropsTriggerManager::Get()->AddPropTrigger(propType,true);
				if (propTrigger)
				{
					//m_parentLayer->addChild(propTrigger);
					propTrigger->setPosition(pt);
					m_propTrigger = propTrigger;
					m_propTrigger->setScale(UIManager::Get()->GetMapScaleFactor());
				}				
			}
		}
	}	
}

bool BattleUISkillIconPanel::ccTouchBegan(CCTouch *pTouches, CCEvent *pEvent)
{
	m_touchEvent = pTouches;
	return true;
}

void BattleUISkillIconPanel::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_touchEvent && m_propTrigger && m_parentLayer)
	{
		CCPoint pt = m_parentLayer->convertTouchToNodeSpace(pTouch);
		m_propTrigger->setPosition(pt);
	}
}

void BattleUISkillIconPanel::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (m_touchEvent && m_propTrigger)
	{
		BattleLayer* pBattleLayer = CommonLookUpUtils::GetBattleLayer();
		if (pBattleLayer)
		{
			BattleManager* pBattleMgr = pBattleLayer->GetBattleManager();
			if (pBattleMgr)
			{
				CCPoint pt = pBattleLayer->ConvertTouchToMap(pTouch);
				PropsType propType = m_propTrigger->GetPropType();
				//pBattleMgr->AddOnePropToBattle(pBattleLayer,propType,pt);
				PropBase* pProp = PropManager::Get()->AddOneProp(propType,NULL,pBattleLayer,false,true);
				if (pProp)
				{
					pProp->UseProp(pt);
				}
			}
		}
		m_propTrigger->destroy();
		m_propTrigger = NULL;
		m_touchEvent = NULL;
		m_propTrigger = NULL;
	}
}