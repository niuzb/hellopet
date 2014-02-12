#ifndef _PROP_MANAGER_H_
#define _PROP_MANAGER_H_

#include "Singleton_t.h"
#include "vector"
#include "set"
#include "map"
#include "PropBase.h"

class PropManager : public TSingleton<PropManager>
{
public:
	PropManager();
	~PropManager();

	PropBase* AddOneProp(PropsType propType,SpriteBase* pUser,CCNode* pParentNode,bool isHero,bool isPreload = false);
	void RemoveOneProp(PropBase* pProp);
	void Update(float dt);

	/**
	* Instruction : 
	* @param : 
	* @result : 
	*/
	bool IsOneTypePropBelongToOneRole(PropsType propType,CCNode* pNode);
protected:
	PropBase* CreateOneProp(PropsType propType,SpriteBase* pUser,CCNode* pParentNode,bool isHero);
private:
	std::set<PropBase*> mVecProps;
	std::map<PropsType,PropBase*> m_PreloadProps;
	bool mIsDeleteOneElement;
};

#endif	//_PROP_MANAGER_H_