#include "CConnectionData.h"
#include "cocos2d.h"

USING_NS_CC;


CConnDataReader::CConnDataReader(const char* _xmlConnFile)
{
	unsigned long _size = 0;
	m_pstrContext = (char*)CCFileUtils::sharedFileUtils()->getFileData(_xmlConnFile , "rb", &_size);
	m_fileSize = _size;
	m_curPos = 0;
}

CConnDataReader::~CConnDataReader()
{
	CC_SAFE_DELETE_ARRAY(m_pstrContext);
}

bool CConnDataReader::ReadFloat(float &fVal)
{
	if (m_curPos + 4 <= m_fileSize)
	{
		//fVal = *(float *)(m_pstrContext + m_curPos);
		memcpy(&fVal,m_pstrContext + m_curPos,sizeof(float));
		m_curPos += 4;
		return true;
	}

	return false;
}

bool CConnDataReader::ReadInt32(int &iVal)
{
	if (m_curPos + 4 <= m_fileSize)
	{
		//iVal = *(int *)(m_pstrContext + m_curPos);
		memcpy(&iVal,m_pstrContext + m_curPos,sizeof(int));
		m_curPos += 4;
		return true;
	}

	return false;
}

bool CConnDataReader::ReadString(string & strVal)
{
	int nLen = 0;
	if (ReadInt32(nLen))
	{
		char * pszTemp = new char[nLen +1];
		strncpy(pszTemp, (m_pstrContext + m_curPos), nLen);
		pszTemp[nLen] = '\0';
		strVal = pszTemp;
		delete []pszTemp;
		m_curPos += nLen;
		return true;
	}

	return false;
}


CCConnectionData *CCConnectionData::sSharedConnectionData = NULL;

CCConnectionData *CCConnectionData::sharedConnectionData() {
    if (sSharedConnectionData == NULL) {
        sSharedConnectionData = new CCConnectionData();
        if (!sSharedConnectionData || !sSharedConnectionData->init()) {
            CC_SAFE_DELETE(sSharedConnectionData);
        }
    }
    return sSharedConnectionData;
}

void CCConnectionData::purgeConnectionData()
{
	if (sSharedConnectionData)
	{
		delete sSharedConnectionData;
		sSharedConnectionData = NULL;
	}
}

CCConnectionData::CCConnectionData(void) {

}


CCConnectionData::~CCConnectionData(void)
{
	removeAll();

	// free CCBones Pool
	MyCCBone::removePoolObject();
	MyCCTween::removePoolObject();
}

bool CCConnectionData::init() {
    bool bRet = false;
    do {

        mArmarureDatas = new CCDictionary();
        CCAssert(mArmarureDatas, "create CCConnectionData::mArmarureDatas fail!");

        mAnimationDatas = new CCDictionary();
        CCAssert(mAnimationDatas, "create CCConnectionData::mAnimationDatas fail!");

		mTextureDatas = new CCDictionary();
		CCAssert(mTextureDatas, "");

        bRet = true;
    } while (0);

    return bRet;
}

CCArray *CCConnectionData::getArmatureData(const char* _id) {
    return (CCArray *)mArmarureDatas->objectForKey(_id);
}

CCArmatureAniData* CCConnectionData::getAnimationData(const char* _id) {
    return (CCArmatureAniData*)mAnimationDatas->objectForKey(_id);
}

void CCConnectionData::addData(const char* _xml)
{
    //CCXLOG("Enter CCConnectionData::addData: %s", _xml);
	CConnDataReader file(_xml);
	string tempVal = "";
	bool bRet = file.ReadString(tempVal);
	CCAssert(tempVal == TEXTURE_ATLAS, "Texture_Atlas Node not found!");
	decodeTextures(&file);
	decodeArmatures(&file);
	decodeAnimations(&file);
}

