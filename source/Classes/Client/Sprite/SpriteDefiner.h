#ifndef _SPRITE_DEFINER_H_
#define _SPRITE_DEFINER_H_

typedef enum SpriteType
{
	kType_Sprite_Hero = 0,
	kType_Sprite_Oth_Hero,
	kType_Sprite_Trigger,
	kType_Sprite_Prop,
	kType_Sprite_UnKnow
};

enum RoleActionType
{
	// 特效
	kType_Play = 100000,

	// 副本中IDLE
	kTypeIdle_FaceHor_OTH = 1002,

	// 副本中跑动
	kTypeRun_FaceHor_OTH	= 1011,	

	// 攻击
	kTypeAttack_FaceHor_OTH = 1014,

	// 受伤
	kTypeHurt_FaceHor	= 1023,

	// 死亡
	kTypeDie_FaceHor	= 1026,

	kTypeAction_UnKnow	= 1111
};
#endif	//_SPRITE_DEFINER_H_