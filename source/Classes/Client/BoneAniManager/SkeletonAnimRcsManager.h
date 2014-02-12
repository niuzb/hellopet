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
	* Instruction : RoleActorConfig.xml��ȡ����
	* @param : 
	* @result : 
	*/
	void LoadRoleAnimConfigFile();
	/**
	* Instruction : �������ж�����������Դ
	* @param : 
	* @result : 
	*/
	void LoadAllAnimConnectionData();
	/**
	* Instruction : ����ͨ�ö�����Դ
	* @param : 
	* @result : 
	*/
	void LoadCommonRcs(bool bInOtherLand);
	/**
	* Instruction : ����һ����ɫ���ж�����Դ
	* @param : 
	* @result : 
	*/
	void LoadOneRoleRcs(int roleId,bool bInOtherLand);	
	/**
	* Instruction : ����һ����ɫ����Ч��ص���Դ
	* @param 
	*/
	void LoadOneRoleRcsExcepthEffects(int roleId);
	/**
	* Instruction : �ж�ĳ��ɫ��Դ�Ƿ����
	* @param : 
	* @result : 
	*/
	bool IsOneActorRcsExist(int typeId);
	/**
	* Instruction : ��ȡĳһ����ɫ ĳ�����Ĳ�����֡��
	* @param 
	*/
	int GetOneRoleActorFrames(int roleId,int animId);
	/**
	* Instruction : ��ȡ����ʱ��s
	* @param 
	*/
	float GetOneRoleActorDuration(int roleId,int animId);

	/**
	* Instruction : ������ɫ�����Ĺ�������
	* @param : 
	* @result : 
	*/
	std::map<std::string,RoleActorBase*> * CreateOneRoleArmatures(int role_id,bool bMainLand = true);
	/**
	* Instruction : ��ȡһ����ɫ��صĶ�������
	* @param : 
	* @result : 
	*/
	OneRoleActorData * GetOneRoleArmatureActionData(int id);
	/**
	* Instruction : ���ض�����ص���ײ�����Ϣ
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
	// Note: ���س�����Ҫ����Դ
	//void LoadLayerNeedRcs(XLogicManager::GAME_LOGIC_LAYER sceneTag);
private:
	void loadOneRcs(std::string rcsPath);
	void loadOneRoleAttachEffectRcs(int roleId);

	/**
	* Instruction : �����ַ�����ȡ����ID
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
