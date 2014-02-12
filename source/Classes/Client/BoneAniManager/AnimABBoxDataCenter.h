#ifndef _ANIM_ABBOX_DATA_CENTER_H_
#define _ANIM_ABBOX_DATA_CENTER_H_

#include "BoxDefine.h"
#include "cocos2d.h"

class TiXmlElement;

USING_NS_CC;

/// <summary> 
/// ¹Ç÷À¶¯»­Åö×²¿ò£¬¹¥»÷¿òµÈÐÅÏ¢´æ´¢
/// </summary> 

class AnimABBoxDataCenter
{
public:
	AnimABBoxDataCenter();
	virtual ~AnimABBoxDataCenter();

	void ReadData();

	bool GetColliderData(int role_id,int action_id,CCMoveAreaData &data);
	bool GetViewRectData(int role_id,std::string armatureName,CCAreaData &areaData);

	bool GetRoleColliderData(unsigned int id,CCColliderData& colliderData);
	bool GetRoleViewRectData(unsigned int roleId,std::map<std::string,CCAreaData> & areaData);
protected:
	void decodeColliderAreaAndPointData(TiXmlElement *_rootXML);
	void decodeColliderAreas(TiXmlElement *_collidersXML,CCColliderData &);
	void decodeAttachPointData(TiXmlElement *_attachPointsXML,std::map<int,CCPoint> &);
private:
	std::map<int,CCColliderData> *kvRoleIdAndColliderData;
	std::map<int,std::map<int,CCPoint> > *kvRoleIdAndAttachPointsData;
};

#endif	//_ANIM_ABBOX_DATA_CENTER_H_