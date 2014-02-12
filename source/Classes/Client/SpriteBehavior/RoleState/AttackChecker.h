// TAOMEE GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Taomee Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 2012-2015 Taomee Game Technologies. 
//      All Rights Reserved.
//
// Taomee Game Technologies, Shanghai, China
// http://www.taomee.com
//
#pragma once

#include <list>
#include <map>
#include <vector>

#include "SkillInfo.h"
#include "Singleton_t.h"
#include "../../Sprite/UserData.h"
#include "SkillInfo.h"
#include "cocos2d.h"

using namespace std;

class SpriteHeroBase;
class BoneParticle;

namespace AttackChecker
{
	class CBase
	{
	public:
		enum ACTION
		{
			E_PLAYER_ATTACK_MONSTER,
			E_PLAYER_ATTACK_PLAYER,
			E_FAIRY_ATTACK_MONSTER,
			E_FAIRY_ATTACK_PLAYER,
		};

		struct INJURE_DATA
		{
			INJURE_DATA(void):hurt(0),attackType(tagSkillInfo::E_NORMAL){}
			int hurt;
			tagSkillInfo::ATTACK_TYPE attackType;
		};

	public:
		CBase(SpriteHeroBase* pAttacker);
		virtual ~CBase(void);

		virtual void Update(float dt);
		virtual void SetSkillID(unsigned int id);
		virtual void SetCanAttackOtherPlayer(bool b){m_bAttackOtherPlayer = b;}

		virtual void DoAttack(SpriteHeroBase* pDefender, int count );
		virtual void IntersectsRect(cocos2d::CCRect& attackBox, SpriteHeroBase* pOther);

		virtual INJURE_DATA CalInjure(tagSkillInfo::ATTACK_TYPE attackType, unsigned int damage, const BATTLEINFO* pAttackInfo, const BATTLEINFO* pDefenerInfo);
		virtual void SetAttackerID(unsigned int id){m_attackerID = id;}
		virtual unsigned int GetAttackerID(void){return m_attackerID;}
		virtual unsigned int GetDefenderID(void){return m_defenderID;}
		
		void SetFullScreenAttack(bool b){m_bFullScreenAttack = b;}

		void SetAction( ACTION action ){m_action = action;}

		void SetEffect(BoneParticle* pEffect){m_pEffect = pEffect;}

	protected:
		/// …Í«Î≤•∑≈±©ª˜…˘“Ù
		void PlayCritSound(float dt);

		/// …Í«Î≤•∑≈∑«±©ª˜…˘“Ù
		void PlayUncritSound(float dt);

	
		int GetAttackCoef( );

		bool IsBattleSide(SpriteHeroBase* pOther);
	protected:
		int m_skillID;
		// monster ID, attack count
		map<unsigned int, int> m_attackedMonsterList;

		// sound effect
		bool m_bPlayCritSound;
		bool m_bPlayUncritSound;
		float m_fDeltaTimeCrit;
		float m_fDeltaTimeUncrit;

		unsigned int m_attackerID;
		unsigned int m_defenderID;

		float m_curAttackTime;
		float m_attackPeriod;

		int m_attackNumber;
		bool m_bAttackOtherPlayer;

		bool m_bBasedOnFrame;

		float m_beatBackDistance;

		EventType m_type;

		tagSkillInfo::ATTACK_TYPE m_attackType;

		SpriteHeroBase* m_pAttacker;
		int m_attackBoxFrame;
		bool m_bFullScreenAttack;

		bool m_bShakeCamera;
		unsigned int m_uRagePoint;

		int m_hurtAddValue;
		int m_hurtPercent;

		ACTION m_action;

		int m_attackRange;
		BoneParticle* m_pEffect;


	};


	class CNormalAttack : public CBase
	{
	public:
		CNormalAttack(SpriteHeroBase* pRole): CBase(pRole){}
		virtual ~CNormalAttack(void){}
		virtual void DoAttack(SpriteHeroBase* pDefender, int count );
	public:
		//std::vector<AttackMonsterInfo> m_attackMessage;

	protected:

	};
};