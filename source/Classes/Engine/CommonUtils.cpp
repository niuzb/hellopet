#include "CommonUtils.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <Windows.h>
#endif
#include "CCStdC.h"
#include "math.h"
#include "cocos2d.h"
#include "Map/MapDataCenter.h"

#define MAX_LEN         (cocos2d::kMaxLogLen + 1)

USING_NS_CC;

std::string CommonUtils::StringAppendMethod(std::string str,const char *suffix)
{
	if (NULL ==suffix)
	{
		return str;
	}	
	return std::string(str+std::string(suffix));
}

void SetColor(unsigned short ForeColor=4,unsigned short BackGroundColor=0)                                                                                                   //可以接受0/1/2个参数
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,ForeColor|BackGroundColor);
#endif
}

void CommonUtils::Log(std::string TAG,const char * pszFormat, ...)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	SetColor(4);

	char szBuf[MAX_LEN];

	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf_s(szBuf, MAX_LEN, MAX_LEN, pszFormat, ap);
	va_end(ap);

	WCHAR wszBuf[MAX_LEN] = {0};
	MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
	OutputDebugStringW(wszBuf);
	OutputDebugStringA("\n");

	WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), szBuf, sizeof(szBuf), NULL, FALSE);
	printf("%s\n", szBuf);

#else
#define CCError CCLog
#endif
}

bool CommonUtils::IsPointEqual(const CCPoint &pt1,const CCPoint &pt2)
{
	return (pt1.x == pt2.x && pt1.y == pt2.y);
}

void CommonUtils::Swap(int* m,int* n)
{
	int t = 0;
	t=*m;
	*m=*n;
	*n=t;
}

