/********************************************************************
	created:	2013/09/01
	created:	1:9:2013   13:57
	filename: 	E:\MagicLand\source\Classes\Client\BoneAniManager\SkeletonAnimCommonDefine.h
	file path:	E:\MagicLand\source\Classes\Client\BoneAniManager
	file base:	SkeletonAnimCommonDefine
	file ext:	h
	author:		jackran
	
	purpose:	
*********************************************************************/
#ifndef _SKELETON_ANIM_COMMON_DEFINE_ 
#define _SKELETON_ANIM_COMMON_DEFINE_  


#define SKELETON_ANIMATION_DIR "skeleton_animation/"
#define DATA_DIR "Data/"

#include "cocos2d.h"
#include "map"
#include <algorithm>

using namespace cocos2d;

enum ANIMATION_ACTION_TYPE
{
	kType_ANI_Action_Play = 100000,
};

enum ANIMATION_STATE
{
	kType_ANI_STATE_START = 0,
	kType_ANI_STATE_RUN,
	kType_ANI_STATE_COMPLETE,
	kType_ANI_STATE_UNKNOW
};

enum ATTACH_POINT_TYPE
{
	kType_PLAYER_NAME = 0,
	kType_ATTACK_HURT,
	kType_SHOOT_HOR,
	kType_SHOOT_UP,
	kType_SHOOT_DOWN
};

// Note:  角色相关的资源信息
// Note:  包括角色相关的动画XML文件名和绑定的特效
class OneRoleAniRcsData
{
public:
	OneRoleAniRcsData()
	{
		mMainLandFileNames = new std::vector<std::string>();
		mOtherLandFileNames = new std::vector<std::string>();
		mVecAttachEffects = new std::vector<int>();
	}

	~OneRoleAniRcsData()
	{
		if (NULL != mMainLandFileNames)
		{
			mMainLandFileNames->clear();
			CC_SAFE_DELETE(mMainLandFileNames);
		}

		if (NULL != mOtherLandFileNames)
		{
			mOtherLandFileNames->clear();
			CC_SAFE_DELETE(mOtherLandFileNames);
		}

		if (0 != mVecAttachEffects)
		{
			mVecAttachEffects->clear();
			CC_SAFE_DELETE(mVecAttachEffects);
		}
	}

	bool AddOneElement(std::string file_name,bool bOtherLand)
	{
		std::vector<std::string> *pVec = mMainLandFileNames;
		if (bOtherLand)
		{
			pVec = mOtherLandFileNames;
		}

		pVec->push_back(file_name);
		return true;
	}

	bool AddOneEffectID(int id)
	{
		if (find(mVecAttachEffects->begin(), mVecAttachEffects->end(), id) == mVecAttachEffects->end())
		{
			mVecAttachEffects->push_back(id);
			return true;
		}
		return false;
	}

	int getCount(bool bOtherLand)
	{
		std::vector<std::string> *pVec = mMainLandFileNames;
		if (bOtherLand)
		{
			pVec = mOtherLandFileNames;
		}

		if (NULL != pVec)
		{
			return pVec->size();
		}

		return 0;
	}

	const std::vector<std::string>* GetMainLandNames()
	{
		return mMainLandFileNames;
	}

	const std::vector<std::string>* GetOtherLandNames()
	{
		return mOtherLandFileNames;
	}

	const std::vector<int>* GetAttachEffects()
	{
		return mVecAttachEffects;
	}
private:
	// Note: 依赖的动画资源文件
	std::vector<std::string> *mMainLandFileNames;
	std::vector<std::string> *mOtherLandFileNames;
	// Note: 依赖的特效ID
	std::vector<int> *mVecAttachEffects;
};

// Note: 角色动画资源数据集
class RolesAnimRcsDataCollection
{
public:
	RolesAnimRcsDataCollection()
	{
	}

	~RolesAnimRcsDataCollection()
	{
		for (std::map<int,OneRoleAniRcsData *>::iterator iter = kvRoleIdAndRcsNameMap.begin();
			iter != kvRoleIdAndRcsNameMap.end(); iter++)
		{
			delete((*iter).second);
			(*iter).second = 0;
		}

		kvRoleIdAndRcsNameMap.clear();
	}

	bool AddOneElement(int id,OneRoleAniRcsData *data)
	{
		if (0 == data)
		{
			return false;
		}
		kvRoleIdAndRcsNameMap.insert(std::make_pair(id,data));
		return true;
	}

	const std::map<int,OneRoleAniRcsData* >& GetRolesAnimRcsData()
	{
		return kvRoleIdAndRcsNameMap;
	}
private:
	std::map<int,OneRoleAniRcsData *> kvRoleIdAndRcsNameMap;
};

// 动画基本信息列表
class OneAniBasicData
{
public:
	OneAniBasicData()
	{
		armature_index = 0;
		armature_name = "";
		animation_name = "";
		png_file_name = "";
	}
private:
	int armature_index;
	std::string armature_name;
	std::string animation_name;
	std::string png_file_name;
};

// Note: 具体一个动作对应的数据
// Note: xml <-> action name
class OneAnimActorData
{
public:
	OneAnimActorData()
	{
		this->xmlFileName = "";
		this->actionName = "";
	}
	OneAnimActorData(std::string xmlFileName,std::string actionName)
	{
		this->xmlFileName = xmlFileName;
		this->actionName = actionName;
	}

	std::string GetXmlFileName()
	{
		return xmlFileName;
	}

	std::string GetActionName()
	{
		return actionName;
	}
private:
	std::string xmlFileName;
	std::string actionName;
};

// Note: 一个角色所有动作列表
class OneRoleActorData
{
public:
	OneRoleActorData()
	{

	}

	~OneRoleActorData()
	{
		kvRoleActionTypeAndValues.clear();
	}

	void PushOneElement(int id,OneAnimActorData oneData)
	{
		kvRoleActionTypeAndValues.insert(std::make_pair(id,oneData));
	}

	const std::map<int,OneAnimActorData >& GetOneRoleActorData()
	{
		return kvRoleActionTypeAndValues;
	}
private:
	std::map<int,OneAnimActorData > kvRoleActionTypeAndValues;
};

// Note: 角色动作列表的管理
class RolesActorDataCollection
{
public:
	RolesActorDataCollection()
	{		
	}

	~RolesActorDataCollection()
	{
		for (std::map<int,OneRoleActorData *>::iterator iter = kvRoleTypeAndValues.begin();
			iter != kvRoleTypeAndValues.end(); iter++)
		{
			delete((*iter).second);
		}

		kvRoleTypeAndValues.clear();
	}

	void PushOneElement(int id,OneRoleActorData *oneData)
	{
		kvRoleTypeAndValues.insert(std::make_pair(id,oneData));
	}

	const std::map<int,OneRoleActorData* >& GetRolesActorData()
	{
		return kvRoleTypeAndValues;
	}
private:
	std::map<int,OneRoleActorData *> kvRoleTypeAndValues;
};

// 地图绑定的角色资源信息
class MapAttachedAniRcsData
{
public:
	MapAttachedAniRcsData()
	{
	}

	~MapAttachedAniRcsData()
	{
		mEffectCommonIdVec.clear();
	}

	void PushOneEffectId(int effectId)
	{
		mEffectCommonIdVec.push_back(effectId);
	}
	const std::vector<int> & GetCommonEffects()
	{
		return mEffectCommonIdVec;
	}
private:
	std::vector<int> mEffectCommonIdVec;
};

#endif //_SKELETON_ANIM_COMMON_DEFINE_