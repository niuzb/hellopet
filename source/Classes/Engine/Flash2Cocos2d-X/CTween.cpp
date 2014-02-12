#include "CTween.h"

//cocos2d::CCArray * CCTween::sObjectPool = NULL;
//int CCTween::sPoolIndex = -1;

MyCCTween* MyCCTween::create() {

	//if( !sObjectPool ){
	//	sObjectPool = new CCArray();
	//	CCAssert(sObjectPool->init(), "create CCTween fail!");
	//}

	//sPoolIndex ++;

	//if ( sPoolIndex < sObjectPool->count()) {
	//	CCTween* _tween =(CCTween*) sObjectPool->objectAtIndex(sPoolIndex);
	//	return _tween;
	//}

	MyCCTween *pTween = new MyCCTween();
	if (pTween && pTween->init()){
		pTween->autorelease();
		//sObjectPool->addObject(pTween);
		return pTween;
	}
	CC_SAFE_DELETE(pTween);
	return NULL;

}

void MyCCTween::removePoolObject(){
	//if( sObjectPool ){
	//	sObjectPool->removeAllObjects();
	//	CC_SAFE_DELETE( sObjectPool );
	//}
}


void MyCCTween::recycle(MyCCTween* _tween) {
	//sPoolIndex --;
}



MyCCTween::MyCCTween(){
	mFrom		= NULL;
	mTo			= NULL;
	mNode		= NULL;
	mTweenList	= NULL;
	mPauseOnOver = false;
}


MyCCTween::~MyCCTween(void){
	CC_SAFE_DELETE( mFrom );
	CC_SAFE_DELETE( mTo );
}


bool MyCCTween::init(){
	bool bRet = false;
	do {

		if( !mFrom ){
			mFrom = new CCTweenNode();
		}
		if( !mTo ){
			mTo = new CCTweenNode();
		}
		
		bRet = true;
	} while (0);

	return bRet;
}



void MyCCTween::remove(){
	stop();
	MyCCProcessBase::remove();
	mNode = NULL;
	mTweenList = NULL;
	mFrom->remove();
	mTo->remove();
	recycle(this);
}

void MyCCTween::setNode(CCTweenNode* _node) {
	mNode = _node;
}

void MyCCTween::playTo(void * _to, int _toFrames, int _listFrames, bool _loop, int _ease){

	MyCCProcessBase::playTo(_to, _toFrames, _listFrames, _loop, _ease);

	mPauseOnOver = false;
	setActive(true);

	mNode->reset();
	mNode->rotation = (int)(mNode->rotation) % 360;
	mFrom->copy(mNode);
	mTweenList = (CCFrameNodeList*)_to;

	mEase = _ease;

	if (mTweenList->getLength() == 1) {
		//��ͨ����
		mLoop = SINGLE;
		mFrom->copy(mTweenList->getFrame(0));
		mTo->copy(mTweenList->getFrame(0));
		mTotalFrames = mDuration = 1;
	}else {
		if (_loop) {
			//ѭ������
			mLoop = LIST_LOOP_START;
			mDuration = mTweenList->getFrame();
		}else {
			//�б����
			mLoop = LIST_START;
			mDuration = mTweenList->getFrame() - 1;
		}
		mDurationTween = _listFrames * mTweenList->getScale();
		if (_loop && mTweenList->getDelay() != 0) {
			float _playedFrames = mDuration * (1 - mTweenList->getDelay());
			int _prevFrameID = 0;
			int _toFrameID = 0;
			int _listEndFrame = 0;
			int _betweenFrame = 0;
			do {
				_betweenFrame = mTweenList->getFrame(_toFrameID)->frame;
				_listEndFrame += _betweenFrame;
				_prevFrameID = _toFrameID;
				if (++_toFrameID >= mTweenList->getLength()) {
					_toFrameID = 0;
				}
			}while (_playedFrames >= _listEndFrame);

			mTo->betweenValue(mTweenList->getFrame(_prevFrameID), mTweenList->getFrame(_toFrameID));

			float _currentPrecent = 1 - (_listEndFrame - _playedFrames) / _betweenFrame;
			if (mEase == 2) {
				_currentPrecent = 0.5 * (1 - cos(_currentPrecent * M_PI ));
			}else if (mEase != 0) {
				_currentPrecent = mEase > 0?sin(_currentPrecent * HALF_PI):(1 - cos(_currentPrecent * HALF_PI));
			}
			mTo->tweenTo(_currentPrecent);
		}else {
			mTo->copy(mTweenList->getFrame(0));
			mFrom->copy(mTweenList->getFrame(0));
			mCurrentFrame = 0;
		}
	}
	mNode->betweenValue(mFrom, mTo);	
	mNode->setIsSameFrameFlag(true);
}


