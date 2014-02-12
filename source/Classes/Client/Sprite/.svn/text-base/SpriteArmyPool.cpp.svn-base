#include "SpriteArmyPool.h"
#include "GameResourceManager.h"
#include "SkeletonAnimRcsManager.h"


SpriteArmyPool::SpriteArmyPool()
{

}

SpriteArmyPool::~SpriteArmyPool()
{
	Reset();
}

void SpriteArmyPool::Reset()
{
	for (std::map<unsigned int,SpriteStates >::iterator iter = mapArmys.begin();
		iter != mapArmys.end(); iter++)
	{
		for (std::vector<OneSpriteState>::iterator _iter = (*iter).second.vecSpriteState.begin();
			_iter != (*iter).second.vecSpriteState.end(); _iter++)
		{
			(*_iter).pSprite->removeFromParent();
		}		
	}	
	mapArmys.clear();
}

void SpriteArmyPool::AddOneTypeSprite(unsigned int typeId)
{
	SkeletonAnimRcsManager::Get()->LoadOneRoleRcs(typeId,true);
	std::map<unsigned int,SpriteStates >::iterator iter = mapArmys.find(typeId);
	if (iter == mapArmys.end())
	{
		std::vector<OneSpriteState> vecSpriteState;
		for (int index = 0;index < PRE_LOAD_SPRITE_NUM; index++)
		{
			SpriteHero* pSprite = new SpriteHero(typeId);
			if (pSprite)
			{
				OneSpriteState spriteState;
				spriteState.pSprite = pSprite;
				spriteState.nState = 0;
				vecSpriteState.push_back(spriteState);
			}
		}
		SpriteStates spriteStates;
		spriteStates.notUsedCount = PRE_LOAD_SPRITE_NUM;
		spriteStates.sumCount = PRE_LOAD_SPRITE_NUM;
		spriteStates.usedCount = 0;
		spriteStates.vecSpriteState = vecSpriteState;

		mapArmys.insert(std::make_pair(typeId,spriteStates));
	}
	else
	{
		CCLOG("%s One TypeId Exist %d",__FUNCTION__,typeId);
	}
}

SpriteHero* SpriteArmyPool::CreateOneArmy(unsigned int typeId)
{
	std::map<unsigned int,SpriteStates >::iterator iter = mapArmys.find(typeId);
	if (iter == mapArmys.end())
	{
		this->AddOneTypeSprite(typeId);
	}

	iter = mapArmys.find(typeId);
	if (iter != mapArmys.end())
	{
		if ((*iter).second.notUsedCount > 0)
		{
			(*iter).second.usedCount ++;
			(*iter).second.notUsedCount --;
			for (std::vector<OneSpriteState>::iterator _iter = (*iter).second.vecSpriteState.begin();
				 _iter != (*iter).second.vecSpriteState.end(); _iter++)
			{
				if ((*_iter).nState == 0)
				{
					(*_iter).nState = 1;
					(*_iter).pSprite->setVisible(true);
					return (*_iter).pSprite;
				}
			}
		}
		else
		{
			SpriteHero* pSprite = new SpriteHero(typeId);
			if (pSprite)
			{
				(*iter).second.usedCount ++;
				(*iter).second.sumCount ++;

				OneSpriteState spriteState;
				spriteState.nState = 1;
				spriteState.pSprite = pSprite;
				(*iter).second.vecSpriteState.push_back(spriteState);
			}
			return pSprite;
		}
	}

	return NULL;
}

void SpriteArmyPool::DestroyOneArmy(SpriteHero* pSprite)
{
	unsigned int typeId = pSprite->GetRcsTypeId();
	if (typeId != 0)
	{
		std::map<unsigned int,SpriteStates >::iterator iter = mapArmys.find(typeId);
		if (iter != mapArmys.end())
		{
			if ((*iter).second.sumCount > MAX_SPRITE_NUM)
			{
				// Note: 大于可以容纳的最大数量，删除对象
				bool bDelete = false;
				for (std::vector<OneSpriteState>::iterator _iter = (*iter).second.vecSpriteState.begin();
					 _iter != (*iter).second.vecSpriteState.end(); _iter++)
				{
					if ((*_iter).pSprite == pSprite)
					{
						pSprite->autorelease();
						pSprite->removeFromParent();
						(*iter).second.vecSpriteState.erase(_iter);
						bDelete = true;
						break;
					}
				}				
				if (bDelete)
				{
					(*iter).second.sumCount --;
					(*iter).second.usedCount --;
				}
			}
			else
			{
				// Note: 小于可以容纳的最大数量，对象隐藏掉
				bool bFindIt = false;
				for (std::vector<OneSpriteState>::iterator _iter = (*iter).second.vecSpriteState.begin();
					_iter != (*iter).second.vecSpriteState.end(); _iter++)
				{
					if ((*_iter).pSprite == pSprite)
					{
						pSprite->removeFromParent();
						(*_iter).nState = 0;
						(*_iter).pSprite->setVisible(false);
						(*_iter).pSprite->PauseAnimation();
						bFindIt = true;
						break;
					}
				}				
				if (bFindIt)
				{
					(*iter).second.usedCount --;
					(*iter).second.notUsedCount ++;
				}
			}
		}
	}
}