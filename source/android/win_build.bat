@echo off


rem current path
set DIR=%cd%

cd ..
set COCOS2DX_ROOT=%cd%
set APP_ANDROID_ROOT=%DIR%
cd %DIR%
set COCOS2DX_ROOT=%COCOS2DX_ROOT:\=/% 
set COCOS2DX_ROOT=%COCOS2DX_ROOT: =%

set APP_ANDROID_ROOT=%APP_ANDROID_ROOT:\=/% 
echo %1
set build=%1%
if "%1"=="" set build=%NDK_HOME%/ndk-build.cmd
%build% -C %APP_ANDROID_ROOT%  NDK_DEBUG=1 -j2 
