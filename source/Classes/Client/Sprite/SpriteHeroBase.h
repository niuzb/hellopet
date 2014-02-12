#ifndef _SPRITE_HERO_BASE_
#define	_SPRITE_HERO_BASE_

#include "Sprite/SpriteBase.h"
#include "Sprite/UserData.h"
#include "NetWork/BaseMsgHandler.h"
#include "Sprite/SpriteDefiner.h"
#include "SpriteDecorationBatchNode.h"

class SpriteHeroBase : public SpriteBase, public InterfaceMsgHandle , public HeroInfoInterface
{
public:
	enum SIDE
	{
		LEFT,
		RIGHT,

	};

public:
	SpriteHeroBase(int type,SpriteHeroBase::SIDE side = SpriteHeroBase::LEFT);
	virtual ~SpriteHeroBase();

	virtual void PlayOneAnimation(int animId, int nloop, bool isLoop = true);

	virtual void update(float dt);	
	/**
	* Instruction : 当角色死亡的时候需要将该状态转给所有需要的对象
	* @param : 
	* @result : 
	*/
	virtual void Die();

	void SetBattleSide(SpriteHeroBase::SIDE side)
	{
		m_battleSide = side;
	}

	SpriteHeroBase::SIDE GetBattleSide(void)
	{
		return m_battleSide;
	}

	// Note: 状态机相关
	virtual void StartStateMachine();
	bool IsStateMachineStart(){
		return m_isStateMachineStart;
	}

	// Note: 重载CCNode部分函数
	virtual void setVisible(bool visible);
	
	// Note: 获取角色在地图中格子为单位的坐标
	void SetYPosInCell(unsigned int yPos){
		m_posYInCell = yPos;
	}
	unsigned int GetYPosInCell(){
		return m_posYInCell;
	}

	CCPoint GetPrevPosition(void){return m_prevPos;}

	virtual void setPosition(const CCPoint &position);

	CCPoint GetBattlePos(void)
	{
		CCPoint ret = getPosition();
		ret.y = GetYPosInCell();
		return ret;
	}

protected:
	virtual void animationHandler(const char* _aniType, const char* _aniID, const char* _frameID);
	virtual void HandlerMessage(unsigned int cmd,const NORMAL_MSG_PACKAGE* msg);

protected:
	SIDE  m_battleSide;
	unsigned int m_posYInCell;

	SkillStateMachine	* m_pStateMachine;
	bool m_isStateMachineStart;
	StateFactory* m_pStateFactory;

	// Note: 人物装饰相关
	BloodBar* m_pBloorBar;
	CCSprite* m_pShadowSprite;

	CCPoint m_prevPos;
};

#endif	//_SPRITE_HERO_BASE_