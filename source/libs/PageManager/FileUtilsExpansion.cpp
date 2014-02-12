#include "FileUtilsExpansion.h"
#include "cocos2d.h"
USING_NS_CC;

// record the resource path
static char s_pszResourcePath[MAX_PATH] = {0};

static void _CheckPath()
{
	if (! s_pszResourcePath[0])
	{
		WCHAR  wszPath[MAX_PATH] = {0};
		int nNum = WideCharToMultiByte(CP_ACP, 0, wszPath,
			GetCurrentDirectoryW(sizeof(wszPath), wszPath),
			s_pszResourcePath, MAX_PATH, NULL, NULL);
		s_pszResourcePath[nNum] = '\\';
	}
}


FileUtilsExpansion::FileUtilsExpansion()
{
}

FileUtilsExpansion::~FileUtilsExpansion()
{
}

const char* FileUtilsExpansion::fullPathFromRelativePath(const char *pszRelativePath,const char * additionalPath)
{
	return fullPathFromRelativePath((std::string(pszRelativePath)+std::string(additionalPath)).c_str());
}

const char* FileUtilsExpansion::fullPathFromRelativePath(const char *pszRelativePath)
{
	bool bFileExist = true;
	const char* resDir = m_obDirectory.c_str();
	CCString* pRet = CCString::create("");

	const std::string& resourceRootPath = CCApplication::sharedApplication()->getResourceRootPath();
	if ((strlen(pszRelativePath) > 1 && pszRelativePath[1] == ':'))
	{
		// path start with "x:", is absolute path
		pRet->m_sString = pszRelativePath;
	}
	else if (strlen(pszRelativePath) > 0
		&& ('/' == pszRelativePath[0] || '\\' == pszRelativePath[0]))
	{
		// path start with '/' or '\', is absolute path without driver name
		char szDriver[3] = {s_pszResourcePath[0], s_pszResourcePath[1], 0};
		pRet->m_sString = szDriver;
		pRet->m_sString += pszRelativePath;
	}
	else if (resourceRootPath.length() > 0)
	{
		pRet->m_sString = resourceRootPath.c_str();
		pRet->m_sString += m_obDirectory.c_str();
		pRet->m_sString += pszRelativePath;
	}
	else
	{
		pRet->m_sString = s_pszResourcePath;
		pRet->m_sString += resDir;
		pRet->m_sString += pszRelativePath;
	}

	// If file or directory doesn't exist, try to find it in the root path.
	if (GetFileAttributesA(pRet->m_sString.c_str()) == -1)
	{
		pRet->m_sString = s_pszResourcePath;
		pRet->m_sString += pszRelativePath;

		if (GetFileAttributesA(pRet->m_sString.c_str()) == -1)
		{
			bFileExist = false;
		}
	}

	if (!bFileExist)
	{ // Can't find the file, return the relative path.
		pRet->m_sString = pszRelativePath;
	}

	return pRet->m_sString.c_str();
}

void FileUtilsExpansion::setResourceDirectory(const char* pszResourceDirectory)
{
	m_obDirectory = pszResourceDirectory;
	if (m_obDirectory.size() > 0 && m_obDirectory[m_obDirectory.size() - 1] != '/')
	{
		m_obDirectory.append("/");
	}
}

const char* FileUtilsExpansion::getResourceDirectory()
{
	return m_obDirectory.c_str();
}