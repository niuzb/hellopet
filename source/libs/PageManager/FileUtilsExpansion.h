#ifndef _FILE_UTILS_EXPANSION_H_
#define _FILE_UTILS_EXPANSION_H_

#include "string"
#include <Singleton_t.h>

class FileUtilsExpansion:public TSingleton<FileUtilsExpansion>
{
public:	
	FileUtilsExpansion();
	virtual ~FileUtilsExpansion();
	   
    const char* fullPathFromRelativePath(const char *pszRelativePath);
	const char* fullPathFromRelativePath(const char *pszRelativePath,const char * additionalPath);

	/**
    @brief  Set the resource directory; we will find resources relative to this directory.
    @param pszDirectoryName  Relative path to root.
    */
    void setResourceDirectory(const char *pszDirectoryName);

    /**
    @brief  Get the resource directory
    */
    const char* getResourceDirectory();
protected:
	std::string m_obDirectory;
private:
	
};

#endif	//_FILE_UTILS_EXPANSION_H_
