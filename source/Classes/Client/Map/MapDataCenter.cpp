#include "MapDataCenter.h"
#include "cocos2d.h"
#include "CommonUtils.h"

USING_NS_CC;

CCSize MapDataCenter::SceneSize = CCSize(1136,640);

MapDataCenter::MapDataCenter():
	oneCellWidth(32),
	oneCellHeight(32),
	onePhysicalCellWidth(16),
	onePhysicalCellHeight(16)
{
	CCSize screenSize = MapDataCenter::SceneSize;
	mapPixelWidth = screenSize.width;
	mapPixelHeight = screenSize.height;

	float _mapCellNumsHor = screenSize.width / oneCellWidth;
	if (_mapCellNumsHor - (int)_mapCellNumsHor != 0)
	{
		mapCellNumsHor = (int)_mapCellNumsHor + 1;
	}
	else
	{
		mapCellNumsHor = (unsigned int)_mapCellNumsHor;
	}
	
	float _mapCellNumsVer = screenSize.height / oneCellHeight;
	if (_mapCellNumsVer - (int)_mapCellNumsVer != 0)
	{
		mapCellNumsVer = (int)_mapCellNumsVer + 1;
	}
	else
	{
		mapCellNumsVer = (unsigned int)_mapCellNumsVer;
	}

	float _mapPhyscialCellNumsHor = screenSize.width / onePhysicalCellWidth;
	if (_mapPhyscialCellNumsHor - (int)_mapPhyscialCellNumsHor != 0)
	{
		mapPhysicalCellNumsHor = (int)_mapPhyscialCellNumsHor + 1;
	}
	else
	{
		mapPhysicalCellNumsHor = (unsigned int)_mapPhyscialCellNumsHor;
	}

	float _mapPhysicalCellNumsVer = screenSize.height / onePhysicalCellHeight;
	if (_mapPhysicalCellNumsVer - (int)_mapPhysicalCellNumsVer != 0)
	{
		mapPhysicalCellNumsVer = (int)_mapPhysicalCellNumsVer + 1;
	}
	else
	{
		mapPhysicalCellNumsVer = (unsigned int)_mapPhysicalCellNumsVer;
	}

	InitMapData();
}

MapDataCenter::~MapDataCenter()
{
	vecMapRcsFileNames.clear();
}

void MapDataCenter::InitMapData()
{
	vecMapRcsFileNames.push_back("BigSprites/guide_main_bk.jpg");
	vecMapRcsFileNames.push_back("BigSprites/sp_main_bk2.jpg");
	vecMapRcsFileNames.push_back("BigSprites/sp_main_bk3.jpg");
	vecMapRcsFileNames.push_back("UI/LOADING.png");
}

const char* MapDataCenter::GetRandomMapRcsFileName()
{
	size_t mapRcsNums = vecMapRcsFileNames.size();

	return vecMapRcsFileNames[0].c_str();
}

void MapDataCenter::ConvertPtToCellPos(const CCPoint &prePt,CCPoint &newPt)
{
	newPt.x = (int)(prePt.x / oneCellWidth);
	newPt.y = (int)(prePt.y / oneCellHeight);
}

void MapDataCenter::ConvertPtToStandardCellMidPos(const CCPoint &prePt,CCPoint &newPt)
{
	int cellPosX = (int)(prePt.x / oneCellWidth);
	int cellPosY = (int)(prePt.y / oneCellHeight);

	ConvertCellPosToWordPos(cellPosX,cellPosY,newPt);
}

void MapDataCenter::ConvertCellPosToWordPos(unsigned int posx,unsigned int posy,CCPoint &newPt)
{
	unsigned int oneCellWidth = MapDataCenter::Get()->GetOneCellWidth();
	unsigned int oneCellHeight = MapDataCenter::Get()->GetOneCellHeight();
	newPt.x = posx * oneCellWidth + oneCellWidth/2.0;
	newPt.y = posy * oneCellHeight + oneCellHeight/2.0;
}

void MapDataCenter::ConvetPtToMapRange(CCPoint &pt)
{
	pt.x = (int)pt.x;
	pt.y = (int)pt.y;

	if (pt.x < 0)
	{
		pt.x = 0;
	}
	else
	{
		if (pt.x >= mapCellNumsHor)
		{
			pt.x = mapCellNumsHor - 1;
		}		
	}
	if (pt.y < 0)
	{
		pt.y = 0;
	}
	else
	{
		if (pt.y >= mapCellNumsVer)
		{
			pt.y = mapCellNumsVer - 1;
		}
	}
}