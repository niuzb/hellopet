#ifndef _CCFILE_DATA_H_
#define _CCFILE_DATA_H_

#include "cocos2d.h"

USING_NS_CC;

class CCFileData
{
public:
	CCFileData(const char* pszFileName, const char* pszMode);
	~CCFileData();

	bool reset(const char* pszFileName, const char* pszMode);	

	CC_SYNTHESIZE_READONLY(unsigned char *, m_pBuffer, Buffer);
	CC_SYNTHESIZE_READONLY(unsigned long ,  m_uSize,   Size);
};

#endif	//_CCFILE_DATA_H_