void MyCCTween::updateHandler() {
	if (mCurrentPrecent >= 1) {
		switch(mLoop) {
		case LIST:
			mCurrentPrecent = 1;
			mIsComplete = true;
			break;
		case LIST_LOOP_START:
			//ѭ����ʼ
			mLoop = 0;
			mCurrentPrecent = mCurrentPrecent * mTotalFrames / mDurationTween;
			mTotalFrames = mDurationTween;
			if (mTweenList->getDelay() != 0) {
				mCurrentFrame = (1 - mTweenList->getDelay()) * mTotalFrames;
				mCurrentPrecent += mCurrentFrame / mTotalFrames;
			}
			
			mTotalDuration = 0;
			
			break;
		case LIST_START:
			//�б����
			mLoop = SINGLE;
			mCurrentFrame = mCurrentPrecent * mTotalFrames;
			mCurrentPrecent = mCurrentFrame / mDurationTween;
			if (mCurrentPrecent >= 1) {
				//
			}else {
				mTotalFrames = mDurationTween;
				//mCurrentPrecent = (int)(mCurrentPrecent) % 1;
				mTotalDuration = 0;
				break;
			}
		case SINGLE:
			if (mLoop == false)
			{
				mNode->visible = false;
			}			
			mCurrentPrecent = 1;
			mIsComplete = true;
			break;
		
		default:
			//����ѭ��			
			mLoop += int(mCurrentPrecent);
			mCurrentPrecent = (int)(mCurrentPrecent) % 1;
			break;
		}
	}else if (mLoop < -1) {
		mCurrentPrecent = sin(mCurrentPrecent * HALF_PI);
	}
	if (SINGLE == mLoop || mLoop >= -1) {
		if (mTweenList->getLength() != 1)
		{
			//��ؼ�֡��������
			updateCurrentPrecent();
		}
	}
	mNode->tweenTo(mCurrentPrecent);
}

void MyCCTween::updateCurrentPrecent(){
	float _playedFrames = mDuration * mCurrentPrecent;

	//����ͷ���ﵱǰ֡��ǰ������������Ѱ�ҵ�ǰ֡
	if (_playedFrames <= mTotalDuration-mBetweenDuration || _playedFrames > mTotalDuration) {
		mTotalDuration = 0;
		mToFrameID = 0;
		int _prevFrameID = 0;
		
		do {
			mBetweenDuration = mTweenList->getFrame(mToFrameID)->frame;
			mTotalDuration += mBetweenDuration;
			_prevFrameID = mToFrameID;

			if (++mToFrameID >= mTweenList->getLength()) {
				if (mPauseOnOver)
				{
					mToFrameID --;
				}
				else
				{
					mToFrameID = 0;
				}								
			}
		}while (_playedFrames >= mTotalDuration);

		mFrom->copy(mTweenList->getFrame(_prevFrameID));
		mTo->copy(mTweenList->getFrame(mToFrameID));
		
		mNode->betweenValue(mFrom, mTo);

	}

	mCurrentPrecent = 1 - (mTotalDuration - _playedFrames) / mBetweenDuration;

	
	/*if (mEase == 2) {
		mCurrentPrecent = 0.5 * (1 - cos(mCurrentPrecent * M_PI ));
	}else if (mEase != 0) {
		mCurrentPrecent = mEase > 0?sin(mCurrentPrecent * HALF_PI):(1 - cos(mCurrentPrecent * HALF_PI));
	}*/
}

void MyCCTween::setActive(bool _active){
	mActive = _active;
	mNode->active = _active;
}

bool MyCCTween::getActive(){
	return mActive;
}