#include "MapPhysicalLayer.h"
#include "MapDataCenter.h"
#include "Sprite/SpriteHero.h"
#include "Sprite/SpriteDefiner.h"

//MapPhysicalLayer* MapPhysicalLayer::s_instance = NULL;
//
//MapPhysicalLayer::MapPhysicalLayer()
//	: arrayPhysicalData(NULL)
//	, m_mapCellWidthNums(0)
//	, m_mapCellHeightNums(0)
//{
//	s_instance = this;
//}
//
//void MapPhysicalLayer::InitMapPhysicalLayer(const CCSize& mapSize,const CCPoint& mapLeftDownPt)
//{
//	m_mapSize = mapSize;
//	m_mapLeftDownPt = mapLeftDownPt;
//	m_mapCellHeightNums = 3;
//	if (0 == ((int)m_mapSize.width % CELL_WIDTH))
//	{
//		m_mapCellWidthNums = m_mapSize.width / CELL_WIDTH;
//	}	
//	else
//	{
//		m_mapCellWidthNums = int(m_mapSize.width / CELL_WIDTH) + 1;
//	}
//
//	arrayPhysicalData = new (CCNode***[m_mapCellWidthNums]);
//	for (unsigned int index = 0;index<m_mapCellWidthNums;index++)
//	{
//		arrayPhysicalData[index] = new (CCNode**[m_mapCellHeightNums]);
//		for (unsigned int _index = 0;_index < m_mapCellHeightNums;_index++)
//		{
//			arrayPhysicalData[index][_index] = new (CCNode*[ONE_CELL_MAX_PLAYER_COUNT]);
//			memset(arrayPhysicalData[index][_index],NULL,ONE_CELL_MAX_PLAYER_COUNT * sizeof(CCNode*));
//		}
//	}
//
//	arrayCellHeroNums = new (int*[m_mapCellWidthNums]);
//	for (unsigned int index = 0;index<m_mapCellWidthNums;index++)
//	{
//		arrayCellHeroNums[index] = new int[m_mapCellHeightNums];
//		memset(arrayCellHeroNums[index],0,m_mapCellHeightNums*sizeof(int));
//	}
//}
//
//MapPhysicalLayer::~MapPhysicalLayer()
//{
//	if (arrayPhysicalData)
//	{
//		for (unsigned int index = 0;index<m_mapCellWidthNums;index++)
//		{
//			for (unsigned int _index = 0;_index < m_mapCellHeightNums;_index++)
//			{
//				delete []arrayPhysicalData[index][_index];
//			}
//			delete []arrayPhysicalData[index];
//		}
//		delete []arrayPhysicalData;
//		arrayPhysicalData = NULL;
//	}
//	
//	if (arrayCellHeroNums)
//	{
//		for (unsigned int index = 0;index<m_mapCellWidthNums;index++)
//		{
//			delete []arrayCellHeroNums[index];
//		}
//		delete []arrayCellHeroNums;
//	}
//
//	s_instance = NULL;
//}
//
//MapPhysicalLayer* MapPhysicalLayer::GetInstance()
//{
//	return s_instance;
//}
//
//unsigned int MapPhysicalLayer::getPosXInCell(float posX)
//{
//	unsigned int offsetX = posX - m_mapLeftDownPt.x;
//	unsigned int _posX = offsetX / CELL_WIDTH;
//	return _posX;
//}
//
//void MapPhysicalLayer::Update(float dt,const std::vector<SpriteHeroBase*>& vecHeros)
//{
//	for (unsigned int index = 0;index<m_mapCellWidthNums;index++)
//	{
//		for (unsigned int _index = 0;_index < m_mapCellHeightNums;_index++)
//		{
//			memset(arrayPhysicalData[index][_index],NULL,ONE_CELL_MAX_PLAYER_COUNT * sizeof(SpriteHeroBase*));
//		}
//	}
//	for (unsigned int index = 0;index<m_mapCellWidthNums;index++)
//	{
//		memset(arrayCellHeroNums[index],0,m_mapCellHeightNums*sizeof(int));
//	}
//
//	for (std::vector<SpriteHeroBase*>::const_iterator iter = vecHeros.begin();
//		 iter != vecHeros.end(); iter++)
//	{
//		if ((*iter)->IsStateMachineStart())
//		{
//			//UpdateItemPos((*iter));
//		}		
//	}
//}
//
//void MapPhysicalLayer::UpdateItemPos(CCNode* pNode)
//{
//	if (pNode)
//	{
//		SpriteHeroBase* pHero = dynamic_cast<SpriteHeroBase*>(pNode);
//		if (pHero)
//		{
//			unsigned int yPosInCell = pHero->GetYPosInCell();
//			CCPoint pos = pHero->getPosition();
//			unsigned int xPosInCell = getPosXInCell(pos.x);
//			int oneCellHeroNums = arrayCellHeroNums[xPosInCell][yPosInCell];
//			if (oneCellHeroNums < ONE_CELL_MAX_PLAYER_COUNT)
//			{
//				arrayPhysicalData[xPosInCell][yPosInCell][oneCellHeroNums] = pNode;
//				arrayCellHeroNums[xPosInCell][yPosInCell] ++;
//			}			
//		}
//	}
//}
//
//bool MapPhysicalLayer::SearchNearByItems(CCNode* pNode,int xOffset,int yOffset,std::vector<CCNode*> &outNodes)
//{
//	bool bRet = false;
//	if (pNode)
//	{
//		SpriteHeroBase* pHero = dynamic_cast<SpriteHeroBase*>(pNode);
//		if (pHero)
//		{
//			CCPoint pos = pHero->getPosition();
//			unsigned int xPosInCell = getPosXInCell(pos.x);
//			unsigned int yPosInCell = pHero->GetYPosInCell();
//
//			unsigned int newPosX = xPosInCell + xOffset;
//			unsigned int newPosY = yPosInCell + yOffset;
//			if ((newPosX) >= 0 && 
//				(newPosX) < m_mapCellWidthNums && 
//				(newPosY) >= 0 && 
//				(newPosY) < m_mapCellHeightNums)
//			{
//				outNodes.clear();
//				for (int index = 0;index < arrayCellHeroNums[xPosInCell][yPosInCell];index++)
//				{
//					outNodes.push_back(arrayPhysicalData[xPosInCell][yPosInCell][index]);
//				}
//				bRet = true;
//			}
//		}
//	}
//	return bRet;
//}

