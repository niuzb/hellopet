#include "CArmature.h"
#include "CConnectionData.h"
#include "CConstValue.h"

CCBoneDisplayFactory::~CCBoneDisplayFactory()
{	
	//for(size_t i = 0; i < m_vecDisplay.size(); i++)
	//{
	//	CCSprite* sprite = (m_vecDisplay[i]);
	//	if (sprite)
	//	{
	//		sprite->release();
	//	}
	//}
	//m_vecDisplay.clear();
}


void CCBoneDisplayFactory::RecordBoneDisplay(CCSprite* sprite)
{
	//m_vecDisplay.push_back(sprite);
}


MyCCArmature *MyCCArmature::create(const char* _name, 
	const char* _animationName,
	CCSpriteBatchNode *_batchNode, 
	int _index, 
	bool _isRadian, 
	const char* _eachImageSuffix) {
    //CCXLOG("Enter MyCCArmature::createArmature");

    MyCCArmature *_armature = new MyCCArmature();
    if (_armature && _armature->init(_name, _animationName, _batchNode, _index, _isRadian, _eachImageSuffix)) {
        _armature->autorelease();
        return _armature;
    }
    CC_SAFE_DELETE(_armature);
    return NULL;

    //CCXLOG("Finish MyCCArmature::createArmature");
}


CCSprite* MyCCArmature::createBoneDisplay(const char* _boneName) {
	std::string _boneNameStr = _boneName;
	_boneNameStr.append(mEachImageSuffix);
	return getTextureDisplay(_boneNameStr.c_str() );
}

CCSprite* MyCCArmature::getTextureDisplay(const char* _boneName) {
    CCSprite *_display = CCSprite::createWithSpriteFrameName(_boneName);
	
	/// name current bone sprite
	if (_display)
	{
		//_display->m_name = _boneName;
	}else
	{
		CCLog("MyCCArmature::getTextureDisplay error! %s", _boneName);
	}

    return _display;
}

CCSprite* MyCCArmature::createArmatureDisplay(const char* _armatureName) {
    return CCSprite::create();
}




MyCCArmature::MyCCArmature() {
    mAnimation				= NULL;
    mDisplay				= NULL;
    mIsRadian				= false;
    mArmaureDisplayFactory	= NULL;
    mBoneDisplayFactory		= NULL;
	mBoneDic				= NULL;
	mBoneList				= NULL;
	mDisPlayBatchNode		= NULL;
	mEachImageSuffix		= SKELETON_IMAGE_FILE_SUFFIX;
	mbUpdate = true;
}


MyCCArmature::~MyCCArmature(void) {
	remove();
	CC_SAFE_DELETE(mBoneDic);
	CC_SAFE_DELETE(mBoneList);
	if (mCurBoneVec)
	{
		mCurBoneVec->clear();
		CC_SAFE_DELETE(mCurBoneVec);
	}
	if (mNotVisibleBoneVec)
	{
		mNotVisibleBoneVec->clear();
		CC_SAFE_DELETE(mNotVisibleBoneVec);
	}
	unscheduleUpdate();
}

void MyCCArmature::clearAllData()
{

}

void MyCCArmature::getCurBoneLst()
{
	clearCurBoneLst();

	CCObject *_object = NULL;
	CCARRAY_FOREACH(mBoneList, _object){
		MyCCBone *_bone = (MyCCBone*)_object;
		if (_bone->getTweenNode()->active)
		{
			mCurBoneVec->push_back(_bone);
		}
		else
		{
			mNotVisibleBoneVec->push_back(_bone);
		}
	}
}

void MyCCArmature::clearCurBoneLst()
{	
	if (mCurBoneVec)
	{
		mCurBoneVec->clear();
	}
	if (mNotVisibleBoneVec)
	{
		mNotVisibleBoneVec->clear();
	}
}