void CommonUtils::Bresenhamline(int x0,int y0,int xEnd,int yEnd,std::vector<CCPoint> &outVecPt)
{
	outVecPt.clear();

	// Note: 点重复时不考虑
	if (x0 == xEnd && y0 == yEnd)
	{
		return ;
	}
	
	// Note: 判断象限
	// Note: X轴
	if (y0 == yEnd)
	{
		// Note: 正X轴 
		if (xEnd - x0 >0)
		{
			for (int pos = x0;pos <= xEnd;pos++)
			{
				outVecPt.push_back(ccp(pos,y0));	
			}
		}
		// Note: 负X轴 
		else
		{
			for (int pos = x0;pos >= xEnd;pos--)
			{
				outVecPt.push_back(ccp(pos,y0));
			}
		}
	}
	// Note: Y轴
	else if(x0 == xEnd)
	{
		// Note: 正Y轴
		if (yEnd - y0 > 0)
		{
			for (int pos = y0;pos <= yEnd;pos++)
			{
				outVecPt.push_back(ccp(x0,pos));	
			}
		}
		// Note: 负Y轴
		else
		{
			for (int pos = y0;pos >= yEnd;pos--)
			{
				outVecPt.push_back(ccp(x0,pos));
			}
		}
	}
	else
	{
		int deltaX = xEnd - x0;
		int deltaY = yEnd - y0;

		// Note: 第一象限
		if (deltaX > 0 && deltaY > 0)
		{
			// Note: 斜率=1
			if (deltaX == deltaY)
			{
				for (int posx = x0,posy = y0;posx <= xEnd,posy <= yEnd;posx++,posy++)
				{
					outVecPt.push_back(ccp(posx,posy));	
				}
			}
			// Note: 斜率<1
			else if (deltaX > deltaY)
			{
				int dx = deltaX ;
				int dy = deltaY ;
				int p = 2*dy - dx;
				int twoDy = 2 * dy;
				int twoByMinusDx = 2 * (dy - dx);
				int x,y;
				x = x0;
				y = y0;

				outVecPt.push_back(ccp(x,y));

				while(x < xEnd)
				{
					x ++;
					if (p < 0)
					{
						p += twoDy;
					}
					else
					{
						y++;
						p += twoByMinusDx;
					}
					outVecPt.push_back(ccp(x,y));
				}
			}
			// Note: 斜率>1
			else if (deltaX < deltaY)
			{
				int newEndPosX = x0 + (yEnd - y0);
				int newEndPosY = y0 + (xEnd - x0);

				int dx = newEndPosX - x0 ;
				int dy = newEndPosY - y0 ;
				int p = 2*dy - dx;
				int twoDy = 2 * dy;
				int twoByMinusDx = 2 * (dy - dx);
				int x,y;
				x = x0;
				y = y0;

				outVecPt.push_back(ccp(x,y));

				while(x < newEndPosX)
				{
					x ++;
					if (p < 0)
					{
						p += twoDy;
					}
					else
					{
						y++;
						p += twoByMinusDx;
					}
					int newDeltaX = x - x0;
					int newDeltaY = y - y0;
					outVecPt.push_back(ccp(x0+newDeltaY,y0+newDeltaX));
				}
			}
		}
		// Note: 第四象限
		if (deltaX > 0 && deltaY < 0)
		{
			deltaY = -deltaY;
			yEnd = (y0) + deltaY;			

			// Note: 斜率=1
			if (deltaX == deltaY)
			{
				for (int posx = x0,posy = y0;posx <= xEnd,posy <= yEnd;posx++,posy++)
				{
					float newDeltaY = posy - y0;
					outVecPt.push_back(ccp(posx,y0-newDeltaY));	
				}
			}
			// Note: 斜率<1
			else if (deltaX > deltaY)
			{
				int dx = deltaX ;
				int dy = deltaY ;
				int p = 2*dy - dx;
				int twoDy = 2 * dy;
				int twoByMinusDx = 2 * (dy - dx);
				int x,y;
				x = x0;
				y = y0;

				outVecPt.push_back(ccp(x,y));

				while(x < xEnd)
				{
					x ++;
					if (p < 0)
					{
						p += twoDy;
					}
					else
					{
						y++;
						p += twoByMinusDx;
					}
					float newDeltaY = y - y0;
					outVecPt.push_back(ccp(x,y0-newDeltaY));
				}
			}
			// Note: 斜率>1
			else if (deltaX < deltaY)
			{
				int newEndPosX = x0 + (yEnd - y0);
				int newEndPosY = y0 + (xEnd - x0);

				int dx = newEndPosX - x0 ;
				int dy = newEndPosY - y0 ;
				int p = 2*dy - dx;
				int twoDy = 2 * dy;
				int twoByMinusDx = 2 * (dy - dx);
				int x,y;
				x = x0;
				y = y0;

				outVecPt.push_back(ccp(x,y));

				while(x < newEndPosX)
				{
					x ++;
					if (p < 0)
					{
						p += twoDy;
					}
					else
					{
						y++;
						p += twoByMinusDx;
					}
					int newDeltaX = x - x0;
					int newDeltaY = y - y0;
					int newPosX = x0+newDeltaY;
					int newPosY = y0+newDeltaX;
					float _newDeltaY = newPosY - y0;
					outVecPt.push_back(ccp(newPosX,y0-_newDeltaY));
				}
			}			
		}
		// Note: 第二象限
		if (deltaX < 0 && deltaY > 0)
		{
			deltaX = -deltaX;
			xEnd = (x0) + deltaX;			

			// Note: 斜率=1
			if (deltaX == deltaY)
			{
				for (int posx = x0,posy = y0;posx <= xEnd,posy <= yEnd;posx++,posy++)
				{
					int newDeltaX = posx - x0;
					outVecPt.push_back(ccp(x0 - newDeltaX,posy));	
				}
			}
			// Note: 斜率<1
			else if (deltaX > deltaY)
			{
				int dx = deltaX ;
				int dy = deltaY ;
				int p = 2*dy - dx;
				int twoDy = 2 * dy;
				int twoByMinusDx = 2 * (dy - dx);
				int x,y;
				x = x0;
				y = y0;

				outVecPt.push_back(ccp(x,y));

				while(x < xEnd)
				{
					x ++;
					if (p < 0)
					{
						p += twoDy;
					}
					else
					{
						y++;
						p += twoByMinusDx;
					}
					int newDeltaX = x - x0;
					outVecPt.push_back(ccp(x0 - newDeltaX,y));
				}
			}
			// Note: 斜率>1
			else if (deltaX < deltaY)
			{
				int newEndPosX = x0 + (yEnd - y0);
				int newEndPosY = y0 + (xEnd - x0);

				int dx = newEndPosX - x0 ;
				int dy = newEndPosY - y0 ;
				int p = 2*dy - dx;
				int twoDy = 2 * dy;
				int twoByMinusDx = 2 * (dy - dx);
				int x,y;
				x = x0;
				y = y0;

				outVecPt.push_back(ccp(x,y));

				while(x < newEndPosX)
				{
					x ++;
					if (p < 0)
					{
						p += twoDy;
					}
					else
					{
						y++;
						p += twoByMinusDx;
					}
					int newDeltaX = x - x0;
					int newDeltaY = y - y0;
					int newPosX = x0+newDeltaY;
					int newPosY = y0+newDeltaX;
					float _newDeltaX = newPosX - x0;
					outVecPt.push_back(ccp(x0 - _newDeltaX,newPosY));
				}
			}			
		}
		// Note: 第三象限
		if (deltaX < 0 && deltaY < 0)
		{
			deltaX = -deltaX;
			deltaY = -deltaY;
			xEnd = x0 + deltaX;
			yEnd = y0 + deltaY;

			// Note: 斜率=1
			if (deltaX == deltaY)
			{
				for (int posx = x0,posy = y0;posx <= xEnd,posy <= yEnd;posx++,posy++)
				{
					float newDeltaX = posx - x0;
					float newDeltaY = posy - y0;
					outVecPt.push_back(ccp(x0 - newDeltaX,y0 - newDeltaY));	
				}
			}
			// Note: 斜率<1
			else if (deltaX > deltaY)
			{
				int dx = deltaX ;
				int dy = deltaY ;
				int p = 2*dy - dx;
				int twoDy = 2 * dy;
				int twoByMinusDx = 2 * (dy - dx);
				int x,y;
				x = x0;
				y = y0;

				outVecPt.push_back(ccp(x,y));

				while(x < xEnd)
				{
					x ++;
					if (p < 0)
					{
						p += twoDy;
					}
					else
					{
						y++;
						p += twoByMinusDx;
					}
					float newDeltaX = x - x0;
					float newDeltaY = y - y0;
					outVecPt.push_back(ccp(x0 - newDeltaX,y0 - newDeltaY));
				}
			}
			// Note: 斜率>1
			else if (deltaX < deltaY)
			{
				int newEndPosX = x0 + (yEnd - y0);
				int newEndPosY = y0 + (xEnd - x0);

				int dx = newEndPosX - x0 ;
				int dy = newEndPosY - y0 ;
				int p = 2*dy - dx;
				int twoDy = 2 * dy;
				int twoByMinusDx = 2 * (dy - dx);
				int x,y;
				x = x0;
				y = y0;

				outVecPt.push_back(ccp(x,y));

				while(x < newEndPosX)
				{
					x ++;
					if (p < 0)
					{
						p += twoDy;
					}
					else
					{
						y++;
						p += twoByMinusDx;
					}
					int newDeltaX = x - x0;
					int newDeltaY = y - y0;
					int newPosX = x0+newDeltaY;
					int newPosY = y0+newDeltaX;
					float _newDeltaX = newPosX - x0;
					float _newDeltaY = newPosY - y0;
					outVecPt.push_back(ccp(x0 - _newDeltaX,y0 - _newDeltaY));
				}
			}
		}
	}
}

void CommonUtils::ConvertWinCoordToOpenGL(CCPoint& pt)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	pt.y = size.height - pt.y;
}