void CCConnectionData::decodeTextures(CConnDataReader* pFile)
{
	int nTextures = 0;
	bool bRet = pFile->ReadInt32(nTextures);
	if (bRet)
	{
		for(int i = 0; i < nTextures; i++)
		{
			CCTexutreData *_texture = CCTexutreData::create();
			bRet = pFile->ReadString(_texture->name);
			bRet = pFile->ReadFloat(_texture->pivotX);
			bRet = pFile->ReadFloat(_texture->pivotY);
			bRet = pFile->ReadFloat(_texture->width);
			bRet = pFile->ReadFloat(_texture->height);
			//CCLog("decodeTextures: %s", _texture->name.c_str());
			mTextureDatas->setObject(_texture, _texture->name);
		}
	}
}

void CCConnectionData::decodeArmatures(CConnDataReader* pFile)
{
	int nArmature = 0;
	bool bRet = pFile->ReadInt32(nArmature);
	if (bRet)
	{				
		for(int i = 0; i < nArmature; i ++)
		{
			string name = "";
			bRet =  pFile->ReadString(name);
			CCArray *_newDatas = CCArray::create();
			mArmarureDatas->setObject(_newDatas, name);

			int nBones = 0;
			bRet =  pFile->ReadInt32(nBones);
			for(int j = 0; j < nBones ; j++)
			{
				CCArmatureData *_armatureData = CCArmatureData::create();

				bRet = bRet &&  pFile->ReadString(_armatureData->name);
				bRet = bRet && pFile->ReadString(_armatureData->boneImage);
				bRet = bRet && pFile->ReadString(_armatureData->parent);

				bRet = bRet && pFile->ReadFloat((_armatureData->x));
				bRet = bRet && pFile->ReadFloat((_armatureData->y));
				bRet = bRet && pFile->ReadFloat((_armatureData->skewX));
				bRet = bRet && pFile->ReadFloat((_armatureData->skewY));
				bRet = bRet && pFile->ReadFloat((_armatureData->z));
				CCAssert(bRet, "read file wrong!");
				_armatureData->y = -_armatureData->y;
				_armatureData->skewY = -_armatureData->skewY;
				_armatureData->rotation = _armatureData->skewX;

				CCTexutreData *_textureData = (CCTexutreData *)mTextureDatas->objectForKey(_armatureData->boneImage);
				CCAssert(_textureData, "");

				_armatureData->pivotX = _textureData->pivotX;
				_armatureData->pivotY = _textureData->pivotY;
				_armatureData->width = _textureData->width;
				_armatureData->height = _textureData->height;

				_newDatas->addObject( _armatureData );	
			}
		}
	}
}

CCPoint CCConnectionData::getOneImageAnchorPoint(std::string imageName)
{
	int startPos = imageName.rfind(".pvr.ccz");
	imageName = imageName.substr(0,startPos);

	CCTexutreData *_textureData = (CCTexutreData *)mTextureDatas->objectForKey(imageName.c_str());
	CCAssert(_textureData, "");
	float pivotX = _textureData->pivotX;
	float pivotY = _textureData->pivotY;

	float _anchorPointX =  pivotX / _textureData->width;
	float _anchorPointY = (_textureData->height - pivotY) / _textureData->height;

	return ccp(_anchorPointX,_anchorPointY);
}

