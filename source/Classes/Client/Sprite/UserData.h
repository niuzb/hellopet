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
	EncodeValue<unsigned int> accurate ; // ����
	EncodeValue<unsigned int> dodge;		// ����
	EncodeValue<unsigned int> wreck;		// �ƻ�
	EncodeValue<unsigned int> parry;		// ��
	EncodeValue<unsigned int> critical_strike;	// ����
	EncodeValue<unsigned int> tenacity;			// ����
	EncodeValue<unsigned int> slay;				// ��ɱ
	EncodeValue<unsigned int> proficiency;
	EncodeValue<unsigned int> speed;				// ����
	EncodeValue<unsigned int> total_hp;
	EncodeValue<unsigned int> courage; // ����
	EncodeValue<unsigned int> charm; // ħ��
	EncodeValue<unsigned int> trick; // ����
	EncodeValue<unsigned int> effectiveness; // ս����
	EncodeValue<unsigned int> ragePoint;		//// ����ŭ�� 
	EncodeValue<unsigned int> totalRangePoint;	

	void ResetRagePoint();//���þ���ŭ�����ص����ǵ�ʱ��

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
//	���ǵ���Ϣ
/// </summary>
class UserData : public TSingleton<UserData>,public UserDataInterface
{
public:
	UserData();
	~UserData();
};

/// <summary>
//	������Ϣ
/// </summary>
class CastleInfo
{
public:
	unsigned int id;	//���ǵ�ID
	unsigned int level; //���ǵĵȼ�
	unsigned int blood; //���ǵ�Ѫ��
	unsigned int curBlood;	// ���ǵĵ�ǰѪ��
	unsigned int animId;	// ���ǵĶ���ID

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
	unsigned int id;	//Ӣ�۵�ID
	unsigned int typeID;	
	unsigned int animId;	// Ӣ�۵���ԴID
	unsigned int level; //Ӣ�۵ĵȼ�
	unsigned int totalBlood; //Ӣ�۵���Ѫ��
	int curBlood;	//Ӣ�۵ĵ�ǰѪ��
	unsigned int speed; //Ӣ�۵��ٶ�
	

	unsigned int skillID;	// ������ÿһ����ɫ���ҽ���һ������

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