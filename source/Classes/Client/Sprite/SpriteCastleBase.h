#ifndef _SPRITE_CASTLE_BASE_
#define	_SPRITE_CASTLE_BASE_

#include "Sprite/SpriteBase.h"
#include "Sprite/UserData.h"
#include "NetWork/BaseMsgHandler.h"
#include "Sprite/SpriteDefiner.h"
#include "SpriteDecorationBatchNode.h"

class SpriteCastleBase : public SpriteBase, public InterfaceMsgHandle , public CastleInfoInterface
{
public:
	enum SIDE
	{
		LEFT,
		RIGHT,

	};
public:
	SpriteCastleBase(int typeId,SpriteCastleBase::SIDE side);
	virtual ~SpriteCastleBase();

	virtual void PlayOneAnimation(int animId, int nloop, bool isLoop = true);

	virtual void update(float dt);
	virtual void Die();

	void SetBattleSide(SpriteCastleBase::SIDE side)
	{
		m_battleSide = side;
	}
	SpriteCastleBase::SIDE GetBattleSide(void)
	{
		return m_battleSide;
	}

	// Note: ����CCNode���ֺ���
	virtual void setVisible(bool visible);	
protected:
	virtual void animationHandler(const char* _aniType, const char* _aniID, const char* _frameID);
	virtual void HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg);
protected:
	SIDE  m_battleSide;
	// Note: װ�����
	BloodBar* m_pBloorBar;
};

#endif	//_SPRITE_CASTLE_BASE_