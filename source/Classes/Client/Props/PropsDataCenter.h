#ifndef _PROPS_DATA_CENTER_H_
#define _PROPS_DATA_CENTER_H_

#include "map"
#include "set"
#include "string"
#include "Props/PropsDefiner.h"
#include "Singleton_t.h"

struct PropTriggerData{
	unsigned int type;
	unsigned int aniRcsId;
	unsigned int soundId;
	std::string batchFileName;
	std::string frameFileName;
	bool isExplosionSelf;
	PropTriggerData(){
		type = 0;
		aniRcsId = 0;
		soundId = 0;
		isExplosionSelf = false;
		batchFileName = "";
		frameFileName = "";
	}
};

/// <summary>
//	只保存相关每一个Trigger的基本查询信息，可以为静态实例
/// </summary>

class PropsDataCenter : public TSingleton<PropsDataCenter>
{
public:
	PropsDataCenter();
	~PropsDataCenter();

	void Init(){
		ReadData();
	}
	const std::set<std::string>& GetPropBatchFiles(){
		return setPropBatchFileNames;
	}
	bool GetBatchFileNameAndFrameName(PropsType type,std::string &batchFileName,std::string &frameFileName);
	bool GetAnimRcsIdByPropType(PropsType type,unsigned int &id);
	bool GetSoundIdByPropType(PropsType type,unsigned int &id);

	unsigned int GetMaxPropNums();

	bool GetTriggerData(PropsType propType,PropTriggerData &data);
protected:
	void ReadData();
private:
	std::map<unsigned int,PropTriggerData> mapPropsData;
	std::set<std::string> setPropBatchFileNames;
};

#endif	//_PROPS_DATA_CENTER_H_