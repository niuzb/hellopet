#pragma once

#include "CArmature.h"
#include "CBone.h"
#include "tinyxml.h"
#include "CConstValue.h"
#include "CTextureData.h"
#include "SkeletonAnimRcsManager.h"

#include <string>
using namespace  std;

class CConnDataReader
{
public:
	CConnDataReader(const char* _xmlConnFile);
	~CConnDataReader();

public:
	/// read float value
	bool  ReadFloat(float &fVal); 
	
	/// read string valule
	bool  ReadString(string & strVal);
	
	/// read int value
	bool  ReadInt32(int & iVal);

protected:
	unsigned long m_fileSize;
	unsigned long m_curPos;
	char* m_pstrContext;
};

class CConnDataWriter
{
public:
	CConnDataWriter(const char* _xmlConnFile);
	~CConnDataWriter();

public:
	/// write float value 
	void WriteFloat(float fVal);
	
	/// write string value , first write the string lenght then the content
	void WriteString(const string& val);

	/// write an int32 value
	void WriteInt32(const int & iVal);

protected:
	string m_strFile;
};



//格式化、管理骨骼配置与骨骼动画
class CCConnectionData : public CCObject {
public:
    static CCConnectionData *sharedConnectionData();
	static void purgeConnectionData();


private:
    CCConnectionData(void);
    ~CCConnectionData(void);

public:
    virtual bool init();
    
    CCArray *getArmatureData(const char* _id);
    
    CCArmatureAniData *getAnimationData(const char* _id);

	CCTexutreData *getTextureData(const char *_textureName);
    /**
    * 将XML数据转换成内置数据 ArmatureAniData 等
    * @param _xml XML数据
    */
    void addData(const char* _xml);

    void removeAll(bool _deletMe = false);

	/**
	* Instruction : 得到某一张图片的锚点
	* @param 
	*/
	CCPoint getOneImageAnchorPoint(std::string imageName);

	// Note: 数据管理
	void ClearDataExceptColliderAndPointData();
private:
    CCFrameNodeList	*getFrameNodeList(CConnDataReader* pFile, const char* _boneName);

    CCFrameNode	*getFrameNode(CConnDataReader* pFile);

	void decodeTextures(CConnDataReader* pFile);
	void decodeArmatures(CConnDataReader* pFile);
	void decodeAnimations(CConnDataReader* pFile);
private:
    //save armature datas.			 <const char*, std::vector<PCCArmatureData> > ;
	CC_SYNTHESIZE_READONLY(CCDictionary *, mArmarureDatas, ArmarureDatas);

    //save armature animation datas. <const char*, CCArmatureAniData*> ;
	CC_SYNTHESIZE_READONLY(CCDictionary *, mAnimationDatas, AnimationDatas);

	//save texture datas			 <const char*, CCTextureData*>
	CC_SYNTHESIZE_READONLY(CCDictionary *, mTextureDatas, TextureDatas);
private:
    static CCConnectionData *sSharedConnectionData;
};

