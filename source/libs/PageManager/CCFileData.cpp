#include "CCFileData.h"

CCFileData::CCFileData(const char* pszFileName, const char* pszMode)
	: m_pBuffer(0)
	, m_uSize(0)
{
	m_pBuffer = CCFileUtils::sharedFileUtils()->getFileData(pszFileName, pszMode, &m_uSize);
}

CCFileData::~CCFileData()
{
	CC_SAFE_DELETE_ARRAY(m_pBuffer);
}

bool CCFileData::reset(const char* pszFileName, const char* pszMode)
{
	CC_SAFE_DELETE_ARRAY(m_pBuffer);
	m_uSize = 0;
	m_pBuffer = CCFileUtils::sharedFileUtils()->getFileData(pszFileName, pszMode, &m_uSize);
	return (m_pBuffer) ? true : false;
}