// --------------------------------------------------------------------

CHeroPhysicalLayer::CHeroPhysicalLayer(void)
{
	m_leftHeros.Create(1136, 3, NULL);
	m_rightHeros.Create(1136, 3, NULL);

}

CHeroPhysicalLayer::~CHeroPhysicalLayer(void)
{
	
}

void CHeroPhysicalLayer::Register(SpriteHeroBase* pNode)
{
	std::map<SpriteHeroBase*, SpriteHeroBase*>::iterator iter = m_rigisterHeros.find(pNode);
	if(iter != m_rigisterHeros.end())
		return;

	m_rigisterHeros.insert(std::make_pair(pNode, pNode));

}

void CHeroPhysicalLayer::UnRegister(SpriteHeroBase* pNode)
{
	m_rigisterHeros.erase(pNode);
}

CCPoint CHeroPhysicalLayer::ConvertToArrayCoordate(const CCPoint heroPos)
{
	return CCPointZero;
}

void CHeroPhysicalLayer::ChangePos(SpriteHeroBase* pNode)
{
#ifdef _DEBUG
	bool bFind = false;
	std::map<SpriteHeroBase*, SpriteHeroBase*>::iterator iter = m_rigisterHeros.find(pNode);
	CCAssert( iter != m_rigisterHeros.end(), "Please register you node first!");

#endif

	Array2D<SpriteHeroBase*>* pHeros = &m_leftHeros;

	if(pNode->GetBattleSide() == SpriteHeroBase::RIGHT)
	{
		pHeros = &m_rightHeros;
	}

	CCPoint prevPos = pNode->GetPrevPosition();
	if(pHeros->Get((int)prevPos.x, (int)pNode->GetYPosInCell()) == pNode)
	{
		pHeros->Set((int)prevPos.x, (int)pNode->GetYPosInCell(), NULL);
	}

	CCPoint pos = pNode->getPosition();

	SpriteHeroBase* pContainNode = pHeros->Get((int)pos.x, (int)pNode->GetYPosInCell());
	if(pContainNode != NULL)
	{
		if(pNode->GetHeroInfo().id < pContainNode->GetHeroInfo().id)
		{
			pHeros->Set((int)pos.x, (int)pNode->GetYPosInCell(), pNode);
		}
	}
	else
	{
		pHeros->Set((int)pos.x, (int)pNode->GetYPosInCell(), pNode);
	}
	
	

}

SpriteHeroBase* CHeroPhysicalLayer::FindNearestHero(const CCPoint& startPos, int range, SpriteHeroBase::SIDE side)
{
	Array2D<SpriteHeroBase*>* pHeros = &m_leftHeros;

	if(side == SpriteHeroBase::LEFT)
	{
		pHeros = &m_rightHeros;
	}

	int y = (int)startPos.y;

	
	for(int i = 0; i < range; i++)
	{
		int x = (int)startPos.x;
		if(side == SpriteHeroBase::LEFT)
		{
			x = x + i;
		}
		else
		{
			x = x - i;
		}

		SpriteHeroBase* pNode = pHeros->Get(x, y);
		if(pNode)
		{
			return pNode;
		}

	}

	return NULL;
}