void CCConnectionData::decodeAnimations(CConnDataReader* pFile){
	int nAnimation = 0;
	bool bRet = pFile->ReadInt32(nAnimation);
	for(int i = 0; i < nAnimation; i++)
	{
		string _name = "";
		bRet = bRet && pFile->ReadString(_name);
		CCArmatureAniData	*_aniData = (CCArmatureAniData*)mAnimationDatas->objectForKey(_name);
		if (_aniData) {
			CCXLOG("CCArmatureAniData (%s) is already exit", _name.c_str());
			return;
		}

		_aniData =  CCArmatureAniData::create();
		mAnimationDatas->setObject( _aniData, _name);

		int nMovement = 0;
		bRet = bRet && pFile->ReadInt32(nMovement);
		for(int j = 0; j < nMovement; j++)
		{
			string _aniName;
			string _boneName;
			CCBoneAniData* _boneAniData = NULL;
						
			bRet = bRet && pFile->ReadString(_aniName);

			_boneAniData = CCBoneAniData::create();
			_aniData->addAnimation(_aniName.c_str(), _boneAniData);

			int _duration, _durationTo, _durationTween, _loop = 0;
			float _tweenEasing = 0.0f;

			bRet = bRet && pFile->ReadInt32(_duration);
			bRet = bRet && pFile->ReadInt32(_durationTo);
			bRet = bRet && pFile->ReadInt32(_durationTween);
			bRet = bRet && pFile->ReadInt32(_loop);
			bRet = bRet && pFile->ReadFloat(_tweenEasing);
			CCAssert(bRet, "decodeAnimations file wrong!");

			_boneAniData->setDuration(_duration);
			_boneAniData->setDurationTo(_durationTo);
			_boneAniData->setDurationTween(_durationTween);
			_boneAniData->setLoop((bool)(_loop != 0));
			_boneAniData->setTweenEasing(_tweenEasing);

			int nBones = 0;
			bRet = bRet && pFile->ReadInt32(nBones);
			for(int k = 0; k < nBones ; k++)
			{
				bRet = bRet && pFile->ReadString(_boneName);
				_boneAniData->addAnimation(getFrameNodeList(pFile, _boneName.c_str()), _boneName.c_str());
			}
		}
	}
}

CCFrameNodeList* CCConnectionData::getFrameNodeList(CConnDataReader* pFile, const char* _boneName) 
{
	CCFrameNodeList* _nodeList = CCFrameNodeList::create();
	float _scale, _delay;
	bool bRet = pFile->ReadFloat(_scale);
	bRet = bRet && pFile->ReadFloat(_delay);

	_nodeList->setScale(_scale);
	_nodeList->setDelay(_delay);   

	int nFrameNode = 0;
	bRet = bRet && pFile->ReadInt32(nFrameNode);
	for(int i = 0 ; i < nFrameNode; i++)
	{
		_nodeList->addFrame( getFrameNode( pFile ) );
	}

	return _nodeList;
}

CCFrameNode* CCConnectionData::getFrameNode(CConnDataReader* pFile)
{
    CCFrameNode* _node = CCFrameNode::create();
	
	bool bRet = pFile->ReadString(_node->img);
	bRet = bRet && pFile->ReadFloat(_node->rotation);
	bRet = bRet && pFile->ReadFloat(_node->x);
	bRet = bRet && pFile->ReadFloat(_node->y);  _node->y = -_node->y;
	bRet = bRet && pFile->ReadFloat(_node->z);
	bRet = bRet && pFile->ReadFloat(_node->scaleX);
	bRet = bRet && pFile->ReadFloat(_node->scaleY);
	bRet = bRet && pFile->ReadFloat(_node->skewX);
	bRet = bRet && pFile->ReadFloat(_node->skewY);  _node->skewY = -_node->skewY;

	bRet = bRet && pFile->ReadInt32(_node->frame);

	bRet = bRet && pFile->ReadFloat(_node->alpha);  _node->alpha = _node->alpha * 255;

	int _hide = 0;
	bRet = bRet && pFile->ReadInt32(_hide);
	CCAssert(bRet, "getFrameNode file wrong!");
	_node->visible = !(bool)(_hide != 0);   

    return _node;
}

void CCConnectionData::removeAll(bool _deletMe) 
{
    if( mAnimationDatas ) {
        mAnimationDatas->removeAllObjects();
		delete mAnimationDatas;
		mAnimationDatas = NULL;
    }
    if( mArmarureDatas ) {
        mArmarureDatas->removeAllObjects();
		delete mArmarureDatas;
		mArmarureDatas = NULL;
    }
	if( mTextureDatas ){
		mTextureDatas->removeAllObjects();
		delete mTextureDatas;
		mTextureDatas = NULL;
	}
}

void CCConnectionData::ClearDataExceptColliderAndPointData()
{
	if( mAnimationDatas ) {
		mAnimationDatas->removeAllObjects();
	}
	if( mArmarureDatas ) {
		mArmarureDatas->removeAllObjects();
	}
	if( mTextureDatas ){
		mTextureDatas->removeAllObjects();
	}
}