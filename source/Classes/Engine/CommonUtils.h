#ifndef _COMMON_UTILS_H_
#define _COMMON_UTILS_H_

#include "string"
#include "cocos2d.h"
#include "vector"

USING_NS_CC;

class CommonUtils
{
public:
	static std::string StringAppendMethod(std::string str,const char *suffix);
	static void Log(std::string TAG,const char * pszFormat, ...);
	static bool IsPointEqual(const CCPoint &pt1,const CCPoint &pt2);
	static void Swap(int* m,int* n);
	static void Bresenhamline(int x0,int y0,int x1,int y1,std::vector<CCPoint> &outVecPt);
	static void ConvertWinCoordToOpenGL(CCPoint& pt);	
};

#endif	//_COMMON_UTILS_H_