bool MyCCArmature::init(const char* _name, const char* _animationName, CCSpriteBatchNode *_batchNode, int _index, bool _isRadian, const char* _eachImageSuffix) 
{   
	//CCObject::m_name = _name;
	//CCObject::m_name = CCObject::m_name + _animationName;
	
	bool bRet = false;
    do {

		// init attributes
        mAnimation	= MyCCArmatureAnimation::create();
        CCAssert(mAnimation, "create MyCCArmature::mAnimation fail!");
        addChild(mAnimation);

		mIsRadian	= _isRadian;

		mBoneDic	= new CCDictionary();
		CCAssert(mBoneDic, "create MyCCArmature::mBoneDic fail!");

		mBoneList	= new CCArray();
		CCAssert(mBoneList->init(), "create MyCCArmature::boneList fail!");

		mCurBoneVec	= new std::vector<MyCCBone*>();
		mNotVisibleBoneVec = new std::vector<MyCCBone*>();

        mEachImageSuffix = _eachImageSuffix;

		mDisPlayBatchNode = _batchNode;
		mDisPlayBatchNode->retain();

		mName = _name;
		

		// create armature display , which is the top parent of the bone display
        if( !mArmaureDisplayFactory ) {
            mArmaureDisplayFactory = this;
        }

        do {
            mDisplay = mArmaureDisplayFactory->createArmatureDisplay(_name);

			//mDisplay->m_name = _name;


            CCAssert(mDisplay, "create MyCCArmature::init::mDisplay fail.");
			if( _batchNode ){
				if( static_cast<CCSprite*>(mDisplay) ){
					CCSprite *_sprite = (CCSprite*)mDisplay;
					_sprite->initWithTexture(mDisPlayBatchNode->getTexture(), CCRectZero);
				}

				mDisPlayBatchNode->addChild(mDisplay, _index);
			}

        } while (0);


        CCArmatureAniData* _animationData = CCConnectionData::sharedConnectionData()->getAnimationData(_animationName);
        CCAssert(_animationData, "CCArmatureAniData not exist! ");
		mAnimation->setData(_animationData);


		CCArray *_armatureDatas = CCConnectionData::sharedConnectionData()->getArmatureData(_name);
		CCAssert(_armatureDatas->count()>0, "_armatureData->count() should not <=0");
		
		/// create bones 
		if (false == createBones(_armatureDatas))
			return false;
        
        scheduleUpdate();		
		pauseAllAnimation();
		mDisPlayBatchNode->setVisible(false);
		mDisplay->setVisible(false);

		setArmaturetOpacity(255);

        bRet = true;		
    } while (0);

    return bRet;
}

bool MyCCArmature::createBones(CCArray *_armatureDatas)
{

	MyCCBone			*_bone;
	PCCArmatureData _boneData;
	const char		*_boneName;
	const char		*_parentName;
	const char		*_imageName;
	CCSprite		*_boneDisplay;
	int				_indexZ;
	int				_length = _armatureDatas->count();

	for(int indexI = 0; indexI < _length; indexI++) {
		_boneData = (PCCArmatureData)_armatureDatas->objectAtIndex(indexI);
		_boneName = _boneData->name.c_str();
		_parentName = _boneData->parent.c_str();
		_imageName = _boneData->boneImage.c_str();
		_indexZ = _boneData->z;

		if( !mBoneDisplayFactory ) 
		{
			mBoneDisplayFactory = this;
		}

		do 
		{
			_boneDisplay = mBoneDisplayFactory->createBoneDisplay(_imageName);
			mBoneDisplayFactory->RecordBoneDisplay(_boneDisplay);
			CCAssert(_boneDisplay, "create MyCCArmature::init::_boneDisplay fail.");
			if (NULL == _boneDisplay)
				return false;
		} while (0);


		_bone = addBone(_boneName, _parentName, _boneDisplay, _indexZ,_imageName);

		float _anchorPointX = _boneData->pivotX / _boneData->width;
		float _anchorPointY = (_boneData->height - _boneData->pivotY) / _boneData->height;

		if (_bone->getDisplay())
			_bone->getDisplay()->setAnchorPoint(ccp(_anchorPointX, _anchorPointY));
		_bone->setLockPosition( _boneData->x, _boneData->y , _boneData->skewX, _boneData->skewY);
	}


	resetBonesParent();

	return true;
}

void MyCCArmature::resetBonesParent()
{
	CCDictElement *_element = NULL;
	CCDICT_FOREACH(mBoneDic, _element){
		MyCCBone *_bone = (MyCCBone *)_element->getObject();
		MyCCBone *_boneParent = (MyCCBone *)mBoneDic->objectForKey(_bone->getParentName());
		if(_boneParent) {
			_bone->setParent(_boneParent);
		}
	}
}


void MyCCArmature::update(float dt) 
{
	//dt = 1.0/60;

	if (mbAnimationPause)
	{
		if (this->getDisplay()->isVisible())
		{
			this->getDisPlayBatchNode()->setVisible(false);
			this->getDisplay()->setVisible(false);
		}
		return ;
	}
	if(false == this->getDisplay()->isVisible())
	{
		this->getDisPlayBatchNode()->setVisible(true);
		this->getDisplay()->setVisible(true);
	}

	mAnimation->update( dt );

	if (mNotVisibleBoneVec->size() != 0)
	{
		for (std::vector<MyCCBone*>::iterator iter = mNotVisibleBoneVec->begin();iter != mNotVisibleBoneVec->end(); iter++)
		{
			MyCCBone *_bone = (MyCCBone*)(*iter);
			if (_bone->getDisplay())
				_bone->getDisplay()->setVisible(false);
		}
		mNotVisibleBoneVec->clear();
	}

	bool bSingleAnimationOver = mAnimation->GetSingleAnimationOverOrNot();
	if (bSingleAnimationOver)
	{
		int i;
		i = 0;
	}
	if (mbUpdate && false == bSingleAnimationOver)
	{
		for (std::vector<MyCCBone*>::iterator iter = mCurBoneVec->begin();iter != mCurBoneVec->end(); iter++)
		{
			MyCCBone *_bone = (MyCCBone*)(*iter);
			mAnimation->updateTween(_bone->getTween(), dt);				
			_bone->update( dt );
		}
	}	

	mAnimation->SendAnimationHandleMessage();

	if (mbUpdate == false)
	{
		if (this->getDisplay()->isVisible())
		{
			this->getDisPlayBatchNode()->setVisible(false);
			this->getDisplay()->setVisible(false);
		}
	}
	else
	{
		if (false == this->getDisplay()->isVisible())
		{
			this->getDisPlayBatchNode()->setVisible(true);
			this->getDisplay()->setVisible(true);
		}
	}

	if (bSingleAnimationOver)
	{
		if (this->getDisplay()->isVisible())
		{
			this->getDisPlayBatchNode()->setVisible(false);
			this->getDisplay()->setVisible(false);
		}
	}
}

