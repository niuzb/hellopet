#pragma once

#include "Singleton_t.h"
#include <cocos2d.h>
#include <string>
#include <set>

extern "C" {
#	include "lua.h"
#	include "lualib.h"
#	include "lauxlib.h"
}
#include "Lua/lua_tinker.h"

struct lua_State;

using namespace std;
using namespace cocos2d;

class LuaTinkerManager : public TSingleton<LuaTinkerManager>
{
public:
	LuaTinkerManager();
	virtual ~LuaTinkerManager();

	//ͨ�õ��ýӿڣ���֧�ַ���ֵΪvoid
	template<typename RVal>
	RVal callLuaFunc(const char* filePath, const char* funcName)
	{
		if (strcmp(filePath, ""))
		{
			bool flag = this->checkAnyLoadFile(filePath);
			CCAssert(flag, "check lua file failed");
		}		

		return lua_tinker::call<RVal>(this->curLuaState, funcName);
	}

	template<typename RVal, typename T1>
	RVal callLuaFunc(const char* filePath, const char* funcName, T1 arg)
	{
		if (strcmp(filePath, ""))
		{
			bool flag = this->checkAnyLoadFile(filePath);
			CCAssert(flag, "check lua file failed");
		}		

		return lua_tinker::call<RVal>(this->curLuaState, funcName, arg);
	}

	template<typename RVal, typename T1, typename T2>
	RVal callLuaFunc(const char* filePath, const char* funcName, T1 arg1, T2 arg2)
	{

		if (strcmp(filePath, ""))
		{
			bool flag = this->checkAnyLoadFile(filePath);
			CCAssert(flag, "check lua file failed"); 
		}

		return lua_tinker::call<RVal>(this->curLuaState, funcName, arg1, arg2);
	}

	template<typename RVal, typename T1, typename T2, typename T3>
	RVal callLuaFunc(const char* filePath, const char* funcName, T1 arg1, T2 arg2, T3 arg3)
	{
		if (strcmp(filePath, ""))
		{
			bool flag = this->checkAnyLoadFile(filePath);
			CCAssert(flag, "check lua file failed"); 
		}

		return lua_tinker::call<RVal>(this->curLuaState, funcName, arg1, arg2, arg3);
	}

	//��ȡ����
	template<typename RVal, typename T1, typename T2>
	RVal getLuaConfig(string configFileName, const char * tableName, T1 idName, T2 typeName)
	{
		bool flag = this->checkAnyLoadFile("Script/GameConfig/" + configFileName + ".lua");
		CCAssert(flag, "check lua file failed");

		lua_tinker::table gTable = lua_tinker::get<lua_tinker::table>(this->curLuaState, tableName);
		lua_tinker::table inTable = gTable.get<lua_tinker::table>(idName);
		return inTable.get<RVal>(typeName);
	}

	bool checkAnyLoadFile(string filePath);
private:
	

private:
	lua_State *curLuaState;

	//�Ѿ����ص�lua�ļ�����
	set<string> loadedFiles;
};