#include "CProcessBase.h"

#define USE_FIX_FRAME_RATES

MyCCProcessBase::MyCCProcessBase(void) {
    mScale = 1;
    mIsComplete = false;
    mIsPause = false;
    mCurrentFrame = 0;
	mToFrameID = 0;

	mDuration = 0;
	mCurrentPrecent = 0;
	mLoop = true;
	mEase = 0;

	mBetweenDuration = 0;
	mTotalDuration = 0;

	mTotalFrames = 0;
	mDurationTween = 0;	

#ifdef USE_FIX_FRAME_RATES
	mAnimationInternal = 1.0f / FRAME_RATES;
#else
	mAnimationInternal = CCDirector::sharedDirector()->getAnimationInterval();
#endif	
}


MyCCProcessBase::~MyCCProcessBase(void) {
}

void MyCCProcessBase::resetValue()
{
	mScale = 1;
	mIsComplete = true;
	mIsPause = false;
	mCurrentFrame = 0;
	mToFrameID = 0;
}


void MyCCProcessBase::remove() {
    mScale = 1;
    mIsComplete = true;
    mIsPause = false;
    mCurrentFrame = 0;
}
void MyCCProcessBase::pause() {
    mIsPause = true;
}


void MyCCProcessBase::resume() {
    mIsPause = false;
}

void MyCCProcessBase::stop() {
    mIsComplete = true;
    mCurrentFrame = 0;
}

void MyCCProcessBase::playTo(void * _to, int _durationTo, int _durationTween,  bool _loop, int _ease) {
    mIsComplete = false;
    mIsPause = false;
    mCurrentFrame = 0;
    mTotalFrames = 0;
	mCurrentPrecent = 0;
    mEase = _ease;
	mLoop = _loop;

	mScale = 1;
	mToFrameID = 0;

	mDuration = 0;

	mBetweenDuration = 0;
	mTotalDuration = 0;

	mDurationTween = 0;	
}

void MyCCProcessBase::update(float dt) {
    if (mIsComplete || mIsPause) {
        return;
    }
	
    if( mTotalFrames == 0 ) {
        //CCLOG( "mTotalFrames is zero!" );
		mCurrentPrecent = 1;
    }
	else
	{
		mCurrentFrame += 1 * (dt/mAnimationInternal);

		mCurrentPrecent = mCurrentFrame / (mTotalFrames);

		if( mCurrentFrame > mTotalFrames ){
			mCurrentFrame = (int)(mCurrentFrame) % mTotalFrames;
		}
	}
    
    updateHandler();
}

void MyCCProcessBase::updateHandler() {
}