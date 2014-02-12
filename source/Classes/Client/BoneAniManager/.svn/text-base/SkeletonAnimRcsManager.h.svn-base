#ifndef _SKELETON_ANIM_RCS_MANAGER_
#define _SKELETON_ANIM_RCS_MANAGER_

#include "string"
#include "Engine/XmlParser/TinyXml/tinystr.h"
#include "Engine/XmlParser/TinyXml/tinyxml.h"
#include "Engine/Singleton_t.h"
#include "SkeletonAnimCommonDefine.h"
#include "Client/Sprite/RoleActorBase.h"
#include "Client/GameManager/XLogicManager.h"

class AnimABBoxDataCenter;

class SkeletonAnimRcsManager:public TSingleton<SkeletonAnimRcsManager>
{
public:	
	SkeletonAnimRcsManager();
	virtual ~SkeletonAnimRcsManager();
	
	/**
	* Instruction : RoleActorConfig.xml读取数据
	* @param : 
	* @result : 
	*/
	void LoadRoleAnimConfigFile();
	/**
	* Instruction : 加载所有动画的数据资源
	* @param : 
	* @result : 
	*/
	void LoadAllAnimConnectionData();
	/**
	* Instruction : 加载通用动画资源
	* @param : 
	* @result : 
	*/
	void LoadCommonRcs(bool bInOtherLand);
	/**
	* Instruction : 加载一个角色所有动画资源
	* @param : 
	* @result : 
	*/
	void LoadOneRoleRcs(int roleId,bool bInOtherLand);	
	/**
	* Instruction : 加载一个角色除特效相关的资源
	* @param 
	*/
	void LoadOneRoleRcsExcepthEffects(int roleId);
	/**
	* Instruction : 判断某角色资源是否存在
	* @param : 
	* @result : 
	*/
	bool IsOneActorRcsExist(int typeId);
	/**
	* Instruction : 获取某一个角色 某动画的播放总帧数
	* @param 
	*/
	int GetOneRoleActorFrames(int roleId,int animId);
	/**
	* Instruction : 获取动画时间s
	* @param 
	*/
	float GetOneRoleActorDuration(int roleId,int animId);

	/**
	* Instruction : 创建角色依赖的骨骼动画
	* @param : 
	* @result : 
	*/
	std::map<std::string,RoleActorBase*> * CreateOneRoleArmatures(int role_id,bool bMainLand = true);
	/**
	* Instruction : 获取一个角色相关的动画数据
	* @param : 
	* @result : 
	*/
	OneRoleActorData * GetOneRoleArmatureActionData(int id);
	/**
	* Instruction : 加载动画相关的碰撞框等信息
	* @param : 
	* @result : 
	*/
	void ReadABBoxData();
	/**
	* Instruction : get data center
	* @param : 
	* @result : 
	*/
	AnimABBoxDataCenter* GetABBoxDataCenter();

	void ClearAllLoadedRcs();
	// Note: 加载场景需要的资源
	//void LoadLayerNeedRcs(XLogicManager::GAME_LOGIC_LAYER sceneTag);
private:
	void loadOneRcs(std::string rcsPath);
	void loadOneRoleAttachEffectRcs(int roleId);

	/**
	* Instruction : 根据字符串获取动作ID
	* @param : 
	* @result : 
	*/
	int getOneActionId(const char* actionTypeStr);

	/**
	* Instruction : read role animation info from out file
	* @param : 
	* @result : 
	*/
	TiXmlElement * initXML(const char * filePath);

	bool readMapAttachedRcsDataFromFile(TiXmlElement *root);
	bool readRolesAnimRcsDataFromFile(TiXmlElement *root);
	bool readRolesActorDataFromFile(TiXmlElement *root);
	bool readArmatureRcsDataFromeFile(TiXmlElement *root);		
private:
	RolesActorDataCollection* rolesActorRcsDataCollection;
	RolesAnimRcsDataCollection* rolesAnimRcsDataCollection;
	MapAttachedAniRcsData*	mapAttachAnimRcsData;

	AnimABBoxDataCenter* abBoxDataCenter;

	bool m_isLoadAllData;

	std::set<std::string> setLoadedAnimFiles;
	std::set<unsigned int> setLoadRoles;
};

#endif	//_SKELETON_ANIM_RCS_MANAGER_
