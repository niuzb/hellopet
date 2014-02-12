#include "UserData.h"

// ----------------------------------------------------------------

BATTLEINFO::BATTLEINFO()
{
	physical_attack = 0;
	magic_attack = 0;
	skill_attack = 0;
	physical_defence = 0;
	magic_defence = 0;
	skill_defence = 0;
	health_point = 0;
	accurate  = 0; // 命中
	dodge = 0;		// 闪避
	wreck = 0;		// 破击
	parry = 0;		// 格挡
	critical_strike = 0;	// 暴击
	tenacity = 0;			// 任性
	slay = 0;				// 必杀
	proficiency = 0;
	speed = 0;				// 减速
	total_hp = 0;
	courage = 0; // 勇气
	charm = 0; // 魔力
	trick = 0; // 技巧
	effectiveness = 0; // 战斗力
	ragePoint = 0;		//// 精灵怒气 
	totalRangePoint = 0;	

	totalRangePoint = 1000;

}

BATTLEINFO BATTLEINFO::operator+( const BATTLEINFO& info )
{
	BATTLEINFO ret;

	ret.physical_attack = physical_attack + info.physical_attack;
	ret.magic_attack = magic_attack + info.magic_attack;
	ret.skill_attack = skill_attack + info.skill_attack;
	ret.physical_defence = physical_defence + info.physical_defence;
	ret.magic_defence = magic_defence + info.magic_defence;
	ret.skill_defence = skill_defence + info.skill_defence;
	ret.health_point = health_point + info.health_point;
	ret.accurate = accurate + info.accurate;
	ret.dodge = dodge + info.dodge;
	ret.wreck = wreck + info.wreck;
	ret.parry = parry + info.parry;
	ret.critical_strike = critical_strike + info.critical_strike;
	ret.tenacity = tenacity + info.tenacity;
	ret.slay = slay + info.slay;
	ret.proficiency = proficiency + info.proficiency;
	ret.speed = speed + info.speed;
	ret.total_hp = total_hp + info.total_hp;
	ret.courage = courage + info.courage;
	ret.charm = charm + info.charm;
	ret.trick = trick + info.trick;
	ret.effectiveness = effectiveness + info.effectiveness;


	return ret;
}

const BATTLEINFO& BATTLEINFO::operator=( const BATTLEINFO& info )
{
	if(this == &info)
		return * this;
	memcpy(this, &info, sizeof(BATTLEINFO));
	return *this;
}

void BATTLEINFO::ResetRagePoint()
{
	ragePoint = 0;
}

// -------------------------------------------------------------------------

UserData::UserData()
{

}

UserData::~UserData()
{

}

UserDataInterface::UserDataInterface()
{

}

UserDataInterface::~UserDataInterface()
{

}

const USERINFO & UserDataInterface::GetUserInfo()
{
	return this->userInfo;
}

void UserDataInterface::SetUserInfo(USERINFO info)
{
	this->userInfo = info;
}

const BATTLEINFO & UserDataInterface::GetBattleInfo()
{
	return this->battleInfo;
}

void UserDataInterface::SetBattleInfo(BATTLEINFO info)
{
	this->battleInfo = info;
}