
#pragma once
#include <map>
#include <string>
#include "../../StateMachine/StateEventType.h"
#include "../../Sprite/UserData.h"





typedef struct tagSkillInfo
{
	tagSkillInfo(void)
		:Id(0)
		,partID(0)
		,linkSkillId(0)
		,linkTime(0.0f)
		,displacement(0)
		,beatBackDistance(0)
		,isSpecial(false)
		,canCommonBreak(false)
		,canSpecialBreak(false)
		,damage(0)
		,criticalRate(0.0f)
		,attackNumber(0)
		,canControl(false)
		,continueTime(0.0f)
		,whichTime(0)
		,iShakeCamera(0)
		,bCameraStartTime(0.0f)
		,fCoolTime(0.0f)
		,SoundId(0)
		,bSoundLoop(false)
		,aim(E_AIM_NONE)
		,effectId(0)
		,linkEffectId(0)
		,longDistanceAttackRange(0)
		,bAdaptationDistance(false)
		,bBasedOnFrame(false)
		,girleVoiceID(0)
		,boyVoiceID(0)
		,ragePoint(0)
		,bInvincible(false)
		,skillPriority(0)
		,skillConflict(0)
		,bRotateEffect(false)
		,effectZOrder(E_DYNAMIC)
		,animationID(0)
	{

	}

	enum ATTACK_TYPE
	{
		E_NORMAL = 1,
		E_MAGIC,
		E_SKILL,
		E_FAIRY_SKILL,

		E_DODGE,	// 闪避
		E_PARRY,	// 格挡
		E_STRIKE,	// 暴击
	};

	enum AIM_TYPE
	{
		E_AIM_NONE,
		E_AIM_ENEMY,
		E_AIM_HERO
	};

	enum EFFECT_Z_ORDER
	{
		E_DYNAMIC,
		E_BEHIDE_HERO,
		E_FRONT_HERO
	};

	// skill Id
	int Id;
	EventType type;

	int partID;
	int linkSkillId;

	unsigned int animationID;
	
	float linkTime;
	int displacement;
	int beatBackDistance;
	bool isSpecial;
	bool canCommonBreak;
	bool canSpecialBreak;
	int damage;
	float criticalRate;

	// 主角该技能过程中可以击中的次数
	int attackNumber;

	// 技能释放过程中是否可以移动（0为不行，1为可以）
	bool canControl;

	// 该技能可持续时间
	float continueTime;

	// 主角形成位移时的速度由哪个时间控制（1为动画时间，2为continue_time。。。）
	int whichTime;

	/// skill description
	char   SkillDesp[512];


	/// camera effect
	int   iShakeCamera;
	float  bCameraStartTime;
	float  fCoolTime;
	
	int SoundId;

	bool bSoundLoop;
	AIM_TYPE aim;

	int effectId;
	int linkEffectId;
	int effectsoundID;

	std::string actionName;
	std::string actionIcon;

	int longDistanceAttackRange;
	float longDistanceEffectSpeed;
	bool bShowFarWay;	// 在某个地方瞬间出来
	bool bDisappear;
	float alpha;

	float ownCD;
	float shareCD;

	bool bAdaptationDistance;

	bool bBasedOnFrame;

	bool bBuff;

	ATTACK_TYPE attackType;

	unsigned int firstSkillID;

	unsigned int boyVoiceID;
	unsigned int girleVoiceID;
	unsigned int ragePoint;

	bool bInvincible;

	int skillPriority;
	int skillConflict;

	EFFECT_Z_ORDER effectZOrder;
	bool bRotateEffect;


}SKILL_INFO, *LPSKILL_INFO;
typedef const SKILL_INFO*   LPCSKILL_INFO;


typedef struct tagSkillSlotInfo
{
	unsigned int slotIndex;
	unsigned int skillId;

	tagSkillSlotInfo(){
		slotIndex = 0;
		skillId = 0;
	}
}SKILL_SLOT_INFO, *LPSKILL_SLOT_INFO;
typedef const SKILL_SLOT_INFO*   LPCSKILL_SLOT_INFO;

struct FAIRY_SKILL_INFO : public INFOID, public BATTLEINFO
{
	enum TYPE
	{
		E_ATTACK,
		E_BUFFER,

	};

	enum AIM
	{
		E_HERO,
		E_ENEMY,
		E_FULL_SCREEN,

	};

	enum EFFECT_Z_ORDER
	{
		E_DYNAMIC,
		E_BEHIDE_HERO,
		E_FRONT_HERO
	};

	FAIRY_SKILL_INFO(void)
	{
		memset(this, 0x00, sizeof(FAIRY_SKILL_INFO));
	}

	unsigned int  fairy_ID;
	TYPE type;
	AIM aim;
	bool bLock;
	int attack_number;
	float continueTime;
	int effectID;
	int longDistanceAttackRange;
	int longDistanceEffectSpeed;
	int soundID;
	int effectSoundID;
	int hurt;
	int hurtAddValue;

	EFFECT_Z_ORDER effectZOrder;

	float ownCD;

};