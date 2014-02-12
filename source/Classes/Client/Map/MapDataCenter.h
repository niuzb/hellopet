#ifndef _MAP_DATA_CENTER_H_
#define _MAP_DATA_CENTER_H_

#include "Singleton_t.h"
#include "vector"
#include "string"
#include "SpriteBase.h"

#include "cocos2d.h"

USING_NS_CC;

struct OnePhysicalCellData
{
	unsigned int objectType;
	SpriteBase* object;
	OnePhysicalCellData(){
		objectType = 0;
		object = NULL;
	}
};

class MapDataCenter : public TSingleton<MapDataCenter>
{
public:
	MapDataCenter();
	virtual ~MapDataCenter();

	// Note: ������ѯ
	unsigned int GetOneCellWidth(){
		return oneCellWidth;
	}
	unsigned int GetOneCellHeight(){
		return oneCellHeight;
	}
	unsigned int GetMapPixelWidth(){
		return mapPixelWidth;
	}
	unsigned int GetMapPixelHeigth(){
		return mapPixelHeight;
	}
	unsigned int GetMapCellNumsHor(){
		return mapCellNumsHor;
	}
	unsigned int GetMapCellNumsVer(){
		return mapCellNumsVer;
	}
	unsigned int GetMapPhyscialCellNumsHor(){
		return mapPhysicalCellNumsHor;
	}
	unsigned int GetMapPhyscialCellNumsVer(){ 
		return mapPhysicalCellNumsVer;
	}
	unsigned int GetOnePhysicalCellWidth(){
		return onePhysicalCellWidth;
	}
	unsigned int GetOnePhysicalCellHeight(){
		return onePhysicalCellHeight;
	}


	void ConvertPtToCellPos(const CCPoint &prePt,CCPoint &newPt);
	void ConvertPtToStandardCellMidPos(const CCPoint &prePt,CCPoint &newPt);
	void ConvertCellPosToWordPos(unsigned int posx,unsigned int posy,CCPoint &newPt);

	const char* GetRandomMapRcsFileName();

	void ConvetPtToMapRange(CCPoint &pt);
protected:	
	void InitMapData();
public:
	// Note: ��Ϸ�����ܴ�С
	static CCSize SceneSize;
private:
	// Note: ��ͼ��Ԫ��ߴ�
	unsigned int oneCellWidth;
	unsigned int oneCellHeight;

	// Note: ����㵥Ԫ��ĳߴ�
	unsigned int onePhysicalCellWidth;
	unsigned int onePhysicalCellHeight;

	// Note: ��ͼ���ص㳤��
	unsigned int mapPixelWidth;
	unsigned int mapPixelHeight;

	// Note: ��ͼ������
	unsigned int mapCellNumsHor;
	unsigned int mapCellNumsVer;

	// Note: ��ͼ���������
	unsigned int mapPhysicalCellNumsHor;
	unsigned int mapPhysicalCellNumsVer;

	std::vector<std::string> vecMapRcsFileNames;
};

#endif	// _MAP_DATA_CENTER_H_