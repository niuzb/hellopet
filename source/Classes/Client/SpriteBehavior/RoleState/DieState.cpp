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

#include "DieState.h"
#include "../../Sprite/SpriteDefiner.h"
#include "../../Sprite/SpriteHeroBase.h"

DieState::DieState(BaseAttackEvt *pEvt) :  BaseAttackState(pEvt)
	//, m_CurfaceDir(DIRECTION_UNKNOW)
{
	m_Type = ToDie;

	m_LowPriority.push_back(ToIdle);
}


DieState::~DieState( void )
{

}


unsigned int DieState::PlayAnim(void)
{
	int actionID = kTypeDie_FaceHor;
	m_pRole->PlayOneAnimation(actionID, 1, true);

	// 判断是否在主城中
	//m_CurfaceDir = m_pRole->getDirection();
	//switch(m_CurfaceDir)
	//{
	//case DIRECTION_LEFT:
	//	actionID = kTypeDie_FaceHor;
	//	m_pRole->SetAnim(actionID, 1, false);		 
	//	break;

	//case DIRECTION_RIGHT:

	//	actionID = kTypeDie_FaceHor;
	//	m_pRole->SetAnim(actionID, 1, false);
	//	m_pRole->SetAnimFlipX(true);
	//	break;

	//case DIRECTION_UP:
	//	
	//	actionID = kTypeDie_FaceUp;
	//	m_pRole->SetAnim(actionID, 1, false);
	//	break;

	//case DIRECTION_BOTTOM:
	//	
	//	actionID = kTypeDie_FaceDown;
	//	m_pRole->SetAnim(actionID, 1, false);
	//	break;

	//default:
	//	
	//	actionID = kTypeDie_FaceHor;
	//	m_pRole->SetAnim(actionID, 1, false);
	//	break;
	//}

	//m_pRole->SetAnimPauseOnOver(true);

	return actionID;
}

bool DieState::Entered()
{
	if (false == BaseAttackState::Entered())
		return false;

	CCLOG("DieState::Entered()----------------------------------");

	// init the animation

	unsigned int actionID = PlayAnim();

	return true;
}

void DieState::Exited()
{
	BaseAttackState::Exited();
}

void DieState::Update(float dt)
{
	BaseAttackState::Update(dt);
}

void DieState::Reset()
{
	BaseAttackState::Reset();
}    

