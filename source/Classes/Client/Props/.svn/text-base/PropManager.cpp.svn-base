#include "PropManager.h"
#include "LocalExplosionProp.h"
#include "FlySingleBombProp.h"
#include "AwayExplosionProp.h"
#include "RoundFlyBombProp.h"
#include "WithHeroProtectProp.h"

PropManager::PropManager():
	mIsDeleteOneElement(false)
{

}

PropManager::~PropManager()
{
	for (std::map<PropsType,PropBase*>::iterator iter = m_PreloadProps.begin();
		 iter == m_PreloadProps.end(); iter++)
	{
		(*iter).second->release();
	}
	m_PreloadProps.clear();
}

PropBase* PropManager::CreateOneProp(PropsType propType,SpriteBase* pUser,CCNode* pParentNode,bool isHero)
{
	PropBase* pProp = NULL;
	//if (pUser)
	{
		switch(propType)
		{
		case kType_Prop_LOCAL_ICE_EXPLOSION:
		case kType_Prop_LOCAL_CROSS_EXPLOSION:
			{
				pProp = new LocalExplosionProp(propType,pUser,pParentNode,isHero);
			}
			break;
		case kType_Prop_DROP_FIRE_BALL:
			{
				FlySingleBombProp* _pProp = new FlySingleBombProp(propType,pUser,pParentNode,isHero);
				if (_pProp)
				{
					_pProp->SetPropRunningTimer(5);
					_pProp->SetMoveSpeed(10);

					pProp = _pProp;
				}				
			}
			break;
		case kType_Prop_AWAY_EXPLOSION:
			{
				AwayExplosionProp* _pProp = new AwayExplosionProp(propType,pUser,pParentNode,isHero);
				if (_pProp)
				{				
					pProp = _pProp;
				}
			}
			break;
		case kType_Prop_ROUND_BOMB:
			{
				RoundFlyBombProp* _pProp = new RoundFlyBombProp(propType,pUser,pParentNode,isHero);
				if (_pProp)
				{				
					_pProp->SetPropRunningTimer(5);
					_pProp->SetMoveSpeed(10);

					pProp = _pProp;
				}
			}
			break;
		case kType_Prop_WithHero_Protect:
			{
				if (false == IsOneTypePropBelongToOneRole(propType,pUser))
				{
					WithHeroProtectProp* _pProp = new WithHeroProtectProp(propType,pUser,pParentNode,isHero);
					if (_pProp)
					{
						_pProp->SetLastTimer(10);

						pProp = _pProp;
					}
				}
			}
			break;
		};
	}
	return pProp;
}

PropBase* PropManager::AddOneProp(PropsType propType,SpriteBase* pUser,CCNode* pParentNode,bool isHero,bool isPreload /* = false */)
{
	PropBase* pProp = NULL;
	if (isPreload)
	{
		std::map<PropsType,PropBase*>::iterator iter = m_PreloadProps.find(propType);
		if (iter == m_PreloadProps.end())
		{
			pProp = CreateOneProp(propType,pUser,pParentNode,isHero);
			pProp->SetIsDestroySelfWhenEnd(false);
			pProp->PreloadAnimRcs();
			m_PreloadProps.insert(std::make_pair(propType,pProp));
		}
		else
		{
			pProp = (*iter).second;
		}
	}
	else
	{
		pProp = CreateOneProp(propType,pUser,pParentNode,isHero);
		if (pProp)
		{
			pProp->SetIsDestroySelfWhenEnd(true);
			mVecProps.insert(pProp);
		}
	}
	return pProp;
}

bool PropManager::IsOneTypePropBelongToOneRole(PropsType propType,CCNode* pNode)
{
	if (pNode)
	{
		for (std::set<PropBase*>::iterator iter = mVecProps.begin();
			iter != mVecProps.end(); iter++)
		{
			if (propType == (*iter)->GetPropType())
			{
				if (pNode == (*iter)->GetUserSprite())
				{
					return true;
				}
			}
		}
	}
	return false;
}

void PropManager::RemoveOneProp(PropBase* pProp)
{
	if (pProp)
	{
		if (false == pProp->GetIsDestroySelfWhenEnd())
		{
			for (std::set<PropBase*>::iterator iter = mVecProps.begin();
				iter != mVecProps.end(); iter++)
			{
				if ((*iter) == pProp)
				{
					mVecProps.erase(iter);
					mIsDeleteOneElement = true;
					break;
				}
			}
		}
	}
}

void PropManager::Update(float dt)
{
	std::set<PropBase*>::iterator pre_iter = mVecProps.begin();
	for (std::set<PropBase*>::iterator iter = mVecProps.begin();
		iter != mVecProps.end(); )
	{				
		iter ++;
		(*pre_iter)->Update(dt);	 
		pre_iter = iter;
	}
}