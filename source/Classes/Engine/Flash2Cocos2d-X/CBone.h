#pragma once

#include "CBaseNode.h"
#include "CTweenNode.h"
#include "CTween.h"
#include "map"

using namespace cocos2d;

#define  ANGLE_TO_RADIAN  (M_PI / 180)

class MyCCArmature;

class MyCCBone : public CCObject
{
public:
	/**
	* ����Boneʵ����Bone ��Ϊ���õ�ʵ�����ö���ع���������
	* @param _isRadian ������ת�Ƕ��Ƿ���û����ƣ����� Starling ʹ�õ��ǻ�����
	* @return ���� Bone ʵ��
	*/
	static MyCCBone* create(bool _isRadian = false,MyCCArmature *pArmature = NULL);

	static void	removePoolObject();

protected:

	//static CCArray	*sObjectPool;

	//static int		sPoolIndex;

	static void		recycle(MyCCBone* _bone);
	
	// �����������������!!!!
	MyCCBone();

public:
	~MyCCBone(void);

	virtual bool init(bool _isRadian,MyCCArmature *pArmature);

	
	/* ɾ�������� */
	void	remove();

	/* ����ӹ��� */
	void	addBoneChild(MyCCBone* _child);
	/* �����ڸ������еİ�λ�ã�����ӵ�� parent ʱ������ */
	void	setLockPosition(float _x, float _y, float _skewX = 0, float _skewY = 0);
	/* ����λ�� */
	void	update( float dt );
	/* ��ȡ�� Armatur.display �е�ȫ�� x ���� */
	float	 getGlobalX();
	/* ��ȡ�� Armatur.display �е�ȫ�� y ���� */
	float	getGlobalY();
	/* ��ȡ�� Armatur.display �е�ȫ�� rotation */
	float	getGlobalR();
	float	getGlobalSkewX();
	float	getGlobalSkewY();

	/* �жϹ����Ƿ�Ϊ����֡����*/
	bool    isBoneFrames();

	void	setTween(MyCCTween *_tween)
	{
		mAttachTweenNode = _tween;
	}

	MyCCTween*	getTween()
	{
		return mAttachTweenNode;
	}

	void SetBoneDisplay(CCSprite* display,const char* _displayImageName);
public:
	/* ���� display */
	void updateDisplay();
	void reset();
public:

	/* �������� Armature ͨ������������ Bone��Animation ͨ������������ Bone �� Tween �Ĺ��� */	
	CC_SYNTHESIZE(const char *, mName, Name);
	
	/* �����󶨵���ʾ���󣬲����Ǳ���ģ����Բ�����ʾ���� */
	CC_SYNTHESIZE(CCNode	*, mDisplay, Display);

	/* �����ܿ��ƵĹؼ��� */
	CC_SYNTHESIZE(CCBaseNode	*, mNode, Node);

	/* �� Tween ���ƵĹؼ��㣬������ Tween ������ node �ĺ�ֵ���� */
	CC_SYNTHESIZE(CCTweenNode *, mTweenNode, TweenNode);

	CC_SYNTHESIZE(MyCCBone *, mParent, Parent);
	CC_SYNTHESIZE_PASS_BY_REF(std::string, mParentName, ParentName);

	/* �����Ƿ�Ϊ����֡����*/
	CC_SYNTHESIZE(bool, mIsFrames, IsFrames);

protected:
	
	bool	mIsRadian;
	float	mTransformX;
	float	mTransformY;
	float	mTransformSkewX;
	float	mTransformSkewY;
	float	mTransformRotation;
	float	mLockX;
	float	mLockY;
	float	mLockR;
	float	mLockSkewX;
	float	mLockSkewY;
	float	mParentX;
	float	mParentY;
	float	mParentR;
	float	mParentSkewX;
	float	mParentSkewY;

private:
	MyCCTween *mAttachTweenNode;
	MyCCArmature *mDependArmature;

	// Note: Ӧ���ڹ��������Ż�
	std::map<std::string,CCSprite*>	mAttachBoneSprites;
};

