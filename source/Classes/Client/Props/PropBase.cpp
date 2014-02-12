#include "PropBase.h"
#include "PropManager.h"
#include "PropsTriggerManager.h"
#include "PropsDataCenter.h"
#include "Sound/GameAudioManager.h"

PropBase::PropBase(PropsType propType,SpriteBase* pUserSprite,CCNode* pParentNode,bool isHero):
	mPropType(propType),
	mUserSprite(pUserSprite),
	mIsHero(isHero),
	mAnimRcsId(0),
	m_nSoundId(0),
	mParentNode(pParentNode),
	mDirection(CCPointZero),
	m_isDestorySelfWhenEnd(false)
{	
	PropsDataCenter* pData = PropsDataCenter::Get();
	if (pData)
	{
		unsigned int aniRcsId = 0;
		if (pData->GetAnimRcsIdByPropType(mPropType,aniRcsId))
		{
			mAnimRcsId = aniRcsId;
		}

		// Note: 获得特效播放时声音
		pData->GetSoundIdByPropType(mPropType,m_nSoundId);
	}
}

PropBase::~PropBase()
{
	PropManager::Get()->RemoveOneProp(this);
}

void PropBase::UseProp(CCPoint pt,bool bPlaySound /* = true */)
{
	if (bPlaySound)
	{
		if (0 != m_nSoundId)
		{
			GameAudioManager::Get()->PlayOneEffectInBattle(m_nSoundId);
		}
	}
}

void PropBase::DestroySelf()
{

}