#ifndef _USER_DATA_H_
#define _USER_DATA_H_

#include "string"
#include "Singleton_t.h"
#include "../../libs/EncodeCode/EncodeValue.hpp"

using namespace std;

class INFOID
{
public:
	INFOID(void){}
	//PLAYER_ID  id;
	unsigned int id;

};

class BATTLEINFO
{
public:
	BATTLEINFO();
	BATTLEINFO operator + (const BATTLEINFO& info);
	const BATTLEINFO& operator = (const BATTLEINFO& info);

	EncodeValue<unsigned int> physical_attack;
	EncodeValue<unsigned int> magic_attack;
	EncodeValue<unsigned int> skill_attack;
	EncodeValue<unsigned int> physical_defence;
	EncodeValue<unsigned int> magic_defence;
	EncodeValue<unsigned int> skill_defence;
	EncodeValue<unsigned int> health_point;
	EncodeValue<unsigned int> accurate ; // 命中
	EncodeValue<unsigned int> dodge;		// 闪避
	EncodeValue<unsigned int> wreck;		// 破击
	EncodeValue<unsigned int> parry;		// 格挡
	EncodeValue<unsigned int> critical_strike;	// 暴击
	EncodeValue<unsigned int> tenacity;			// 任性
	EncodeValue<unsigned int> slay;				// 必杀
	EncodeValue<unsigned int> proficiency;
	EncodeValue<unsigned int> speed;				// 减速
	EncodeValue<unsigned int> total_hp;
	EncodeValue<unsigned int> courage; // 勇气
	EncodeValue<unsigned int> charm; // 魔力
	EncodeValue<unsigned int> trick; // 技巧
	EncodeValue<unsigned int> effectiveness; // 战斗力
	EncodeValue<unsigned int> ragePoint;		//// 精灵怒气 
	EncodeValue<unsigned int> totalRangePoint;	

	void ResetRagePoint();//重置精灵怒气，回到主城的时候

};

class USERINFO
{
public:
	// Note: basic info
	string player_name;
	unsigned int player_id;
	unsigned int reg_time;
	unsigned int channel_id;
	unsigned int type_id;
	USERINFO()
	{
		player_name = "";
		player_id = 0;
		reg_time = 0;
		channel_id = 0;
		type_id = 0;
	}
};

class UserDataInterface
{
public:
	UserDataInterface();
	~UserDataInterface();
	const USERINFO & GetUserInfo();
	void SetUserInfo(USERINFO info);
	const BATTLEINFO & GetBattleInfo();
	void SetBattleInfo(BATTLEINFO info);
protected:
	USERINFO userInfo;
	BATTLEINFO battleInfo;
};

/// <summary>
//	主角的信息
/// </summary>
class UserData : public TSingleton<UserData>,public UserDataInterface
{
public:
	UserData();
	~UserData();
};

/// <summary>
//	主城信息
/// </summary>
class CastleInfo
{
public:
	unsigned int id;	//主城的ID
	unsigned int level; //主城的等级
	unsigned int blood; //主城的血量
	unsigned int curBlood;	// 主城的当前血量
	unsigned int animId;	// 主城的动画ID

	CastleInfo()
		: id(0)
		, level(0)
		, blood(0)
		, curBlood(0)
		, animId(0)
	{
	}
};

class HeroInfo
{
public:
	unsigned int id;	//英雄的ID
	unsigned int typeID;	
	unsigned int animId;	// 英雄的资源ID
	unsigned int level; //英雄的等级
	unsigned int totalBlood; //英雄的总血量
	int curBlood;	//英雄的当前血量
	unsigned int speed; //英雄的速度
	

	unsigned int skillID;	// 现在是每一个角色有且仅有一个技能

	HeroInfo()
		: id(0)
		, typeID(0)
		, animId(0)
		, level(0)
		, totalBlood(100)
		, speed(0)
		, skillID(0)
		, curBlood(100)
	{
	}

	BATTLEINFO battleInfo;

	void SubBlood(int value)
	{
		curBlood -= value;
		if(curBlood < 0)
			curBlood = 0;
	}

};

class HeroInfoInterface
{
public:
	HeroInfoInterface(){}
	virtual ~HeroInfoInterface(){}

	void SetHeroInfo(const HeroInfo& info)
	{
		m_heroInfo = info;
	}
	
	HeroInfo& GetHeroInfo(){
		return m_heroInfo;
	}

	void SetId(unsigned int id)
	{
		m_heroInfo.id = id;
	}

protected:
	HeroInfo m_heroInfo;
};

class CastleInfoInterface
{
public:
	CastleInfoInterface(){}
	virtual ~CastleInfoInterface(){}

	void SetCastleInfo(const CastleInfo& info){
		m_castleInfo = info;
	}
	const CastleInfo& GetCastleInfo(){
		return m_castleInfo;
	}
protected:
	CastleInfo m_castleInfo;
};

#endif	//_USER_DATA_H_