void MyCCArmature::remove() {

	CCObject *_object = NULL;
	MyCCBone *_bone;
	CCARRAY_FOREACH(mBoneList, _object){
		_bone = (MyCCBone*)_object;
		CCSprite* pSprite = (CCSprite*)_bone->getDisplay();
		pSprite->getParent()->removeChild(pSprite,true);
		_bone->remove();
	}

	mAnimation->remove();
    mAnimation = NULL;

	if( mDisPlayBatchNode ){
		mDisPlayBatchNode->removeChild(mDisplay, true);
		mDisPlayBatchNode->release();
	}
	mDisPlayBatchNode = NULL;
	mDisplay = NULL;

    mBoneDic->removeAllObjects();
    mBoneList->removeAllObjects();
}


MyCCBone* MyCCArmature::addBone(const char* _name, const char* _parentName, CCNode* _display, int _index,const char	*_displayImagName) 
{	
    MyCCBone *_bone = (MyCCBone*)mBoneDic->objectForKey(_name);
    if(!_bone) {
        _bone = MyCCBone::create(mIsRadian,this);
        _bone->setName(_name);		
        mBoneList->addObject(_bone);
        mBoneDic->setObject(_bone, _name);
        mAnimation->addTween(_bone);
		_bone->isBoneFrames();
		_bone->setParentName(_parentName);
    }
	else
	{
		CCLog("bone exist");
		_bone->reset();
	}

    if(_display) {
        CCNode* _displayOld = _bone->getDisplay();
        //_bone->setDisplay(_display);
		_bone->SetBoneDisplay((CCSprite*)_display,_displayImagName);
        if(_displayOld) {
			_displayOld->removeFromParentAndCleanup(true);
            mDisplay->addChild(_display, _index);
        } else if (_index == -1) {
            mDisplay->addChild(_display);
        } else if (_index >= 0) {
            mDisplay->addChild(_display, _index);
        }
    }
    return _bone;
}

MyCCBone *MyCCArmature::getBone(const char* _name) {
    return (MyCCBone*)mBoneDic->objectForKey(_name);
}

void MyCCArmature::removeBone(const char* _name) {
    MyCCBone *_bone = (MyCCBone*)mBoneDic->objectForKey(_name);
    if(_bone) {
        if(_bone->getDisplay() /*&& display->contains(_bone->display)*/) {
            mDisplay->removeChild(_bone->getDisplay(), false);
        }
        mAnimation->removeTween(_bone);
        _bone->remove();
    }
}

// stop
void MyCCArmature::pauseAllAnimation()
{
	this->getAnimation()->stop();
	mbAnimationPause = true;
}

// resume
void MyCCArmature::resumeAllAnimation()
{
	this->getAnimation()->resume();
	mbAnimationPause = false;
}

void MyCCArmature::setArmaturetOpacity(GLubyte var)
{
	//CCLog("------------------- setArmaturetOpacity ");
	std::vector<MyCCBone*> vecTmpBones = (*mCurBoneVec);

	bool bCalOpacity = false;
	GLubyte opacity = 0;
	CCObject *_object = NULL;
	CCARRAY_FOREACH(mBoneList, _object){
		MyCCBone *_bone = (MyCCBone*)_object;
		CCSprite* _pSprite = (CCSprite*)_bone->getDisplay();
		opacity = _pSprite->getOpacity();
		if (bCalOpacity == false)
		{
			bCalOpacity = true;
			if (var == opacity)
			{
				break;
			}
		}
		(_pSprite)->setOpacity(var);
	}
}

void MyCCArmature::setArmatureColor(ccColor3B color)
{
	CCObject *_object = NULL;
	CCARRAY_FOREACH(mBoneList, _object){
		MyCCBone *_bone = (MyCCBone*)_object;
		((CCSprite*)_bone->getDisplay())->setColor(color);
	}
}